// This file defines a structure for quaternions. 

// The written quaternion could be represented mathematically as 
// w + x + y + z, where w is the real part of the ordered pair
// quaternion


/*  DOC NOTE:-
*
*
* Quaternions are formatted in the mathematical form in the menmory,
* that is, in the form of a + bi + cj + dk. The equivalent form of
* this struct is w + x + y + z.
*
*
* Memory format
*
* Bytes: 	  w			   x			y			z
*         00000000    000000000    000000000   000000000
*
*   (00000000  represents 4 bytes.)
*
*/




#pragma once

#include<iostream>


namespace Math {

    struct Vector3;
    struct Vector4;


	struct Quaternion
	{
		float w;

		float x;
		float y;
		float z;


        Quaternion() = default;
		Quaternion(float x, float y, float z, float w);
        
        Quaternion(const Quaternion& q);
        Quaternion(Quaternion&&);
        
        
        void makeConjugate();
        void normalize();
		void scale(float val);

        float mag() const;
        
        Vector3 toEulerAngles() const;
        
        
        static Quaternion Slerp(const Quaternion& a, const Quaternion& b);
        static Quaternion Normalize(const Quaternion& q);
        static Quaternion Conjugate(const Quaternion& q);
        static Quaternion Inverse(const Quaternion& q);
        static Quaternion PureQuaternion(const Quaternion& q);




		//Complete all the remaining functions and operators
		//Add the scalar mult operator.

      
        void operator = (const Quaternion& q);

        Quaternion operator - (const Quaternion& q) const;   
        Quaternion operator + (const Quaternion& q) const;
        
        Quaternion operator - (const Vector3& v) const;
        Quaternion operator + (const Vector3& v) const;
            
		Quaternion operator * (const Quaternion& q) const;
		Quaternion operator * (const Vector3& v) const;
        
        Quaternion operator / (const Quaternion& q) const;
        
        void operator += (const Quaternion& q);
        void operator -= (const Quaternion& q);
        
        void operator += (const Vector3& v);
        void operator -= (const Vector3& v);
        
        void operator *= (const Quaternion& q); 
		void operator *= (const Vector3& v);

		void operator /= (const Quaternion& q);
        
        
        bool operator == (const Quaternion& q) const;
        bool operator != (const Quaternion& q) const;
        
        Quaternion operator - () const;

		friend std::ostream& operator << (std::ostream&, const Quaternion& q);
	};





}