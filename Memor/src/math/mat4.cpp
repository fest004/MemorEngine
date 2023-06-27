#include "mat4.hpp"
#include <memory.h>
#include "radians.hpp"

namespace math {

// Matrices are to store information about rotation, position and scaling 
// of pixels.



// Default constructor creates empty matrix

mat4::mat4()
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;
	}

/*
   x, 0, 0, 0
   0, x, 0, 0
   0, 0, x, 0
   0, 0, 0, x

   Diagonal matrix where x = diagonal
*/


	mat4::mat4(float diagonal)
	{
		for (int i = 0; i < 4 * 4; i++)
			elements[i] = 0.0f;

		elements[0 + 0 * 4] = diagonal;
		elements[1 + 1 * 4] = diagonal;
		elements[2 + 2 * 4] = diagonal;
		elements[3 + 3 * 4] = diagonal;
	}

	mat4 mat4::identity()
	{
		return mat4(1.0f);
	}

// Multiplies two matrices
//
// mat41.multiply(mat4 other)
//
// Multiplies ecah corresponding index with eachother 


	mat4& mat4::multiply(const mat4& other)
	{
		float data[16];
		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				float sum = 0.0f;
				for (int e = 0; e < 4; e++)
				{
					sum += elements[x + e * 4] * other.elements[e + y * 4];
				}
				data[x + y * 4] = sum;
			}
		}
		memcpy(elements, data, 4 * 4 * sizeof(float));

		return *this;
	}

	//Multiplying a mat4 with a vec3 and returning a vec3
	vec3 mat4::multiply(const vec3& other) const
	{
		return vec3(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z
		);
	}


	//Multiplying a mat4 with a vec4 and returning a vec4
	vec4 mat4::multiply(const vec4& other) const
	{
		return vec4(
			columns[0].x * other.x + columns[1].x * other.y + columns[2].x * other.z + columns[3].x * other.w,
			columns[0].y * other.x + columns[1].y * other.y + columns[2].y * other.z + columns[3].y * other.w,
			columns[0].z * other.x + columns[1].z * other.y + columns[2].z * other.z + columns[3].z * other.w,
			columns[0].w * other.x + columns[1].w * other.y + columns[2].w * other.z + columns[3].w * other.w
		);
	}

	mat4 operator*(mat4 left, const mat4& right)
	{
		return left.multiply(right);
	}

	mat4& mat4::operator*=(const mat4& other)
	{
		return multiply(other);
	}

	vec3 operator*(const mat4& left, const vec3& right)
	{
		return left.multiply(right);
	}

	vec4 operator*(const mat4& left, const vec4& right)
	{
		return left.multiply(right);
	}


/*
Orthographic matrix:

| 2/(right - left)     0                   0                -(right + left)/(right - left) 
|                                                                                             
|     0           2/(top - bottom)         0              -(top + bottom)/(top - bottom)   
|                                                                                             
|     0                0           -2/(far - near)     -(far + near)/(far - near)           
|                                                                                             
|     0                0                   0                         1                       
   */

	mat4 mat4::orthographic(float left, float right, float bottom, float top, float near, float far)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = 2.0f / (right - left);

		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);

		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

/*
Perspective matrix

   a              0              0              0    
   0              q              0              0    
   0              0              b              c    
   0              0              -1             0    
   */



	mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
	{
		mat4 result(1.0f);

		float q = 1.0f / tan(toRadians(0.5f * fov));
		float a = q / aspectRatio;

		float b = (near + far) / (near - far);
		float c = (2.0f * near * far) / (near - far);

		result.elements[0 + 0 * 4] = a;
		result.elements[1 + 1 * 4] = q;
		result.elements[2 + 2 * 4] = b;
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = c;

		return result;
	}


/*
Translation matrix where t = vec3 translation
   1     0     0     t.x   
   0     1     0     t.y   
   0     0     1     t.z   
   0     0     0     1    
*/
	mat4 mat4::translation(const vec3& translation)
	{
		mat4 result(1.0f);

		result.elements[0 + 3 * 4] = translation.x;
		result.elements[1 + 3 * 4] = translation.y;
		result.elements[2 + 3 * 4] = translation.z;

		return result;
	}


/*
 Rotation matrix, idfk
   r11    r12    r13    0   
   r21    r22    r23    0   
   r31    r32    r33    0   
   0      0      0      1   
*/

	mat4 mat4::rotation(float angle, const vec3& axis)
	{
		mat4 result(1.0f);

		float r = toRadians(angle);
		float c = cos(r);
		float s = sin(r);
		float omc = 1.0f - c;
		
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;

		result.elements[0 + 0 * 4] = x * omc + c;
		result.elements[1 + 0 * 4] = y * x * omc + z * s;
		result.elements[2 + 0 * 4] = x * z * omc - y * s;

		result.elements[0 + 1 * 4] = x * y * omc - z * s;
		result.elements[1 + 1 * 4] = y * omc + c;
		result.elements[2 + 1 * 4] = y * z * omc + x * s;

		result.elements[0 + 2 * 4] = x * z * omc + y * s;
		result.elements[1 + 2 * 4] = y * z * omc - x * s;
		result.elements[2 + 2 * 4] = z * omc + c;
		
		return result;
	}


/*
Scale matrix where s = vec3 scale
   sx    0     0     0   
   0     sy    0     0   
   0     0     sz    0   
   0     0     0     1   

*/
	mat4 mat4::scale(const vec3& scale)
	{
		mat4 result(1.0f);

		result.elements[0 + 0 * 4] = scale.x;
		result.elements[1 + 1 * 4] = scale.y;
		result.elements[2 + 2 * 4] = scale.z;

		return result;
	}

} // namespace math





