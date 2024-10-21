#pragma once

#include "SystemEnums.h"
#include <GameObject.h>
#include <vector>
#include <SFML\Window\Event.hpp>

class System
{
public:
	System(Sys _id);
	virtual ~System();

	virtual void Initialize(); 

	virtual void Update(GameObject& _object);

	virtual void HandleMessages(sf::Event& _event);

	void resetUse(){ use = true; };

	Sys getId(){ return id; };
	

protected:
	bool use;//Allows update to call some function only once each program loop

private:
	Sys id;
	
};