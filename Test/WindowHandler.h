#pragma once

namespace window_handler_auxilary
{
	using WindowProc = LRESULT(HWND, UINT, WPARAM, LPARAM);
}

class CWindowHandler
{
public:

	CWindowHandler(const HINSTANCE hInstance, const TCHAR* szAppName, window_handler_auxilary::WindowProc WndProc = nullptr);

	~CWindowHandler() = default;

	/* CWindowHandler should be neither copyable nor movable */
	CWindowHandler(const CWindowHandler&) = delete;
	CWindowHandler(CWindowHandler&&) = delete;

	CWindowHandler& operator=(const CWindowHandler&) = delete;
	CWindowHandler& operator=(CWindowHandler&&) = delete;

	INT DisplayWindow(INT iCmdShow) const;

private:
	
	WNDCLASS m_wndClass;
	HWND	 m_hWnd;
};