#include <math.h>

#include "ifs.h"
#include "library/sml.h"

inline float smlMat44Determinant(struct SmlMat44 const *const p_matrix) {
	return
		(p_matrix->r22 * (
			(p_matrix->r33 * ((p_matrix->r44 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r43))) -
			(p_matrix->r34 * ((p_matrix->r43 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r42))) +
			(p_matrix->r24 * ((p_matrix->r43 * p_matrix->r43) - (p_matrix->r44 * p_matrix->r42))))) -
		(p_matrix->r23 * (
			(p_matrix->r32 * ((p_matrix->r44 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r43))) -
			(p_matrix->r34 * ((p_matrix->r42 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r41))) +
			(p_matrix->r24 * ((p_matrix->r42 * p_matrix->r43) - (p_matrix->r44 * p_matrix->r41))))) +
		(p_matrix->r24 * (
			(p_matrix->r32 * ((p_matrix->r43 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r42))) -
			(p_matrix->r33 * ((p_matrix->r42 * p_matrix->r44) - (p_matrix->r34 * p_matrix->r41))) +
			(p_matrix->r24 * ((p_matrix->r42 * p_matrix->r42) - (p_matrix->r43 * p_matrix->r41))))) -
		(p_matrix->r14 * (
			(p_matrix->r32 * ((p_matrix->r43 * p_matrix->r43) - (p_matrix->r44 * p_matrix->r42))) -
			(p_matrix->r33 * ((p_matrix->r42 * p_matrix->r43) - (p_matrix->r44 * p_matrix->r41))) +
			(p_matrix->r34 * ((p_matrix->r42 * p_matrix->r42) - (p_matrix->r43 * p_matrix->r41)))));
}

inline struct SmlMat44* smlMat44AdjugateSame(struct SmlMat44 *const p_matrix) {
	struct SmlMat44 cof;
	smlMat44Cofactors(p_matrix, &cof);
	smlMat44SwapMajorityToNew(&cof, p_matrix);
	return p_matrix;
}

inline struct SmlMat44* smlMat44SwapMajority(struct SmlMat44 *const p_matrix) {
	float temp;

	temp = p_matrix->r12;  p_matrix->r12 = p_matrix->r21;  p_matrix->r21 = temp;
	temp = p_matrix->r13;  p_matrix->r13 = p_matrix->r31;  p_matrix->r31 = temp;
	temp = p_matrix->r14;  p_matrix->r14 = p_matrix->r41;   p_matrix->r41 = temp;

	temp = p_matrix->r23;  p_matrix->r23 = p_matrix->r32;  p_matrix->r32 = temp;
	temp = p_matrix->r24;  p_matrix->r24 = p_matrix->r42;  p_matrix->r42 = temp;

	temp = p_matrix->r34;  p_matrix->r34 = p_matrix->r43;  p_matrix->r43 = temp;

	return p_matrix;
}

inline struct SmlMat44* smlMat44Identity(struct SmlMat44 *const p_destination) {
	p_destination->r11 = 1;
	p_destination->r12 = 0;
	p_destination->r13 = 0;
	p_destination->r14 = 0;
	p_destination->r21 = 0;
	p_destination->r22 = 1;
	p_destination->r23 = 0;
	p_destination->r24 = 0;
	p_destination->r31 = 0;
	p_destination->r32 = 0;
	p_destination->r33 = 1;
	p_destination->r34 = 0;
	p_destination->r41 = 0;
	p_destination->r42 = 0;
	p_destination->r43 = 0;
	p_destination->r44 = 1;

	return p_destination;
}

inline struct SmlMat44* smlMat44Scale(struct SmlMat44 *const p_matrix, struct SmlVec3 *const p_scale) {
	p_matrix->r11 *= p_scale->x;
	p_matrix->r12 *= p_scale->x;
	p_matrix->r13 *= p_scale->x;
	p_matrix->r14 *= p_scale->x;

	p_matrix->r21 *= p_scale->y;
	p_matrix->r22 *= p_scale->y;
	p_matrix->r23 *= p_scale->y;
	p_matrix->r24 *= p_scale->y;

	p_matrix->r31 *= p_scale->z;
	p_matrix->r32 *= p_scale->z;
	p_matrix->r33 *= p_scale->z;
	p_matrix->r34 *= p_scale->z;

	return p_matrix;
}

inline float smlMat44Invert(struct SmlMat44 const *const p_matrix, struct SmlMat44 *const p_destination) {
	float const det = smlMat44Determinant(p_matrix);

	ifu(det == 0.0f) {

		return 0.0f;

	}

	smlMat44InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);

	return det;
}

inline struct SmlMat44* smlMat44Adjugate(struct SmlMat44 *const p_matrix, struct SmlMat44 *const p_destination) {
	smlMat44Cofactors(p_matrix, p_destination);
	smlMat44SwapMajority(p_destination);
	return p_destination;
}

inline float smlMat44InvertUnchecked(struct SmlMat44 const *const p_matrix, struct SmlMat44 *const p_destination) {
	float const det = smlMat44Determinant(p_matrix);
	smlMat44InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);
	return det;
}

inline struct SmlMat44* smlMat44Copy(struct SmlMat44 const *const p_matrix, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_matrix->r11;
	p_destination->r12 = p_matrix->r12;
	p_destination->r13 = p_matrix->r13;
	p_destination->r14 = p_matrix->r14;
	p_destination->r21 = p_matrix->r21;
	p_destination->r22 = p_matrix->r22;
	p_destination->r23 = p_matrix->r23;
	p_destination->r24 = p_matrix->r24;
	p_destination->r31 = p_matrix->r31;
	p_destination->r32 = p_matrix->r32;
	p_destination->r33 = p_matrix->r33;
	p_destination->r34 = p_matrix->r34;
	p_destination->r41 = p_matrix->r41;
	p_destination->r42 = p_matrix->r42;
	p_destination->r43 = p_matrix->r43;
	p_destination->r44 = p_matrix->r44;

	return p_destination;
}

inline struct SmlMat44* smlMat44Cofactors(struct SmlMat44 const* const p_matrix, struct SmlMat44 *const p_destination) {
	// Without parenthesis everywhere, expressions go BEHIND the `=`!
	p_destination->r11 = (p_matrix->r22 * (p_matrix->r33 * p_matrix->r44 - p_matrix->r34 * p_matrix->r43) -
						  p_matrix->r23 * (p_matrix->r32 * p_matrix->r44 - p_matrix->r34 * p_matrix->r42) +
						  p_matrix->r24 * (p_matrix->r32 * p_matrix->r43 - p_matrix->r33 * p_matrix->r42));
	p_destination->r12 = -(p_matrix->r12 * (p_matrix->r33 * p_matrix->r44 - p_matrix->r34 * p_matrix->r43) -
						  p_matrix->r13 * (p_matrix->r32 * p_matrix->r44 - p_matrix->r34 * p_matrix->r42) +
						  p_matrix->r14 * (p_matrix->r32 * p_matrix->r43 - p_matrix->r33 * p_matrix->r42));
	p_destination->r13 = (p_matrix->r12 * (p_matrix->r23 * p_matrix->r44 - p_matrix->r24 * p_matrix->r43) -
						  p_matrix->r13 * (p_matrix->r22 * p_matrix->r44 - p_matrix->r24 * p_matrix->r42) +
						  p_matrix->r14 * (p_matrix->r22 * p_matrix->r43 - p_matrix->r23 * p_matrix->r42));
	p_destination->r14 = -(p_matrix->r12 * (p_matrix->r23 * p_matrix->r34 - p_matrix->r24 * p_matrix->r33) -
						   p_matrix->r13 * (p_matrix->r22 * p_matrix->r34 - p_matrix->r24 * p_matrix->r32) +
						   p_matrix->r14 * (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32));

	p_destination->r21 = -(p_matrix->r21 * (p_matrix->r33 * p_matrix->r44 - p_matrix->r34 * p_matrix->r43) -
						   p_matrix->r23 * (p_matrix->r31 * p_matrix->r44 - p_matrix->r34 * p_matrix->r41) +
						   p_matrix->r24 * (p_matrix->r31 * p_matrix->r43 - p_matrix->r33 * p_matrix->r41));
	p_destination->r22 = (p_matrix->r11 * (p_matrix->r33 * p_matrix->r44 - p_matrix->r34 * p_matrix->r43) -
						  p_matrix->r13 * (p_matrix->r31 * p_matrix->r44 - p_matrix->r34 * p_matrix->r41) +
						  p_matrix->r14 * (p_matrix->r31 * p_matrix->r43 - p_matrix->r33 * p_matrix->r41));
	p_destination->r23 = -(p_matrix->r11 * (p_matrix->r23 * p_matrix->r44 - p_matrix->r24 * p_matrix->r43) -
						   p_matrix->r12 * (p_matrix->r21 * p_matrix->r44 - p_matrix->r24 * p_matrix->r41) +
						   p_matrix->r14 * (p_matrix->r21 * p_matrix->r43 - p_matrix->r23 * p_matrix->r41));
	p_destination->r24 = (p_matrix->r11 * (p_matrix->r23 * p_matrix->r34 - p_matrix->r24 * p_matrix->r33) -
						  p_matrix->r12 * (p_matrix->r21 * p_matrix->r34 - p_matrix->r24 * p_matrix->r31) +
						  p_matrix->r13 * (p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31));

	p_destination->r31 = (p_matrix->r21 * (p_matrix->r32 * p_matrix->r44 - p_matrix->r34 * p_matrix->r42) -
						  p_matrix->r22 * (p_matrix->r31 * p_matrix->r44 - p_matrix->r34 * p_matrix->r41) +
						  p_matrix->r24 * (p_matrix->r31 * p_matrix->r42 - p_matrix->r32 * p_matrix->r41));
	p_destination->r32 = -(p_matrix->r11 * (p_matrix->r32 * p_matrix->r44 - p_matrix->r34 * p_matrix->r42) -
						   p_matrix->r12 * (p_matrix->r31 * p_matrix->r44 - p_matrix->r34 * p_matrix->r41) +
						   p_matrix->r14 * (p_matrix->r31 * p_matrix->r42 - p_matrix->r32 * p_matrix->r41));
	p_destination->r33 = (p_matrix->r11 * (p_matrix->r22 * p_matrix->r44 - p_matrix->r24 * p_matrix->r42) -
						  p_matrix->r12 * (p_matrix->r21 * p_matrix->r44 - p_matrix->r24 * p_matrix->r41) +
						  p_matrix->r14 * (p_matrix->r21 * p_matrix->r42 - p_matrix->r22 * p_matrix->r41));
	p_destination->r34 = -(p_matrix->r11 * (p_matrix->r22 * p_matrix->r34 - p_matrix->r23 * p_matrix->r32) -
						   p_matrix->r12 * (p_matrix->r21 * p_matrix->r34 - p_matrix->r23 * p_matrix->r31) +
						   p_matrix->r13 * (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31));

	p_destination->r41 = -(p_matrix->r21 * (p_matrix->r32 * p_matrix->r43 - p_matrix->r33 * p_matrix->r42) -
						   p_matrix->r22 * (p_matrix->r31 * p_matrix->r43 - p_matrix->r33 * p_matrix->r41) +
						   p_matrix->r23 * (p_matrix->r31 * p_matrix->r42 - p_matrix->r32 * p_matrix->r41));
	p_destination->r42 = (p_matrix->r11 * (p_matrix->r32 * p_matrix->r43 - p_matrix->r33 * p_matrix->r42) -
						  p_matrix->r12 * (p_matrix->r31 * p_matrix->r43 - p_matrix->r33 * p_matrix->r41) +
						  p_matrix->r13 * (p_matrix->r31 * p_matrix->r42 - p_matrix->r32 * p_matrix->r41));
	p_destination->r43 = -(p_matrix->r11 * (p_matrix->r22 * p_matrix->r43 - p_matrix->r23 * p_matrix->r42) -
						   p_matrix->r12 * (p_matrix->r21 * p_matrix->r43 - p_matrix->r23 * p_matrix->r41) +
						   p_matrix->r13 * (p_matrix->r21 * p_matrix->r42 - p_matrix->r22 * p_matrix->r41));
	p_destination->r44 = (p_matrix->r11 * (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32) -
						  p_matrix->r12 * (p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31) +
						  p_matrix->r13 * (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31));

	return p_destination;
}

inline struct SmlMat44* smlMat44SwapMajorityToNew(struct SmlMat44 *const p_matrix, struct SmlMat44 *const p_destination) {
	smlMat44Copy(p_matrix, p_destination);
	smlMat44SwapMajority(p_destination);
	return p_destination;
}

inline struct SmlMat44* smlMat44AddScalar(struct SmlMat44 const *const p_matrix, float const p_scalar, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_matrix->r11 + p_scalar;
	p_destination->r12 = p_matrix->r12 + p_scalar;
	p_destination->r13 = p_matrix->r13 + p_scalar;
	p_destination->r14 = p_matrix->r14 + p_scalar;
	p_destination->r21 = p_matrix->r21 + p_scalar;
	p_destination->r22 = p_matrix->r22 + p_scalar;
	p_destination->r23 = p_matrix->r23 + p_scalar;
	p_destination->r24 = p_matrix->r24 + p_scalar;
	p_destination->r31 = p_matrix->r31 + p_scalar;
	p_destination->r32 = p_matrix->r32 + p_scalar;
	p_destination->r33 = p_matrix->r33 + p_scalar;
	p_destination->r34 = p_matrix->r34 + p_scalar;
	p_destination->r41 = p_matrix->r41 + p_scalar;
	p_destination->r42 = p_matrix->r42 + p_scalar;
	p_destination->r43 = p_matrix->r43 + p_scalar;
	p_destination->r44 = p_matrix->r44 + p_scalar;

	return p_destination;
}

inline struct SmlMat44* smlMat44DivScalar(struct SmlMat44 const *const p_matrix, float const p_scalar, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_matrix->r11 / p_scalar;
	p_destination->r12 = p_matrix->r12 / p_scalar;
	p_destination->r13 = p_matrix->r13 / p_scalar;
	p_destination->r14 = p_matrix->r14 / p_scalar;
	p_destination->r21 = p_matrix->r21 / p_scalar;
	p_destination->r22 = p_matrix->r22 / p_scalar;
	p_destination->r23 = p_matrix->r23 / p_scalar;
	p_destination->r24 = p_matrix->r24 / p_scalar;
	p_destination->r31 = p_matrix->r31 / p_scalar;
	p_destination->r32 = p_matrix->r32 / p_scalar;
	p_destination->r33 = p_matrix->r33 / p_scalar;
	p_destination->r34 = p_matrix->r34 / p_scalar;
	p_destination->r41 = p_matrix->r41 / p_scalar;
	p_destination->r42 = p_matrix->r42 / p_scalar;
	p_destination->r43 = p_matrix->r43 / p_scalar;
	p_destination->r44 = p_matrix->r44 / p_scalar;

	return p_destination;
}

inline struct SmlMat44* smlMat44SubScalar(struct SmlMat44 const *const p_matrix, float const p_scalar, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_matrix->r11 - p_scalar;
	p_destination->r12 = p_matrix->r12 - p_scalar;
	p_destination->r13 = p_matrix->r13 - p_scalar;
	p_destination->r14 = p_matrix->r14 - p_scalar;
	p_destination->r21 = p_matrix->r21 - p_scalar;
	p_destination->r22 = p_matrix->r22 - p_scalar;
	p_destination->r23 = p_matrix->r23 - p_scalar;
	p_destination->r24 = p_matrix->r24 - p_scalar;
	p_destination->r31 = p_matrix->r31 - p_scalar;
	p_destination->r32 = p_matrix->r32 - p_scalar;
	p_destination->r33 = p_matrix->r33 - p_scalar;
	p_destination->r34 = p_matrix->r34 - p_scalar;
	p_destination->r41 = p_matrix->r41 - p_scalar;
	p_destination->r42 = p_matrix->r42 - p_scalar;
	p_destination->r43 = p_matrix->r43 - p_scalar;
	p_destination->r44 = p_matrix->r44 - p_scalar;

	return p_destination;
}

inline struct SmlMat44* smlMat44MultScalar(struct SmlMat44 const *const p_matrix, float const p_scalar, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_matrix->r11 * p_scalar;
	p_destination->r12 = p_matrix->r12 * p_scalar;
	p_destination->r13 = p_matrix->r13 * p_scalar;
	p_destination->r14 = p_matrix->r14 * p_scalar;
	p_destination->r21 = p_matrix->r21 * p_scalar;
	p_destination->r22 = p_matrix->r22 * p_scalar;
	p_destination->r23 = p_matrix->r23 * p_scalar;
	p_destination->r24 = p_matrix->r24 * p_scalar;
	p_destination->r31 = p_matrix->r31 * p_scalar;
	p_destination->r32 = p_matrix->r32 * p_scalar;
	p_destination->r33 = p_matrix->r33 * p_scalar;
	p_destination->r34 = p_matrix->r34 * p_scalar;
	p_destination->r41 = p_matrix->r41 * p_scalar;
	p_destination->r42 = p_matrix->r42 * p_scalar;
	p_destination->r43 = p_matrix->r43 * p_scalar;
	p_destination->r44 = p_matrix->r44 * p_scalar;

	return p_destination;
}

inline struct SmlMat44* smlMat44Add(struct SmlMat44 const *const p_first, struct SmlMat44 const *const p_second, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_first->r11 + p_second->r11;
	p_destination->r12 = p_first->r12 + p_second->r12;
	p_destination->r13 = p_first->r13 + p_second->r13;
	p_destination->r14 = p_first->r14 + p_second->r14;
	p_destination->r21 = p_first->r21 + p_second->r21;
	p_destination->r22 = p_first->r22 + p_second->r22;
	p_destination->r23 = p_first->r23 + p_second->r23;
	p_destination->r24 = p_first->r24 + p_second->r24;
	p_destination->r31 = p_first->r31 + p_second->r31;
	p_destination->r32 = p_first->r32 + p_second->r32;
	p_destination->r33 = p_first->r33 + p_second->r33;
	p_destination->r34 = p_first->r34 + p_second->r34;
	p_destination->r41 = p_first->r41 + p_second->r41;
	p_destination->r42 = p_first->r42 + p_second->r42;
	p_destination->r43 = p_first->r43 + p_second->r43;
	p_destination->r44 = p_first->r44 + p_second->r44;

	return p_destination;
}

inline struct SmlMat44* smlMat44Sub(struct SmlMat44 const *const p_first, struct SmlMat44 const *const p_second, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_first->r11 - p_second->r11;
	p_destination->r12 = p_first->r12 - p_second->r12;
	p_destination->r13 = p_first->r13 - p_second->r13;
	p_destination->r14 = p_first->r14 - p_second->r14;
	p_destination->r21 = p_first->r21 - p_second->r21;
	p_destination->r22 = p_first->r22 - p_second->r22;
	p_destination->r23 = p_first->r23 - p_second->r23;
	p_destination->r24 = p_first->r24 - p_second->r24;
	p_destination->r31 = p_first->r31 - p_second->r31;
	p_destination->r32 = p_first->r32 - p_second->r32;
	p_destination->r33 = p_first->r33 - p_second->r33;
	p_destination->r34 = p_first->r34 - p_second->r34;
	p_destination->r41 = p_first->r41 - p_second->r41;
	p_destination->r42 = p_first->r42 - p_second->r42;
	p_destination->r43 = p_first->r43 - p_second->r43;
	p_destination->r44 = p_first->r44 - p_second->r44;

	return p_destination;
}

inline struct SmlMat44* smlMat44Mult(struct SmlMat44 const *const p_first, struct SmlMat44 const *const p_second, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11 + p_first->r12 * p_second->r21 + p_first->r13 * p_second->r31 + p_first->r14 * p_second->r41;
	p_destination->r12 = p_first->r11 * p_second->r12 + p_first->r12 * p_second->r22 + p_first->r13 * p_second->r32 + p_first->r14 * p_second->r42;
	p_destination->r13 = p_first->r11 * p_second->r13 + p_first->r12 * p_second->r23 + p_first->r13 * p_second->r33 + p_first->r14 * p_second->r43;
	p_destination->r14 = p_first->r11 * p_second->r14 + p_first->r12 * p_second->r24 + p_first->r13 * p_second->r34 + p_first->r14 * p_second->r44;

	p_destination->r21 = p_first->r21 * p_second->r11 + p_first->r22 * p_second->r21 + p_first->r23 * p_second->r31 + p_first->r24 * p_second->r41;
	p_destination->r22 = p_first->r21 * p_second->r12 + p_first->r22 * p_second->r22 + p_first->r23 * p_second->r32 + p_first->r24 * p_second->r42;
	p_destination->r23 = p_first->r21 * p_second->r13 + p_first->r22 * p_second->r23 + p_first->r23 * p_second->r33 + p_first->r24 * p_second->r43;
	p_destination->r24 = p_first->r21 * p_second->r14 + p_first->r22 * p_second->r24 + p_first->r23 * p_second->r34 + p_first->r24 * p_second->r44;

	p_destination->r31 = p_first->r31 * p_second->r11 + p_first->r32 * p_second->r21 + p_first->r33 * p_second->r31 + p_first->r34 * p_second->r41;
	p_destination->r32 = p_first->r31 * p_second->r12 + p_first->r32 * p_second->r22 + p_first->r33 * p_second->r32 + p_first->r34 * p_second->r42;
	p_destination->r33 = p_first->r31 * p_second->r13 + p_first->r32 * p_second->r23 + p_first->r33 * p_second->r33 + p_first->r34 * p_second->r43;
	p_destination->r34 = p_first->r31 * p_second->r14 + p_first->r32 * p_second->r24 + p_first->r33 * p_second->r34 + p_first->r34 * p_second->r44;

	p_destination->r41 = p_first->r41 * p_second->r11 + p_first->r42 * p_second->r21 + p_first->r43 * p_second->r31 + p_first->r44 * p_second->r41;
	p_destination->r42 = p_first->r41 * p_second->r12 + p_first->r42 * p_second->r22 + p_first->r43 * p_second->r32 + p_first->r44 * p_second->r42;
	p_destination->r43 = p_first->r41 * p_second->r13 + p_first->r42 * p_second->r23 + p_first->r43 * p_second->r33 + p_first->r44 * p_second->r43;
	p_destination->r44 = p_first->r41 * p_second->r14 + p_first->r42 * p_second->r24 + p_first->r43 * p_second->r34 + p_first->r44 * p_second->r44;

	return p_destination;
}

inline struct SmlQuat* smlMat44MultVec4(struct SmlMat44 const *const p_matrix, struct SmlQuat const *const p_vector4, struct SmlQuat *const p_destination) {
	float const x = p_vector4->x;
	float const y = p_vector4->y;
	float const z = p_vector4->z;
	float const w = p_vector4->w;

	p_destination->x = p_matrix->r11 * x + p_matrix->r12 * y + p_matrix->r13 * z + p_matrix->r14 * w;
	p_destination->y = p_matrix->r21 * x + p_matrix->r22 * y + p_matrix->r23 * z + p_matrix->r24 * w;
	p_destination->z = p_matrix->r31 * x + p_matrix->r32 * y + p_matrix->r33 * z + p_matrix->r34 * w;
	p_destination->w = p_matrix->r41 * x + p_matrix->r42 * y + p_matrix->r43 * z + p_matrix->r44 * w;

	return p_destination;
}

inline struct SmlMat44* smlMat44DivMembers(struct SmlMat44 const *const p_first, struct SmlMat44 const *const p_second, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_first->r11 / p_second->r11;
	p_destination->r12 = p_first->r12 / p_second->r12;
	p_destination->r13 = p_first->r13 / p_second->r13;
	p_destination->r14 = p_first->r14 / p_second->r14;
	p_destination->r21 = p_first->r21 / p_second->r21;
	p_destination->r22 = p_first->r22 / p_second->r22;
	p_destination->r23 = p_first->r23 / p_second->r23;
	p_destination->r24 = p_first->r24 / p_second->r24;
	p_destination->r31 = p_first->r31 / p_second->r31;
	p_destination->r32 = p_first->r32 / p_second->r32;
	p_destination->r33 = p_first->r33 / p_second->r33;
	p_destination->r34 = p_first->r34 / p_second->r34;
	p_destination->r41 = p_first->r41 / p_second->r41;
	p_destination->r42 = p_first->r42 / p_second->r42;
	p_destination->r43 = p_first->r43 / p_second->r43;
	p_destination->r44 = p_first->r44 / p_second->r44;

	return p_destination;
}

inline struct SmlMat44* smlMat44MultMembers(struct SmlMat44 const *const p_first, struct SmlMat44 const *const p_second, struct SmlMat44 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11;
	p_destination->r12 = p_first->r12 * p_second->r12;
	p_destination->r13 = p_first->r13 * p_second->r13;
	p_destination->r14 = p_first->r14 * p_second->r14;
	p_destination->r21 = p_first->r21 * p_second->r21;
	p_destination->r22 = p_first->r22 * p_second->r22;
	p_destination->r23 = p_first->r23 * p_second->r23;
	p_destination->r24 = p_first->r24 * p_second->r24;
	p_destination->r31 = p_first->r31 * p_second->r31;
	p_destination->r32 = p_first->r32 * p_second->r32;
	p_destination->r33 = p_first->r33 * p_second->r33;
	p_destination->r34 = p_first->r34 * p_second->r34;
	p_destination->r41 = p_first->r41 * p_second->r41;
	p_destination->r42 = p_first->r42 * p_second->r42;
	p_destination->r43 = p_first->r43 * p_second->r43;
	p_destination->r44 = p_first->r44 * p_second->r44;

	return p_destination;
}

inline struct SmlMat44* smlMat44InvertGivenInvertedDeterminant(struct SmlMat44 const *const p_matrix, struct SmlMat44 *const p_destination, float p_invertedDeterminant) {
	struct SmlMat44 cof;
	smlMat44SwapMajorityToNew(smlMat44Cofactors(p_matrix, &cof), p_destination);

	for (int i = 0; i < 16; ++i)
		p_destination->one[i] *= p_invertedDeterminant;

	return p_destination;
}
