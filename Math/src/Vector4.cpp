#include"../Headers/Vector.h"

namespace Math {

		Vector4::Vector4(float x ,float y ,float z,float w)
			: 
			x(x), y(y), z(z), w(w)
		{}

		Vector4::Vector4(const Vector3& v, float w)
			:
			x(v.x), y(v.y), z(v.z), w(w)
		{}


		Vector4::Vector4(Vector4&& v)
			:
			x(v.x),
			y(v.y),
			z(v.z),
			w(v.w)
		{}

		Vector4::Vector4(const Vector4& v)
			:
			x(v.x),
			y(v.y),
			z(v.z),
			w(v.w)
		{}









		// // // // // // // //
		//
		// Operators
		// 
		// // // // // // // //

		void Vector4::operator = (const Vector4& v) {
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
		}

		Vector4 Vector4::operator + (const Vector4& v) const {
			return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
		}
		Vector4 Vector4::operator - (const Vector4& v) const {
			return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
		}
		Vector4 Vector4::operator * (const Vector4& v) const {
			return Vector4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
		}
		Vector4 Vector4::operator / (const Vector4& v) const {
			return Vector4(this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w);
		}



		Vector4 Vector4::operator + (const Vector3 &v) const {
			return Vector4(this->x + v.x, this->y + v.y, this->z + v.z, this->w);
		}
		Vector4 Vector4::operator - (const Vector3 &v) const {
			return Vector4(this->x - v.x, this->y - v.y, this->z - v.z, this->w);
		}
		Vector4 Vector4::operator / (const Vector3 &v) const {
			return Vector4(this->x / v.x, this->y / v.y, this->z / v.z, this->w);
		}
		Vector4 Vector4::operator * (const Vector3 &v) const {
			return Vector4(this->x * v.x, this->y * v.y, this->z * v.z, this->w);
		}


		Vector4 Vector4::operator + (const Vector2 &v) const {
			return Vector4(this->x + v.x, this->y + v.y, this->z, this->w);
		}
		Vector4 Vector4::operator - (const Vector2 &v) const {
			return Vector4(this->x - v.x, this->y - v.y, this->z, this->w);
		}
		Vector4 Vector4::operator / (const Vector2 &v) const {
			return Vector4(this->x / v.x, this->y / v.y, this->z, this->w);
		}
		Vector4 Vector4::operator * (const Vector2 &v) const {
			return Vector4(this->x * v.x, this->y * v.y, this->z, this->w);
		}



		Vector4 Vector4::operator * (float val) const {
			return Vector4(this->x * val, this->y * val, this->z * val, this->w * val);
		}
		Vector4 Vector4::operator / (float val) const {
			return Vector4(this->x / val, this->y / val, this->z / val, this->w / val);
		}



		void Vector4::operator += (const Vector4& v) {
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
			this->w += v.w;
		}
		void Vector4::operator -= (const Vector4& v) {
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
			this->w -= v.w;
		}
		void Vector4::operator *= (const Vector4& v) {
			this->x *= v.x;
			this->y *= v.y;
			this->z *= v.z;
			this->w *= v.w;
		}
		void Vector4::operator /= (const Vector4& v) {
			this->x /= v.x;
			this->y /= v.y;
			this->z /= v.z;
			this->w /= v.w;
		}


		void Vector4::operator += (const Vector3 &v) {
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}
		void Vector4::operator -= (const Vector3& v) {
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}
		void Vector4::operator *= (const Vector3& v) {
			this->x *= v.x;
			this->y *= v.y;
			this->z *= v.z;
		}
		void Vector4::operator /= (const Vector3& v) {
			this->x /= v.x;
			this->y /= v.y;
			this->z /= v.z;
		}



		void Vector4::operator += (const Vector2 &v) {
			this->x += v.x;
			this->y += v.y;
		}
		void Vector4::operator -= (const Vector2& v) {
			this->x -= v.x;
			this->y -= v.y;
		}
		void Vector4::operator *= (const Vector2& v) {
			this->x *= v.x;
			this->y *= v.y;
		}
		void Vector4::operator /= (const Vector2& v) {
			this->x /= v.x;
			this->y /= v.y;
		}


		std::ostream& operator << (std::ostream& stream, const Vector4& v) {
			stream << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
			return stream;
		}

}