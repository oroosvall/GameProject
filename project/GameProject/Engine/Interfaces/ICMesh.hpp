#ifndef I_CMESH_HPP
#define I_CMESH_HPP

namespace Engine {
	namespace Interfaces {

		class ICAnimation;

		class ICMesh {
		public:

			virtual bool hasAnimations() = 0;
			virtual ICAnimation* getAnimData() = 0;

			virtual void bind() = 0;
			virtual void render() = 0;

		};
	}
}


#endif