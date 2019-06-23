#include "pch.h"

/****************************************
 * It is necessary to include both
 * *.h and *.cpp files to make
 * tests work 
 ****************************************/
#include "..//Test/WindowHandler.h"
#include "..//Test/WindowHandler.cpp"
//***************************************/


TEST(Creation, nullptr_in_ctor)
{
	ASSERT_THROW(CWindowHandler(nullptr, TEXT("Test case")), std::runtime_error);
}