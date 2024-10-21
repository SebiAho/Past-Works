#include "Test2.h"
#include "MemLeakDetector.h"

Test2::Test2()
{
	core::MemLeakDetector::getInstance();
	as =  New int(100);
	//Delete as;
}


Test2::~Test2()
{
	Delete as;
}
