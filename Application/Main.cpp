#include "../Engine/Engine.h"

#include <iostream>

int main(int argc, char** argv)
{
	LOG("Application Started...");

	neu::InitializeMemory();

	neu::SetFilePath("../Assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();

	LOG("Engine Initialized...");

	neu::g_renderer.CreateWindow("Neumont", 800, 600, false);

	LOG("Window Initialized...");

	auto scene = neu::g_resources.Get<neu::Scene>("scenes/basicLit.scn");

	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic_phong.prog");
	program->Link();
	program->Use();

	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("Materials/ogre.mtrl");
	material->Bind();
		
	auto actor = scene->GetActorFromName("Ogre");

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed) quit = true;

		actor->m_transform.rotation.y += std::sin(90 * neu::g_time.deltaTime);

		scene->Update();
		
		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();


	}
	scene->Clear();

	neu::Engine::Instance().Shutdown();

	return 0;
}