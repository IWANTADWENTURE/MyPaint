#include "stdafx.h"
#include "Shape.h"


class EllipseShape :Shape {

private:
public:
	void Draw(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		Ellipse(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
	}
protected:
};