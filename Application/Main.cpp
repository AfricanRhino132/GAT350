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


float vertices[] = { // pos color uv
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
						 				    
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
						 				    
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
						 				    
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
						 				    
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f,
						 
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

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

	std::shared_ptr<neu::VertexBuffer> vb = neu::g_resources.Get<neu::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	auto m = neu::g_resources.Get<neu::Model>("models/ogre.obj");

	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic.prog");
	program->Link();
	program->Use();

	
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/ogre.mtrl");
	material->Bind();

	material->GetProgram()->SetUniform("scale", 0.5f);
	//material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));

	
	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, (float)neu::g_renderer.getScreenWidth() / neu::g_renderer.getScreenHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 0, 2 };
	float cameraSpeed = 3;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed) quit = true;
		
		if (neu::g_inputSystem.GetKeyState(neu::key_a) == neu::InputSystem::State::Held)
		{
			cameraPosition.x -= cameraSpeed * neu::g_time.deltaTime;
		}

		if (neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::State::Held)
		{
			cameraPosition.y -= cameraSpeed * neu::g_time.deltaTime;
		}

		if (neu::g_inputSystem.GetKeyState(neu::key_d) == neu::InputSystem::State::Held)
		{
			cameraPosition.x += cameraSpeed * neu::g_time.deltaTime;
		}

		if (neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::State::Held)
		{
			cameraPosition.y += cameraSpeed * neu::g_time.deltaTime;
		}

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		
		model = glm::eulerAngleXYZ(0.0f, neu::g_time.time, 0.0f);

		glm::mat4 mvp = projection * view * model;
		material->GetProgram()->SetUniform("mvp", mvp);
		
		neu::g_renderer.BeginFrame();

		m->m_vertexBuffer.Draw();

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}