#include "Engine.h"

namespace neu
{
	InputSystem g_inputSystem;
	Renderer g_renderer;
	Time g_time;
	AudioSystem g_audioSystem;
	ResourceManager g_resources;
	PhysicsSystem g_physics;
	EventManager g_eventManager;
	GUI g_gui;

	void Engine::Register()
	{
		REGISTER_CLASS(Actor);
		REGISTER_CLASS(AudioComponent);
		REGISTER_CLASS(SpriteComponent);
		REGISTER_CLASS(ModelComponent);
		REGISTER_CLASS(PhysicsComponent);
		REGISTER_CLASS(RBPhysicsComponent);
		REGISTER_CLASS(CollisionComponent);
		REGISTER_CLASS(PlayerComponent);
		REGISTER_CLASS(SpriteAnimComponent);
		REGISTER_CLASS(TextComponent);
		REGISTER_CLASS(TilemapComponent);
		REGISTER_CLASS(CameraComponent);
		REGISTER_CLASS(LightComponent);
		REGISTER_CLASS(CameraController);
		
	}

	void Engine::Initialize()
	{
		g_renderer.Initialize();
		g_inputSystem.Initialize();
		g_audioSystem.Initialize();
		g_resources.Initialize();
		g_physics.Initialize();
		g_eventManager.Initialize();
	}

	void Engine::Update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			g_gui.Update(event);
		}
		g_time.Tick();
		g_eventManager.Update();
		g_physics.Update();
		g_inputSystem.Update();
		g_audioSystem.Update();


	}

	void Engine::Shutdown()
	{
		Factory::Instance().Shutdown();

		g_eventManager.Shutdown();
		g_physics.Shutdown();
		g_resources.Shutdown();
		g_inputSystem.Shutdown();
		g_audioSystem.Shutdown();
		g_gui.Shutdown();
		g_renderer.Shutdown();
	}
}