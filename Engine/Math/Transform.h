#pragma once
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace neu
{
	struct Transform : public ISerializable
	{
		glm::vec3 position{ 0 };
		glm::vec3 scale{ 1 };
		glm::quat rotation;

		glm::mat4 matrix{ 1 };

		Transform() = default;
		Transform(const glm::vec3& position, const glm::quat& rotation = glm::vec3{ 0 }, const glm::vec3& scale = { 1, 1, 1 }) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		glm::vec3 getRight() { return ((glm::mat4)(*this))[0]; }
		glm::vec3 getUp() { return ((glm::mat4)(*this))[1]; }
		glm::vec3 getForward() { return ((glm::mat4)(*this))[2]; }

		void Update()
		{
			matrix = *this;
		}

		void Update(const glm::mat4& parent)
		{
			matrix = parent * (glm::mat4)(*this);
		}

		operator glm::mat4 () const
		{
			glm::mat4 mxScale = glm::scale(scale);
			glm::mat4 mxRotate = glm::mat4_cast(rotation);
			glm::mat4 mxTranslate = glm::translate(position);

			return { mxTranslate * mxRotate * mxScale };
		}
	};
}