#include "stdafx.h"
#include "WindowHandler.h"

constexpr auto szAppName = L"App name";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
VOID    CALLBACK DrawTextOnWindow(HDC* pHdc, RECT* pRect, PAINTSTRUCT* pPs, HWND* pHwnd, const std::wstring& sText);
VOID    CALLBACK RedrawTextOnWindow(HDC* pHdc, RECT* pRect, PAINTSTRUCT* pPs, HWND* pHwnd, const std::wstring& sText);

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance
                      , _In_ LPWSTR lpCmdLine, _In_ INT iShowCmd)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	CWindowHandler window(hInstance, szAppName, WndProc);
	return window.DisplayWindow(iShowCmd);
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton;
	static LONG lWndWidth = 0;
	static LONG lWndHeight = 0;

	static auto lUnits	  = GetDialogBaseUnits();
	static auto lButtonWidth  = MulDiv(LOWORD(lUnits), 50, 4);
	static auto lButtonHeight = MulDiv(HIWORD(lUnits), 14, 8);

	auto         iKeyPressed = 0;
	/*HDC	     hdc;
	PAINTSTRUCT  paintStruct;*/
	RECT	     rect;
	std::wstring sText;

	GetClientRect(hWnd, &rect);

	switch (uMessage)
	{
	case WM_CREATE: // Window creation
		iKeyPressed = MessageBox(hWnd, L"Creation", L"Message", MB_ICONINFORMATION | MB_OKCANCEL);

		if (iKeyPressed == IDCANCEL) {
			PostQuitMessage(0);
		}

		return 0;

	case WM_CLOSE: // Window close button clicked
		PostQuitMessage(0);
		return 0;

	case WM_SIZE: // Window resized
		lWndWidth = rect.right - rect.left; lWndHeight = rect.bottom - rect.top;

		DestroyWindow(hButton);
		hButton = CreateWindow(L"BUTTON", L"Press me!", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON
                                       , (lWndWidth - lButtonWidth) / 2, (lWndHeight - lButtonHeight) / 2, lButtonWidth, lButtonHeight
                                       , hWnd, nullptr, GetModuleHandle(nullptr), nullptr);
		return 0;

	case WM_COMMAND: // button clicked
		return 0;

	default:
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
}



VOID CALLBACK DrawTextOnWindow(HDC* pHdc, RECT* pRect, PAINTSTRUCT* pPs, HWND* pHwnd, const std::wstring& sText)
{
	auto szText = (!sText.empty() ? sText.c_str() : L"Default text");

	*pHdc = BeginPaint(*pHwnd, pPs);

	GetClientRect(*pHwnd, pRect);
	DrawText(*pHdc, szText, -1, pRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	EndPaint(*pHwnd, pPs);
}

VOID CALLBACK RedrawTextOnWindow(HDC* pHdc, RECT* pRect, PAINTSTRUCT* pPs, HWND* pHwnd, const std::wstring& sText)
{
	InvalidateRect(*pHwnd, nullptr, TRUE);
	DrawTextOnWindow(pHdc, pRect, pPs, pHwnd, sText);
	UpdateWindow(*pHwnd);
}
