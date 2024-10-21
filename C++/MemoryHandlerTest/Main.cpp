#include <iostream>

#include "MemLeakDetector.h"
#include "Test2.h"

#include <cassert>

using namespace std;


class aclass
{
private:
	int num;
	char mychar;
public:
	aclass(int num, char mychar) :num(num), mychar(mychar){}
	aclass(){ num = 0; mychar = 'a'; }
	void output(){ cout << num << " " << mychar << endl; }
};

void Del()
{
	Test2 test2;
	core::MemLeakDetector::getInstance();
	int *a = New int(100);
	aclass *b = New aclass(100, 'b');
	aclass *c = New aclass[2];

	bool astest = true;


	Delete a;
//	Delete b;
	Delete[] c;
}

int main()
{
	//core::MemLeakDetector detect;
	Del();
	core::MemLeakDetector::getInstance()->ShowLeaks();
	system("pause");
	
	return 0;
}