#pragma once
#include "main.h"

HINSTANCE nInst;

nodeTable * nodes = new nodeTable();
edgeTable * edges = new edgeTable(nodes);

POINT point, sPoint;

bool sft = false;
bool eve = false;

node* sNode = nullptr, *bNode = nullptr;
edge* sEdge = nullptr;

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
			vector<size_t> node_index, edge_index;
			
			node_index.push_back(nodes->add(100, 200));
			node_index.push_back(nodes->add(200, 100));
			node_index.push_back(nodes->add(200, 200));
			node_index.push_back(nodes->add(200, 300));
			node_index.push_back(nodes->add(300, 100));
			node_index.push_back(nodes->add(300, 200));
			node_index.push_back(nodes->add(300, 300));
			node_index.push_back(nodes->add(400, 100));
			node_index.push_back(nodes->add(400, 200));
			node_index.push_back(nodes->add(400, 300));
			node_index.push_back(nodes->add(500, 100));
			node_index.push_back(nodes->add(500, 200));
			node_index.push_back(nodes->add(500, 300));
			node_index.push_back(nodes->add(600, 200));
			
			edge_index.push_back(edges->add(0, 1, 2, 3));
			edge_index.push_back(edges->add(0, 2, 5, 5));
			edge_index.push_back(edges->add(0, 3, 4, 10));

			edge_index.push_back(edges->add(1, 4, 4, 3));
			edge_index.push_back(edges->add(1, 5, 5, 5));
			edge_index.push_back(edges->add(1, 6, 2, 10));
			edge_index.push_back(edges->add(2, 4, 4, 3));
			edge_index.push_back(edges->add(2, 5, 2, 5));
			edge_index.push_back(edges->add(2, 6, 5, 10));
			edge_index.push_back(edges->add(3, 4, 2, 3));
			edge_index.push_back(edges->add(3, 5, 5, 5));
			edge_index.push_back(edges->add(3, 6, 4, 10));

			edge_index.push_back(edges->add(4, 7, 5, 3));
			edge_index.push_back(edges->add(4, 8, 2, 5));
			edge_index.push_back(edges->add(4, 9, 4, 10));
			edge_index.push_back(edges->add(5, 7, 2, 3));
			edge_index.push_back(edges->add(5, 8, 5, 5));
			edge_index.push_back(edges->add(5, 9, 2, 10));
			edge_index.push_back(edges->add(6, 7, 2, 3));
			edge_index.push_back(edges->add(6, 8, 4, 5));
			edge_index.push_back(edges->add(6, 9, 5, 10));

			edge_index.push_back(edges->add(7, 10, 2, 3));
			edge_index.push_back(edges->add(7, 11, 5, 5));
			edge_index.push_back(edges->add(7, 12, 2, 10));
			edge_index.push_back(edges->add(8, 10, 2, 3));
			edge_index.push_back(edges->add(8, 11, 4, 5));
			edge_index.push_back(edges->add(8, 12, 5, 10));
			edge_index.push_back(edges->add(9, 10, 2, 3));
			edge_index.push_back(edges->add(9, 11, 4, 5));
			edge_index.push_back(edges->add(9, 12, 2, 10));

			edge_index.push_back(edges->add(10, 13, 4, 3));
			edge_index.push_back(edges->add(11, 13, 5, 5));
			edge_index.push_back(edges->add(12, 13, 2, 10));
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
			if (wParam == 16) 
				sft = true;
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_KEYUP:
		{
			if (wParam == 16)
				sft = false;
			InvalidateRect(hwnd, NULL, FALSE);
		}
		case WM_RBUTTONDOWN:
		{
			POINT pt = { lParam & 0xffff, lParam >> 16 };
			FOR_EACH_NODE((*nodes), iter)
			{
				node * node_ = iter->second;
				if (node_->x - node_->r < pt.x && node_->x + node_->r > pt.x &&
					node_->y - node_->r < pt.y && node_->y + node_->r > pt.y)
				{
					edges->del(node_);
					nodes->del(node_);
					sNode = nullptr;
					bNode = nullptr;
					break;
				}
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			eve = false;
			POINT pt = { lParam & 0xffff, lParam >> 16 };
			FOR_EACH_NODE((*nodes), iter)
			{
				node * node_ = iter->second;
				if (node_->x - node_->r < pt.x && node_->x + node_->r > pt.x &&
					node_->y - node_->r < pt.y && node_->y + node_->r > pt.y)
				{
					sNode = node_;
					sPoint = { pt.x - node_->x, pt.y - node_->y };
					break;
				}
			}
			if (sft && bNode != nullptr)
			{
				edges->add(bNode, sNode, 2, 4);
				eve = true;
			}
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		case WM_MOUSEMOVE:
		{
			if (sNode != nullptr)
			{
				point.x = lParam & 0xffff;
				point.y = lParam >> 16;

				sNode->x = (point.x - sPoint.x);
				sNode->y = (point.y - sPoint.y);

				InvalidateRect(hwnd, NULL, FALSE);
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			InvalidateRect(hwnd, NULL, FALSE);
			if (!eve)
				bNode = sNode;

			sNode = nullptr;
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
				draw_edge_table(mDC, *edges);
				draw_node_table(mDC, *nodes);
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

