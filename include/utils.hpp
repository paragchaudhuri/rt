/*
    This file is part of rt.

    rt is a simple ray tracer meant to be used for teaching ray tracing.

    Copyright (c) 2018 by Parag Chaudhuri

	Some parts of rt are derived from Nori by Wenzel Jacob.
	https://github.com/wjakob/nori/

    rt is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    rt is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

namespace rt
{
	const float EPSILON = 1e-4f;

	/* A few useful constants */
	#undef M_PI

	#define M_PI         3.14159265358979323846f
	#define INV_PI       0.31830988618379067154f
	#define INV_TWOPI    0.15915494309189533577f
	#define INV_FOURPI   0.07957747154594766788f
	#define SQRT_TWO     1.41421356237309504880f
	#define INV_SQRT_TWO 0.70710678118654752440f


	inline bool is_zero(const float x)
	{
		if ((x < EPSILON) && (x > -EPSILON)) return true; else return false;
	}

	inline bool is_equal(const float x, const float y)
	{
		return is_zero(x-y);
	}

	inline bool is_equal(const Vector3f& v1, const Vector3f& v2) 
	{
		float v1_x = v1.data()[0];
		float v1_y = v1.data()[1];
		float v1_z = v1.data()[2];

		float v2_x = v2.data()[0];
		float v2_y = v2.data()[1];
		float v2_z = v2.data()[2];

		return is_equal(v1_x, v2_x) && is_equal(v1_y, v2_y) && is_equal(v1_z, v2_z);
	}

	//// Convert radians to degrees
	inline float rad2deg(float value) { return value * (180.0f / M_PI); }

	/// Convert degrees to radians
	inline float deg2rad(float value) { return value * (M_PI / 180.0f); }

	///Clamp a float to be between 0.0 and 1.0.
    inline float clamp(float x){ return x<0.0f ? 0.0f : x>1.0f ? 1.0f : x; }
    
    ///Cast a float between 0.0 and 1.0 to a char. A gamme value of 2.2 is used.
    inline char to_char(float x){ return char(pow(clamp(x),1/2.2)*255+.5); }
}