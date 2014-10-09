// 27.10.2013 01:01

#ifndef __MAT__
#define __MAT__

#include <cmath>

struct mx_matrix3
{
	float data[9];
	//------------------------------------------------
	//           KONSTRUKTORY
	mx_matrix3();
	mx_matrix3(const float *M);
	mx_matrix3(float m11, float m12, float m13, 
			float m21, float m22, float m23,
			float m31, float m32, float m33
			);
	//-----------------------------------------------
	//             OPERATORY
	const float &operator [] (int i) const;
	//----------------------------------------------
	//				OPERACJE
	float det();
};
struct mx_matrix4
{
	float data[16];
	//------------------------------------------------
	//           KONSTRUKTORY
	mx_matrix4();
	mx_matrix4(const float *M);
	mx_matrix4(float m11, float m12, float m13, float m14,
		   float m21, float m22, float m23, float m24,
		   float m31, float m32, float m33, float m34,
		   float m41, float m42, float m43, float m44); 
	//------------------------------------------------
	//             TRANSFORMACJE
	
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z, float a);
	void scale(float x, float y, float z);
	void inverse();
	void transpose();
	void LoadIdentity();
	void Frustum(float left, float right, float bottom, float top, float close, float wide);
	void Ortho(float left, float right, float bottom, float top, float close, float wide);
	//-----------------------------------------------
	//             OPERATORY
	
	mx_matrix4 operator *= (const mx_matrix4 &M);
	mx_matrix4 operator *= (const float x);
	const float &operator [] (int i) const;
	//----------------------------------------------
	//				OPERACJE
	float det();
};

struct mx_vector3
{
	float data[3];
	//----------------------------------------------
	//
	mx_vector3();
	mx_vector3(const float *V);
	mx_vector3(float x, float y, float z);
	//---------------------------------------------
	//			TRANSFORMACJE
	mx_vector3 normalize();

	//---------------------------------------------
	//OPERATORY
	mx_vector3 operator += (const mx_vector3 &V);
	mx_vector3 operator -= (const mx_vector3 &V);
	const float &operator [] (int i) const;
};

struct mx_vector4
{
	float data[4];
	//----------------------------------------------
	//			KONSTRUKTORY
	mx_vector4();
	mx_vector4(const float *V);
	mx_vector4(float x, float y, float z, float w);
	//---------------------------------------------
	//			TRANSFORMACJE
	mx_vector4 normalize();
	//---------------------------------------------
	//OPERATORY
	mx_vector4 operator *= (const mx_vector4 &V);
	const float &operator [] (int i) const;
};

mx_matrix4 operator * (const mx_matrix4 M1, const mx_matrix4 M2);
mx_vector4 operator * (const mx_matrix4 M, const mx_vector4 V);
mx_vector4 operator * (const mx_vector4 V, const mx_matrix4 M);

mx_vector3 operator * (const float a, const mx_vector3 V);
mx_vector3 operator * (const mx_vector3 V1, const mx_vector3 V2);
mx_vector3 operator / (const mx_vector3 V, const float a);
mx_vector3 operator - (const mx_vector3 V1, const mx_vector3 V2);

bool operator == (mx_vector3 V1, mx_vector3 V2); 

float dot3(const mx_vector3 V1, const mx_vector3 V2);

float length(const mx_vector3 V);

#endif