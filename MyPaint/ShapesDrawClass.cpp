#include "stdafx.h"
#include <iostream>
#include "stdafx.h"
#include <string>


class DrawShapes {

private:
	int ShapesBorderWidth;
	HDC hdc;
	POINTS ptsBegin;
	POINTS ptsEnd;
	void DrawRect() {
		Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
		/*HPEN hPenOld;
		HPEN hLinePen;
		COLORREF qLineColor;
		qLineColor = RGB(255, 0, 0);
		hLinePen = CreatePen(PS_SOLID, ShapesBorderWidth, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);

		MoveToEx(hdc, 100, 100, NULL);
		LineTo(hdc, 500, 250);

		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);*/
	}
	void DrawElip() {

	}
	void DrawLine() {
		MoveToEx(hdc, ptsBegin.x, ptsBegin.y, (LPPOINT)NULL);
		LineTo(hdc, ptsEnd.x, ptsEnd.y);
	}

public:

	DrawShapes(int ShapesBorderWidth, HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		ShapesBorderWidth = ShapesBorderWidth;
		hdc = hdc;
		ptsBegin = ptsBegin;
		ptsEnd = ptsEnd;
		printf((char*)hdc);
	}

	void DrawShape(char ChoosedShape) { //define and draw shape
		switch (ChoosedShape) {
		case 'Rect':
			DrawRect();
			break;
		case 'Elip':
			DrawElip();
			break;
		case 'Line':
			DrawLine();
			break;
		}
	}
protected:

};