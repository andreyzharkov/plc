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
	
	// инициализирует _vtable функци€ми родител€
	LEARN_FROM_BASE(Derived, Base)
	// методы потомка
	DECLARE_METHOD(Derived, Both, std::cout << "Derived::Both" << std::endl;)
	DECLARE_METHOD(Derived, OnlyDerived, std::cout << "Derived::OnlyDerived" << std::endl;)

	Base base;

	base.a = 0;
	Derived derived;

	// полиморфизм
	Base* reallyDerived = reinterpret_cast<Base*>(&derived);
	// без того что ниже полиморфизм тоже сработает
	// но будут лишние функции
	// в частности не выполнитс€ последний ассерт
	auto it = (reallyDerived->vfuncs).begin();
	while (it != (reallyDerived->vfuncs).end()) {
		if ((reallyDerived->_vfuncs).find(it->first) == (reallyDerived->_vfuncs).end()) {
			auto toerase = it;
			++it;
			(reallyDerived->vfuncs).erase(toerase);
		} else {
			++it;
		}
	}
	for (auto it : reallyDerived->_vfuncs) {
		if ((reallyDerived->vfuncs).find(it.first) == (reallyDerived->vfuncs).end()) {
			(reallyDerived->vfuncs).insert(it);
		}
	}

	VIRTUAL_CALL((&base), Both); // печатает УBase::Both a = 0Ф
	VIRTUAL_CALL(reallyDerived, Both); // печатает УDerived::Both b = 1Ф
	VIRTUAL_CALL(reallyDerived, OnlyBase);  // печатает УBase::OnlyBaseФ
	VIRTUAL_CALL(reallyDerived, OnlyDerived); // assert
	return 0;
}