#pragma once
struct Vector2
{
	Vector2(float _x, float _y) :x(_x), y(_y){}
	~Vector2() = default;
	Vector2(const Vector2&v)
	{
		x = v.x;
		y = v.y;
	}
	Vector2& operator=(const Vector2& v) = default;
	Vector2(Vector2&& v) = default;
	Vector2& operator=(Vector2&& v) = default;
	float x;
	float y;
};
