#pragma once

#include "Serialization/Json.h"
#include "Renderer/Model.h"
#include "Renderer/GUI.h"

#include "Physics/PhysicsSystem.h"

#include "Core/Memory.h"
#include "Core/File.h"
#include "Core/Time.h"
#include "Core/Logger.h"

#include "Math/MathUtils.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
 
#include "FrameWork/Scene.h"
#include "FrameWork/Game.h"
#include "FrameWork/Singleton.h"
#include "FrameWork/Factory.h"
#include "FrameWork/EventManager.h"

#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Renderer/Program.h"
#include "Renderer/Material.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/CubemapTexture.h"
#include "Renderer/Framebuffer.h"

#include "Input/InputSystem.h"

#include "Resource/ResourceManager.h"

#include "Audio/AudioSystem.h"

#include "Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/PhysicsComponent.h"
#include "Components/RBPhysicsComponent.h"
#include "Components/ModelComponent.h"
#include "Components/SpriteAnimComponent.h"
#include "Components/TextComponent.h"
#include "Components/TilemapComponent.h"
#include "Components/CharacterComponent.h"
#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Components/CameraController.h"

#include <memory>

namespace neu
{
	extern InputSystem g_inputSystem;
	extern Renderer g_renderer;
	extern Time g_time;
	extern AudioSystem g_audioSystem;
	extern ResourceManager g_resources;
	extern PhysicsSystem g_physics;
	extern EventManager g_eventManager;
	extern GUI g_gui;

	class Engine : public Singleton<Engine>
	{
	public:
		void Register();

		void Initialize();

		void Update();

		void Shutdown();
	};
}
