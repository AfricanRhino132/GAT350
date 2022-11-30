#include "../Engine/Engine.h"

#include <iostream>

#define POST_PROCESS 


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

	// create framebuffer texture
	auto texture = std::make_shared<neu::Texture>();
	texture->CreateTexture(1024, 1024);
	neu::g_resources.Add<neu::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = neu::g_resources.Get<neu::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	auto scene = neu::g_resources.Get<neu::Scene>("scenes/rtt.scn");

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

		{
			auto actor = scene->GetActorFromName("rtt");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		scene->Update();

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		auto prog = neu::g_resources.Get<neu::Program>("shaders/postprocess/postprocess.prog");
		if (prog)
		{
			prog->Use();
			prog->SetUniform("offset", neu::g_time.time);
		}

		// render pass 1 (render scene to framebuffer) 
		neu::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		neu::g_renderer.RestoreViewport();
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(neu::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 

		neu::g_gui.Draw();

		neu::g_renderer.EndFrame();
		neu::g_gui.EndFrame();


	}
	scene->Clear();

	neu::Engine::Instance().Shutdown();

	return 0;
}