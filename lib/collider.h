#pragma once
#include <litegfx.h>
#include <Vec2.h>
#include <conio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>

class Collider {
public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	//virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;
};

bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);
bool checkCircleRect(const Vec2& circlePos, float circleRadius, const Vec2& rectPos, const Vec2& rectSize);
bool checkRectRect(const Vec2& rectPos1, const Vec2& rectSize1,	const Vec2& rectPos2, const Vec2& rectSize2);

class CircleCollider : public Collider {
private:
	Vec2  *pos;
	float *rad;
public:
	CircleCollider(Vec2& p, float& radio) { pos = &p; rad = &radio; };
	bool collides(const Collider & other) const { return other.collides(*pos, *rad); };
	bool collides(const Vec2& circlePos, float circleRadius) const { return checkCircleCircle(*pos, *rad, circlePos, circleRadius); };
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const { return checkCircleRect(*pos, *rad, rectPos, rectSize); };
	//bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;*/
};

class RectCollider : public Collider {
private:
	Vec2 *pos;
	Vec2 *size;
public:
	RectCollider(Vec2& p, Vec2& s) { pos = &p; size = &s; }; 
	bool collides(const Collider& other) const { return other.collides(*pos, *size); };
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const { return checkRectRect(*pos, *size, rectPos, rectSize); };
	bool collides(const Vec2& circlePos, float circleRadius) const { return checkCircleRect(circlePos, circleRadius, *pos, *size); };
	//bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const ;
};

class PixelsCollider : public Collider {
private:
	Vec2 pos;
	Vec2 size;
	uint8_t* pixels;
public:
	//bool collides(const Collider& other) const { return other.collides(pos, size, pixels); };
	/*bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& rectPos, const Vec2& rectSize) const ;*/
};


