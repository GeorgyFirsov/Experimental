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

	void InitializeWndClass(PWNDCLASS pWndClass, const HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc)
	{
		assert(pWndClass != nullptr);
		assert(WndProc != nullptr);

		pWndClass->style = CS_HREDRAW | CS_VREDRAW;
		pWndClass->lpfnWndProc = WndProc;
		pWndClass->cbClsExtra = 0;
		pWndClass->cbWndExtra = 0;
		pWndClass->hInstance = hInstance;
		pWndClass->hIcon = LoadIcon(nullptr, IDI_APPLICATION);
		pWndClass->hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		pWndClass->lpszMenuName = nullptr;
		pWndClass->lpszClassName = szAppName;
	}

} // window_handler_auxilary

CWindowHandler::CWindowHandler(const HINSTANCE hInstance, const TCHAR* szAppName, window_handler_auxilary::WindowProc WndProc)
{
	if(!hInstance) {
		throw std::runtime_error("Invalid hInstance");
	}

	if(!WndProc) {
		WndProc = window_handler_auxilary::WndProcDefault;
	}

	window_handler_auxilary::InitializeWndClass(&m_wndClass, hInstance, szAppName, WndProc);

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
