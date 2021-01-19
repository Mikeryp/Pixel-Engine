#pragma once

#include"../Headers/Vector.h"




namespace Math {


	Vector2::Vector2(float x,float y)
		:
		x(x),
		y(y)
	{}

	Vector2::Vector2(int x, int y)
		: x(float(x)),
		  y(float(y))
	{}

	Vector2::Vector2(const Vector2& v)
		:
		x(v.x),
		y(v.y)
	{}








	float Vector2::getMag() const {
		return sqrt((this->x * this->x) + (this->y * this->y));
	}

	void Vector2::setMag(float mag) {
		this->normalise();

		this->x *= mag;
		this->y *= mag;
	}

	void Vector2::normalise() {
		if (this->x == 0 && this->y == 0)
			return;

		auto mag = this->getMag();
		if (mag == 1)
			return;

		this->x /= mag;
		this->y /= mag;

		return;
	}

	void Vector2::rotate(float angle) {
		this->x *= cos(angle);
		this->y *= sin(angle);
	}

	float Vector2::DistanceFrom(const Vector2& v) const {
		return sqrt(PX_Square(v.x - this->x) + PX_Square(v.y - this->y));
	}
	float Vector2::AngleFromOrigin() const {
		return acosf(this->y / this->getMag());
	}
















	// // // // // // // // 
	//
	// Static Functions
	//
	// // // // // // // //
	float Vector2::Distance(const Vector2& v1, const Vector2& v2) {
		return 	sqrt(PX_Square(v2.x - v1.x) + PX_Square(v2.y - v1.y));
	}

	Vector2 Vector2::DistanceVector(const Vector2 &v1, const Vector2 &v2) {
		return Vector2(v1.x - v2.x, v1.y - v2.y);
	}

	float Vector2::dot(const Vector2 &v1, const Vector2 &v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	float Vector2::angleBetween(const Vector2 &v1, const Vector2 &v2) {
		if ((v1.x == 0 && v1.y == 0))
			return 0;

		auto mag1 = v1.getMag();
		auto mag2 = v2.getMag();

		auto dot = Vector2::dot(v1, v2);

		auto num = dot / (mag1 * mag2);

		if (num < -1.0)
			return (float)PX_PI;
		if (num > 1.0)
			return 0.0f;

		return (float)(acosf(num) * 180 / PX_PI);

	}

	Vector2 Vector2::normalised(const Vector2& v)
	{
		return Vector2(v.x / v.getMag(), v.y / v.getMag());
	}
















	// // // // // // // // 
	//
	// Operators
	//
	// // // // // // // //

	void Vector2::operator = (const Vector2& v) {
		this->x = v.x;
		this->y = v.y;
	}

	Vector2 Vector2::operator + (const Vector2& v) const {
		return Vector2{ this->x + v.x, this->y + v.y };
	}
	Vector2 Vector2::operator - (const Vector2& v) const {
		return Vector2(this->x - v.x, this->y - v.y);
	}
	Vector2 Vector2::operator * (const Vector2& v) const {
		return Vector2(this->x * v.x, this->y * v.y);
	}




	Vector2 Vector2::operator / (const Vector2& v) const {
		return Vector2(this->x / v.x, this->y / v.y);
	}

	Vector2 Vector2::operator * (float val) const {
		return Vector2(this->x * val, this->y * val);
	}
	Vector2 Vector2::operator / (float val) const {
		return Vector2(this->x / val, this->y / val);
	}




	void Vector2::operator += (const Vector2& v) {
		this->x += v.x;
		this->y += v.y;
	}
	void Vector2::operator -= (const Vector2& v) {
		this->x -= v.x;
		this->y -= v.y;
	}
	void Vector2::operator *= (const Vector2& v) {
		this->x *= v.x;
		this->y *= v.y;
	}
	void Vector2::operator /= (const Vector2& v) {
		this->x /= v.x;
		this->y /= v.y;
	}




	bool Vector2::operator == (const Vector2& v) const {
		return (this->x == v.x) && (this->y == v.y);
	}
	bool Vector2::operator != (const Vector2& v) const {
		return !((this->x == v.x) && (this->y == v.y));
	}



	Vector2 Vector2::operator - () {
		return Vector2(-this->x, -this->y);
	}

	std::ostream& operator << (std::ostream& stream,const Vector2& v) {
		stream << '(' << v.x << ',' << v.y << ')';
		return stream;
	}

}