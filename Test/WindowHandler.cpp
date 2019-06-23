#include "stdafx.h"
#include "WindowHandler.h"

namespace window_handler_auxilary
{
	LRESULT CALLBACK WndProcDefault(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
	{
		HDC hdc;

		switch (uMessage)
		{
		case WM_CREATE:

			PlaySound(TEXT("hellowin.wav"), nullptr, SND_FILENAME | SND_ASYNC);
			return 0;

		case WM_PAINT:

			PAINTSTRUCT paintStruct;
			RECT rect;
			hdc = BeginPaint(hWnd, &paintStruct);
			GetClientRect(hWnd, &rect);
			DrawText(hdc, TEXT("Hello Windows"), -1, &rect
				, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hWnd, &paintStruct);
			return 0;

		case WM_DESTROY:

			PostQuitMessage(0);
			return 0;

		default:

			return DefWindowProc(hWnd, uMessage, wParam, lParam);
		}
	}
}

CWindowHandler::CWindowHandler(HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc)
{
	if(!WndProc) {
		WndProc = window_handler_auxilary::WndProcDefault;
	}

	m_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	m_wndClass.lpfnWndProc   = WndProc;
	m_wndClass.cbClsExtra    = 0;
	m_wndClass.cbWndExtra    = 0;
	m_wndClass.hInstance     = hInstance;
	m_wndClass.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
	m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	m_wndClass.lpszMenuName  = nullptr;
	m_wndClass.lpszClassName = szAppName;

	if (!RegisterClass(&m_wndClass)) {
		throw std::runtime_error("Can not initialize Window Class");
	}

	m_hWnd = CreateWindow(szAppName, TEXT("App window header"), WS_OVERLAPPEDWINDOW
                          , CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
                          , nullptr, nullptr, hInstance, nullptr);
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