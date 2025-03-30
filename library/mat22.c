#include <math.h>

#include "internals/ifs.h"
#include "library/library.h"

inline struct SmlMat22* smlMat22Mul(
	struct SmlMat22 const *const p_first,
	struct SmlMat22 const *const p_second,
	struct SmlMat22 *const p_destination
) {
	p_destination->r11 = p_first->r11 * p_second->r11 + p_first->r12 * p_second->r21;
	p_destination->r12 = p_first->r11 * p_second->r12 + p_first->r12 * p_second->r22;
	p_destination->r21 = p_first->r21 * p_second->r11 + p_first->r22 * p_second->r21;
	p_destination->r22 = p_first->r21 * p_second->r12 + p_first->r22 * p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22Add(
	struct SmlMat22 const *const p_first,
	struct SmlMat22 const *const p_second,
	struct SmlMat22 *const p_destination
) {
	p_destination->r11 = p_first->r11 + p_second->r11;
	p_destination->r12 = p_first->r12 + p_second->r12;
	p_destination->r21 = p_first->r21 + p_second->r21;
	p_destination->r22 = p_first->r22 + p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22Sub(
	struct SmlMat22 const *const p_first,
	struct SmlMat22 const *const p_second,
	struct SmlMat22 *const p_destination
) {
	p_destination->r11 = p_first->r11 - p_second->r11;
	p_destination->r12 = p_first->r12 - p_second->r12;
	p_destination->r21 = p_first->r21 - p_second->r21;
	p_destination->r22 = p_first->r22 - p_second->r22;

	return p_destination;
}

inline struct SmlMat22* smlMat22MultMembers(
	struct SmlMat22 const *const p_first,
	struct SmlMat22 const *const p_second,
	struct SmlMat22 *const p_destination
) {
	p_destination->r11 = p_first->r11 * p_second->r11;
	p_destination->r12 = p_first->r12 * p_second->r12;
	p_destination->r21 = p_first->r21 * p_second->r21;
	p_destination->r22 = p_first->r22 * p_second->r22;

	return p_destination;
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

inline float smlMat22Invert(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination) {
	ifu(smlMat22Determinant(p_matrix) == 0.0f) {
		
	}
}

inline float smlMat22InvertUnchecked(struct SmlMat22 const *const p_matrix, struct SmlMat22 *const p_destination) {
}
