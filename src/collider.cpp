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
	float closestX = std::clamp(circlePos.x, rectPos.x, rectPos.y); //change this!
		/*closestX = clamp(cirX, topLeftX, bottomRightX);
	closestY = clamp(cirY, topLeftY, bottomRightY);*/
	
	return false;
}
