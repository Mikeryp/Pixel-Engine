#define _CRT_SECURE_NO_WARNINGS

#include"../Headers/Matrix.h"

namespace Math {

	mat4::mat4(float val)
	{
		for (float& f : elements)
			f = 0.0f;

		elements[0 + 0 * 4] = val;
		elements[1 + 1 * 4] = val;
		elements[2 + 2 * 4] = val;
		elements[3 + 3 * 4] = val;
	}

	mat4::mat4(const Vector4& c1, const Vector4& c2, const Vector4& c3, const Vector4& c4)
	{	   
		column[0] = c1;
		column[1] = c2;
		column[2] = c3;
		column[3] = c4;
	}

	mat4::mat4(float e00, float e01, float e02, float e03,
		float e10, float e11, float e12, float e13,
		float e20, float e21, float e22, float e23,
		float e30, float e31, float e32, float e33)
	{
		elements[0 + 0 * 4] = e00;
		elements[1 + 0 * 4] = e01;
		elements[2 + 0 * 4] = e02;
		elements[3 + 0 * 4] = e03;

		elements[0 + 1 * 4] = e10;
		elements[1 + 1 * 4] = e11;
		elements[2 + 1 * 4] = e12;
		elements[3 + 1 * 4] = e13;

		elements[0 + 2 * 4] = e20;
		elements[1 + 2 * 4] = e21;
		elements[2 + 2 * 4] = e22;
		elements[3 + 2 * 4] = e23;

		elements[0 + 3 * 4] = e30; 
		elements[1 + 3 * 4] = e31;
		elements[2 + 3 * 4] = e32;
		elements[3 + 3 * 4] = e33;
	}

	mat4::mat4(const mat4& m)
	{
		memcpy(this->elements, m.elements, sizeof(float) * 16);
	}



	// // // // // // // // //
	// 
	// Methods
	//
	// // // // // // // // //


	void mat4::translate(float x, float y, float z)
	{
		this->column[3].x = x;
		this->column[3].y = y;
		this->column[3].z = z;
	}							

	void mat4::translate(const Math::Vector3& v)
	{
		this->column[3].x = v.x;
		this->column[3].y = v.y;
		this->column[3].z = v.z;
	}

	void mat4::scale(float x, float y, float z)
	{
		this->elements[0 + 0 * 4] = x;
		this->elements[1 + 1 * 4] = y;
		this->elements[2 + 2 * 4] = z;
		this->elements[3 + 3 * 4] = 1.0f;
	}

	void mat4::scale(const Math::Vector3& v)
	{
		this->elements[0 + 0 * 4] = v.x;
		this->elements[1 + 1 * 4] = v.y;
		this->elements[2 + 2 * 4] = v.z;
		this->elements[3 + 3 * 4] = 1.0f;
	}


	void mat4::makeIdentity()
	{
		*this = mat4::identity();
	}

	void mat4::makeOrtho(float left, float right,
		float top, float bottom,
		float near, float far)
	{
		*this = mat4::orthographic(left,right, top,bottom, near,far);
	}

	void mat4::makePerspective(float fov, float asp, float near, float far)
	{
		*this = mat4::perspective(fov, asp, near, far);
	}

	void mat4::makeLookAt(const Math::Vector3& eyePos, const Math::Vector3& target, const Math::Vector3& up)
	{
		*this = mat4::lookAt(eyePos, target, up);
	}












	// // // // // // // // //
	//
	// Operators
	//
	// // // // // // // // //

	mat4 mat4::operator +(float val) const {
		mat4 result = *this;

		for (float& f : result.elements)
			f += val;

		return result;
	}

	mat4 mat4::operator+ (const mat4& mat) const {
		mat4 result = *this;

		for (int column = 0; column < 4; column++)
			for (int row = 0; row < 4; row++)
				result.elements[row + column * 4] += mat.elements[row + column * 4];


		return result;
	}


	mat4 mat4::operator -(float val) const {
		mat4 result = *this;

		for (float& f : result.elements)
			f -= val;

		return result;
	}

	mat4 mat4::operator - (const mat4& mat) const {
		mat4 result = *this;

		for (int column = 0; column < 4; column++)
			for (int row = 0; row < 4; row++)
				result.elements[row + column * 4] -= mat.elements[row + column * 4];


		return result;
	}




	mat4 operator * (mat4& m, float val) {
		mat4 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}

	mat4 operator * (float val, mat4& m) {
		mat4 result = m;

		for (float& f : result.elements)
			f *= val;

		return result;
	}

	mat4 mat4::operator * (const mat4& mat) const {
		mat4 result;

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				float sum = 0.0f;

				for (int e = 0; e < 4; e++) {
					sum += this->elements[e + y * 4] * mat.elements[x + e * 4];
				}
				result.elements[x + y * 4] = sum;
			}
		}

		return result;
	}

	Vector4 mat4::operator * (const Vector4& v) const
	{
		const Vector4* vec = &v;
		Vector4 result;

		Vector4* res = &result;

		for (int x = 0; x < 4; x++)
		{
			for (int e = 0; e < 4; e++)
			{
				*((float*)&res->x + x) += *((float*)&vec->x + e) * elements[e + x * 4];
			}
		}

		return result;
	}




	void mat4::operator += (const mat4& mat)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				elements[y + x * 4] += mat.elements[y + x * 4];
			}
		}
	}

	void mat4::operator -= (const mat4& mat)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				elements[y + x * 4] -= mat.elements[y + x * 4];
			}
		}
	}

	void mat4::operator *= (const mat4& mat)
	{
		*this = *this * mat;
	}

	void mat4::operator /= (float val)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				elements[y + x * 4] /= val;
			}
		}
	}






	void mat4::operator = (const mat4& mat) {
		for (int y = 0; y < 4; y++)
			for (int x = 0; x < 4; x++)
				elements[y + x * 4] = mat.elements[y + x * 4];

	}



	mat4::operator float *() { return &elements[0]; }
























	// // // // // // // // //
	//
	// Static Methods
	//
	// // // // // // // // //

	mat4 mat4::identity() {
		mat4 result;

		result.elements[0 + 0 * 4] = 1.0f;
		result.elements[1 + 1 * 4] = 1.0f;
		result.elements[2 + 2 * 4] = 1.0f;
		result.elements[3 + 3 * 4] = 1.0f;

		return result;
	}



	mat4 mat4::translate(const mat4& mat, const Vector3& vec) {
		mat4 result = mat;

		result.column[3].x = vec.x;
		result.column[3].y = vec.y;
		result.column[3].z = vec.z;

		return result;
	}


	mat4 mat4::translate(const mat4& mat, float x, float y, float z) {
		mat4 result = mat;

		result.column[3].x = x;
		result.column[3].y = y;
		result.column[3].z = z;

		return result;
	}






	mat4 mat4::scale(const mat4& mat, const Vector3& vec) {
		mat4 result = mat;

		result.elements[0 + 0 * 4] = vec.x;
		result.elements[1 + 1 * 4] = vec.y;
		result.elements[2 + 2 * 4] = vec.z;
		result.elements[3 + 3 * 4] = 1.0f;

		return result;
	}

	mat4 mat4::scale(const mat4& mat, float x, float y, float z) {
		mat4 result = mat;

		result.elements[0 + 0 * 4] =  x;
		result.elements[1 + 1 * 4] =  y;
		result.elements[2 + 2 * 4] =  z;
		result.elements[3 + 3 * 4] = 1.0f;

		return result;
	}


   
	mat4 mat4::rotation(float x, float y, float z, float angle)
	{
		float s = (float)sin(PX_toRadians(angle));
		float c = (float)cos(PX_toRadians(angle));

		float _c = 1 - c;

		mat4 result(1);

		result.column[0].x = c + PX_Square(x) * _c;
		result.column[0].y = x * y * _c + z * s;
		result.column[0].z = x * z * _c - y * s;

		result.column[1].x = x * y * _c - z  * s;
		result.column[1].y = c + PX_Square(y)	* _c;
		result.column[1].z = z * y * _c + x * s;

		result.column[2].x = x * z * _c + y * s;
		result.column[2].y = y * z * _c - x * s;
		result.column[2].z = c + PX_Square(z) * _c;
		
		return result;
	}

	mat4 mat4::rotation(const Vector3& r,float angle)
	{
		//cosO + square(Rx)(1 - cosO)    RxRy(1 - cosO) - Rz sinO		RxRz(1 - cosO) + Ry sinO
		//RyRx(1 - cosO) + Rz sinO	   cosO + square(Ry)(1 - cosO)	    RyRz(1 - cosO) - Rx sinO
		//RzRx(1 - cos) - Ry sinO  		RzRy(1 - cosO) + Rx sinO			   cos + square(Rz)(1 - cosO)

		float s = (float)sin(PX_toRadians(angle));
		float c = (float)cos(PX_toRadians(angle));

		float _c = 1 - c;

		mat4 result(1.0f);

		result.column[0].x = c + PX_Square(r.x) * _c;
		result.column[0].y = r.x * r.y * _c + r.z * s;
		result.column[0].z = r.x * r.z * _c - r.y * s;

		result.column[1].x = r.x * r.y * _c - r.z  * s;
		result.column[1].y = c + PX_Square(r.y)	* _c;
		result.column[1].z = r.z * r.y * _c + r.x * s;

		result.column[2].x = r.x * r.z * _c + r.y * s;
		result.column[2].y = r.y * r.z * _c - r.x * s;
		result.column[2].z = c + PX_Square(r.z) * _c;

		return result;
	}







	mat4 mat4::orthographic(float left, float right,
							float top, float bottom,
							float near, float far) 
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] =  2 / (right - left);
		result.elements[1 + 1 * 4] =  2 / (top - bottom);
		result.elements[2 + 2 * 4] = -2 / (far - near);

		result.elements[0 + 3 * 4] = -((right + left) / (right - left));
		result.elements[1 + 3 * 4] = -((top + bottom) / (top - bottom));
		result.elements[2 + 3 * 4] = -((far + near) / (far - near));

		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	mat4 mat4::perspective(float fov, float asp, float near, float far) {
		mat4 result(0.0f);

		result.elements[0 + 0 * 4] = 1 / (asp * (tan(fov / 2)));
		result.elements[1 + 1 * 4] = 1 / (tan(fov / 2));
		result.elements[2 + 2 * 4] = -(far + near)/ (far - near);

		result.elements[2 + 3 * 4] = -(2 * far * near) / (far - near);
		result.elements[3 + 2 * 4] = -1;			

		return result;
	}


	mat4 mat4::lookAt(const Math::Vector3& eyePos, const Math::Vector3& target, const Math::Vector3& up)
	{
		mat4 result(1.0f);

		Vector3 forward = Vector3::normalised(target - eyePos);
		Vector3 side = Vector3::normalised(Vector3::cross(forward, up));
		Vector3 above = Vector3::cross(side, forward);

		result.elements[0 + 0 * 4] = side.x;
		result.elements[0 + 1 * 4] = side.y;
		result.elements[0 + 2 * 4] = side.z;

		result.elements[0 + 3 * 4] = -(Vector3::dot(side, eyePos));

		result.elements[1 + 0 * 4] = above.x;
		result.elements[1 + 1 * 4] = above.y;
		result.elements[1 + 2 * 4] = above.z;

		result.elements[1 + 3 * 4] = -(Vector3::dot(above,eyePos));
		
		result.elements[2 + 0 * 4] = -forward.x;
		result.elements[2 + 1 * 4] = -forward.y;
		result.elements[2 + 2 * 4] = -forward.z;

		result.elements[2 + 3 * 4] = (Vector3::dot(forward, eyePos));

		return result;
	}


	Vector4 operator * (const Vector4& v, const mat4& m)
	{
		Vector4 result(0,0,0,0);

		const Vector4* res = &result;
		const Vector4* vec = &v;

		for (int y = 0; y < 4; y++)
		{
			for (int e = 0; e < 4; e++)
			{
				float* r_component = (((float*)&res->x) + y);
				float* v_component = (((float*)&vec->x) + e);
				*r_component +=  (*v_component) * m.elements[y + e * 4];
			}
		}

		return result;
	}





	void PrintMat(const mat4& mat) {
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++)
				std::cout << mat.elements[y + x * 4] << ' ';

			std::cout << '\n';
		}
		std::cout << '\n';
	}
}