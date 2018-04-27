#pragma once

#include <iostream>
#include <map>
#include <string>
#include <cassert>

#define VIRTUAL_CLASS(Base) struct Base { \
    static std::map<std::string, void (*)()> _vfuncs; \
    std::map<std::string, void(*)()> vfuncs; \
	Base() : vfuncs(_vfuncs) {}

#define END_DEFINITION(Base) \
    }; \
    std::map<std::string, void(*)()> Base::_vfuncs = std::map<std::string, void(*)()>();

#define DECLARE_METHOD(Base, method_name, body) \
    Base::_vfuncs[std::string(#method_name)] = []()->void{body};

#define VIRTUAL_CLASS_DERIVED(Derived, Base) struct Derived { \
    static std::map<std::string, void (*)()> _vfuncs; \
    std::map<std::string, void(*)()> vfuncs; \
    Derived() : vfuncs(_vfuncs) {}

#define END_DERIVED(Derived, Base) \
    }; \
    std::map<std::string, void(*)()> Derived::_vfuncs = Base::_vfuncs;

#define LEARN_FROM_BASE(Derived, Base) \
    Derived::_vfuncs = Base::_vfuncs;

#define VIRTUAL_CALL(instance_ptr, method_name) \
    assert ((instance_ptr->vfuncs).find(std::string(#method_name)) != (instance_ptr->vfuncs).end()), \
    (instance_ptr->vfuncs)[#method_name]();
