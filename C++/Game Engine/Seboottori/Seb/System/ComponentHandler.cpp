#include "ComponentHandler.h"

using namespace seb;

ComponentHandler::ComponentHandler() :inUse(true)
{
}


ComponentHandler::~ComponentHandler()
{
}

int ComponentHandler::RemoveComponent(ObjectID _objectId)
{
	return -1;
}

void ComponentHandler::ClearAll()
{

}

std::vector<Component*>::iterator ComponentHandler::getComponentsBegin()
{
	return component_array.begin();
}

std::vector<Component*>::iterator ComponentHandler::getComponentsEnd()
{
	return component_array.end();
}
