#include"../Headers/Quaternion.h"
#include"../Headers/Vector.h"
#include"../Headers/Constants.h"

#include<cmath>
#include<iostream>



namespace Math {


    Quaternion::Quaternion(float x, float y, float z, float w)
        :
        x(x),
        y(y),
        z(z),
        w(w)
    {}
    
    Quaternion::Quaternion(const Quaternion& q)
        :
        x(q.x),
        y(q.y),
        z(q.z), 
        w(q.w)
    {}
    
    Quaternion::Quaternion(Quaternion&& q)
        :
        x(q.x),
        y(q.y),
        z(q.z),
        w(q.w)
    {}











	 // // // // // // // // 
	 // 
	 //	Methods
	 //
	 // // // // // // // // 
     
     
     
     void Quaternion::makeConjugate()
     {
        this->x = -this->x;
        this->y = -this->y;
        this->z = -this->z;
     }
     
     
     void Quaternion::normalize()
     {
        float m = this->mag();
        
        this->x /= m;
        this->y /= m;
        this->z /= m;
        this->w /= m;
     }


	 void Quaternion::scale(float val)
	 {
		 this->x *= val;
		 this->y *= val;
		 this->z *= val;
		 this->w *= val;
	 }
     
     
     
     float Quaternion::mag() const
     {
		 return sqrt(PX_Square(this->x) + PX_Square(this->y) + PX_Square(this->z) + PX_Square(this->w));
     }
     









     
     
	 Quaternion Quaternion::Normalize(const Quaternion& q)
	 {
		float m = q.mag();
		return Quaternion(q.x / m, q.y / m, q.z / m, q.w / m);
	 }

     
	 Quaternion Quaternion::Conjugate(const Quaternion& q)
	 {
		 return Quaternion(-q.x, -q.y, -q.z, q.w);
	 }

	 Quaternion Quaternion::Inverse(const Quaternion& q)
	 {
		 Quaternion r(q);
		 r.makeConjugate();

		 float m = r.mag(); 

		 r.x *= 1 / m;
		 r.y *= 1 / m;
		 r.z *= 1 / m;
		 r.w *= 1 / m;

		 return r;
	 }


	 Quaternion Quaternion::PureQuaternion(const Quaternion& q)
	 {
		 return Quaternion(q.x, q.y, q.z, 0.f);
	 }

	 // @TODO: void Quaternion::EulerAngle()
     
     
     
     
     
     
     
     
     // // // // // // // // 
	 // 
	 // Operators
	 //
	 // // // // // // // //
     
     
     
     
     void Quaternion::operator = (const Quaternion& q)
     {
         this->x = q.x;
         this->y = q.y;
         this->z = q.z;
         this->w = q.w;
     }
     
     
     Quaternion Quaternion::operator + (const Quaternion& q) const
     {
         return Quaternion(this->x + q.x, this->y + q.y, 
                           this->z + q.z, this->w + q.w);
     }
     
     
     Quaternion Quaternion::operator - (const Quaternion& q) const
     {
         return Quaternion(this->x - q.x, this->y - q.y, 
                           this->z - q.z, this->w - q.w);
     }





	 Quaternion Quaternion::operator + (const Vector3& q) const
     {
         return Quaternion(this->x + q.x, this->y + q.y, 
                           this->z + q.z, this->w);
     }
     
     
     Quaternion Quaternion::operator - (const Vector3& q) const
     {
         return Quaternion(this->x - q.x, this->y - q.y, 
                           this->z - q.z, this->w);
     }









	 Quaternion Quaternion::operator * (const Quaternion& q) const
	 {
		return Quaternion(this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
			              this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
						  this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
						  this->w * q.w - this->x - q.x - this->y - q.y - this->z - q.z);
	 }

	 Quaternion	Quaternion::operator * (const Vector3& q) const
	 {
		 return Quaternion(this->w * q.x + this->y * q.z - this->z * q.y,
						   this->w * q.y + this->z * q.x - this->x * q.z,
						   this->w * q.z + this->x * q.y - this->y * q.x,
						  -this->x * q.x - this->y * q.y - this->z * q.z);
	 }



	 Quaternion Quaternion::operator / (const Quaternion& q) const
	 {
		 return Quaternion((*this) * Quaternion::Inverse(q));
	 }
     


	 void Quaternion::operator *= (const Quaternion& q)
	 {
		 *this = *this * q;
	 }

	 void Quaternion::operator *= (const Vector3& v)
	 {
		 *this = *this * v;
	 }

     
	 void Quaternion::operator /= (const Quaternion& q)
	 {
		 *this = q * Quaternion::Inverse(*this);
	 }




     // @TODO: operator /=(Vector)
     
     
     
     
     
     
     
     void Quaternion::operator += (const Quaternion& q)
     {
         this->x += q.x;
         this->y += q.y;
         this->z += q.z;
         this->w += q.w;
     }
     
     void Quaternion::operator -= (const Quaternion& q)
     {
         this->x -= q.x;
         this->y -= q.y;
         this->z -= q.z;
         this->w -= q.w;
     }






	 void Quaternion::operator += (const Vector3& r)
	 {
		 this->x += r.x;
		 this->y += r.y;
		 this->z += r.z;
	 }

	 void Quaternion::operator -= (const Vector3& r)
	 {
		 this->x -= r.x;
		 this->y -= r.y;
		 this->z -= r.z;
	 }
     
     

    
     bool Quaternion::operator == (const Quaternion& q) const
     {
         return (this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w); 
     }
     
     bool Quaternion::operator != (const Quaternion& q) const
     {
         return !(this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w); 
     }
     
     Quaternion Quaternion::operator - () const
     {
		 return Quaternion(-this->x, -this->y, -this->z, -this->w);
     }



	 std::ostream& operator << (std::ostream& s, const Quaternion& q)
	 {
		 s << "Quaternion(" << q.x << ',' << q.y << ',' << q.z << ',' << q.w << ')';
		 return s;
	 }




}