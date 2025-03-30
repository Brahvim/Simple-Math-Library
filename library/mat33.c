#include <math.h>

#include "internals/ifs.h"
#include "library/library.h"

inline struct SmlMat33* smlMat33Mul(
	struct SmlMat33 const *const p_first,
	struct SmlMat33 const *const p_second,
	struct SmlMat33 *const p_destination
) {
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

inline struct SmlMat33* smlMat33Add(
	struct SmlMat33 const *const p_first,
	struct SmlMat33 const *const p_second,
	struct SmlMat33 *const p_destination
) {
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

inline struct SmlMat33* smlMat33Sub(
	struct SmlMat33 const *const p_first,
	struct SmlMat33 const *const p_second,
	struct SmlMat33 *const p_destination
) {
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

inline struct SmlMat33* smlMat33MultMembers(
	struct SmlMat33 const *const p_first,
	struct SmlMat33 const *const p_second,
	struct SmlMat33 *const p_destination
) {
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

inline float smlMat33Determinant(struct SmlMat33 const *const p_matrix) {
	return (p_matrix->r11 * ((p_matrix->r22 * p_matrix->r33) - (p_matrix->r23 * p_matrix->r32)))
		- (p_matrix->r12 * ((p_matrix->r21 * p_matrix->r33) - (p_matrix->r23 * p_matrix->r31)))
		+ (p_matrix->r13 * ((p_matrix->r21 * p_matrix->r32) - (p_matrix->r22 * p_matrix->r31)));
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
