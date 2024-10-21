#pragma once
#include "SystemEnums.h"
#include "System.h"
#include "GameObject.h"
#include <vector>

class SystemManager
{
public:
	SystemManager();
	~SystemManager();

	void Inititalize();//Calls the initialize functions in systems 
	void Update();//Calls the update functions in systems 
	void HandleMessages(sf::Event _event);

	int AddSubSystem(System* _system);//Add a new system to SubSystems array (returns systems location in vector)
	System* GetSystem(int _loc){ return SubSystems.at(_loc); };
	int RemoveSubSystem(int _loc);//Return -1 if succesfull

	int RegisterGameObject(GameObject& _object);//Register a GameObject to be used by the systems(Returns objects location in vector)
	int UnregisterGameObject(int _id);//Remove object from register (returns -1 if succesfull)
	void ToggleObject(int _id, bool _value);//Toggle GameObject on/off
	
	GameObject& getObject(int _id){ return objects.at(_id); };

private:
	std::vector<System*> SubSystems;
	std::vector<GameObject> objects;
};

