#define _CRT_SECURE_NO_WARNINGS

#include"../Headers/Matrix.h"

namespace Math {


	mat3::mat3(float val)
	{
		for (float& f : elements)
			f = 0.0f;

		elements[0 + 0 * 3] = val;
		elements[1 + 1 * 3] = val;
		elements[2 + 2 * 3] = val;
	}

	mat3::mat3(float e00, float e01, float e02,
		float e10, float e11, float e12,
		float e20, float e21, float e22)
	{
		elements[0 + 0 * 3] = e00;
		elements[1 + 0 * 3] = e00;
		elements[2 + 0 * 3] = e00;

		elements[0 + 1 * 3] = e10;
		elements[1 + 1 * 3] = e10;
		elements[2 + 1 * 3] = e10;
		
		elements[0 + 2 * 3] = e20;
		elements[1 + 2 * 3] = e21;
		elements[2 + 2 * 3] = e22;
	}

	mat3::mat3(const mat3& m)
	{
		memcpy(&this->elements[0], &m.elements[0], sizeof(float) * 9);
	}

	 // // // // // // // // 
	 // 
	 //	Methods
	 //
	 // // // // // // // // 

	void mat3::makeIdentity()
	{
		*this = mat3::identity();
	}




	void mat3::translate(const Vector2& v)
	{
		mat3::translate(*this, v);
	}

	void  mat3::translate(float x, float y)
	{
		mat3::translate(*this, x,y);
	}



	void mat3::scale(const Vector2& v)
	{
		mat3::scale(*this, v);
	}
	
	void mat3::scale(float x, float y)
	{
		mat3::scale(*this, x,y);
	}







	// // // // // // //
	//
	// Operators
	//
	// // // // // // //

	mat3 mat3::operator + (float val) const
	{
		mat3 mat = *this;
		
		for (float& f : mat.elements)
			f += val;

		return mat;
	}

	mat3 mat3::operator + (const mat3& mat) const
	{
		mat3 result = *this;

		for (int column = 0; column < 3; column++) 
			for (int row = 0; row < 3; row++)
				result.elements[row + column * 3] += mat.elements[row + column * 3];


		return result;
	}




	mat3 mat3::operator - (float val) const
	{
		mat3 mat = *this;

		for (float& f : mat.elements)
			f -= val;

		return mat;
	}

	mat3 mat3::operator - (const mat3& mat) const 
	{
		mat3 result = *this;

		for (int column = 0; column < 3; column++)
			for (int row = 0; row < 3; row++)
				result.elements[row + column * 3] -= mat.elements[row + column * 3];


		return result;
	}





	mat3 operator * (mat3& m, float val) {
		mat3 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}

	mat3 operator * (float val, mat3& m) {
		mat3 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}

	mat3 mat3::operator * (const mat3& mat) const {
		mat3 result;

		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				float sum = 0.0f;

				for (int e = 0; e < 3; e++) {
					sum += this->elements[e + y * 3] * mat.elements[x + e * 3];
				}
				result.elements[x + y * 3] = sum;
			}
		}

		return result;
	}

	Vector3 mat3::operator  * (const Vector3& v)const
	{
		Vector3 result;

		Vector3* res = &result;
		const Vector3* vec = &v;

		for (int x = 0; x < 3; x++)
		{
			for (int e = 0; e < 3; e++)
			{
				*((float*)&res->x + x) += *((float*)&vec->x + e)  * elements[e + x * 3];
			}
		}

		return result;
	}

	Vector3 operator * (const Vector3& v, const mat3& m)
	{
		Vector3 result;

		const Vector3* res = &result;
		const Vector3* vec = &v;

		for (int y = 0; y < 3; y++)
		{
			for (int e = 0; e < 3; e++)
			{
				*((float*)&res->x + y) += *((float*)&vec->x + e) * m.elements[y + e * 3];
			}
		}

		return result;
	}



	mat3 mat3::operator / (float val) const {
		mat3 result = *this;

		for (float& f : result.elements)
			f /= val;

		return result;
	}







	void mat3::operator += (const mat3& mat)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				elements[y + x * 3] += mat.elements[y + x * 3];
			}
		}
	}

	void mat3::operator -= (const mat3& mat)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				elements[y + x * 3] -= mat.elements[y + x * 3];
			}
		}
	}

	void mat3::operator *= (const mat3& mat)
	{
		*this = *this * mat;
	}

	void mat3::operator /= (float val)
	{
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				elements[y + x * 3] /= val;
			}
		}
	}






	void mat3::operator= (const mat3& mat) 
	{
		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++)
				elements[y + x * 3] = mat.elements[y + x * 3];
	}

	mat3::operator float *() { return &elements[0]; }





















	// // // // // // //
	//
	// Static Methods
	//
	// // // // // // //

	mat3 mat3::identity()
	{
		mat3 result(1.0f);
		return result;
	}



	mat3 mat3::translate(const mat3& mat, const Vector2& vec) {
		mat3 result;

		result.column[3].x = vec.x;
		result.column[3].y = vec.y;

		return result;
	}

	mat3 mat3::translate(const mat3& mat, float x, float y)
	{
		mat3 result;

		result.column[3].x = x;
		result.column[3].y = y;

		return result;
	}



	mat3 mat3::scale(const mat3& mat, const Vector2& vec) {
		mat3 result = mat;

		result.elements[0 + 0 * 3] = vec.x;
		result.elements[1 + 1 * 3] = vec.y;

		return result;
	}

	mat3 mat3::scale(const mat3& mat, float x, float y) {
		mat3 result = mat;

		result.elements[0 + 0 * 3] = x;
		result.elements[1 + 1 * 3] = y;

		return result;
	}










	void PrintMat(const mat3& mat) {
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++)
				std::cout << mat.elements[y + x * 3] << ' ';

			std::cout << '\n';
		}
		std::cout << '\n';
	}

}