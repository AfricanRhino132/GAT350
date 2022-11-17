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

	neu::g_gui.Initialize(neu::g_renderer);

	auto scene = neu::g_resources.Get<neu::Scene>("scenes/cubemap.scn");

	//auto actor = scene->GetActorFromName("Light");

	glm::vec3 rot = { 0, 0, 0 };
	float ri = 1;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();
		neu::g_gui.BeginFrame(neu::g_renderer);

		if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed) quit = true;

		//actor->m_transform.rotation.y += std::sin(90 * neu::g_time.deltaTime);

		auto actor = scene->GetActorFromName("Model");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}

		/*if (actor)
		{
			actor->m_transform.position = p;
		}*/

		auto program = neu::g_resources.Get<neu::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}

		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction Index", &ri, 0.01f, 1, 3);
		ImGui::End();

		scene->Update();
		
		neu::g_renderer.BeginFrame();

		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();


	}
	scene->Clear();

	neu::Engine::Instance().Shutdown();

	return 0;
}