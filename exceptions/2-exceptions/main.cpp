#include "handler.hpp"
#include "stack.hpp"
#include <iostream>


void f1(Object obj)
{
	THROW(ERROR_2);
}

void f2()
{
	Object obj_f2("f2_local");
	f1(obj_f2);
}

int main()
{
	//{
	//	Object o;
	//	(&o)->~Object();
	//}
	//return 0;
	/*TRY(
		std::cout << "throwing " << ERROR_1 << std::endl;
	    THROW(ERROR_1);
	) CATCH(ERROR_1,
		std::cout << "caught " << ERROR_1 << std::endl;
	)

	TRY(
		Object o0;
		std::cout << "throwing " << ERROR_3 << std::endl;
	    THROW(ERROR_3);
	) CATCH(ERROR_1,
		std::cout << "caught " << ERROR_1 << std::endl;
	) CATCH(ERROR_2,
		std::cout << "caught " << ERROR_2 << std::endl;
	) CATCH(ERROR_3,
		std::cout << "caught " << ERROR_3 << std::endl;
	)
	return 0;*/
	//Object o00;
 //   THROW(ERROR_1);

	/*TRY(
		Object o0;
	    Object o1;
	    Object o2;
		{
			Object o3; Object o4;
		}
		Object o5;
	)*/

	/*TRY(
		Object o0;
		TRY(
			Object o1;
		    THROW(ERROR_1)
		) CATCH(ERROR_1, 
			std::cout << "caught " << ERROR_1 << std::endl;
		)
	    Object o2;
		{
			Object o3; Object o4;
		}
	    Object o5;
	)*/

	TRY(
		/*Object o0;
		TRY(
			Object o1;
		    THROW(ERROR_1)
		) CATCH(ERROR_1,
			std::cout << "caught " << ERROR_1 << std::endl;
		)*/
		Object o2;
		{
			Object o3; Object o4; f2();
		}
		Object o5;
	) CATCH(ERROR_1, 
		std::cout << "caught " << ERROR_1 << std::endl
	) CATCH(ERROR_2,
		std::cout << "caught " << ERROR_1 << std::endl
	)
	return 0;
}