#include "../Engine/Engine.h"

#include <iostream>

float points[] = {
	-1.0f, 1.0f,  0.0f,
   1.0f,  1.0f,  0.0f,
   1.0f, -1.0f,  0.0f,

	-1.0f, -1.0f,  0.0f,
   -1.0f,  1.0f,  0.0f,
   1.0f, -1.0f,  0.0f,

};

glm::vec3 colors[] = {
	{ 0, 1, 1 },
	{ 1, 1, 0 },
	{ 1, 0, 0 },
	{ 0, 0, 1 },
	{ 1, 0, 1 },
	{ 0, 1, 0 }
};

glm::vec2 texcoords[] = {
	{ 0, 0 },
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ 0, 0 },
	{ 1, 1 },	
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

	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	std::shared_ptr<neu::Shader> vs = neu::g_resources.Get<neu::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<neu::Shader> fs = neu::g_resources.Get<neu::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vs->m_shader);
	glAttachShader(program, fs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("Textures/llama.jpg");
	std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("Textures/wood.png");
	texture1->Bind();

	GLint uniform1 = glGetUniformLocation(program, "transform");
	GLint uniform2 = glGetUniformLocation(program, "tint");

	glUniform3f(uniform2, 1, 1, 1);

	glm::mat4 mx{ 1 };
	//mx = glm::scale(glm::vec3{ 0.5, 0.5, 0.5 });

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_esc) == neu::InputSystem::State::Pressed) quit = true;

		//mx = glm::eulerAngleXYZ(0.0f, 0.0f, neu::g_time.time * 200);
		glUniformMatrix4fv(uniform1, 1, GL_FALSE, glm::value_ptr(mx));

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();

	return 0;
}