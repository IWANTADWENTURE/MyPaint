#include "stdafx.h"
#include "Shape.h"


class RectangleShape:Shape {

private:
	float PercentRound = 0.85f;//default value
public:
	void Draw(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		Rectangle(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y);
	}
	void DrawRounded(HDC hdc, POINTS ptsBegin, POINTS ptsEnd) {
		RoundRect(hdc, ptsBegin.x, ptsBegin.y, ptsEnd.x, ptsEnd.y, PercentRound*(ptsBegin.x - ptsEnd.x), PercentRound*(ptsBegin.y - ptsEnd.y));
	}

protected:
};