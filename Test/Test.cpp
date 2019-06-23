#include "stdafx.h"
#include "WindowHandler.h"

constexpr auto szAppName = TEXT("First application");

INT APIENTRY _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance
					   , _In_ LPTSTR lpCmdLine, _In_ INT iCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	const CWindowHandler window = { hInstance, szAppName };

	return window.DisplayWindow(iCmdShow);
}