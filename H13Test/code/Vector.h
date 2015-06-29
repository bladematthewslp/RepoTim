#pragma once
#include <cmath>

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

	Vector2D operator+(Vector2D vec)
	{
		return Vector2D(x + vec.x, y + vec.y);
	}

	Vector2D operator-(Vector2D vec)
	{
		return Vector2D(x - vec.x, y - vec.y);
	}

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


	Vector2D rotateCW()
	{
		return Vector2D(y, -x);
	}
	Vector2D rotateCCW()
	{
		return Vector2D(-y, x);
	}

	float dot(const Vector2D other) const
	{
		return x * other.x + y * other.y;
	}
	float magnitudeSquared() const
	{
		return this->dot(*this);
	}
	float Vector2D::magnitude() const
	{
		//return sqrt(x*x + y*y + z*z);
		return sqrt(magnitudeSquared());
	}
	

	Vector2D normalized()
	{
		float inverseMagnitude = 1.0f / magnitude();
		return (*this) * inverseMagnitude;
	}


};
