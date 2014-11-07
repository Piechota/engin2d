// 27.10.2013 01:01

#include "matrix.h"

//--------------------------------------------------------------------------
//						VECTOR2
mx_vector2::mx_vector2()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
}
mx_vector2::mx_vector2(const float *V)
{
	data[0] = V[0];
	data[1] = V[1];
}

mx_vector2::mx_vector2(float x, float y)
{
	data[0] = x;
	data[1] = y;
}

mx_vector2 mx_vector2::normalize()
{
	float distance = sqrt((data[0] * data[0]) + (data[1] * data[1]));

	if (distance)
	{
		data[0] /= distance;
		data[1] /= distance;
	}
	return *this;
}

mx_vector2 mx_vector2::operator += (const mx_vector2 &V)
{
	data[0] += V[0];
	data[1] += V[1];

	return *this;
}

mx_vector2 mx_vector2::operator -= (const mx_vector2 &V)
{
	data[0] -= V[0];
	data[1] -= V[1];

	return *this;
}

const float &mx_vector2::operator [] (int i) const
{
	return data[i];
}
float &mx_vector2::operator[] (int i)
{
	return data[i];
}
//--------------------------------------------------------------------------
//						VECTOR3
mx_vector3::mx_vector3()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
}
mx_vector3::mx_vector3(const float *V)
{
	data[0] = V[0];
	data[1] = V[1];
	data[2] = V[2];
}

mx_vector3::mx_vector3(float x, float y, float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

mx_vector3 mx_vector3::normalize()
{
	float distance = sqrt((data[0]*data[0])+(data[1]*data[1])+(data[2]*data[2]));

	if(distance)
	{
	data[0] /= distance;
	data[1] /= distance;
	data[2] /= distance;
	}
	return *this;
}

mx_vector3 mx_vector3::operator += (const mx_vector3 &V)
{
	data[0] += V[0];
	data[1] += V[1];
	data[2] += V[2];

	return *this;
}

mx_vector3 mx_vector3::operator -= (const mx_vector3 &V)
{
	data[0] -= V[0];
	data[1] -= V[1];
	data[2] -= V[2];

	return *this;
}

const float &mx_vector3::operator [] (int i) const
{
	return data[i];
}

//--------------------------------------------------------------------------
//						VECTOR4
mx_vector4::mx_vector4()
{
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
}

mx_vector4::mx_vector4(const float *V)
{
	data[0] = V[0];
	data[1] = V[1];
	data[2] = V[2];
	data[3] = V[3];
}

mx_vector4::mx_vector4(float x, float y, float z, float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}

mx_vector4 mx_vector4::normalize()
{
	if(data[3])
	{
	data[0] /= data[3];
	data[1] /= data[3];
	data[2] /= data[3];
	data[3] /= data[3];
	}
	return *this;
}

mx_vector4 mx_vector4::operator *= (const mx_vector4 &V)
{
	data[0] = data[1]*V[2]-data[2]*V[1];
	data[1] = data[0]*V[2]-data[2]*V[0];
	data[2] = data[0]*V[1]-data[1]*V[0];

	data[3] = sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);

	return *this;
}

const float &mx_vector4::operator [] (int i) const
{
	return data[i];
}
//---------------------------------------------------------------------------
//						MATRIX3
mx_matrix3::mx_matrix3()
{
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 0.0f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[5] = 0.0f;
	data[6] = 0.0f;
	data[7] = 0.0f;
	data[8] = 0.0f;
}

mx_matrix3::mx_matrix3(const float *M)
{
	data[0] = M[0];
	data[1] = M[1];
	data[2] = M[2];
	data[3] = M[3];
	data[4] = M[4];
	data[5] = M[5];
	data[6] = M[6];
	data[7] = M[7];
	data[8] = M[8];
}

mx_matrix3::mx_matrix3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	data[0] = m11; data[1] = m12; data[2] = m13;
	data[3] = m21; data[4] = m22; data[5] = m23;
	data[6] = m31; data[7] = m32; data[8] = m33;
}

const float &mx_matrix3::operator [] (int i) const
{
	return data[i];
}

float mx_matrix3::det()
{
	return (data[0]*data[4]*data[8])+(data[1]*data[5]*data[6])+(data[2]*data[3]*data[7])
		-(data[2]*data[4]*data[6])-(data[0]*data[5]*data[7])-(data[1]*data[3]*data[8]);
}
//---------------------------------------------------------------------------
//						MATRIX4

mx_matrix4::mx_matrix4()
{
	data[0]  = 1.0f; data[1]  = 0.0f; data[2]  = 0.0f; data[3]  = 0.0f;
	data[4]  = 0.0f; data[5]  = 1.0f; data[6]  = 0.0f; data[7]  = 0.0f;
	data[8]  = 0.0f; data[9]  = 0.0f; data[10] = 1.0f; data[11] = 0.0f;
	data[12] = 0.0f; data[13] = 0.0f; data[14] = 0.0f; data[15] = 1.0f;
}

mx_matrix4::mx_matrix4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	data[0]  = m11; data[1]  = m12; data[2]  = m13; data[3]  = m14;
	data[4]  = m21; data[5]  = m22; data[6]  = m23; data[7]  = m24;
	data[8]  = m31; data[9]  = m32; data[10] = m33; data[11] = m34;
	data[12] = m41; data[13] = m42; data[14] = m43; data[15] = m44;
}
mx_matrix4::mx_matrix4(const float *M)
{
	data[0]  = M[0]; data[1]  = M[1]; data[2]  = M[2]; data[3]  = M[3];
	data[4]  = M[4]; data[5]  = M[5]; data[6]  = M[6]; data[7]  = M[7];
	data[8]  = M[8]; data[9]  = M[9]; data[10] = M[10]; data[11] = M[11];
	data[12] = M[12]; data[13] = M[13]; data[14] = M[14]; data[15] = M[15];
}

const float &mx_matrix4::operator [] (int i) const 
 {
	 return data[i];
 }

mx_matrix4 mx_matrix4::operator *= (const mx_matrix4 &M)
 {
	 mx_matrix4 temp(
					data[0] * M[0] + data[1] * M[4] + data[2] * M[8] + data[3] * M[12],
					data[0] * M[1] + data[1] * M[5] + data[2] * M[9] + data[3] * M[13],
                    data[0] * M[2] + data[1] * M[6] + data[2] * M[10] + data[3] * M[14],
                    data[0] * M[3] + data[1] * M[7] + data[2] * M[11] + data[3] * M[15],
                    data[4] * M[0] + data[5] * M[4] + data[6] * M[8] + data[7] * M[12],
                    data[4] * M[1] + data[5] * M[5] + data[6] * M[9] + data[7] * M[13],
                    data[4] * M[2] + data[5] * M[6] + data[6] * M[10] + data[7] * M[14],
                    data[4] * M[3] + data[5] * M[7] + data[6] * M[11] + data[7] * M[15],
                    data[8] * M[0] + data[9] * M[4] + data[10] * M[8] + data[11] * M[12],
                    data[8] * M[1] + data[9] * M[5] + data[10] * M[9] + data[11] * M[13],
                    data[8] * M[2] + data[9] * M[6] + data[10] * M[10] + data[11] * M[14],
                    data[8] * M[3] + data[9] * M[7] + data[10] * M[11] + data[11] * M[15],
                    data[12] * M[0] + data[13] * M[4] + data[14] * M[8] + data[15] * M[12],
                    data[12] * M[1] + data[13] * M[5] + data[14] * M[9] + data[15] * M[13],
                    data[12] * M[2] + data[13] * M[6] + data[14] * M[10] + data[15] * M[14],
                    data[12] * M[3] + data[13] * M[7] + data[14] * M[11] + data[15] * M[15] );

	 *this = temp;
	 return *this;
 }

mx_matrix4 mx_matrix4::operator *= (const float x)
{
	data[0] *= x; data[1] *= x; data[2] *= x; data[3] *= x;
	data[4] *= x; data[5] *= x; data[6] *= x; data[7] *= x;
	data[8] *= x; data[9] *= x; data[10] *= x; data[11] *= x;
	data[12] *= x; data[13] *= x; data[14] *= x; data[15] *= x; 
	return *this;
}

 void mx_matrix4::translate(float x, float y, float z)
 {
	 mx_matrix4 temp(
		 1.0f, 0.0f, 0.0f, x,
		 0.0f, 1.0f, 0.0f, y,
		 0.0f, 0.0f, 1.0f, z,
		 0.0f, 0.0f, 0.0f, 1.0f);

	 *this *= temp;
 }

  void mx_matrix4::rotate(float x, float y, float z, float a)
 {
	 const float d = ( sqrt( x * x + y * y + z * z ) );
    if( d != 1.0 && d != 0.0 )
    {
        x /= d;
        y /= d;
        z /= d;
    }
    const float c = ( cos( a * 3.141592653589793 / 180.0 ) );
    const float s = ( sin( a * 3.141592653589793 / 180.0 ) );
    mx_matrix4 tmp( 
		( x * x * (1 - c) + c ), ( x * y * (1 - c) - z * s ), ( x * z * (1 - c) + y * s ), ( 0.0 ),
        ( y * x * (1 - c) + z * s ), ( y * y * (1 - c) + c ), ( y * z * (1 - c) - x * s ), ( 0.0 ),
        ( x * z * (1 - c) - y * s ), ( y * z * (1 - c) + x * s ), ( z * z * (1 - c) + c ), ( 0.0 ),
        ( 0.0 ), ( 0.0 ), ( 0.0 ), ( 1.0 ) 
		);
    *this *= tmp;
 }

 void mx_matrix4::scale(float x, float y, float z)
 {
	 mx_matrix4 tmp(
	x, 0.0f, 0.0f, 0.0f,
	0.0f, y, 0.0f, 0.0f,
	0.0f, 0.0f, z, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
	);
	 *this *= tmp;
 }

 void mx_matrix4::inverse()
 {
	 if(det() != 0.0f)
	 {
	 mx_matrix4 tmp4;

	 mx_matrix3 tmp3;
	 tmp3.data[0] = data[5];
	 tmp3.data[1] = data[6];
	 tmp3.data[2] = data[7];
	 tmp3.data[3] = data[9];
	 tmp3.data[4] = data[10];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[13];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[0] = tmp3.det();
	 //--------------------------------------
	 tmp3.data[0] = data[4];
	 tmp3.data[1] = data[6];
	 tmp3.data[2] = data[7];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[10];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[1] = -tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[4];
	 tmp3.data[1] = data[5];
	 tmp3.data[2] = data[7];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[9];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[15];

	 tmp4.data[2] = tmp3.det();
	 //---------------------------------------
	 
	 tmp3.data[0] = data[4];
	 tmp3.data[1] = data[5];
	 tmp3.data[2] = data[6];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[9];
	 tmp3.data[5] = data[10];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[14];

	 tmp4.data[3] = -tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[1];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[9];
	 tmp3.data[4] = data[10];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[13];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[4] = -tmp3.det();
	 //--------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[10];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[5] = tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[9];
	 tmp3.data[5] = data[11];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[15];

	 tmp4.data[6] = -tmp3.det();
	 //--------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[2];
	 tmp3.data[3] = data[8];
	 tmp3.data[4] = data[9];
	 tmp3.data[5] = data[10];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[14];

	 tmp4.data[7] = tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[1];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[5];
	 tmp3.data[4] = data[6];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[13];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[8] = tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[6];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[14];
	 tmp3.data[8] = data[15];

	 tmp4.data[9] = -tmp3.det();
	 //----------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[5];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[15];

	 tmp4.data[10] = tmp3.det();
	 //----------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[2];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[5];
	 tmp3.data[5] = data[6];
	 tmp3.data[6] = data[12];
	 tmp3.data[7] = data[13];
	 tmp3.data[8] = data[14];

	 tmp4.data[11] = -tmp3.det();
	 //----------------------------------------
	 tmp3.data[0] = data[1];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[5];
	 tmp3.data[4] = data[6];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[9];
	 tmp3.data[7] = data[10];
	 tmp3.data[8] = data[11];

	 tmp4.data[12] = -tmp3.det();
	 //---------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[2];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[6];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[8];
	 tmp3.data[7] = data[10];
	 tmp3.data[8] = data[11];

	 tmp4.data[13] = tmp3.det();
	 //--------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[3];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[5];
	 tmp3.data[5] = data[7];
	 tmp3.data[6] = data[8];
	 tmp3.data[7] = data[9];
	 tmp3.data[8] = data[11];

	 tmp4.data[14] = -tmp3.det();
	 //-------------------------------------
	 tmp3.data[0] = data[0];
	 tmp3.data[1] = data[1];
	 tmp3.data[2] = data[2];
	 tmp3.data[3] = data[4];
	 tmp3.data[4] = data[5];
	 tmp3.data[5] = data[6];
	 tmp3.data[6] = data[8];
	 tmp3.data[7] = data[9];
	 tmp3.data[8] = data[10];

	 tmp4.data[15] = tmp3.det();
	 //--------------------------------------

	 tmp4.transpose();

	 tmp4 *= (1.0f/det());

	 *this = tmp4;
	 }
 }

 void mx_matrix4::transpose()
 {
	 mx_matrix4 tmp(
				data[0], data[4], data[8], data[12],
				data[1], data[5], data[9], data[13],
				data[2], data[6], data[10], data[14],
				data[3], data[7], data[11], data[15]
				);
	*this = tmp;
 }

  float mx_matrix4::det()
 {
	 return data[0]*(data[5]*data[10]*data[15]+data[6]*data[11]*data[13]+data[7]*data[9]*data[14]-data[7]*data[10]*data[13]-data[11]*data[14]*data[5]-data[15]*data[9]*data[6])
		 -data[1]*(data[4]*data[10]*data[15]+data[6]*data[11]*data[12]+data[7]*data[8]*data[14]-data[7]*data[10]*data[12]-data[11]*data[14]*data[4]-data[15]*data[8]*data[6])
		 +data[2]*(data[4]*data[9]*data[15]+data[5]*data[11]*data[12]+data[7]*data[8]*data[13]-data[7]*data[9]*data[12]-data[11]*data[13]*data[4]-data[15]*data[8]*data[5])
		 -data[3]*(data[4]*data[9]*data[14]+data[5]*data[10]*data[12]+data[6]*data[8]*data[13]-data[6]*data[9]*data[12]-data[13]*data[10]*data[4]-data[14]*data[8]*data[5]);
 }

   void mx_matrix4::LoadIdentity()
  {
	  mx_matrix4 tmp(
		  1.0f, 0.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, 1.0f, 0.0f,
		  0.0f, 0.0f, 0.0f, 1.0f
		  );
	  *this = tmp;
  }

   void mx_matrix4::Frustum(float left, float right, float bottom, float top, float close, float wide)
  {
	  mx_matrix4 tmp(
		  (2.0f*close)/(right-left), 0.0f, (right+left)/(right-left), 0.0f,
		  0.0f, (2.0f*close)/(top-bottom), (top+bottom)/(top-bottom), 0.0f,
		  0.0f, 0.0f, -((wide+close)/(wide-close)), -((2.0f*wide*close)/(wide-close)),
		  0.0f, 0.0f, -1.0f, 0.0f
		  );
	  *this *= tmp;
  }

   void mx_matrix4::Ortho(float left, float right, float bottom, float top, float close, float wide)
   {
	   mx_matrix4 tmp(
		   2.0f/(right-left), 0.0f, 0.0f, -(right+left)/(right-left),
		   0.0f, 2.0f/(top-bottom), 0.0f, -(top+bottom)/(top-bottom),
		   0.0f, 0.0f, -2.0f/(wide-close), -(wide+close)/(wide-close),
		   0.0f, 0.0f, 0.0f, 1.0f);

	   *this *= tmp;
   }

 //---------------- OPERATORY

 mx_matrix4 operator * (const mx_matrix4 M1, const mx_matrix4 M2)
 {
	 mx_matrix4 tmp(M1);
	 return tmp *= M2;
 }

 mx_vector4 operator * (const mx_matrix4 M, const mx_vector4 V)
 {
	 mx_vector4 tmp(
					(M[0]  * V[0]) + (M[1]  * V[1]) + (M[2]  * V[2]) + (M[3]  * V[3]),
					(M[4]  * V[0]) + (M[5]  * V[1]) + (M[6]  * V[2]) + (M[7]  * V[3]),
					(M[8]  * V[0]) + (M[9]  * V[1]) + (M[10] * V[2]) + (M[11] * V[3]),
					(M[12] * V[0]) + (M[13] * V[1]) + (M[14] * V[2]) + (M[15] * V[3])
					);

	 return tmp;
 }

 mx_vector4 operator * (const mx_vector4 V, const mx_matrix4 M)
 {
	 mx_vector4 tmp(
					(V[0]*M[0] + V[1]*M[4] + V[2]*M[8]  + V[3]*M[12]),
					(V[0]*M[1] + V[1]*M[5] + V[2]*M[9]  + V[3]*M[13]),
					(V[0]*M[2] + V[1]*M[6] + V[2]*M[10] + V[3]*M[14]),
					(V[0]*M[3] + V[1]*M[7] + V[2]*M[11] + V[3]*M[15])
					);

	 return tmp;
 }
 mx_vector3 operator * (const float a, const mx_vector3 V)
 {
	 mx_vector3 tmp(a*V[0], a*V[1], a*V[2]); 
	 return tmp;
 }

 mx_vector3 operator * (const mx_vector3 V1, const mx_vector3 V2)
 {
	 mx_vector3 tmp(
		V1[1]*V2[2] - V1[2]*V2[1],
		V1[2]*V2[0] - V1[0]*V2[2],
		V1[0]*V2[1] - V1[1]*V2[0]
	 );

	 return tmp;
 }
 
 mx_vector3 operator / (const mx_vector3 V, const float a)
 {
	 mx_vector3 tmp(V[0]/a, V[1]/a, V[2]/a);
	 return tmp;
 }

 mx_vector3 operator - (const mx_vector3 V1, const mx_vector3 V2)
 {
	 mx_vector3 tmp(V1[0]-V2[0], V1[1]-V2[1], V1[2]-V2[2]);
	 return tmp;
 }

 mx_vector2 operator * (const mx_vector2 V, const float a)
 {
	 mx_vector2 tmp(a*V[0], a*V[1]);
	 return tmp;
 }
 mx_vector2 operator + (const mx_vector2 V1, const mx_vector2 V2)
 {
	 mx_vector2 tmp(V1[0] + V2[0], V1[1] + V2[1]);
	 return tmp;
 }

 mx_vector2 operator - (const mx_vector2 V1, const mx_vector2 V2)
 {
	 mx_vector2 tmp(V1[0] - V2[0], V1[1] - V2[1]);
	 return tmp;
 }

 bool operator == (mx_vector3 V1, mx_vector3 V2)
 {
	 return (V1[0] == V2[0] && V1[1] == V2[1] && V1[2] == V2[2]);
 }

 //-----------------------FUNKCJE

 float dot3(const mx_vector3 V1, const mx_vector3 V2)
 {
	 return V1[0]*V2[0] + V1[1]*V2[1] + V1[2]*V2[2];
 }
 float dot2(const mx_vector2 V1, const mx_vector2 V2)
 {
	 return V1[0] * V2[0] + V1[1] * V2[1];
 }

 float length(const mx_vector3 V)
 {
	 return sqrt( (V[0]*V[0]) + (V[1]*V[1]) + (V[2]*V[2]));
 }