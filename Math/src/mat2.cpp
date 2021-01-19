#define _CRT_SECURE_NO_WARNINGS

#include"../Headers/Matrix.h"


namespace Math {
	
	mat2::mat2(float val)
	{
		for (float& f : elements)
			f = 0;

		elements[0 + 0 * 2] = val;
		elements[1 + 1 * 2] = val;
	}


	mat2::mat2(const mat2& m)
	{
		memcpy(&this->elements[0], &m.elements[0], sizeof(float) * 4);
	}

	mat2::mat2(float e00, float e01, float e10, float e11) 
	{
		this->elements[0] = e00;
		this->elements[1] = e10;
		this->elements[2] = e01;
		this->elements[3] = e11;
	}
	











	void mat2::makeIdentity()
	{
		*this = mat2::identity();
	}






	// // // // // // //
	//
	// Operators
	//
	// // // // // // //

	mat2 mat2::operator + (float val) const {
		mat2 result = *this; 

		for (float& f : result.elements)
			f += val;

		return  result;
	}

	mat2 mat2::operator + (const mat2& mat) const {
		mat2 result = *this;

		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				result.elements[y + x * 2] += mat.elements[y + x * 2];

		return result;
	}





	mat2 mat2::operator - (float val) const {
		mat2 result = *this;

		for (float& f : result.elements)
			f -= val;

		return  result;
	}

	mat2 mat2::operator - (const mat2& mat) const {
		mat2 result = *this;

		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				result.elements[y + x * 2] -= mat.elements[y + x * 2];

		return  result;
	}




	mat2 operator * (mat2& m, float val)
	{
		mat2 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}

	mat2 operator * (float val, mat2& m)
	{
		mat2 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}



	mat2 mat2::operator * (const mat2& mat)const {
		mat2 result;

		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 2; x++) {
				float sum = 0.0f;

				for (int e = 0; e < 2; e++) {
					sum += this->elements[e + y * 2] * mat.elements[x + e * 2];
				}
				result.elements[x + y * 2] = sum;
			}
		}

		return result;
	}

	Vector2 mat2::operator * (const Vector2& v) const
	{
		Vector2 result;

		Vector2* res = &result;
		const Vector2* vec = &v;

		for (int x = 0; x < 2; x++)
		{
			for (int e = 0; e < 2; e++)
			{
				*((float*)&res->x + x) += *((float*)&vec->x + e) * elements[e + x * 2];
			}
		}

		return result;
	}
	



	mat2 mat2::operator / (float val) const {
		mat2 result = *this;

		for (float& f : result.elements)
			f /= val;

		return result;
	}





	void mat2::operator += (const mat2& mat)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				elements[y + x * 2] += mat.elements[y + x * 2];
			}
		}
	}

	void mat2::operator -= (const mat2& mat)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				elements[y + x * 2] -= mat.elements[y + x * 2];
			}
		}
	}

	void mat2::operator *= (const mat2& mat)
	{
		*this = *this * mat;
	}

	void mat2::operator /= (float val)
	{
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				elements[y + x * 2] /= val;
			}
		}
	}







	void mat2::operator = (const mat2& mat) {
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				elements[y + x * 2] = mat.elements[y + x * 2];
	}






	Vector2 operator * (const Vector2& v, const mat2& m)
	{
		Vector2 result;

		const Vector2* res = &result;
		const Vector2* vec = &v;

		for (int x = 0; x < 2; x++)
		{
			for (int e = 0; e < 2; e++)
			{
				*((float*)&res->x + x) += *((float*)&vec->x + e) * m.elements[x + e * 2];
			}
		}

		return result;
	}

	mat2::operator float * () {
		return &this->elements[0];
	}







	
	// // // // // // //
	//
	// Static Methods
	//
	// // // // // // //

	mat2 mat2::identity() {
		mat2 result(1.0f);
		return result;
	}

	mat2 mat2::inverse(const mat2& m) {
		float d = (m.column[0].x * m.column[1].y) - (m.column[1].x * m.column[0].y);

		mat2 mat(m);

		mat.elements[0] += mat.elements[3];	// This is to swap the 1st and 4th element


		mat.elements[1] *= -1;
		mat.elements[2] *= -1;
		mat.elements[3] = mat.elements[0] - mat.elements[3];
		mat.elements[0] -= mat.elements[3];

		return 1/d * mat;

	}

	mat2 mat2::adjugate(const mat2& m)
	{
		mat2 mat = m;

		mat.elements[1] *= -1;
		mat.elements[2] *= -1;
		mat.elements[3] = mat.elements[0] - mat.elements[3];
		mat.elements[0] -= mat.elements[3];

		return mat;
	}











	void PrintMat(const mat2& mat) {
		for (int y = 0; y < 2; y++) {
			for (int x = 0; x < 2; x++)
				std::cout << mat.elements[y + x * 2] << ' ';

			std::cout << '\n';
		}
		std::cout << '\n';
	}


}