#include "TransformComponent.h"


using namespace seb;
TransformComponent::TransformComponent() :Component(COMP::TRANSFORM), position(glm::vec2(0.0f,0.0f))
{

}


TransformComponent::~TransformComponent()
{
}
