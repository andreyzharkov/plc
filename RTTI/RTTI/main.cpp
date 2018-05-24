#include <iostream>
#include "TypeInfo.h"
#include <typeinfo>
#include <string>

struct Base {
	virtual void printType() { 
		std::cout << "Base" << std::endl;
	}
	void printCurrentType()
	{
		std::cout << "Base" << std::endl;
	}
	int k;
};

struct EXTENDS(DerivedA, Base)
	virtual void printType()
	{
		std::cout << "DerivedA" << std::endl;
	}
	void printCurrentType()
	{
		std::cout << "DerivedA" << std::endl;
	}
	int d = 20;
	int e = 100;
	int c = 10;
};

struct EXTENDS(DerivedB, Base)
	virtual void printType()
	{
		std::cout << "DerivedB" << std::endl;
	}
	void printCurrentType()
	{
		std::cout << "DerivedB" << std::endl;
	}
	int e = 115;
    int a;
    int b;
};

struct EXTENDS(DerivedBB, DerivedB)
	virtual void printType()
	{
		std::cout << "DerivedBB" << std::endl;
	}
	void printCurrentType()
	{
		std::cout << "DerivedBB" << std::endl;
	}
	int z;
};


struct MEXTENDS(Derived, DerivedA, DerivedB)
	virtual void printType()
	{
		std::cout << "Derived" << std::endl;
	}
	void printCurrentType()
	{
		std::cout << "Derived" << std::endl;
	}
	int a;
    int b;
};

class AAA {
};

int main()
{
	DerivedB *d = NEW(DerivedB, Derived, d);

	DYNAMIC_CAST(DerivedB, DerivedA, d)->printType(); // Derived (function is virtual)
	DYNAMIC_CAST(DerivedB, DerivedA, d)->printCurrentType(); // DerivedA
	
	Base *a = NEW(Base, DerivedB, a);
	Base *b = NEW(Base, Base, b);
	Base *c = NEW(Base, DerivedBB, c);

	// a
	std::cout << "real type of a: " << TYPEID(a).name << std::endl;
	std::cout << "dynamic_cast<Base*>(a):" << std::endl;
	Base* p1 = DYNAMIC_CAST(Base, Base, a);
	p1->printType(); // DerivedB (function is virtual)
	p1->printCurrentType(); // Base
	std::cout << std::endl;

	std::cout << "dynamic_cast<DerivedB*>(a):" << std::endl;
	DerivedB* p2 = DYNAMIC_CAST(Base, DerivedB, a);
	p2->printType(); // DerivedB (function is virtual)
	p2->printCurrentType(); // DerivedB
	std::cout << std::endl;

	// b
	std::cout << "dynamic_cast<Base*>(b):" << std::endl;
	Base* p3 = DYNAMIC_CAST(Base, Base, b);
	p3->printType(); // Base (function is virtual)
	p3->printCurrentType(); // Base
	std::cout << std::endl;

	// c
	std::cout << "dynamic_cast<DerivedB*>(c):" << std::endl;
	DYNAMIC_CAST(Base, DerivedB, c)->printType(); // DerivedBB (function is virtual)
	DYNAMIC_CAST(Base, DerivedB, c)->printCurrentType(); // DerivedB
	std::cout << std::endl;

	// d
	std::cout << "dynamic_cast<DerivedB>(d):" << std::endl;
	std::cout << TYPEID(d).name << std::endl;
	DYNAMIC_CAST(DerivedB, Derived, d)->printType(); // Derived (function is virtual)
	DYNAMIC_CAST(DerivedB, Derived, d)->printCurrentType(); // Derived
	std::cout << std::endl;
	
	// static after dynamic
	Derived* dd = DYNAMIC_CAST(DerivedB, Derived, d);
	static_cast<DerivedA*>(dd)->printType();
	static_cast<DerivedA*>(dd)->printCurrentType();

	// nullptr
	AAA* n1 = DYNAMIC_CAST(DerivedB, AAA, d);
	std::cout << n1;
	
	return 0;
}