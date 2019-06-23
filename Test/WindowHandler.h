#pragma once

class CWindowHandler
{
	using WindowProc = LRESULT(HWND, UINT, WPARAM, LPARAM);

public:

	CWindowHandler(HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc = nullptr);

	~CWindowHandler() = default;

	INT DisplayWindow(INT iCmdShow) const;

private:
	
	WNDCLASS m_wndClass;
	HWND	 m_hWnd;
};