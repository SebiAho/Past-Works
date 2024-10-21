#pragma once
#include "../Components/GraphicsComponent.h"
#include "../Components/TransformComponent.h"
#include "../System/Object.h"

namespace seb
{
	template<typename comp_type> class CompCast//Template class for casting components
	{
	public:
		CompCast(){};
		~CompCast(){};

		//Cast from Component
		comp_type* operator()(Component* _comp)
		{
			return static_cast<comp_type*>(_comp);
		};

		//Cast from Component contained in object
		comp_type* operator()(Object* _object, COMP _comp)
		{
			return static_cast<comp_type*>(_object->getComponent(_comp));
		};
	};
}
