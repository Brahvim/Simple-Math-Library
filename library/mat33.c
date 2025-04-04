#include <math.h>

#include "internals/ifs.h"
#include "library/library.h"

inline float smlMat33Trace(struct SmlMat33 const *const p_matrix) {
	return p_matrix->r11 + p_matrix->r22 + p_matrix->r33;
}

inline char smlMat33IsSymmetric(struct SmlMat33 const *const p_matrix) {
	return (p_matrix->r12 == p_matrix->r21 &&
			p_matrix->r13 == p_matrix->r31 &&
			p_matrix->r23 == p_matrix->r32);
}

inline float smlMat33Determinant(struct SmlMat33 const *const p_matrix) {
	return p_matrix->r11 * (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32)
		- p_matrix->r12 * (p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31)
		+ p_matrix->r13 * (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31);
}

inline struct SmlMat33* smlMat33Identity(struct SmlMat33 *const p_destination) {
	p_destination->r11 = 1;
	p_destination->r12 = 0;
	p_destination->r13 = 0;
	p_destination->r21 = 0;
	p_destination->r22 = 1;
	p_destination->r23 = 0;
	p_destination->r31 = 0;
	p_destination->r32 = 0;
	p_destination->r33 = 1;

	return p_destination;
}

inline float smlMat33Invert(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	float const det = smlMat33Determinant(p_matrix);

	ifu(det == 0.0f) {

		return 0.0f;

	}

	smlMat33InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);

	return det;
}

inline float smlMat33InvertUnchecked(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	float const det = smlMat33Determinant(p_matrix);
	smlMat33InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);
	return det;
}

inline struct SmlMat33* smlMat33Cofactors(struct SmlMat33 const* const p_matrix, struct SmlMat33 *const p_destination) {
	p_destination->r11 = (p_matrix->r22 * p_matrix->r33 - p_matrix->r23 * p_matrix->r32);
	p_destination->r12 = -(p_matrix->r12 * p_matrix->r33 - p_matrix->r13 * p_matrix->r32);
	p_destination->r13 = (p_matrix->r12 * p_matrix->r23 - p_matrix->r13 * p_matrix->r22);
	p_destination->r21 = -(p_matrix->r21 * p_matrix->r33 - p_matrix->r23 * p_matrix->r31);
	p_destination->r22 = (p_matrix->r11 * p_matrix->r33 - p_matrix->r13 * p_matrix->r31);
	p_destination->r23 = -(p_matrix->r11 * p_matrix->r23 - p_matrix->r13 * p_matrix->r21);
	p_destination->r31 = (p_matrix->r21 * p_matrix->r32 - p_matrix->r22 * p_matrix->r31);
	p_destination->r32 = -(p_matrix->r11 * p_matrix->r32 - p_matrix->r12 * p_matrix->r31);
	p_destination->r33 = (p_matrix->r11 * p_matrix->r22 - p_matrix->r12 * p_matrix->r21);

	return p_destination;
}

inline struct SmlMat33* smlMat33Transpose(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11;
	p_destination->r12 = p_matrix->r21;
	p_destination->r13 = p_matrix->r31;
	p_destination->r21 = p_matrix->r12;
	p_destination->r22 = p_matrix->r22;
	p_destination->r23 = p_matrix->r32;
	p_destination->r31 = p_matrix->r13;
	p_destination->r32 = p_matrix->r23;
	p_destination->r33 = p_matrix->r33;
	return p_destination;
}

struct SmlMat33* smlMat33AddScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 + p_scalar;
	p_destination->r12 = p_matrix->r12 + p_scalar;
	p_destination->r13 = p_matrix->r13 + p_scalar;
	p_destination->r21 = p_matrix->r21 + p_scalar;
	p_destination->r22 = p_matrix->r22 + p_scalar;
	p_destination->r23 = p_matrix->r23 + p_scalar;
	p_destination->r31 = p_matrix->r31 + p_scalar;
	p_destination->r32 = p_matrix->r32 + p_scalar;
	p_destination->r33 = p_matrix->r33 + p_scalar;

	return p_destination;
}

struct SmlMat33* smlMat33DivScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 / p_scalar;
	p_destination->r12 = p_matrix->r12 / p_scalar;
	p_destination->r13 = p_matrix->r13 / p_scalar;
	p_destination->r21 = p_matrix->r21 / p_scalar;
	p_destination->r22 = p_matrix->r22 / p_scalar;
	p_destination->r23 = p_matrix->r23 / p_scalar;
	p_destination->r31 = p_matrix->r31 / p_scalar;
	p_destination->r32 = p_matrix->r32 / p_scalar;
	p_destination->r33 = p_matrix->r33 / p_scalar;

	return p_destination;
}

struct SmlMat33* smlMat33SubScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 - p_scalar;
	p_destination->r12 = p_matrix->r12 - p_scalar;
	p_destination->r13 = p_matrix->r13 - p_scalar;
	p_destination->r21 = p_matrix->r21 - p_scalar;
	p_destination->r22 = p_matrix->r22 - p_scalar;
	p_destination->r23 = p_matrix->r23 - p_scalar;
	p_destination->r31 = p_matrix->r31 - p_scalar;
	p_destination->r32 = p_matrix->r32 - p_scalar;
	p_destination->r33 = p_matrix->r33 - p_scalar;

	return p_destination;
}

struct SmlMat33* smlMat33MultScalar(struct SmlMat33 const *const p_matrix, float const p_scalar, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_matrix->r11 * p_scalar;
	p_destination->r12 = p_matrix->r12 * p_scalar;
	p_destination->r13 = p_matrix->r13 * p_scalar;
	p_destination->r21 = p_matrix->r21 * p_scalar;
	p_destination->r22 = p_matrix->r22 * p_scalar;
	p_destination->r23 = p_matrix->r23 * p_scalar;
	p_destination->r31 = p_matrix->r31 * p_scalar;
	p_destination->r32 = p_matrix->r32 * p_scalar;
	p_destination->r33 = p_matrix->r33 * p_scalar;

	return p_destination;
}

inline struct SmlMat33* smlMat33Add(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 + p_second->r11;
	p_destination->r12 = p_first->r12 + p_second->r12;
	p_destination->r13 = p_first->r13 + p_second->r13;
	p_destination->r21 = p_first->r21 + p_second->r21;
	p_destination->r22 = p_first->r22 + p_second->r22;
	p_destination->r23 = p_first->r23 + p_second->r23;
	p_destination->r31 = p_first->r31 + p_second->r31;
	p_destination->r32 = p_first->r32 + p_second->r32;
	p_destination->r33 = p_first->r33 + p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33Sub(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 - p_second->r11;
	p_destination->r12 = p_first->r12 - p_second->r12;
	p_destination->r13 = p_first->r13 - p_second->r13;
	p_destination->r21 = p_first->r21 - p_second->r21;
	p_destination->r22 = p_first->r22 - p_second->r22;
	p_destination->r23 = p_first->r23 - p_second->r23;
	p_destination->r31 = p_first->r31 - p_second->r31;
	p_destination->r32 = p_first->r32 - p_second->r32;
	p_destination->r33 = p_first->r33 - p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33Mult(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11 + p_first->r12 * p_second->r21 + p_first->r13 * p_second->r31;
	p_destination->r12 = p_first->r11 * p_second->r12 + p_first->r12 * p_second->r22 + p_first->r13 * p_second->r32;
	p_destination->r13 = p_first->r11 * p_second->r13 + p_first->r12 * p_second->r23 + p_first->r13 * p_second->r33;
	p_destination->r21 = p_first->r21 * p_second->r11 + p_first->r22 * p_second->r21 + p_first->r23 * p_second->r31;
	p_destination->r22 = p_first->r21 * p_second->r12 + p_first->r22 * p_second->r22 + p_first->r23 * p_second->r32;
	p_destination->r23 = p_first->r21 * p_second->r13 + p_first->r22 * p_second->r23 + p_first->r23 * p_second->r33;
	p_destination->r31 = p_first->r31 * p_second->r11 + p_first->r32 * p_second->r21 + p_first->r33 * p_second->r31;
	p_destination->r32 = p_first->r31 * p_second->r12 + p_first->r32 * p_second->r22 + p_first->r33 * p_second->r32;
	p_destination->r33 = p_first->r31 * p_second->r13 + p_first->r32 * p_second->r23 + p_first->r33 * p_second->r33;

	return p_destination;
}

inline struct SmlVec3* smlMat33MultVec3(struct SmlMat33 const *const p_matrix, struct SmlVec3 const *const p_vector, struct SmlVec3 *const p_destination) {
	p_destination->x = p_matrix->r11 * p_vector->x + p_matrix->r12 * p_vector->y + p_matrix->r13 * p_vector->z;
	p_destination->y = p_matrix->r21 * p_vector->x + p_matrix->r22 * p_vector->y + p_matrix->r23 * p_vector->z;
	p_destination->z = p_matrix->r31 * p_vector->x + p_matrix->r32 * p_vector->y + p_matrix->r33 * p_vector->z;
	return p_destination;
}

inline struct SmlMat33* smlMat33DivMembers(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 / p_second->r11;
	p_destination->r12 = p_first->r12 / p_second->r12;
	p_destination->r13 = p_first->r13 / p_second->r13;
	p_destination->r21 = p_first->r21 / p_second->r21;
	p_destination->r22 = p_first->r22 / p_second->r22;
	p_destination->r23 = p_first->r23 / p_second->r23;
	p_destination->r31 = p_first->r31 / p_second->r31;
	p_destination->r32 = p_first->r32 / p_second->r32;
	p_destination->r33 = p_first->r33 / p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33MultMembers(struct SmlMat33 const *const p_first, struct SmlMat33 const *const p_second, struct SmlMat33 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11;
	p_destination->r12 = p_first->r12 * p_second->r12;
	p_destination->r13 = p_first->r13 * p_second->r13;
	p_destination->r21 = p_first->r21 * p_second->r21;
	p_destination->r22 = p_first->r22 * p_second->r22;
	p_destination->r23 = p_first->r23 * p_second->r23;
	p_destination->r31 = p_first->r31 * p_second->r31;
	p_destination->r32 = p_first->r32 * p_second->r32;
	p_destination->r33 = p_first->r33 * p_second->r33;

	return p_destination;
}

inline struct SmlMat33* smlMat33InvertGivenInvertedDeterminant(struct SmlMat33 const *const p_matrix, struct SmlMat33 *const p_destination, float p_invertedDeterminant) {
	p_destination->r11 = p_matrix->r22 * p_invertedDeterminant;
	p_destination->r12 = -p_matrix->r12 * p_invertedDeterminant;
	p_destination->r21 = -p_matrix->r21 * p_invertedDeterminant;
	p_destination->r11 = p_matrix->r11 * p_invertedDeterminant;

	return p_destination;
}
