#include <math.h>
#include <float.h>
#include "library/library.h"

inline struct SmlVec2 smlVec2(float const *const p_array) {
	return (struct SmlVec2) { p_array[0], p_array[1] };
}

inline struct SmlVec3 smlVec3(float const *const p_array) {
	return (struct SmlVec3) { p_array[0], p_array[1], p_array[2] };
}

inline struct SmlQuat smlQuat(float const *const p_array) {
	return (struct SmlQuat) { { p_array[0], p_array[1], p_array[2], p_array[3] } };
}

inline struct SmlMat22 smlMat22(float const *const array) {
	return (struct SmlMat22) { array[0], array[1], array[2], array[3], };
}

inline struct SmlMat33 smlMat33(float const *const p_array) {
	return (struct SmlMat33) { p_array[0], p_array[1], p_array[2], p_array[3], p_array[4], p_array[5], p_array[6], p_array[7], p_array[8] };
}

inline struct SmlMat44 smlMat44(float const *const p_array) {
	return (struct SmlMat44) { // Looks perfectly aligned in non-monospace fonts 😅}
		/*		 */ p_array[0], p_array[1], p_array[2], p_array[3],
			/*	*/	p_array[4], p_array[5], p_array[6], p_array[7],
			/*	*/	p_array[8], p_array[9], p_array[10], p_array[11],
			/*	*/	p_array[12], p_array[13], p_array[14], p_array[15]
	};
}

inline char smlFloatCompare(const float p_first, const float p_second, float p_epsilon) {
	return fabsf(p_first - p_second) < p_epsilon;
}

inline char smlFloatCompareFltEps(const float p_first, const float p_second) {
	return smlFloatCompare(p_first, p_second, FLT_EPSILON);
}
