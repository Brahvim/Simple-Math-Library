#pragma once

#define SML_FLOAT(p_dataStructure)	((float*) (p_dataStructure))

#define SML_QUAT(p_floatPointer)	((struct SmlQuat*) (p_floatPointer))
#define SML_VEC3(p_floatPointer)	((struct SmlVec3*) (p_floatPointer))
#define SML_VEC2(p_floatPointer)	((struct SmlVec2*) (p_floatPointer))

#define SML_MAT22(p_floatPointer)	((struct SmlMat22*) (p_floatPointer))
#define SML_MAT33(p_floatPointer)	((struct SmlMat33*) (p_floatPointer))
#define SML_MAT44(p_floatPointer)	((struct SmlMat44*) (p_floatPointer))

// Copier functions!:
inline struct SmlQuat smlQuat(float*);
inline struct SmlVec3 smlVec3(float*);
inline struct SmlVec2 smlVec2(float*);
inline struct SmlMat22 smlMat22(float*);
inline struct SmlMat33 smlMat33(float*);
inline struct SmlMat44 smlMat44(float*);

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

// Matrices in **text** are row-major! **Rows** are *stretched-out*!

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
