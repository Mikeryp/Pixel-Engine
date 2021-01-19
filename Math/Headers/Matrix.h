// This file defines matrix structures of 2,3 and 4 diagnol length
// ie: a 2x2,3x3, and 4x4 matrix 

#include"Vector.h"




#pragma once

namespace Math {



	/*
     * Tasks
     * * * * * * * * 
     * 
     * PRIORITY :
     * 
     * implement the inverse of all the matrices
     * 
     * 
     * 
     * SECONDARY :
     * 
     * make all the functions follow the code style: methods start with small letters, static 
     * start with Capital letters.
     * 
	 * Check all the matrix classes properly so that they are robust
*/





 /*This is the definition of a 2x2 matrix.
  * 
  * * * * * * * * 
  * Methods :-  * 
  * * * * * * * * 
  * 
  * makeIdentity : Makes the matrix an identity matrix
  * 
  * 
  * 
  * 
  * 
  * 
  * * * * * * * * * * * * 
  * Static Functions :- *
  * * * * * * * * * * * * 
  *
  * 
  * void identity(mat2&) : makes the passed matrix an identity matrix
  * 
  * mat2 identity() : construct's and return's an identity matrix
  * 
  * 
*/

	struct mat2 {
		union
		{
			float elements[4];
			Vector2 column[2];
		};

		mat2(float val = 1.0f);		 
		mat2(float e00, float e01,
			 float e10, float e11);

		mat2(const mat2&);

		void makeIdentity();

		// Operators
		mat2 operator + (const mat2& mat)const;
		mat2 operator + (float val)const;

		mat2 operator - (const mat2& mat)const;
		mat2 operator - (float val)const;

		mat2 operator * (const mat2& mat)const;

		friend mat2 operator * (mat2& m, float val);
		friend mat2 operator * (float val, mat2& m);

		Vector2 operator * (const Vector2& v) const;

		mat2 operator / (float val) const;

		void operator += (const mat2& mat);
		void operator -= (const mat2& mat);
		void operator *= (const mat2& mat);
		void operator /= (float val);

		void operator = (const mat2& mat);

		operator float* ();

		static mat2 identity();
        
        static mat2 inverse(const mat2& m);
		static mat2 adjugate(const mat2& m);

	 };














	struct mat3 {
		union
		{
			float elements[9];
			Vector3 column[3];
		};

		mat3(float val = 1.0f);
		mat3(float e00, float e01, float e02,
			float e10, float e11, float e12,
			float e20, float e21, float e22);

		mat3(const mat3&);

		void translate(float x,float y);
		void translate(const Vector2& v);

		void scale(float x, float y);
		void scale(const Vector2& v);

		void makeIdentity();


		// Operators
		mat3 operator + (const mat3& mat) const;
		mat3 operator + (float val) const;

		mat3 operator - (const mat3& mat) const;
		mat3 operator - (float val) const;

		mat3 operator * (const mat3& mat) const;
		
		friend mat3 operator * (const mat3& m, float val);
		friend mat3 operator * (float val, const mat3& m);

		Math::Vector3 operator * (const Vector3& v) const;

		mat3 operator / (float val) const;

		void operator += (const mat3& mat);
		void operator -= (const mat3& mat);
		void operator *= (const mat3& mat);
		void operator /= (float val);

		void operator = (const mat3& mat);

		operator float* ();





		// Static methods

		static mat3 identity();
        
        static mat3 inverse(const mat3& m);

		static mat3 translate(const mat3& mat, const Vector2& vec);
		static mat3 translate(const mat3& mat, float x, float y);

		static mat3 scale(const mat3& mat, const Vector2& vec);
		static mat3 scale(const mat3& mat, float x, float y);

	};




















	struct mat4 {

		union 
		{
			float elements[16];
 			Vector4 column[4];
		};

		mat4(float val = 1.0f);
		mat4(const Vector4& c0, const Vector4& c1, const Vector4& c2, const Vector4& c3);

		mat4(float e00, float e01, float e02, float e03,
			float e10, float e11, float e12, float e13,
			float e20, float e21, float e22, float e23,
			float e30, float e31, float e32, float e33);

		mat4(const mat4&);

		void translate(float x, float y, float z);
		void translate(const Math::Vector3& v);

		void scale(float x, float y,float z);
		void scale(const Math::Vector3& v);

		void makeIdentity();

		void makeOrtho(float left, float right,
					   float top, float bottom,
					   float near, float far);
		void makePerspective(float fov, float asp, float near, float far);
		void makeLookAt(const Math::Vector3& eyePos, const Math::Vector3& target, const Math::Vector3& up);

		// Operators
		mat4 operator + (const mat4& mat) const;
		mat4 operator + (float val) const;

		mat4 operator - (const mat4& mat) const;
		mat4 operator - (float val) const;

		mat4 operator * (const mat4& mat) const;
		
		friend mat4 operator * (const mat4& m, float val);
		friend mat4 operator * (float val, const mat4& m);

	    Vector4 operator * (const Vector4& v) const;


		void operator += (const mat4& mat);
		void operator -= (const mat4& mat);
		void operator *= (const mat4& mat);
		void operator /= (float val);


		void operator = (const mat4& mat);

		operator float*();

		// Static Methods
		static mat4 identity();
		
		static mat4 rotation(float x, float y, float z, float degrees);
		static mat4 rotation(const Vector3& rotation, float  degrees);


        static mat4 inverse(const mat4& m);

		static mat4 translate(const mat4& mat, const Vector3& vec);
		static mat4 translate(const mat4& mat, float x, float y, float z);

		static mat4 scale(const mat4& mat4, const Vector3& vec);
		static mat4 scale(const mat4& mat4, float x, float y, float z);



		static mat4 orthographic(float left, float right, 
							     float top, float bottom,
								 float near, float far);

		static mat4 perspective(float fov, float asp, float near, float far);
		static mat4 lookAt(const Math::Vector3& eyePos, const Math::Vector3& target, const Math::Vector3& up);
	};


	void PrintMat(const mat2& m);
	void PrintMat(const mat3& m);
	void PrintMat(const mat4& m);

}
