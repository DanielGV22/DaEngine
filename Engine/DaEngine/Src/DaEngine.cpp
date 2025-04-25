#include "Precompiled.h"
#include "DaEngine.h"

DaEngine::App& DaEngine::MainApp()
{
	static App sApp;
	return sApp;
}