#pragma once
#include "edge.h"
#include "node.h"
#include "main.h"

#define BACK_COLOR 0xffffff
#define BORD_COLOR 0x0
#define BORD_SIZE 5

pair<HPEN, HBRUSH> draw_init(HDC& dc, HPEN& hPen, HBRUSH& hBrush, long back_color, long bord_color, int bord_size);
void draw_delete(HDC& dc, HPEN& hPen, HBRUSH& hBrush, pair<HPEN, HBRUSH> old);
void drawText(HDC * dc, int x, int y, int w, int h, int size, string text, UINT flags);

void draw_node_table(HDC& dc, nodeTable& table);
void draw_edge_table(HDC& dc, edgeTable& table);