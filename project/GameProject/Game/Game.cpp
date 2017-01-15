#include "Game.hpp"

#include "../Core/Input/Input.hpp"

Game::Game() : player(nullptr), running(true), core(nullptr), timepass(0.0f), fps(0), gstate(GameState::eGameStage_MainMenu) {}

Game::~Game() {
	delete player;

	core->release();
}

void Game::init() {
	core = new Core();
	core->init();

	camInput.init(&cam.viewMatrix);

	player = new GameObject();
}

bool Game::isRunning() const {
	return running;
}

void Game::update(float dt) {
	core->update(dt);
	camInput.update(dt);
	tickFPS(dt);
	running = core->isRunning();

	// update gameStuffz
	if ( gstate == GameState::eGameState_PlayMode ) {

	}

	Input* in = Input::getInput();

	KeyBind kb;
	kb.code = 2;
	kb.mod = 0;
	kb.mouse = 0;

	if ( in->releasedThisFrame(kb) ) {
		std::cout << "1 Pressed\n";
		saveGame();
	}

	kb.code = 3;

	if ( in->releasedThisFrame(kb) ) {
		std::cout << "2 Pressed\n";
		loadGame();
	}

}

void Game::render() {
	core->render();
}

void Game::newGame() {}

void Game::saveGame() {
	std::cout << "Saving Game\n";

	core->getMemoryManager()->saveHeap();

}

void Game::loadGame() {
	std::cout << "Loading Game\n";

	core->getMemoryManager()->loadHeap();

}

void Game::tickFPS(float dt) {
	fps++;
	timepass += dt;

	if ( timepass > 1.0f ) {
		core->setFPS(fps);
		fps = 0;
		timepass -= 1.0f;
	}
}