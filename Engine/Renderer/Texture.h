#pragma once 
#include "Math/Vector2.h" 
#include "Resource/Resource.h"
#include "Renderer.h"

#include <string> 

// !! forward declaration for SDL pointers below (SDL likes to use structs) 
struct SDL_Texture;
struct SDL_Surface;

// !! add namespace 
namespace neu{
// !! forward declaration for Renderer below 
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string name, ...) override;
		bool Create(Renderer& renderer, const std::string& filename);
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);
		
		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		// !! allow Renderer to access private texture data (friend) 
		friend class Renderer;

	private:
		GLuint m_texture = 0;
		GLenum m_target = GL_TEXTURE_2D;
		GLuint m_unit = GL_TEXTURE0;
		//SDL_Texture* m_texture = nullptr;
	};
}