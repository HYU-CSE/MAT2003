#pragma once
#include "main.h"

HINSTANCE nInst;

#define abs(x) (x) > 0 ? (x) : (-(x))

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG messages;
	WNDCLASSEX win_main;

	HICON hICON = (HICON)LoadImage(hInstance, MAKEINTRESOURCE(APP_ICON), IMAGE_ICON, 32, 32, LR_DEFAULTCOLOR);
	char szTitle[50], szClass[50];

	LoadString(hInstance, APP_NAME, szTitle, 32);
	LoadString(hInstance, APP_CLASS_NAME, szClass, 32);

	win_main.cbSize = sizeof(WNDCLASSEX);
	win_main.hInstance = nInst = hInstance;
	win_main.style = CS_HREDRAW | CS_VREDRAW;
	win_main.cbClsExtra = 0;
	win_main.cbWndExtra = 0;
	win_main.lpszClassName = szClass;
	win_main.lpszMenuName = NULL;
	win_main.lpfnWndProc = WindowProcedure;
	win_main.hIcon = hICON;
	win_main.hIconSm = hICON;
	win_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	win_main.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	if (!RegisterClassEx(&win_main))
		return 0;

	hwnd = CreateWindow(szClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,
		CW_USEDEFAULT, SIZEWW, SIZEHH, HWND_DESKTOP, NULL, hInstance, NULL);

	if (!hwnd)
		return -1;

	SetProcessWorkingSetSize(hwnd, -1, -1);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	ZeroMemory(&messages, sizeof(messages));
	while (messages.message != WM_QUIT)
	{
		if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
	}
	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
		{
			nodeTable nodes;
			edgeTable * edges = nodes.edges();
			vector<size_t> node_index;
			
			node_index.push_back(nodes.add(100, 100));
			node_index.push_back(nodes.add(100, 200));
			node_index.push_back(nodes.add(100, 300));
			node_index.push_back(nodes.add(100, 400));
			node_index.push_back(nodes.add(100, 500));
			node_index.push_back(nodes.add(100, 600));
			

			break;
		}
		case WM_TIMER:
		{
			break;
		}
		case WM_SIZE:
		{
			break;
		}
		case WM_MOUSEWHEEL:
		{
			int e = ((SHORT)HIWORD(wParam) > 0) ? (-15) : (((SHORT)HIWORD(wParam) < 0) ? (15) : (0));
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_KEYDOWN:
		{
		
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_LBUTTONDBLCLK:
		{

			break;
		}
		case WM_COMMAND:
		{
			break;
		}
		case WM_MOUSEMOVE:
		{
			point.x = lParam & 0xffff;
			point.y = lParam >> 16;
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			RECT		mRC;
			HDC			hdc, mDC;
			HBITMAP		mBitmap, mOldBitmap;

			hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &mRC);
			mDC = CreateCompatibleDC(hdc);
			mBitmap = CreateCompatibleBitmap(hdc, mRC.right, mRC.bottom);
			mOldBitmap = (HBITMAP)SelectObject(mDC, mBitmap);
			PatBlt(mDC, 0, 0, mRC.right, mRC.bottom, WHITENESS);
			SetBkMode(mDC, TRANSPARENT);
			SetStretchBltMode(mDC, COLORONCOLOR);
			{//draw


			}
			BitBlt(hdc, 0, 0, mRC.right, mRC.bottom, mDC, 0, 0, SRCCOPY);
			SelectObject(mDC, mOldBitmap);
			DeleteObject(mBitmap);
			DeleteDC(mDC);

			EndPaint(hwnd, &ps);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

