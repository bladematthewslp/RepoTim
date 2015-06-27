#pragma once

#include <cmath>
#include "Vector.h"

struct Matrix2D
{
	float r0c0, r0c1;
	float r1c0, r1c1;

	explicit Matrix2D(
		float r0c0 = 1, float r0c1 = 0,
		float r1c0 = 0, float r1c1 = 1);
	static Matrix2D rotate(float angleInRadians);

};
Vector2D operator*(const Matrix2D& matrix, const float i);
Vector2D operator*(const Matrix2D& matrix, const Vector2D& vector);

