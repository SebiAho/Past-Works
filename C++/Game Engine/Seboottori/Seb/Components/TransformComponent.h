#pragma once
#include "../System/Component.h"
#include "../3rd_party/GLM/vec2.hpp"
namespace seb
{
	class TransformComponent: public Component
	{
	public:
		TransformComponent();
		~TransformComponent();

		glm::vec2 position;
	};
}

