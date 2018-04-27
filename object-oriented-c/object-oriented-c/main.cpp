#include "oop.h"

// ������� �����
VIRTUAL_CLASS(Base)
    int a;
END_DEFINITION(Base)

// �����-���������
VIRTUAL_CLASS_DERIVED(Derived, Base)
    int b;
END_DERIVED(Derived, Base)

int main(){
	// ������ �������� ������
	DECLARE_METHOD(Base, Both, std::cout << "Base::Both" << std::endl;)
	DECLARE_METHOD(Base, OnlyBase, std::cout << "Base::OnlyBase" << std::endl;)
	
	// �������������� _vtable ��������� ��������
	LEARN_FROM_BASE(Derived, Base)
	// ������ �������
	DECLARE_METHOD(Derived, Both, std::cout << "Derived::Both" << std::endl;)
	DECLARE_METHOD(Derived, OnlyDerived, std::cout << "Derived::OnlyDerived" << std::endl;)

	Base base;

	base.a = 0;
	Derived derived;

	// �����������
	Base* reallyDerived = reinterpret_cast<Base*>(&derived);
	// ��� ���� ��� ���� ����������� ���� ���������
	// �� ����� ������ �������
	// � ��������� �� ���������� ��������� ������
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

	VIRTUAL_CALL((&base), Both); // �������� �Base::Both a = 0�
	VIRTUAL_CALL(reallyDerived, Both); // �������� �Derived::Both b = 1�
	VIRTUAL_CALL(reallyDerived, OnlyBase);  // �������� �Base::OnlyBase�
	VIRTUAL_CALL(reallyDerived, OnlyDerived); // assert
	return 0;
}