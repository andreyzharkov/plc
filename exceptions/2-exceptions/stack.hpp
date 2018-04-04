#pragma once

#include<iostream>
#include<stack>
#include<set>
#include<string>

//count objects with no explicit name passed to constructor
int n_existed_objects = 0;

class Object {
	//unique object id
	std::string object_id;
public:
	Object();
	Object(std::string obj_id);
	Object(const Object& obj);
	~Object();
};

class StackManager {
	int level = -1;
	std::stack<std::set<Object*>> objects;

	bool is_unwinding = false;
public:
	void add_object(Object* obj);
	void del_object(Object* obj);
	void add_level();
	int sub_level();
	int get_level() { return level; }
};

StackManager stack_manager;


Object::Object() :object_id(std::to_string(n_existed_objects++))
{
	stack_manager.add_object(this);
	std::cout << "initialized object " << object_id << std::endl;
}

Object::Object(std::string obj_id) : object_id(obj_id)
{
	stack_manager.add_object(this);
	std::cout << "initialized object " << object_id << std::endl;
}

Object::Object(const Object& obj)
{
	std::cout << "copied" << std::endl;
	object_id = "cp" + obj.object_id;
	stack_manager.add_object(this);
	std::cout << "initialized object " << object_id << std::endl;
}

Object::~Object()
{
	stack_manager.del_object(this);
	std::cout << "deinitialized object " << object_id << std::endl;
}


void StackManager::add_object(Object* obj)
{
	if (level >= 0) {
		objects.top().insert(obj);
	}
}

void StackManager::del_object(Object* obj)
{
	if (!is_unwinding && level >= 0 ) {
		objects.top().erase(obj);
	}
}

void StackManager::add_level()
{
	++level;
	objects.emplace();
}

int StackManager::sub_level()
{
	is_unwinding = true;
	for (auto obj : objects.top()) {
		std::cout << "forcefully delete:" << std::endl;
		obj->~Object();
	}
	is_unwinding = false;
	objects.pop();
	return level--;
}