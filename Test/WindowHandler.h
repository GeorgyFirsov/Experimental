#pragma once

namespace window_auxilary
{
	using WindowProc = LRESULT(HWND, UINT, WPARAM, LPARAM);

	inline LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
	{
		if (uMessage == WM_CLOSE)
		{
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}

class CWindowHandler
{
	using WindowProc = window_auxilary::WindowProc;

public:

	CWindowHandler();
	CWindowHandler(HINSTANCE hInstance, const std::wstring& sWndClassName, WindowProc WndProc = nullptr);

	~CWindowHandler() = default;

	/* CWindowHandler should be neither copyable nor movable */
	CWindowHandler(const CWindowHandler&) = delete;
	CWindowHandler(CWindowHandler&&) = delete;

	CWindowHandler& operator=(const CWindowHandler&) = delete;
	CWindowHandler& operator=(CWindowHandler&&) = delete;

	INT DisplayWindow(INT iCmdShow) const;

private:

	WNDCLASS m_wndClass;
	HWND	 m_hWnd = nullptr;

	VOID CreateMainWindow(HINSTANCE hInstance, const wchar_t* szWndClassName, WindowProc WndProc);
};

VOID InitializeWndClass(PWNDCLASS pWndClass, HINSTANCE hInstance, const wchar_t* szAppName, window_auxilary::WindowProc WndProc);