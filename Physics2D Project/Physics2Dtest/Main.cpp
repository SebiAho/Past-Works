#include <Box2D/Box2D.h>

#include <stdio.h>
#include<SFML\Graphics.hpp>

#include"PhysicsSystem.h"
#include"Program.h"

#include "GameObject.h"
#include "TransformComponent.h"

#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
	Program program;
	program.Loop();
	return 0;
}
