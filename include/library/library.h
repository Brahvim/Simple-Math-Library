#pragma once

#pragma region Macros.
#define SML_180_OVER_PI 57.29577951308232
#define SML_PI_OVER_180 0.017453292519943295

#define SML_DEGREES(radians) SML_180_OVER_PI * (radians)
#define SML_RADIANS(degrees) SML_PI_OVER_180 * (degrees)

#define SML_PI 3.141592653589793
#define SML_TAU 6.283185307179586
#define SML_PI_HALF 1.5707963267948966
#define SML_PI_THIRD 1.0471975511965976
#define SML_PI_QUART 0.7853981633974483

// 12.5%
#define SML_PI_EIGHTH 0.39269908169872414

// 6.25%
#define SML_PI_SIXTEENTH 0.19634954084936207

// 66.666666%
#define SML_PI_TWO_THIRDS 2.0943951023931953

// 75%
#define SML_PI_THREE_FOURTHS 2.356194490192345
#pragma endregion

#pragma region Structures.
struct SmlVec2 {

	union {

		float data[2];

		struct { float x, y; };

		struct { float i, j; };

		struct { float u, v; };

		struct { float s, t; };

	};

};

struct SmlVec3 {

	union {

		float data[3];

		struct {

			union {

				struct SmlVec2 vec2;
				struct { float x, y; };
				struct { float i, j; };
				struct { float r, g; };
				struct { float h, s; };

			};

			float z;
			float k;
			float b;
			float l;
			float v;

		};

	};

};

struct SmlQuat {

	union {

		float data[4];

		struct {

			union {

				struct SmlVec3 vec3;

				struct {

					union {

						struct SmlVec2 vec2;
						struct { float x, y; };
						struct { float i, j; };
						struct { float r, g; };
						struct { float h, s; };

					};

					float z;
					float k;
					float b;
					float l;
					float v;

				};

			};

			union { float a;  float w; };

		};

	};

};

// Matrices in **text** are row-major!: ***Rows*** are *stretched-out*!:

struct SmlMat22 {

	union {

		union {

			struct SmlVec2 xy;
			struct SmlVec2 zw;

		};

		union {

			struct { struct SmlVec2 col0; float c00, c10; };
			struct { struct SmlVec2 col1; float c01, c11; };

		};

		union {

			struct { struct SmlVec2 row0; float r00, r01; };
			struct { struct SmlVec2 row1; float r10, r11; };

		};

		float one[4];

		float two[2][2];

		struct SmlQuat quat;

	};

};

struct SmlMat33 {

	union {

		union {

			struct { struct SmlVec3 col0; float c00, c10, c20; };
			struct { struct SmlVec3 col1; float c01, c11, c21; };
			struct { struct SmlVec3 col2; float c02, c12, c22; };

		};

		union {

			struct { struct SmlVec3 row0; float r00, r01, r02; };
			struct { struct SmlVec3 row1; float r10, r11, r12; };
			struct { struct SmlVec3 row2; float r20, r21, r22; };

		};

		float one[9];

		float two[3][3];

		struct SmlMat22 m22;

	};

};

struct SmlMat44 {

	union {

		union {

			struct { struct SmlQuat col0; float c00, c10, c20, c30; };
			struct { struct SmlQuat col1; float c01, c11, c21, c31; };
			struct { struct SmlQuat col2; float c02, c12, c22, c32; };
			struct { struct SmlQuat col3; float c03, c13, c23, c33; };

		};

		union {

			struct { struct SmlQuat row0; float r00, r01, r02, r03; };
			struct { struct SmlQuat row1; float r10, r11, r12, r13; };
			struct { struct SmlQuat row2; float r20, r21, r22, r23; };
			struct { struct SmlQuat row3; float r30, r31, r32, r33; };

		};

		float one[16];

		float two[4][4];

		struct SmlMat33 mat33;

	};

};
#pragma endregion

// Copier functions!:
struct SmlVec2 smlVec2(float const *const array);
struct SmlVec3 smlVec3(float const *const array);
struct SmlQuat smlQuat(float const *const array);
struct SmlMat22 smlMat22(float const *const array);
struct SmlMat33 smlMat33(float const *const array);
struct SmlMat44 smlMat44(float const *const array);

char smlFloatCompareFltEps(float const first, float const second);
char smlFloatCompare(float const first, float const second, float epsilon);

#pragma region Quaternions.
float smlQuatMagnitude(struct SmlQuat const *const quaternion);
struct SmlQuat* smlQuatIdentity(struct SmlQuat *const destination);
float smlQuatMagnitudeSquared(struct SmlQuat const *const quaternion);
float smlQuatDot(struct SmlQuat const *const first, struct SmlQuat const *const second);
struct SmlQuat* smlQuatInvert(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlVec3* smlQuatToEuler(struct SmlQuat const *const quaternion, struct SmlVec3 * const destination);
struct SmlMat33* smlQuatToMatrix33(struct SmlQuat const *const source, struct SmlMat33 *const destination); // Rotation only!
struct SmlMat44* smlQuatToMatrix44(struct SmlQuat const *const source, struct SmlMat44 *const destination); // Complete transforms only!
struct SmlQuat* smlQuatFromMatrix44(struct SmlMat44 const *const source, struct SmlQuat *const destination);
struct SmlQuat* smlQuatConjugate(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNormalize(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNormalizeUnchecked(struct SmlQuat const *const quaternion, struct SmlQuat *const destination);
struct SmlQuat* smlQuatScale(struct SmlQuat const *const quaternion, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatMultScalar(struct SmlQuat const *const first, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatFromAxisAngle(struct SmlVec3 const *const axisVector, float const angle, struct SmlQuat *const destination);
struct SmlQuat* smlQuatScaleUnchecked(struct SmlQuat const *const quaternion, float const scalar, struct SmlQuat *const destination);
struct SmlQuat* smlQuatAdd(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlQuat* smlQuatSub(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlQuat* smlQuatMult(struct SmlQuat const *const first, struct SmlQuat const *const second, struct SmlQuat *const destination);
struct SmlVec3* smlQuatRotateVector3d(struct SmlQuat const *const quaternion, struct SmlVec3 *const vector, struct SmlVec3 *const destination);
struct SmlVec2* smlQuatRotateVector2d(struct SmlQuat const *const quaternion, struct SmlVec2 *const vector, struct SmlVec2 *const destination); // ???
struct SmlQuat* smlQuatLerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
struct SmlQuat* smlQuatSlerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
struct SmlQuat* smlQuatNlerp(struct SmlQuat const *const source, struct SmlQuat const *const target, float const amount, struct SmlQuat *const destination);
#pragma endregion

#pragma region Two-dimensional vectors.
float smlVec2Direction(struct SmlVec2 const *vector);
float smlVec2Magnitude(struct SmlVec2 const *vector);
struct SmlVec2* smlVec2One(struct SmlVec2 *const vector);
struct SmlVec2* smlVec2Zero(struct SmlVec2 *const vector);
float smlVec2MagnitudeSquared(struct SmlVec2 const *vector);
struct SmlVec2* smlVec2FromAngle(float const angle, struct SmlVec2 *vector);
float smlVec2Dot(struct SmlVec2 const *const first, struct SmlVec2 const *const second);
struct SmlVec2* smlVec2Normalize(struct SmlVec2 const *vector, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2NormalizeUnchecked(struct SmlVec2 const *vector, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Mult(struct SmlVec2 const *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Scale(struct SmlVec2 const *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2ScaleUnchecked(struct SmlVec2 *const vector, float const scalar, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Add(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec2 *const destination);
struct SmlVec2* smlVec2Sub(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec2 *const destination);
struct SmlVec3* smlVec2Cross(struct SmlVec2 const *const first, struct SmlVec2 const *const second, struct SmlVec3 *const destination);
#pragma endregion

#pragma region Three-dimensional vectors.
float smlVec3Direction2d(struct SmlVec3* vector);
float smlVec3Magnitude(struct SmlVec3 const *vector);
struct SmlVec3* smlVec3One(struct SmlVec3 *const vector);
struct SmlVec3* smlVec3Zero(struct SmlVec3 *const vector);
float smlVec3MagnitudeSquared(struct SmlVec3 const *vector);
struct SmlVec3* smlVec3FromAngle2d(struct SmlVec3 *const vector, float const angle);
float smlVec3Dot(struct SmlVec3 const *const first, struct SmlVec3 const *const second);
struct SmlVec3* smlVec3Normalize(struct SmlVec3 const *vector, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3NormalizeUnchecked(struct SmlVec3 const *vector, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Scale(struct SmlVec3 *const vector, float const scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3FromAngle3d(float const x, float const y, float const z, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3ScaleUnchecked(struct SmlVec3 *const vector, float scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Mult(struct SmlVec3 const *const vector, float const scalar, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Add(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Sub(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
struct SmlVec3* smlVec3Cross(struct SmlVec3 const *const first, struct SmlVec3 const *const second, struct SmlVec3 *const destination);
#pragma endregion
