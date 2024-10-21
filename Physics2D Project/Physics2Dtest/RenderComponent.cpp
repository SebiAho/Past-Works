#include "RenderComponent.h"


RenderComponent::RenderComponent() :Component(Comp::REND), state(sf::RenderStates())
{
}


RenderComponent::~RenderComponent()
{
}
