#pragma once
#include "edge.h"
#include "node.h"

#define BACK_COLOR 0xffffff
#define BORD_COLOR 0x0
#define BORD_SIZE 5

pair<HPEN, HBRUSH> draw_init(HDC& dc, HPEN& hPen, HBRUSH& hBrush, long back_color, long bord_color, int bord_size)
{
	hPen = CreatePen(0, bord_size, bord_color);
	hBrush = CreateSolidBrush(back_color);

	return{ (HPEN)SelectObject(dc, hPen), (HBRUSH)SelectObject(dc, hBrush) };
}
void draw_delete(HDC& dc, HPEN& hPen, HBRUSH& hBrush, pair<HPEN, HBRUSH> old)
{
	SelectObject(dc, old.first);
	DeleteObject(hPen);
	SelectObject(dc, old.second);
	DeleteObject(hBrush);
}
void drawText(HDC * dc, int x, int y, int w, int h, int size, string text, UINT flags)
{
	RECT rcDraw;
	HFONT	hFont = CreateFont(size, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, 0, 0, 0, 0 | FF_SWISS, TEXT("¸¼Àº°íµñ")),
		hOldFont = (HFONT)SelectObject(*dc, hFont);

	SetRect(&rcDraw, x, y, x + w, y + h);
	DrawText(*dc, text.c_str(), -1, &rcDraw, DT_HIDEPREFIX | DT_CENTER| flags);

	SelectObject(*dc, hOldFont);
	DeleteObject(hFont);
}

void draw_node_table(HDC& dc, nodeTable& table)
{
	HPEN hPen;
	HBRUSH hBrush;
	pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, BORD_COLOR, BORD_SIZE);
	FOR_EACH_NODE(table, iter)
	{
		node * node_ = iter->second;
		Ellipse(dc, node_->x + node_->r, node_->y + node_->r, node_->x - node_->r, node_->y - node_->r);
	}
	draw_delete(dc, hPen, hBrush, old);
}
void draw_edge_table(HDC& dc, edgeTable& table)
{
	FOR_EACH_EDGE(table, iter)
	{
		long bc = 0;
		if (iter->second->cost == 2)
			bc = 0x0;
		else if (iter->second->cost == 4)
			bc = 0xff0000;
		else if (iter->second->cost == 5)
			bc = 0xff00ff;

		HPEN hPen;
		HBRUSH hBrush;
		pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, bc, BORD_SIZE);

		MoveToEx(dc, iter->second->from->x, iter->second->from->y, NULL);
		LineTo(dc, iter->second->to->x, iter->second->to->y);

		draw_delete(dc, hPen, hBrush, old);
	}
}