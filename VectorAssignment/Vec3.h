#pragma once
#include <math.h>

#define DLL_MACRO extern "C" __declspec(dllexport)

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

DLL_MACRO Vec2 v2_add(Vec2 a, Vec2 b) {
	return { a.x + b.x, a.y + b.y };
}

DLL_MACRO Vec2 v2_subtract(Vec2 a, Vec2 b) {
	return { a.x - b.x, a.y - b.y };
}

DLL_MACRO Vec2 v2_scale(Vec2 v, float s) {
	return { v.x * s, v.y * s };
}

DLL_MACRO float v2_magnitude(Vec2 v) {
	return sqrtf(v.x * v.x + v.y * v.y);
}

DLL_MACRO Vec2 v2_normalize(Vec2 v) {
	float mag = v2_magnitude(v);
	if (mag == 0.0f) return { 0, 0 };
	return { v.x / mag, v.y / mag };
}

DLL_MACRO float v2_dot(Vec2 a, Vec2 b) {
	return a.x * b.x + a.y * b.y;
}

DLL_MACRO Vec3 v3_add(Vec3 a, Vec3 b) {
	return { a.x + b.x, a.y + b.y, a.z + b.z };
}

DLL_MACRO Vec3 v3_subtract(Vec3 a, Vec3 b) {
	return { a.x - b.x, a.y - b.y, a.z - b.z };
}

DLL_MACRO Vec3 v3_scale(Vec3 v, float s) {
	return { v.x * s, v.y * s, v.z * s };
}

DLL_MACRO float v3_magnitude(Vec3 v) {
	return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

DLL_MACRO Vec3 v3_normalize(Vec3 v) {
	float mag = v3_magnitude(v);
	if (mag == 0.0f) return { 0, 0, 0 };
	return { v.x / mag, v.y / mag, v.z / mag };
}

DLL_MACRO float v3_dot(Vec3 a, Vec3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

DLL_MACRO Vec3 v3_cross(Vec3 a, Vec3 b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

DLL_MACRO float v3_distance(Vec3 a, Vec3 b) {
	return v3_magnitude(v3_subtract(a, b));
}

DLL_MACRO float v3_distance_sqr(Vec3 a, Vec3 b) {
	Vec3 d = v3_subtract(a, b);
	return d.x * d.x + d.y * d.y + d.z * d.z;
}

DLL_MACRO float v3_angle_between(Vec3 a, Vec3 b) {
	float dot = v3_dot(a, b);
	float mags = v3_magnitude(a) * v3_magnitude(b);
	if (mags == 0.0f) return 0.0f;
	return acosf(dot / mags);
}

DLL_MACRO Vec3 v3_clamp_magnitude(Vec3 v, float maxLength) {
	float mag = v3_magnitude(v);
	if (mag > maxLength) {
		return v3_scale(v3_normalize(v), maxLength);
	}
	return v;
}

DLL_MACRO Vec3 v3_project(Vec3 a, Vec3 b) {
	float denom = v3_dot(b, b);
	if (denom == 0.0f) return { 0, 0, 0 };
	float scale = v3_dot(a, b) / denom;
	return v3_scale(b, scale);
}

DLL_MACRO Vec2 v2_reflect(Vec2 v, Vec2 normal) {
	float dot = v2_dot(v, normal);
	Vec2 scaledNormal = v2_scale(normal, 2.0f * dot);
	return v2_subtract(v, scaledNormal);
}

DLL_MACRO Vec2 v2_lerp(Vec2 a, Vec2 b, float t) {
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t
	};
}

DLL_MACRO Vec3 v3_lerp(Vec3 a, Vec3 b, float t) {
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	};
}