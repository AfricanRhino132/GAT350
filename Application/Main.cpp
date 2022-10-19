#include "../Engine/Engine.h"

#include <iostream>

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

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	
	std::shared_ptr<neu::Program> program = neu::g_resources.Get<neu::Program>("Shaders/basic.prog");
	program->Link();
	program->Use();
	
	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Bind();

	material->GetProgram()->SetUniform("scale", 0.5f);
	//material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));
	
	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, (float)neu::g_renderer.getScreenWidth() / neu::g_renderer.getScreenHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 2, 2 };
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

		//model = glm::eulerAngleXYZ(0.0f, 0.0f, neu::g_time.time);
		
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		
		glm::mat4 mvp = projection * view * model;

		material->GetProgram()->SetUniform("mvp", mvp);

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}