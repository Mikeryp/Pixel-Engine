#include"../Headers/Vector.h"

namespace Math
{


	Vector2s::Vector2s(short x, short y)
		:
		x(x), y(y)
	{}

	Vector2s::Vector2s(const Vector2s& v)
		:
		x(v.x), y(v.y)
	{}



	// // // // // // // 
	// 
	// Operators
	//
	// // // // // // // 

	void Vector2s::operator = (const Vector2s& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	Vector2s Vector2s::operator + (const Vector2s& v) const
	{
		return Vector2s(this->x + v.x,this->y + v.y);
	}

	Vector2s Vector2s::operator - (const Vector2s& v) const
	{
		return Vector2s(this->x - v.x, this->y - v.y);
	}

	Vector2s Vector2s::operator * (const Vector2s& v) const
	{
		return Vector2s(this->x * v.x, this->y * v.y);
	}
	Vector2s Vector2s::operator / (const Vector2s& v) const
	{
		return Vector2s(this->x / v.x, this->y / v.y);
	}

	Vector2s Vector2s::operator - () const
	{
		return Vector2s(-this->x, -this->y);
	}

	Vector2s Vector2s::operator * (unsigned short val) const
	{
		return Vector2s(this->x * val, this->y * val);
	}

	Vector2s Vector2s::operator / (unsigned short val) const
	{
		return Vector2s(this->x / val, this->y / val);
	}

	void Vector2s::operator += (const Vector2s& v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	void Vector2s::operator -= (const Vector2s& v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}

	void Vector2s::operator *= (const Vector2s& v)
	{
		this->x *= v.x;
		this->y *= v.y;
	}

	void Vector2s::operator /= (const Vector2s& v)
	{
		this->x /= v.x;
		this->y /= v.y;
	}

	bool Vector2s::operator == (const Vector2s& v) const
	{
		return (this->x == v.x) && (this->y == v.y);
	}

	bool Vector2s::operator != (const Vector2s& v) const
	{
		return !(*this == v);
	}

}