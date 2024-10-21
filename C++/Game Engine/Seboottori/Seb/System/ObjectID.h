#pragma once
namespace seb
{
	struct ObjectID
	{
		int index;
		unsigned int revision;//Used to check if object index is valid (i.e. not not removed)
	};
}