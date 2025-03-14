#include <math.h>
#include "library/library.h"

inline struct SmlQuat smlQuat(float *const p_array) {
	return (struct SmlQuat) { p_array[0], p_array[1], p_array[2], p_array[3] };
}

inline struct SmlVec3 smlVec3(float *const p_array) {
	return (struct SmlVec3) { p_array[0], p_array[1], p_array[2] };
}

inline struct SmlVec2 smlVec2(float *const p_array) {
	return (struct SmlVec2) { p_array[0], p_array[1] };
}

inline struct SmlMat22 smlMat22(float *const array) {
	return (struct SmlMat22) { array[0], array[1], array[2], array[3], };
}

inline struct SmlMat33 smlMat33(float *const p_array) {
	return (struct SmlMat33) { p_array[0], p_array[1], p_array[2], p_array[3], p_array[4], p_array[5], p_array[6], p_array[7], p_array[8] };
}

inline struct SmlMat44 smlMat44(float *const p_array) {
	return (struct SmlMat44) { // Looks perfectly aligned in non-monospace fonts 😅:
		/*		 */ p_array[0], p_array[1], p_array[2], p_array[3],
			/*	*/	p_array[4], p_array[5], p_array[6], p_array[7],
			/*	*/	p_array[8], p_array[9], p_array[10], p_array[11],
			/*	*/	p_array[12], p_array[13], p_array[14], p_array[15]
	};
}

#pragma region `struct SmlVec3` functions.
extern inline float smlVec3Direction2D(float const* p_array) {
	return atan2f(p_array[1], p_array[0]);
}

extern inline float* smlVec3FromAngle2d(float const p_angle, float *const p_vector) {
	p_vector[0] = cosf(p_angle);
	p_vector[1] = sinf(p_angle);
	p_vector[2] = 0;
	return p_vector;
}

extern inline float smlVec3Magnitude(float const *p_vector) {
	return sqrtf(smlVec3MagnitudeSquared(p_vector));
}

extern inline float smlVec3MagnitudeSquared(float const *p_vector) {
#define S(x) x * x
	return S(p_vector[0]) + S(p_vector[1]) + S(p_vector[2]);
#undef S
}

extern inline float smlVec3Dot(float *const p_first, float *const p_second) {
	return p_first[0] * p_second[0] + p_first[1] * p_second[1] + p_first[2] * p_second[2];
}

extern inline float smlVec3NormalizeBatch1(float const *p_vector) {
	float mag = smlVec3MagnitudeSquared(p_vector);
	mag = mag == 0.0 ? 1 : sqrtf(mag);
	return mag;
}

extern inline float* smlVec3Normalize(float const *p_vector, float *p_destination) {
	float mag = smlVec3MagnitudeSquared(p_vector);
	mag = mag == 0.0 ? 1 : sqrtf(mag);

	p_destination[0] = p_vector[0] / mag;
	p_destination[1] = p_vector[1] / mag;
	p_destination[2] = p_vector[2] / mag;

	return p_destination;
}

extern inline float* smlVec3NormalizeBatch2(float const p_mag, float const *p_vector, float *p_destination) {
	p_destination[0] = p_vector[0] / p_mag;
	p_destination[1] = p_vector[1] / p_mag;
	p_destination[2] = p_vector[2] / p_mag;

	return p_destination;
}

extern inline float* smlVec3NormalizeUnsafe(float const *p_vector, float *p_destination) {
	float const mag = smlVec3Magnitude(p_vector);

	p_destination[0] = p_vector[0] / mag;
	p_destination[1] = p_vector[1] / mag;
	p_destination[2] = p_vector[2] / mag;

	return p_destination;
}

extern inline float* smlVec3Scale(float *const p_vector, float const p_scalar, float *p_destination) {
	smlVec3Normalize(p_vector, p_destination);
	return smlVec3Mult(p_vector, p_scalar, p_destination);
}

extern inline float* smlVec3Add(float *const p_first, float *const p_second, float *p_destination) {
	p_destination[0] = p_first[0] + p_second[0];
	p_destination[1] = p_first[1] + p_second[1];
	p_destination[2] = p_first[2] + p_second[2];

	return p_destination;
}

extern inline float* smlVec3Sub(float *const p_first, float *const p_second, float *p_destination) {
	p_destination[0] = p_first[0] - p_second[0];
	p_destination[1] = p_first[1] - p_second[1];
	p_destination[2] = p_first[2] - p_second[2];

	return p_destination;
}

extern inline float* smlVec3Mult(float *const p_first, float const p_scalar, float *p_destination) {
	p_destination[0] = p_scalar * p_first[0];
	p_destination[1] = p_scalar * p_first[1];
	p_destination[2] = p_scalar * p_first[2];

	return p_destination;
}

extern inline float* smlVec3Cross(float *const p_first, float *const p_second, float *p_destination) {
	p_destination[0] = p_first[1] * p_second[2] - p_first[2] * p_second[1];
	p_destination[1] = p_first[2] * p_second[0] - p_first[0] * p_second[2];
	p_destination[2] = p_first[0] * p_second[1] - p_first[1] * p_second[0];

	return p_destination;
}

extern inline float* smlVec3FromAngle3d(float const x, float const y, float const z, float *const p_destination) {
	float const cosPitch = cosf(y);

	p_destination[0] = cosf(x) * cosPitch;
	p_destination[1] = sinf(y);
	p_destination[2] = sinf(x) * cosPitch;

	return p_destination;
}

#pragma endregion
