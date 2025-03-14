#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "library/library.h"

int main(int const p_count, char *p_values[]) {
	float arr[] = { 1, 2, 3, 4, };
	struct SmlMat22 mat = smlMat22(arr);
	printf("%f, %f, %f, %f.", mat.r00, mat.r01, mat.r10, mat.r11);

	// memcpy(mat.one, arr, sizeof(struct SmlMat22));
	// struct SmlMat22 mat = (struct SmlMat22) { arr[0], arr[1], arr[2], arr[3], };

	return EXIT_SUCCESS;
}
