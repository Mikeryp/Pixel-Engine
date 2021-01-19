#include"../Headers/Math_Functions.h"

namespace Math {

	float lerp(float min, float max, float percentage) {
		return min + (max - min) * percentage;
	}

	float sin_lerp(float min, float max, float percentage) {
		return map((float)sin((float)PX_toRadians(270 - 180 * percentage)), -1, 1, 0, 1) * (max - min);
	}

	float map(float val, float min, float max, float lowerRange, float UpperRange) {
		return (val - min) / (max - min) * (UpperRange - lowerRange) + lowerRange;
	}

	float inverseLerp(float min, float max, float val) {
		return (val - min) / (max - min);
	}



	Vector2 lerpVec2(const Vector2& start, const Vector2& end, float percentage) {
		return Vector2(lerp(start.x, end.x, percentage), lerp(start.y, end.y, percentage));
	}
	Vector3 lerpVec3(const Vector3& start, const Vector3& end, float percentage) {
		return Vector3(lerp(start.x, end.x, percentage), lerp(start.y, end.y, percentage), lerp(start.z,end.z, percentage));
	}
	Vector4 lerpVec4(const Vector4& start, const Vector4& end, float percentage) {
		return Vector4(lerp(start.x, end.x, percentage), lerp(start.y, end.y, percentage), lerp(start.z, end.z, percentage), lerp(start.w, end.w, percentage));
	}
}