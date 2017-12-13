#include <collider.h>


bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2) {
	Vec2 center1 = pos1 ;
	Vec2 center2 = pos2;
	Vec2 dist = center1 - center2;
	float distLenght = dist.lenght();
	if (distLenght < (radius1 + radius2))
		return true;
	else
		return false;

}

bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize) {
	float closestX = std::clamp(circlePos.x, rectPos.x, (rectPos.x + rectSize.x)); 
	float closestY = std::clamp(circlePos.y, rectPos.y, (rectPos.y + rectSize.y));
	Vec2 closestPoint = Vec2(closestX, closestY);
	Vec2 dist = circlePos - closestPoint;
	float distLenght = dist.lenght();
	if (distLenght < circleRadius)
		return true;
	else
		return false;
}

bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1, const Vec2& rectPos2, const Vec2& rectSize2) { //box then mouse
	
	if (((rectPos2.x < (rectPos1.x + rectSize1.x)) && (rectPos2.x > rectPos1.x)) && ((rectPos2.y > rectPos1.y) && (rectPos2.y < (rectPos1.y + rectSize1.y)))) {
		return true;
	}
	else {
		return false;
	}
}
