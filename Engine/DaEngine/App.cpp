#include "Precompiled.h"
#include "App.h"
#include "AppState.h"

using namespace DaEngine;
using namespace DaEngine::Core;

void App::Run(const AppConfig& config)
{
	LOG("App Started");

	// Initialize everything
	Window myWindow;
	myWindow.Initialize(
		GetModuleHandle(nullptr),
		config.appName,
		config.winWidth,
		config.winHeight
	);

	// Last step before running
	ASSERT(mCurrentState != nullptr, "App: need an app state to run.");
	mCurrentState->Initialize();
	// Process updates
	mRunning = true;
	while (mRunning)
	{
		myWindow.ProcessMessage();
		if (!myWindow.IsActive())
		{
			Quit();
			continue;
		}

		if (mNextState != nullptr)
		{
			mCurrentState->Terminate();
			mCurrentState = std::exchange(mNextState, nullptr);
			mCurrentState->Initialize();
			mNextState = nullptr;
		}

		float deltaTime = TimeUtil::GetDeltaTime();
#if defined(_DEBUG)
		if (deltaTime < 0.5f) // For handling breakpoints
#endif
		{
			mCurrentState->Update(deltaTime);
		}
	}

	// Terminate everything
	LOG("App Quit");
	mCurrentState->Terminate();
	myWindow.Terminate();
}

void DaEngine::App::Quit()
{
	mRunning = false;
}

void DaEngine::App::ChangeState(const std::string& stateName)
{
	auto iter = mAppStates.find(stateName);
	if (iter != mAppStates.end())
	{
		mNextState = iter->second.get();
	}
	else
	{
		LOG("App: State %s not found", stateName.c_str());
	}
}
