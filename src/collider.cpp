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