#ifndef SHAPES_H
#define SHAPES_H
typedef struct CIRCLE
{
	float x, y;
	int r;
}CIRCLE;
typedef struct VECTOR
{
	float x, y;
	VECTOR(float x = 0, float y = 0)
		: x(x), y(y) {}
	VECTOR operator* (const float   e) { return VECTOR(x * e, y * e); }
	VECTOR operator+ (const float   e) { return VECTOR(x + e, y + e); }
	VECTOR operator- (const float   e) { return VECTOR(x - e, y - e); }
	VECTOR operator+ (const VECTOR  v) { return VECTOR(x + v.x, y + v.y); }
	VECTOR operator- (const VECTOR  v) { return VECTOR(x - v.x, y - v.y); }
	void   operator+=(const VECTOR &v) { x += v.x;	y += v.y; }
	void   operator-=(const VECTOR &v) { x -= v.x;	y -= v.y; }
	void   operator*=(const VECTOR &v) { x *= v.x;	y *= v.y; }
}VECTOR;
#endif
typedef struct POINT
{
	float x, y;
	POINT(float x = 0, float y = 0)
		: x(x), y(y) {}
	POINT operator+ (const POINT  v)  { return POINT(x + v.x, y + v.y); }
	void   operator+=(const VECTOR v) { x += v.x;	y += v.y; }
	void   operator+=(const POINT &v) { x += v.x;	y += v.y; }
	void   operator-=(const POINT &v) { x -= v.x;	y -= v.y; }
	void   operator*=(const POINT &v) { x *= v.x;	y *= v.y; }
}POINT;
