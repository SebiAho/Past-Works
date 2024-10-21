#include "Object_base.h"


Object_base::Object_base(void)
{
}


Object_base::~Object_base(void)
{
}

void Object_base::Update()
{
}

void Object_base::Draw(Draw_handler& _draw)
{
	_draw.Rectangle(pos,text);
}