#include "oop.h"

// базовый класс
VIRTUAL_CLASS(Base)
    int a;
END_DEFINITION(Base)

// класс-наследник
VIRTUAL_CLASS_DERIVED(Derived, Base)
    int b;
END_DERIVED(Derived, Base)

int main(){
	// методы базового класса
	DECLARE_METHOD(Base, Both, std::cout << "Base::Both" << std::endl;)
	DECLARE_METHOD(Base, OnlyBase, std::cout << "Base::OnlyBase" << std::endl;)
	
	// инициализирует _vtable функциями родителя
	LEARN_FROM_BASE(Derived, Base)
	// методы потомка
	DECLARE_METHOD(Derived, Both, std::cout << "Derived::Both" << std::endl;)
	DECLARE_METHOD(Derived, OnlyDerived, std::cout << "Derived::OnlyDerived" << std::endl;)

	Base base;

	base.a = 0;
	Derived derived;

	// полиморфизм
	CAST(Base, &derived, reallyDerived);

	VIRTUAL_CALL((&derived), OnlyDerived); // "Devived::OnlyDerived"
	VIRTUAL_CALL((&base), Both); // печатает “Base::Both a = 0”
	VIRTUAL_CALL(reallyDerived, Both); // печатает “Derived::Both b = 1”
	VIRTUAL_CALL(reallyDerived, OnlyBase);  // печатает “Base::OnlyBase”
	VIRTUAL_CALL(reallyDerived, OnlyDerived); // assert
	return 0;
}