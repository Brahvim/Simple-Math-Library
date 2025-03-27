#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "library/library.h"

int main(int const p_count, char *p_values[]) {
	float arr[] = { 1, 2, 3, 4, };
	struct SmlMat22 mat = smlMat22(arr);
	printf("%f, %f, %f, %f.", mat.r00, mat.r01, mat.r10, mat.r11);

	struct SmlVec3 vec1 = smlVec3(arr);
	struct SmlVec3 vec2 = smlVec3(arr);
	// float *vec3 = 
	smlVec3Add(&vec1, &vec2, &vec1);

	// struct SmlQuat q = { .data = { 1, 2, 3, 4 } };

	return EXIT_SUCCESS;
}
