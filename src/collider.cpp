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
	float xPrim2 = rectPos2.x + rectSize2.x;
	float yPrim2 = rectPos2.y + rectSize2.y;
	float xPrim1 = rectPos1.x + rectSize1.x;
	float yPrim1 = rectPos1.y + rectSize1.y;
	float x1 = rectPos1.x;
	float y1 = rectPos1.y;
	float x2 = rectPos2.x;
	float y2 = rectPos2.y;

	if (((x2 < xPrim1)&&((x2 > x1)||(xPrim2 > x1)))&&((y2 < yPrim1)&&((y2 > y1)||(yPrim2 > y1)))) 
		return true;
	else 
		return false;
	
}

bool checkPixelsPixels(const Vec2& pixelsPos1, const Vec2& pixelsSize1, const uint8_t* pixels1, const Vec2& pixelsPos2, const Vec2& pixelsSize2, const uint8_t* pixels2) {

	for (int i = 0; i < (pixelsSize1.y); i++) {
		for (int j = 0; j < (pixelsSize1.x); j = j++) {
			if (pixels1[((i* static_cast<int>(pixelsSize1.x)) + j)*4 +3] >= 128 
			&& pixels2[((i* static_cast<int>(pixelsSize1.x)) + j) * 4 + 3] >= 128) {
				
				return true; //not sure yet about this function
			}
		}
	}
	return false;
	
}
