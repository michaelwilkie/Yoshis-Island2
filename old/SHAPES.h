#ifndef Shapes_H
#define Shapes_H
struct Circle
{
	int x, y;
	int r;
};
typedef struct VECTOR
{
	float x, y;
	VECTOR(float x = 0, float y = 0)
		: x(x), y(y) {}
	VECTOR operator*(const float e) { return VECTOR(x * e, y * e); }
	VECTOR operator+(const float e) { return VECTOR(x + e, y + e); }
	VECTOR operator-(const float e) { return VECTOR(x - e, y - e); }
	VECTOR operator+(const VECTOR v) { return VECTOR(x + v.x, y + v.y); }
	void operator+=(const VECTOR &v) { x += v.x;	y += v.y; }
	void operator-=(const VECTOR &v) { x -= v.x;	y -= v.y; }
	void operator*=(const VECTOR &v) { x *= v.x;	y *= v.y; }
}VECTOR;
#endif