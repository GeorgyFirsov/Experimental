#pragma once

class CWindowHandler
{
	using WindowProc = LRESULT(HWND, UINT, WPARAM, LPARAM);

public:

	CWindowHandler(HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc = nullptr);

	~CWindowHandler() = default;

	CWindowHandler(const CWindowHandler&) = delete;
	CWindowHandler(CWindowHandler&&) = delete;

	CWindowHandler& operator=(const CWindowHandler&) = delete;
	CWindowHandler& operator=(CWindowHandler&&) = delete;

	INT DisplayWindow(INT iCmdShow) const;

private:
	
	WNDCLASS m_wndClass;
	HWND	 m_hWnd;

	void InitializeWndClass(HINSTANCE hInstance, const TCHAR* szAppName, WindowProc WndProc);
};