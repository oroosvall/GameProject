#ifndef CORE_HPP
#define CORE_HPP

// project includes
#include "RenderEngine\IRenderEngine.hpp"
#include "Input\Input.hpp"
#include "ThreadManager.hpp"
#include "Assets\AssetManager.hpp"
#include "Settings\DisplaySettings.hpp"
#include "..\Loader\LibraryLoader.hpp"

#include "Memory\MemoryManager.hpp"

class Core
{
public:

	void init();
	void release();

	bool isRunning();
	bool hadGraphicsReset() const;

	void startWorkerThreads();
	void stopWorkerThreads();

	void setFPS(int fps);
	void update(float dt);

	void render();

	DisplaySettings* getDisplaySettings();

	MemoryManager* getMemoryManager();

private:

	// core variables
	Lib renderEngineLib;
	MemoryManager mem;

	bool hadReset;
	bool running;
	int fps;

	IWindow* window;
	Console* console;

	IRenderEngine* renderEngine;
	Input* input;

	DisplaySettings disp;

	ThreadManager* thrdMgr;
	AssetManager* assetMgr;
};

#endif