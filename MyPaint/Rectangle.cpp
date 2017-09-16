#include "stdafx.h"
#include "Shape.cpp"

class RectangleDraw:Shape {

private:
	HDC hdc;
	POINTS StartPoint;
	POINTS FinishPoint;
	void Rectangles() {
		Rectangle(hdc, StartPoint.x, StartPoint.y, FinishPoint.x, FinishPoint.y);
	}

public:

	RectangleDraw(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		//ShapesBorderWidth = ShapesBorderWidth;
		hdc = hdc;
		StartPoint = ptsBegin;
		FinishPoint = ptsEnd;
	}

	void Draw() {
		Rectangles();
	}
protected:
};