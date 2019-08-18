#include "stdafx.h"
#include "WindowHandler.h"

CWindowHandler::CWindowHandler()
{
	auto hInstance	    = GetModuleHandle(nullptr);
	auto szWndClassName = L"ApplicationDefault";
	auto WndProc	    = window_auxilary::DefaultWndProc;

	CreateMainWindow(hInstance, szWndClassName, WndProc);
}

CWindowHandler::CWindowHandler(HINSTANCE hInstance, const std::wstring& sWndClassName, WindowProc WndProc)
{
	if (!hInstance) {
		throw std::runtime_error("Invalid hInstance");
	}

	if (!WndProc) {
		WndProc = window_auxilary::DefaultWndProc;
	}

	CreateMainWindow(hInstance, sWndClassName.c_str(), WndProc);
}

INT CWindowHandler::DisplayWindow(INT iCmdShow) const
{
	ShowWindow(m_hWnd, iCmdShow);
	UpdateWindow(m_hWnd);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
 		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return static_cast<INT>(msg.wParam);
}

VOID CWindowHandler::CreateMainWindow(HINSTANCE hInstance, const wchar_t* szWndClassName, WindowProc WndProc)
{
	assert(szWndClassName);
	assert(WndProc);

	InitializeWndClass(&m_wndClass, hInstance, szWndClassName, WndProc);
	RegisterClass(&m_wndClass);

	m_hWnd = CreateWindow(szWndClassName, L"App window header", WS_OVERLAPPEDWINDOW
                              , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
                              , nullptr, nullptr, hInstance, nullptr);
}

VOID InitializeWndClass(PWNDCLASS pWndClass, HINSTANCE hInstance, const wchar_t* szAppName, window_auxilary::WindowProc WndProc)
{
	if (!pWndClass) {
		throw std::runtime_error(std::string(__FUNCTION__) + ": window class pointer is null");
	}

	if (!WndProc) {
		WndProc = window_auxilary::DefaultWndProc;
	}

	pWndClass->style	 = CS_HREDRAW | CS_VREDRAW;
	pWndClass->lpfnWndProc	 = WndProc;
	pWndClass->cbClsExtra	 = 0;
	pWndClass->cbWndExtra	 = 0;
	pWndClass->hInstance	 = hInstance;
	pWndClass->hCursor	 = LoadCursor(nullptr, IDC_ARROW);
	pWndClass->hIcon	 = LoadIcon(nullptr, IDI_APPLICATION);
	pWndClass->hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	pWndClass->lpszMenuName	 = nullptr;

	if (!szAppName) pWndClass->lpszClassName = L"ApplicationDefault";
	else		pWndClass->lpszClassName = szAppName;
}
