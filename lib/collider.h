#pragma once
#include <litegfx.h>
#include <Vec2.h>
#include <conio.h>
#include <vector>
#include <math.h>

class Collider {
public:
	virtual bool collides(const Collider& other) const = 0;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const = 0;
	/*virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const = 0;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const = 0;*/
};

bool checkCircleCircle(const Vec2& pos1, float radius1, const Vec2& pos2, float radius2);

class CircleCollider : public Collider {
private:
	Vec2 pos;
	float rad;
public:
	CircleCollider(const Vec2& p, const float r) { pos = p; rad = r; };
	bool collides(const Collider & other) const { return other.collides(pos, rad); };
	bool collides(const Vec2& circlePos, float circleRadius) const { return checkCircleCircle(pos, rad, circlePos, circleRadius); };
	/*bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;*/
};

class RectCollider : public Collider {
private:
	Vec2 pos;
	Vec2 size;
public:
	//bool collides(const Collider& other) const { return other.collides(pos, size); };
	/*bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	bool collides(const Vec2& circlePos, float circleRadius) const;
	bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const ;*/
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


