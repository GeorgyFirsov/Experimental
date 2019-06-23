#pragma once

class CWindowHandler
{
	using WindowProc = LRESULT(HWND, UINT, WPARAM, LPARAM);

public:

	CWindowHandler(HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc = WndProcDefault);

	INT DisplayWindow(INT iCmdShow) const;

private:
	
	WNDCLASS m_wndClass;
	HWND	 m_hWnd;

	static LRESULT CALLBACK WndProcDefault(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
};