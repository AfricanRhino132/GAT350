#include "Renderer.h"
#include "Math/Transform.h"
#include "Texture.h"
#include "Math/Rect.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

namespace neu
{
	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);

		SDL_Surface* surface = IMG_Load("Sprites/cursor1.png");
		SDL_Cursor* cursor = SDL_CreateColorCursor(surface, 0, 0);
		SDL_SetCursor(cursor);
	}

	void Renderer::Shutdown()
	{
		SDL_GL_DeleteContext(m_context);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		IMG_Quit();
	}

	void Renderer::CreateWindow(const char* name, int width, int height, bool fullscreen)
	{
		m_width = width;
		m_height = height;

		int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_OPENGL
			| flags);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);

		m_context = SDL_GL_CreateContext(m_window);
		gladLoadGL();

		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	void Renderer::BeginFrame()
	{
		glClearColor(clear_color.r, clear_color.g, clear_color.b, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::EndFrame()
	{
		SDL_GL_SwapWindow(m_window);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawPoint(float x1, float y1)
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderDrawPointF(m_renderer, x1, y1);
	}

	void Renderer::DrawPoint(const Vector2& v, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(m_renderer, v.x, v.y);
	}

	void Renderer::DrawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(m_renderer, v1.x, v1.y, v2.x, v2.y);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& registration)
	{
		//Vector2 size = texture->GetSize();

		//size *= scale;

		//Vector2 origin = (size * registration);

		//Vector2 tposition = position - origin;

		//SDL_Rect dest;
		//// !! make sure to cast to int to prevent compiler warnings 
		//dest.x = (int)tposition.x;// !! set to position x 
		//dest.y = (int)tposition.y;// !! set to position y 
		//dest.w = (int)size.x;// !! set to size x 
		//dest.h = (int)size.y;// !! set to size y 

		//SDL_Point center{ (int)origin.x, (int)origin.y};

		//SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& registration)
	{
		//Vector2 size = texture->GetSize();

		//size *= transform.scale;

		//Vector2 origin = (size * registration);

		//Vector2 tposition = transform.position - origin;

		//SDL_Rect dest;
		//
		//dest.x = (int)tposition.x;// !! set to position x 
		//dest.y = (int)tposition.y;// !! set to position y 
		//dest.w = (int)size.x;// !! set to size x 
		//dest.h = (int)size.y;// !! set to size y 

		//SDL_Point center{ (int)origin.x, (int)origin.y };

		//SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, transform.rotation, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& registration, bool flipH)
	{
		//Matrix3x3 mx = m_viewport * m_view * transform.matrix;

		//Vector2 size = Vector2{ source.w, source.h};

		//size *= mx.GetScale();

		//Vector2 origin = (size * registration);

		//Vector2 tposition = mx.GetTranslation() - origin;

		//SDL_Rect dest;
		//// !! make sure to cast to int to prevent compiler warnings 
		//dest.x = (int)tposition.x;// !! set to position x 
		//dest.y = (int)tposition.y;// !! set to position y 
		//dest.w = (int)size.x;// !! set to size x 
		//dest.h = (int)size.y;// !! set to size y 

		//SDL_Point center{ (int)origin.x, (int)origin.y };

		//SDL_Rect src{ source.x, source.y, source.w, source.h };

		//SDL_RenderCopyEx(m_renderer, texture->m_texture, &src, &dest, math::RadToDeg(mx.GetRotation()), &center, (SDL_RendererFlip)flipH);
	}
}