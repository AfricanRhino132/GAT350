#include "../Engine/Engine.h"

#include <iostream>


/*
	Copy basic.scene
	rename it to basic_lit.scn
	drag into visual studio
	change where we load in basic.scn to basic_lit.scn
	get the stuff from teams put it before the camera and after the ogre
	change the LightComponent ambient to 0.2, 0.2, 0.2 in basic_lit.scn
*/


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

	auto scene = std::make_unique<neu::Scene>();

	rapidjson::Document document;
	bool success = neu::json::Load("scenes/basic.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}

	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic.prog");
	program->Link();
	program->Use();

	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/ogre.mtrl");
	material->Bind();

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed) quit = true;

		scene->Update();
		
		neu::g_renderer.BeginFrame();

		scene->Draw(neu::g_renderer);

		neu::g_renderer.EndFrame();


	}
	scene->Clear();

	neu::Engine::Instance().Shutdown();

	return 0;
}