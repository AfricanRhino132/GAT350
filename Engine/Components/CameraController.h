#pragma once 
#include "Framework/Component.h" 

namespace neu
{
	class CameraController : public Component
	{
	public:
		CLASS_DECLARATION(CameraController)

		void Initialize() override;
			
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		float speed = 0;
		float sensitivity = 0.5f;
	private:
		float m_yaw = 0; //lr
		float m_pitch = 0; //ud
	};
}