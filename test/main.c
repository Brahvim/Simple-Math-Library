#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "library/sml.h"

int main(int const p_count, char *p_values[]) {
	float arr[] = { 1, 2, 3, 4, };
	struct SmlMat22 mat = smlMat22(arr);
	printf("%f, %f, %f, %f.\n", mat.r11, mat.r12, mat.r21, mat.r22);
	printf("%f, %f, %f, %f.\n", mat.c11, mat.c12, mat.c21, mat.c22);

	struct SmlVec3 vec1 = smlVec3(arr);
	struct SmlVec3 vec2 = smlVec3(arr);
	smlVec3Add(&vec1, &vec2, &vec1);

	return EXIT_SUCCESS;
}
