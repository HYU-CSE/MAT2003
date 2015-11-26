#include "draw.h"
#include <string>
#include <cmath>

template<typename T>
T dist(T x1, T y1, T x2, T y2)
{
	return sqrt(pow(x2 - x1, 2.) + pow(y2 - y1, 2.));
}

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
void drawText(HDC& dc, int x, int y, int w, int h, int size, string text, UINT flags)
{
	RECT rcDraw;
	HFONT	hFont = CreateFont(size, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, 0, 0, 0, 0 | FF_SWISS, TEXT("¸¼Àº°íµñ")),
		hOldFont = (HFONT)SelectObject(dc, hFont);

	SetRect(&rcDraw, x, y, w, h);
	DrawText(dc, text.c_str(), -1, &rcDraw, DT_HIDEPREFIX | DT_CENTER | flags);

	SelectObject(dc, hOldFont);
	DeleteObject(hFont);
}

void draw_node_table(HDC& dc, nodeTable& table)
{
	FOR_EACH_NODE(table, iter)
	{
		node * node_ = iter->second;
		HPEN hPen;
		HBRUSH hBrush;
		pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, ((node_ == sNode) ?  0xffaa00 : (node_ == bNode) ? 0xaacc11 :BORD_COLOR), BORD_SIZE);

		Ellipse(dc, node_->x + node_->r, node_->y + node_->r, node_->x - node_->r, node_->y - node_->r);
		drawText(dc, node_->x - node_->r, node_->y - node_->r/3, node_->x + node_->r, node_->y + node_->r, 22, to_string(iter->first), DT_VCENTER);

		draw_delete(dc, hPen, hBrush, old);
	}
}
void draw_edge_table(HDC& dc, edgeTable& table)
{
	FOR_EACH_EDGE(table, iter)
	{
		long bc = 0;
		if ((*iter)->cost == 2)
			bc = 0x0;
		else if ((*iter)->cost == 4)
			bc = 0xff0000;
		else if ((*iter)->cost == 5)
			bc = 0xff00ff;

		HPEN hPen;
		HBRUSH hBrush;
		pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, bc, BORD_SIZE);

		double p = dist<double>((*iter)->from->x, (*iter)->from->y, (*iter)->to->x, (*iter)->to->y);

		double	pp = 30. / (p + 30.),
				ppp = 28. / (p + 28.);

		int dx = (*iter)->to->x - (*iter)->from->x,
			dy = (*iter)->to->y - (*iter)->from->y;

		int tx = dx * pp,
			ty = dy * pp,
			ttx = dx * ppp,
			tty = dy * ppp;

		double	a = ((*iter)->from->y - (*iter)->to->y) / (double)((*iter)->from->x - (*iter)->to->x);

		int ux = ((a * 3.) / (double)sqrt(a * a + 1.)) + ttx,
			nx = -((a * 3.) / (double)sqrt(a * a + 1.)) + ttx,
			uy = -(6. / (sqrt(a*a+1))) + tty,
			ny = (6. / (sqrt(a*a + 1))) + tty;

		POINT tri[] = { { (*iter)->to->x - ttx , (*iter)->to->y - tty },
						{ (*iter)->to->x - tx - ux, (*iter)->to->y - tty - uy},
						{ (*iter)->to->x - tx - nx, (*iter)->to->y - tty - ny } };

		Polygon(dc, tri , 3);

		MoveToEx(dc, (*iter)->from->x, (*iter)->from->y, NULL);
		LineTo(dc, (*iter)->to->x, (*iter)->to->y);

		draw_delete(dc, hPen, hBrush, old);
	}
}