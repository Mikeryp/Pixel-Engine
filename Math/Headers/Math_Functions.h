#pragma once

#include<math.h>

#include"Constants.h"
#include"Vector.h"

namespace Math {

	float lerp(float start, float end, float percentage);
    float inverse_Lerp(float min, float max, float val);
    float sin_lerp(float start, float end, float percentage);
	
    
	Vector2 lerp_Vec2(const Vector2& start, const Vector2& end, float percentage);
	Vector3 lerp_Vec3(const Vector3& start, const Vector3& end, float percentage);
	Vector4 lerp_Vec4(const Vector4& start, const Vector4& end, float percentage);
    
    Vector2 inverse_Lerp_Vec2(const Vector2& min, const Vector2& max, float val);
    Vector3 inverse_Lerp_Vec3(const Vector3& min, const Vector3& max, float val);
    Vector4 inverse_Lerp_Vec4(const Vector4& min, const Vector4& max, float val);
    
    float map(float val, float min, float max, float maplower, float mapUpper);
    
    
    
    
    // Template functions
    
    template<typename T>
	float clamp(const T& val, const T& min, const T& max) {
		return ((val < min) ? (min) : (val > max ? (max) : (val)) );
	}
    
    
    template<typename T>
    T random(const T& min, const T& max) {
        srand(rand());
        float perc = ((rand() % (int)((1000 + 1) - 0)) + 0) / 1000.0f;
        return (T)(min + (float)((max - min) * perc));
    }
    
}
