#pragma once

#include <setjmp.h>
#include "stack.hpp"

// exception types
#define ERROR_1 1
#define ERROR_2 2
#define ERROR_3 3

#define MAX_DEPTH 20

jmp_buf MY_EVENT[MAX_DEPTH];

// last exception, -1 if no exception
int EXCEPTION_CODE = -1;

#define TRY(body) \
	int jmp_value = 0; \
	if (stack_manager.get_level() == MAX_DEPTH || EXCEPTION_CODE != -1) exit(1); \
	stack_manager.add_level(); \
	jmp_value = setjmp(MY_EVENT[stack_manager.get_level()]); \
	if (jmp_value == 0 && EXCEPTION_CODE == -1) { \
		body; \
	}

#define THROW(exception) \
	if (EXCEPTION_CODE != -1 || stack_manager.get_level() < 0) { \
        if (EXCEPTION_CODE != -1) std::cerr << "Exception appeared while stack unwinding" << std::endl; \
        if (stack_manager.get_level() < 0) std::cerr << "Unhandled exception: " << exception << std::endl; \
        std::cerr << "Aborting" << std::endl; \
        system("pause"); \
        exit(1); \
	} \
	EXCEPTION_CODE = exception; \
	longjmp(MY_EVENT[stack_manager.sub_level()], 1);

#define CATCH(exception_code, body) \
	else if (EXCEPTION_CODE == exception_code) { \
		EXCEPTION_CODE = -1; \
        body; \
	}