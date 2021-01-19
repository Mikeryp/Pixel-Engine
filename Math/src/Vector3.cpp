#pragma once
#include"../Headers/Vector.h"

namespace Math {

		Vector3::Vector3(float x,float y,float z)
			:
			x(x), y(y), z(z)
		{}

		Vector3::Vector3(const Vector2& v, float z)
			:
			x(v.x), y(v.y), z(z)
		{}

		Vector3::Vector3(const Vector3& v)
			:
			x(v.x), y(v.y), z(v.z)
		{}







		// // // // // // // // 
		//
		// Methods
		//
		// // // // // // // //



		float Vector3::getMag() const {
			return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		}

		Vector3 Vector3::perpWith(const Vector3 &v) const {
			return Vector3::cross(*this, v);
		}

		void Vector3::normalise() {
			if (this->x == 0 && this->y == 0 && this->z == 0)
				return;

			auto mag = this->getMag();

			if (mag == 1)
				return;

			this->x /= mag;
			this->y /= mag;
			this->z /= mag;

			return;
		}

		void Vector3::setMag(float mag) {
			this->normalise();

			this->x *= mag;
			this->y *= mag;
			this->z *= mag;
		}

		float Vector3::DistanceFrom(const Vector3& v) const {
			return sqrt(PX_Square(v.x - this->x) + PX_Square(v.y - this->y) + PX_Square(v.z - this->z));
		}


		










		// // // // // // // // 
		//
		// Static Functions
		//
		// // // // // // // //

		float Vector3::Distance(const Vector3 &v1, const Vector3 &v2) {
			return sqrt(PX_Square(v2.x - v1.x) + PX_Square(v2.y - v1.y) + PX_Square(v2.z - v1.z));
		}

		Vector3 Vector3::DistanceVector(const Vector3& v1, const Vector3& v2) {
			return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
		}

		float Vector3::dot(const Vector3 &v1, const Vector3 &v2) {
			return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
		}

		Vector3 Vector3::cross(const Vector3 &v1, const Vector3 &v2) {
			float x = (v1.y * v2.z) - (v1.z * v2.y);
			float y = (v1.z * v2.x) - (v1.x * v2.z) ;
			float z = (v1.x * v2.y) - (v1.y * v2.z);

			return Vector3(x, y, z);
		}

		float Vector3::mag(const Vector3 &v) {
			return sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
		}

		float Vector3::angleBetween(const Vector3 &v1, const Vector3 &v2) {
			if ((v1.x == 0 && v1.y == 0 && v1.z == 0) || (v2.x == 0 && v2.y == 0 && v2.z == 0))
				return 0;

			auto mag1 = Vector3::mag(v1);
			auto mag2 = Vector3::mag(v2);

			auto dot = Vector3::dot(v1, v2);

			auto num = dot / (mag1 * mag2);

			if (num < -1.0)
				return (float)PX_PI;
			if (num > 1.0)
				return 0.0f;

			return (float)(acosf(num) * 180 / PX_PI);
		}

		Vector3 Vector3::normalised(Vector3 v)
		{
			v.normalise();
			return v;
		}















		// // // // // // // // 
		//
		// Operators
		//
		// // // // // // // //

		void Vector3::operator = (const Vector3 &v) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		Vector3 Vector3::operator + (const Vector3 &v) const {
			return Vector3{ this->x + v.x, this->y + v.y, this->z + v.z };
		}
		Vector3 Vector3::operator - (const Vector3 &v) const {
			return Vector3{ this->x - v.x, this->y - v.y, this->z - v.z };
		}
		Vector3 Vector3::operator / (const Vector3 &v) const {
			return Vector3(this->x / v.x, this->y / v.y, this->z / v.z);
		}
		Vector3 Vector3::operator * (const Vector3 &v) const {
			return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
		}


		Vector3 Vector3::operator + (const Vector2 &v) const {
			return Vector3(this->x + v.x, this->y + v.y, this->z);
		}
		Vector3 Vector3::operator - (const Vector2 &v) const {
			return Vector3(this->x - v.x, this->y - v.y, this->z);
		}
		Vector3 Vector3::operator / (const Vector2 &v) const {
			return Vector3(this->x / v.x, this->y / v.y, this->z);
		}
		Vector3 Vector3::operator * (const Vector2 &v) const {
			return Vector3(this->x * v.x, this->y * v.y, this->z);
		}


		Vector3 Vector3::operator / (float val) const {
			return Vector3(this->x / val, this->y / val, this->z / val);
		}
		Vector3 Vector3::operator * (float val) const {
			return Vector3(this->x * val, this->y * val, this->z * val);
		}


		Vector3 Vector3::operator - () const {
			return Vector3(-this->x, -this->y, -this->z);
		}




		void Vector3::operator += (const Vector3 &v) {
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}
		void Vector3::operator -= (const Vector3& v) {
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}
		void Vector3::operator *= (const Vector3& v) {
			this->x *= v.x;
			this->y *= v.y;
			this->z *= v.z;
		}
		void Vector3::operator /= (const Vector3& v) {
			this->x /= v.x;
			this->y /= v.y;
			this->z /= v.z;
		}



		void Vector3::operator += (const Vector2 &v) {
			this->x += v.x;
			this->y += v.y;
		}
		void Vector3::operator -= (const Vector2& v) {
			this->x -= v.x;
			this->y -= v.y;
		}
		void Vector3::operator *= (const Vector2& v) {
			this->x *= v.x;
			this->y *= v.y;
		}
		void Vector3::operator /= (const Vector2& v) {
			this->x /= v.x;
			this->y /= v.y;
		}



		bool Vector3::operator == (const Vector3& v) const {
			return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
		}
		bool Vector3::operator!= (const Vector3& v) const {
			return !((this->x == v.x) && (this->y == v.y) && (this->z == v.z));
		}

		std::ostream& operator << (std::ostream& stream,const Vector3& v) {
			stream << '(' << v.x << ',' << v.y << ',' << v.z << ')';
			return stream;
		}

} 
