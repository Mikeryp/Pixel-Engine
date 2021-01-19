/*

   This is a header provides Vector math functionality. All the 
   Vector class fall under the Math namespace. 

*/

// Vectors:- 
// Vector2, Vector2s(short), Vector3,  Vector4


#pragma once

#include<math.h>
#include<iostream>

#include"Constants.h"

namespace Math {

	struct mat2;
	struct mat3;
	struct mat4;

	struct Vector3;
	struct Vector4;
	struct Vector2s;



	struct Vector2 {
		float x;
		float y;

		Vector2() = default;

		Vector2(float x,float y);
		Vector2(int x,int y);

		Vector2(const Vector2&);


		// // // // // // // 
		// 
		// Methods
		//
		// // // // // // // 

		float getMag() const;
		void setMag(float mag);

		void normalise();
		void rotate(float angle);

		float DistanceFrom(const Vector2& v) const;
		float AngleFromOrigin() const;



		// // // // // // // 
		// 
		// Static Functions
		//
		// // // // // // // 

		static float Distance(const Vector2& v1, const Vector2& v2);
		static Vector2 DistanceVector(const Vector2 &v1, const Vector2 &v2);

		static float dot(const Vector2 &v1, const Vector2 &v2);
		static float angleBetween(const Vector2 &v1, const Vector2 &v2);

		static Vector2 normalised(const Vector2& v);




		// // // // // // // 
		// 
		// Operators
		//
		// // // // // // // 

		void operator = (const Vector2& v);

		Vector2 operator + (const Vector2& v) const;
		Vector2 operator - (const Vector2& v) const;
		Vector2 operator * (const Vector2& v) const;
		Vector2 operator / (const Vector2& v) const;

		Vector2 operator - ();

		Vector2 operator * (float val) const;
		Vector2 operator / (float val) const;

		void operator += (const Vector2& v);
		void operator -= (const Vector2& v);
		void operator *= (const Vector2& v);
		void operator /= (const Vector2& v);

		bool operator == (const Vector2& v) const;
		bool operator != (const Vector2& v) const;

		friend Vector2 operator * (const Vector2& v, const mat2& m);

		friend std::ostream& operator << (std::ostream& stream,const Vector2& v);
	};
 
	struct Vector2s {
		unsigned short x;
		unsigned short y;

		Vector2s() = default;

		Vector2s(short x,short y);
		Vector2s(const Vector2s&);



		// // // // // // // 
		// 
		// Operators
		//
		// // // // // // // 

		void operator = (const Vector2s& v);

		Vector2s operator + (const Vector2s& v) const;
		Vector2s operator - (const Vector2s& v) const;
		Vector2s operator * (const Vector2s& v) const;
		Vector2s operator / (const Vector2s& v) const;

		Vector2s operator - () const;

		Vector2s operator * (unsigned short val) const;
		Vector2s operator / (unsigned short val) const;

		void operator += (const Vector2s& v);
		void operator -= (const Vector2s& v);
		void operator *= (const Vector2s& v);
		void operator /= (const Vector2s& v);

		bool operator == (const Vector2s& v) const;
		bool operator != (const Vector2s& v) const;

		friend std::ostream& operator << (std::ostream& stream, const Vector2& v);
	};


















	struct Vector3 {
		union { float x; float r; };
		union { float y; float g; };
		union { float z; float b; };
			
		Vector3() = default;
		Vector3(float x,float y,float z);

		Vector3(const Vector3&);
		Vector3(const Vector2& v2,float z);
						


		// // // // // // // 
		// 
		// Methods
		//
		// // // // // // // 

		void setMag(float mag);
		float getMag() const;

		void normalise();

		Vector3 perpWith(const Vector3 &v) const;
		float DistanceFrom(const Vector3& v) const;


		// // // // // // // 
		// 
		// Static Functions
		//
		// // // // // // // 

		static float Distance(const Vector3 &v1, const Vector3 &v2);
		static Vector3 DistanceVector(const Vector3& v1, const Vector3& v2);

		static float angleBetween(const Vector3 &v1, const Vector3 &v2);

		static float mag(const Vector3 &v);
		static Vector3 normalised(Vector3 v);

		static float dot(const Vector3 &v1, const Vector3 &v2);
		static Vector3 cross(const Vector3 &v1, const Vector3 &v2);





		// // // // // // // 
		// 
		// Operators
		//
		// // // // // // // 

		void operator = (const Vector3 &v);

		Vector3 operator + (const Vector3 &v) const;
		Vector3 operator - (const Vector3 &v) const;
		Vector3 operator * (const Vector3 &v) const;
		Vector3 operator / (const Vector3 &v) const;


		Vector3 operator + (const Vector2& v) const;
		Vector3 operator - (const Vector2& v) const;
		Vector3 operator * (const Vector2& v) const;
		Vector3 operator / (const Vector2& v) const;

		Vector3 operator * (float val) const;
		Vector3 operator / (float val) const;

		Vector3 operator - () const;

		void operator += (const Vector3& v);
		void operator -= (const Vector3& v);
		void operator *= (const Vector3& v);
		void operator /= (const Vector3& v);

		void operator += (const Vector2& v);
		void operator -= (const Vector2& v);
		void operator *= (const Vector2& v);
		void operator /= (const Vector2& v);

		bool operator == (const Vector3& v) const;
		bool operator != (const Vector3& v) const;

		friend Vector3 operator * (const Vector3& v, const mat3& m);
		friend std::ostream& operator << (std::ostream& stream, const Vector3& v);
	};



















	struct Vector4 {
		
		union { float x, r; };
		union { float y, g; };
		union { float z, b; };
		union { float w, a; };


		Vector4() = default;
		Vector4(float x, float y, float z, float w);

		Vector4(Vector4&&);
		Vector4(const Vector4&);
		Vector4(const Vector3& v3, float w);




		void operator = (const Vector4& v);

		Vector4 operator * (const Vector4& v) const;
		Vector4 operator / (const Vector4& v) const;
		Vector4 operator + (const Vector4& v) const;
		Vector4 operator - (const Vector4& v) const;

		Vector4 operator * (const Vector3& v) const;
		Vector4 operator / (const Vector3& v) const;
		Vector4 operator + (const Vector3& v) const;
		Vector4 operator - (const Vector3& v) const;

		Vector4 operator * (const Vector2& v) const;
		Vector4 operator / (const Vector2& v) const;
		Vector4 operator + (const Vector2& v) const;
		Vector4 operator - (const Vector2& v) const;

		Vector4 operator * (float val) const;
		Vector4 operator / (float val) const;


		void operator += (const Vector4& v);
		void operator -= (const Vector4& v);
		void operator *= (const Vector4& v);
		void operator /= (const Vector4& v);

		void operator += (const Vector3& v);
		void operator -= (const Vector3& v);
		void operator *= (const Vector3& v);
		void operator /= (const Vector3& v);

		void operator += (const Vector2& v);
		void operator -= (const Vector2& v);
		void operator *= (const Vector2& v);
		void operator /= (const Vector2& v);

		friend Vector4 operator * (const Vector4& v, const mat4& m);
		friend std::ostream& operator << (std::ostream& stream,const Vector4& v);
	};

}
