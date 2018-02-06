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
#include <list>
#include <string>
#include <utility>
#include <vector>

#include <Eigen/Dense>
#include <Eigen/Geometry>

using namespace Eigen;

namespace rt
{
	/// A tolerance threshold.
	const double EPSILON = 1e-4f;

	/* A few useful constants */
	#undef M_PI

	#define M_PI         3.14159265358979323846f
	#define INV_PI       0.31830988618379067154f
	#define INV_TWOPI    0.15915494309189533577f
	#define INV_FOURPI   0.07957747154594766788f
	#define SQRT_TWO     1.41421356237309504880f
	#define INV_SQRT_TWO 0.70710678118654752440f

	/// Values between -epsilon and epsilon are considered to be zero.
	inline bool is_zero(const double x)
	{
		if ((x < EPSILON) && (x > -EPSILON)) return true; else return false;
	}

	/// Returns true if the arguments are equal within epsilon tolerance.
	inline bool is_equal(const double x, const double y)
	{
		return is_zero(x-y);
	}

	/// Returns true if the vectors components are equal between epsilon tolerance
	inline bool is_equal(const Vector3d& v1, const Vector3d& v2) 
	{
		double v1_x = v1.data()[0];
		double v1_y = v1.data()[1];
		double v1_z = v1.data()[2];

		double v2_x = v2.data()[0];
		double v2_y = v2.data()[1];
		double v2_z = v2.data()[2];

		return is_equal(v1_x, v2_x) && is_equal(v1_y, v2_y) && is_equal(v1_z, v2_z);
	}

	//// Convert radians to degrees
	inline double rad2deg(double value) { return value * (180.0f / M_PI); }

	/// Convert degrees to radians
	inline double deg2rad(double value) { return value * (M_PI / 180.0f); }

	///Clamp a double to be between 0.0 and 1.0.
    inline double clamp(double x){ return x<0.0f ? 0.0f : x>1.0f ? 1.0f : x; }
    
    ///Cast a double between 0.0 and 1.0 to a char. A gamme value of 2.2 is used.
    inline char to_char(double x){ return char(pow(clamp(x),1/2.2)*255+.5); }
}
