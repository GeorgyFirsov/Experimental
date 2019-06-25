#include "pch.h"

/*****************************************
 * It is necessary to include both
 * *.h and *.cpp files to make
 * tests work 
 ****************************************/
#include "..//Test/WindowHandler.h"
#include "..//Test/WindowHandler.cpp"
//***************************************/

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM)
{
	return 0;
}

TEST(Creation, nullptr_in_ctor)
{
	ASSERT_THROW(CWindowHandler(nullptr, L"AppException"), std::runtime_error);
}

TEST(Creation, valid_instance_in_ctor)
{
	ASSERT_NO_THROW(CWindowHandler(GetModuleHandle(nullptr), L"AppValid"));
}

TEST(Creation, custom_window_procedure)
{
	ASSERT_NO_THROW(CWindowHandler(GetModuleHandle(nullptr), L"AppValid", WndProc));
}

TEST(Creation, default_constructor)
{
	ASSERT_NO_THROW(CWindowHandler());
}