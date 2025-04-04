#include <math.h>

#include "internals/ifs.h"
#include "library/library.h"

#include <math.h>
#include <stdbool.h>

inline int smlMat22Rank(struct SmlMat22 const *const p_matrix) {
	if (smlMat22Determinant(p_matrix) != 0.0f)
		return 2;

	if (p_matrix->r11 != 0 || p_matrix->r12 != 0 || p_matrix->r21 != 0 || p_matrix->r22 != 0)
		return 1;

	return 0;
}

inline char smlMat22Rank1(struct SmlMat22 const *const p_matrix) {
	// If they KNEW the determinant, a check against `0.0f` WOULD reveal that the rank was **TWO**!
	return p_matrix->r11 != 0 || p_matrix->r12 != 0 || p_matrix->r21 != 0 || p_matrix->r22 != 0;
	// If it ain't `1` or `2`, it's `0`.
}

inline float smlMat22Trace(struct SmlMat22 const *const p_matrix) {
	return p_matrix->r11 + p_matrix->r22;
}

inline char smlMat22IsSymmetric(struct SmlMat22 const *const p_matrix) {
	return (p_matrix->r12 == p_matrix->r21);
}

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

inline int smlMat22TraceDeterminantIdentityCheck(struct SmlMat22 const *const p_matrix) {
	return (smlMat22Trace(p_matrix) == ((p_matrix->r11 * p_matrix->r22) - (p_matrix->r12 * p_matrix->r21))) ? 1 : 0;
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

inline struct SmlVec2* smlMat22Eigenvalues(struct SmlMat22 const *const p_matrix, struct SmlVec2 *const p_destination) {
	float const trace = smlMat22Trace(p_matrix);
	float const det = smlMat22Determinant(p_matrix);
	float const sqrtDiscriminant = __builtin_sqrtf((trace * trace) - (4.0f * det));

	p_destination->x = 0.5f * (trace + sqrtDiscriminant);
	p_destination->y = 0.5f * (trace - sqrtDiscriminant);
	return p_destination;
}

inline struct SmlMat22* smlMat22Cofactors(struct SmlMat22 const* const p_matrix, struct SmlMat22 *const p_destination) {
	p_destination->x = p_matrix->w;
	p_destination->y = -p_matrix->z;
	p_destination->z = -p_matrix->y;
	p_destination->w = p_matrix->x;

	return p_destination;
}

inline struct SmlMat22* smlMat22Transpose(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11;
	p_destination->r12 = p_matrix->r21;
	p_destination->r21 = p_matrix->r12;
	p_destination->r22 = p_matrix->r22;
	return p_destination;
}

inline struct SmlMat22* smlMat22Rotate(struct SmlMat22 const *const p_matrix, float angle, struct SmlMat22 *const p_destination) {
	float cosA = cosf(angle);
	float sinA = sinf(angle);

	*p_destination = (struct SmlMat22) {
		.r11 = cosA, .r12 = -sinA,
		.r21 = sinA, .r22 = cosA
	};

	return smlMat22Mult(p_destination, p_matrix, p_destination); // Multiply rotation p_matrix by input p_matrix
}

inline struct SmlMat22* smlMat22AddScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 + p_scalar;
	p_destination->r12 = p_matrix->r12 + p_scalar;
	p_destination->r21 = p_matrix->r21 + p_scalar;
	p_destination->r22 = p_matrix->r22 + p_scalar;

	return p_destination;
}

inline struct SmlMat22* smlMat22DivScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 / p_scalar;
	p_destination->r12 = p_matrix->r12 / p_scalar;
	p_destination->r21 = p_matrix->r21 / p_scalar;
	p_destination->r22 = p_matrix->r22 / p_scalar;

	return p_destination;
}

inline struct SmlMat22* smlMat22SubScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
	p_destination->r11 = p_matrix->r11 - p_scalar;
	p_destination->r12 = p_matrix->r12 - p_scalar;
	p_destination->r21 = p_matrix->r21 - p_scalar;
	p_destination->r22 = p_matrix->r22 - p_scalar;

	return p_destination;
}

inline struct SmlMat22* smlMat22MultScalar(struct SmlMat22 const *const p_matrix, float const p_scalar, struct SmlMat22 *const p_destination) {
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

inline struct SmlVec2* smlMat22MultVec2(struct SmlMat22 const *const p_matrix, struct SmlVec2 const *const p_vector, struct SmlVec2 *const p_destination) {
	p_destination->x = (p_matrix->r11 * p_vector->x) + (p_matrix->r12 * p_vector->y);
	p_destination->y = (p_matrix->r21 * p_vector->x) + (p_matrix->r22 * p_vector->y);
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
