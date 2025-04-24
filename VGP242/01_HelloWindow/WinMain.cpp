#include<DaEngine/Inc/DaEngine.h>

class MainState : public DaEngine::AppState {
public:
	void Initialize()
	{
		LOG("MAIN STATE INITIALIZED");
		mLifeTime - 2.0f;
	}
	void Terminate()
	{
		LOG("MAIN STATE TERMINATED");
	}
	void Update(float deltaTime) override
	{
		mLifeTime -= std::max(deltaTime, 0.01f);
		if (mLifeTime <= 0.0f)
		{
			LOG("MAIN STATE QUIT");
			DaEngine::MainApp().ChangeState("GameState");
		}
	}
private:
	float mLifeTime = 0.0f;
};

class GameState : public DaEngine::AppState {
public:
	void Initialize() override
	{
		LOG("GAME STATE INITIALIZED");
		mLifeTime = 2.0f;
	}
	void Terminate() override
	{
		LOG("GAME STATE TERMINATED");
	}
	void Update(float deltaTime) override
	{
		mLifeTime -= std::max(deltaTime, 0.01f);
		if (mLifeTime <= 0.0f)
		{
			LOG("GAME STATE QUIT");
			DaEngine::MainApp().ChangeState("MainState");
		}
	}
private:
	float mLifeTime = 0.0f;
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
	DaEngine::AppConfig config;
	config.appName = L"HelloWindow";

	DaEngine::App& myApp = DaEngine::MainApp();
	myApp.AddState<MainState>("MainState");
	myApp.AddState<GameState>("GameState");
	myApp.Run(config);

	return 0;
}