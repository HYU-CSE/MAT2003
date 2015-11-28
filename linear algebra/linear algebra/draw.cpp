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
	HFONT	hFont = CreateFont(size, 0, 0, 0, 400, FALSE, FALSE, 0, ANSI_CHARSET, 0, 0, 0, 0 | FF_SWISS, TEXT("맑은고딕")),
		hOldFont = (HFONT)SelectObject(dc, hFont);

	SetRect(&rcDraw, x, y, x+ w, y+h);
	DrawText(dc, text.c_str(), -1, &rcDraw, DT_HIDEPREFIX  | flags);

	SelectObject(dc, hOldFont);
	DeleteObject(hFont);
}

void draw_node_table(HDC& dc, nodeTable& table)
{
	FOR_EACH_NODE(table, idx)
	{
		node * node_ = table.at(idx);
		HPEN hPen;
		HBRUSH hBrush;
		pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, ((node_ == sNode) ?  0xffaa00 : (node_ == bNode) ? 0xaacc11 :BORD_COLOR), BORD_SIZE);

		Ellipse(dc, node_->x + node_->r, node_->y + node_->r, node_->x - node_->r, node_->y - node_->r);
		drawText(dc, node_->x - node_->r, node_->y - node_->r/3, 60, 30, 22, to_string(idx), DT_CENTER|DT_VCENTER);

		draw_delete(dc, hPen, hBrush, old);
	}
}
void draw_edge_table(HDC& dc, edgeTable& table)
{
	FOR_EACH_EDGE(table, idx)
	{
		long bc = 0;
		edge* edge = table.at(idx);
		if (edge->cost == 2)
			bc = 0x0;
		else if (edge->cost == 4)
			bc = 0xff0000;
		else if (edge->cost == 5)
			bc = 0xff00ff;

		HPEN hPen;
		HBRUSH hBrush;
		pair<HPEN, HBRUSH> old = draw_init(dc, hPen, hBrush, BACK_COLOR, bc, BORD_SIZE);


		drawText(dc, (edge->to->x + edge->from->x) / 2, (edge->to->y + edge->from->y) / 2 - 20, 25, 20, 16, to_string(edge->cost), DT_LEFT);
		drawText(dc, (edge->to->x + edge->from->x) / 2, (edge->to->y + edge->from->y) / 2 + 5, 25, 20, 16, to_string(edge->flow), DT_LEFT);

		{
			/*간선의 화살표 만들기 -- 짜증난다 짜증나*/
			double p = dist<double>(edge->from->x, edge->from->y, edge->to->x, edge->to->y);

			double	pp = 30. / (p + 30.),
				ppp = 28. / (p + 28.);

			int dx = edge->to->x - edge->from->x,
				dy = edge->to->y - edge->from->y;

			int tx = dx * pp,
				ty = dy * pp,
				ttx = dx * ppp,
				tty = dy * ppp;

			double	a = (edge->from->y - edge->to->y) / (double)(edge->from->x - edge->to->x);

			int ux = ((a * 3.) / (double)sqrt(a * a + 1.)) + ttx,
				nx = -((a * 3.) / (double)sqrt(a * a + 1.)) + ttx,
				uy = -(6. / (sqrt(a*a + 1))) + tty,
				ny = (6. / (sqrt(a*a + 1))) + tty;

			POINT tri[] = { { edge->to->x - ttx , edge->to->y - tty },
			{ edge->to->x - tx - ux, edge->to->y - tty - uy },
			{ edge->to->x - tx - nx, edge->to->y - tty - ny } };

			Polygon(dc, tri, 3);
			/*간선의 화살표 만들기 종료*/
		}

		MoveToEx(dc, edge->from->x, edge->from->y, NULL);
		LineTo(dc, edge->to->x, edge->to->y);

		draw_delete(dc, hPen, hBrush, old);
	}
}