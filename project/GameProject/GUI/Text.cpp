#include "Text.hpp"

#include <glm\gtc\matrix_transform.hpp>

void Text::init(IRenderEngine* re) {

	mesh = re->createMesh();
	mesh->init(MeshPrimitiveType::TRIANGLE);

}

void Text::release() {
	mesh->release();

	delete this;
}

void Text::setText(char * text, size_t length, float x, float y, float scale) {

	const size_t floatsPerVertex = 5; // 5 elements per vertex
	const size_t nrVertices = 6; // 3 verts per triangle = 6 verts

	const size_t nrVerexFloats = nrVertices * floatsPerVertex; // number of floats per character
	const size_t bytesPerCharacter = sizeof(float) * nrVerexFloats;

	size_t arraySize = nrVerexFloats * length;

	float* verts = new float[arraySize];

	float dx = x;
	float dy = y;

	float yAdv = 0;
	float oldYAdv = 0;

	int fSize = font->getFontSize();

	for ( size_t i = 0; i < length; i++ ) {

		Character ch = font->getCharacter(text[i]);

		if ( i == 0 )
			y += fSize;

		if ( text[i] == '\n' ) {
			if ( yAdv ) {
				y += (fSize * 2);
				oldYAdv = (float)fSize;
			} else {
				y += oldYAdv;
			}
			yAdv = 0;
			x = dx;
			memset(&verts[i * nrVerexFloats], 0, bytesPerCharacter);
			continue;
		} else if ( text[i] == '\t' ) {
			x += (ch.size.x * scale * 2.0f);
			memset(&verts[i * nrVerexFloats], 0, bytesPerCharacter);
			continue;
		} else if ( text[i] == '\0' ) {
			memset(&verts[i * nrVerexFloats], 0, bytesPerCharacter);
			continue;
		}

		float xpos = x + ch.bearing.x * scale;
		float ypos = y + ((ch.size.y - ch.bearing.y) * scale);

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		yAdv = glm::max(yAdv, h);

		int texWidth;
		int texHeight;

		font->getTextureInfo(texWidth, texHeight);

		// Update VBO for each character
		float texX1 = (float)ch.texturePos.x / (float)texWidth;
		float texY1 = (float)ch.texturePos.y / (float)texHeight;

		float texX2 = (float)(ch.texturePos.x + ch.size.x) / (float)texWidth;
		float texY2 = (float)(ch.texturePos.y + ch.size.y) / (float)texHeight;

		float vertices[6][5] = {
			{ xpos,     ypos - h, 0,   texX1, texY1 },
			{ xpos,     ypos, 0,       texX1, texY2 },
			{ xpos + w, ypos, 0,       texX2, texY2 },

			{ xpos,     ypos - h, 0,   texX1, texY1 },
			{ xpos + w, ypos, 0,       texX2, texY2 },
			{ xpos + w, ypos - h, 0,   texX2, texY1 }
		};

		memcpy(&verts[i * nrVerexFloats], vertices, sizeof(vertices));
		
		x += (ch.advance >> 6) * scale;

		assert(sizeof(vertices) == bytesPerCharacter);
		assert(i*nrVerexFloats < nrVerexFloats*length);

	}

	mesh->setMeshData(verts, arraySize * sizeof(float), MeshDataLayout::VERT_UV);

	delete[] verts;

}

void Text::setFont(IFont * fnt) {
	font = fnt;
}

void Text::render(IShaderObject* shader, uint32_t textureLocation) {

	uint32_t texture = 0;
	font->bindFontTexture();
	shader->bindData(textureLocation, UniformDataType::UNI_INT, &texture);

	mesh->bind();
	mesh->render();

}