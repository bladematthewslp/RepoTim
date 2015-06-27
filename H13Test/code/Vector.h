#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
		: x(0)
		, y(0)
	{}

	Vector2D(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vector2D operator*(float scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}

	Vector2D operator*(Vector2D scalar)
	{
		return Vector2D(x * scalar.x, y * scalar.y);
	}
	Vector2D& operator*=(float& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2D operator+=(const Vector2D& rhs)
	{
		Vector2D v;
		v.x += rhs.x;
		v.y += rhs.y;
		return v;

	}

	Vector2D& operator*=(const Vector2D& scalar)
	{
		x *= scalar.x;
		y *= scalar.y;
		return *this;
	}
};