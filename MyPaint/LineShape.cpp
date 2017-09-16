#include "stdafx.h"
#include "Shape.h"


class LineShape:Shape {

private:
public:
	void Draw(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		MoveToEx(hdc, ptsBegin.x, ptsBegin.y, NULL);
		LineTo(hdc, ptsEnd.x, ptsEnd.y);
	}

protected:
};