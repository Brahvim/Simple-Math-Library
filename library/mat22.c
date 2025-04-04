#include <math.h>

#include "internals/ifs.h"
#include "library/library.h"

inline float smlMat22Determinant(struct SmlMat22 const *const p_matrix) {
	return (p_matrix->r11 * p_matrix->r22) - (p_matrix->r12 * p_matrix->r21);
}

inline struct SmlMat22* smlMat22Identity(struct SmlMat22 *const p_destination) {
	p_destination->r11 = 1;
	p_destination->r12 = 0;
	p_destination->r21 = 0;
	p_destination->r22 = 1;

	return p_destination;
}

inline float smlMat22Invert(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination) {
	float const det = smlMat22Determinant(p_matrix);

	ifu(det == 0.0f) {

		return 0.0f;

	}

	smlMat22InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);

	return det;
}

inline float smlMat22InvertUnchecked(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination) {
	float const det = smlMat22Determinant(p_matrix);
	smlMat22InvertGivenInvertedDeterminant(p_matrix, p_destination, 1.0f / det);
	return det;
}

inline struct SmlMat22* smlMat22Cofactors(struct SmlMat22 const* const p_matrix, struct SmlMat22 *const p_destination) {
	p_destination->x = p_matrix->w;
	p_destination->y = -p_matrix->z;
	p_destination->z = -p_matrix->y;
	p_destination->w = p_matrix->x;

	return p_destination;
}

struct SmlMat22* smlMat22AddScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 + p_scalar;
	p_destination->r12 = p_matrix->r12 + p_scalar;
	p_destination->r21 = p_matrix->r21 + p_scalar;
	p_destination->r22 = p_matrix->r22 + p_scalar;

	return p_destination;
}

struct SmlMat22* smlMat22DivScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 / p_scalar;
	p_destination->r12 = p_matrix->r12 / p_scalar;
	p_destination->r21 = p_matrix->r21 / p_scalar;
	p_destination->r22 = p_matrix->r22 / p_scalar;

	return p_destination;
}

struct SmlMat22* smlMat22SubScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 - p_scalar;
	p_destination->r12 = p_matrix->r12 - p_scalar;
	p_destination->r21 = p_matrix->r21 - p_scalar;
	p_destination->r22 = p_matrix->r22 - p_scalar;

	return p_destination;
}

struct SmlMat22* smlMat22MultScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 * p_scalar;
	p_destination->r12 = p_matrix->r12 * p_scalar;
	p_destination->r21 = p_matrix->r21 * p_scalar;
	p_destination->r22 = p_matrix->r22 * p_scalar;

	return p_destination;
}

inline struct SmlMat22* smlMat22Add(struct SmlMat22 const *const p_first, struct SmlMat22 const *const p_second, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_first->r11 + p_second->r11;
	p_destination->r12 = p_first->r12 + p_second->r12;
	p_destination->r21 = p_first->r21 + p_second->r21;
	p_destination->r22 = p_first->r22 + p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22Sub(struct SmlMat22 const *const p_first, struct SmlMat22 const *const p_second, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_first->r11 - p_second->r11;
	p_destination->r12 = p_first->r12 - p_second->r12;
	p_destination->r21 = p_first->r21 - p_second->r21;
	p_destination->r22 = p_first->r22 - p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22Mult(struct SmlMat22 const *const p_first, struct SmlMat22 const *const p_second, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11 + p_first->r12 * p_second->r21;
	p_destination->r12 = p_first->r11 * p_second->r12 + p_first->r12 * p_second->r22;
	p_destination->r21 = p_first->r21 * p_second->r11 + p_first->r22 * p_second->r21;
	p_destination->r22 = p_first->r21 * p_second->r12 + p_first->r22 * p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22DivMembers(struct SmlMat22 const *const p_first, struct SmlMat22 const *const p_second, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_first->r11 / p_second->r11;
	p_destination->r12 = p_first->r12 / p_second->r12;
	p_destination->r21 = p_first->r21 / p_second->r21;
	p_destination->r22 = p_first->r22 / p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22MultMembers(struct SmlMat22 const *const p_first, struct SmlMat22 const *const p_second, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_first->r11 * p_second->r11;
	p_destination->r12 = p_first->r12 * p_second->r12;
	p_destination->r21 = p_first->r21 * p_second->r21;
	p_destination->r22 = p_first->r22 * p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22InvertGivenInvertedDeterminant(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination, float p_invertedDeterminant) {
	p_destination->r11 = p_matrix->r22 * p_invertedDeterminant;
	p_destination->r12 = -p_matrix->r12 * p_invertedDeterminant;
	p_destination->r21 = -p_matrix->r21 * p_invertedDeterminant;
	p_destination->r22 = p_matrix->r11 * p_invertedDeterminant;

	return p_destination;
}
