#include "stdafx.h"
#include "stdafx.h"
#include <string>
#include "RectangleShape.cpp"
#include "EllipseShape.cpp"
#include "LineShape.cpp"
#pragma once

using namespace std;

class DrawShapes {
		
private:
	RectangleShape RectShape;
	EllipseShape ElipShape;
	LineShape LiShape;

	static HDC GetPen(HDC hdc) {
		hLinePen = CreatePen(PS_SOLID, PenWidth, PenColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
		return hdc;
	}

	static COLORREF PenColor;
	static int PenWidth;
	static HPEN hPenOld;
	static HPEN hLinePen;

public:

	DrawShapes() {//Set default values
		PenColor = RGB(0, 0, 0);
		PenWidth = 1;
	}

	void DrawRect(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		RectShape.Draw(GetPen(hdc), ptsBegin, ptsEnd);
		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
		ReleaseCapture();
	}
	void DrawRoundRect(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		RectShape.DrawRounded(GetPen(hdc), ptsBegin, ptsEnd);
	}
	void DrawElip(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		ElipShape.Draw(GetPen(hdc), ptsBegin, ptsEnd);
		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
		ReleaseCapture();
	}
	void DrawLine(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		LiShape.Draw(GetPen(hdc), ptsBegin, ptsEnd);
		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);
		ReleaseCapture();
	}
	void NoDraw(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {};

	static void SetPenWidth(int ChoosedPenWidth) {
		PenWidth = ChoosedPenWidth;
	}
	static void SetPenColor(COLORREF ChoosedPenColor) {
		PenColor = ChoosedPenColor;
	}
	COLORREF GetPenColor() {
		return PenColor;
	}
	int GetPenWidth() {
		return PenWidth;
	}

protected:

};