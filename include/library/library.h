#pragma once

struct SmlQuat {

	union {

		struct {

			float x, y, z, w;

		};

		float data[4];

	};

};

struct SmlVec3 {

	union {

		struct {

			float x, y, z;

		};

		float data[3];

	};

};

struct SmlVec2 {

	union {

		struct {

			float x, y;

		};

		float data[2];

	};

};

// Matrices in **text** are row-major!: ***Rows*** are *stretched-out*!

struct SmlMat22 {

	union {

		struct {

			float r00, r01;
			float r10, r11;

		};

		struct {

			float c00, c10;
			float c01, c11;

		};

		float one[4];

		float two[2][2];

	};

};

struct SmlMat33 {

	union {

		struct {

			float r00, r01, r02;
			float r10, r11, r12;
			float r20, r21, r22;

		};

		struct {

			float c00, c10, c20;
			float c01, c11, c21;
			float c02, c12, c22;

		};

		float one[3];

		float two[3][3];

	};

};

struct SmlMat44 {

	union {

		struct {

			float r00, r01, r02, r03;
			float r10, r11, r12, r13;
			float r20, r21, r22, r23;
			float r30, r31, r32, r33;

		};

		struct {

			float c00, c10, c20, c30;
			float c01, c11, c21, c31;
			float c02, c12, c22, c32;
			float c03, c13, c23, c33;

		};

		float one[16];

		float two[4][4];

	};

};

// Copier functions!:
struct SmlQuat smlQuat(float *const array);
struct SmlVec3 smlVec3(float *const array);
struct SmlVec2 smlVec2(float *const array);
struct SmlMat22 smlMat22(float *const array);
struct SmlMat33 smlMat33(float *const array);
struct SmlMat44 smlMat44(float *const array);

extern float smlVec3Direction(float const*);
extern float smlVec3Magnitude(float const *vector);
extern float smlVec3MagnitudeSquared(float const *vector);

extern float* smlVec3FromAngle2d(float const x, float *vector);
extern float* smlVec3FromAngle3d(float const x, float const y, float const z, float *destination);

extern float smlVec3NormalizeBatch1(float const *vector);
extern float* smlVec3Normalize(float const *vector, float *destination);
extern float* smlVec3NormalizeUnsafe(float const *vector, float *destination);
extern float* smlVec3NormalizeBatch2(float mag, float const *vector, float *destination);

extern float* smlVec3Scale(float *const vector, float scalar, float *destination);
extern float* smlVec3ScaleBatch1(float *const vector, float scalar, float *destination);
extern float* smlVec3ScaleBatch2(float *const vector, float scalar, float *destination);
extern float* smlVec3ScaleUnsafe(float *const vector, float scalar, float *destination);

extern float smlVec3Dot(float *const first, float *const second);
extern float* smlVec3Add(float *const first, float *const second, float *destination);
extern float* smlVec3Sub(float *const first, float *const second, float *destination);
extern float* smlVec3Mult(float *const first, float const scalar, float *destination);
extern float* smlVec3Cross(float *const first, float *const second, float *destination);
