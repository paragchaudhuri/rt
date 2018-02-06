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

#include <ray.hpp>
#include <utils.hpp>

namespace rt
{
    /**
     * \brief Implements a 4x4 tranformation. Stores the transformation and its inverse for convenience.
    **/
	class transform_t
	{
	private:
        /// The transformation
		Eigen::Matrix4d t;
        /// The inverse transformation
    	Eigen::Matrix4d invt;
	public:

        /// Constructor
		transform_t(): 
        t(Eigen::Matrix4d::Identity()), invt(Eigen::Matrix4d::Identity()) { }

    	/// Create a new transform_t instance for the given matrix 
    	transform_t(const Eigen::Matrix4d &_t);

    	/// Create a new transform_t instance for the given matrix and its inverse
    	transform_t(const Eigen::Matrix4d &_t, const Eigen::Matrix4d &_invt) 
        : t(_t), invt(_invt) { }

    	/// Return the underlying matrix
    	const Eigen::Matrix4d &get_matrix() const 
    	{
   		    return t;
    	}

    	/// Return the inverse of the underlying matrix
    	const Eigen::Matrix4d &get_inverse_matrix() const 
    	{
       		 return invt;
    	}

    	/// Return the inverse transformation
    	transform_t inverse() const 
    	{
    	   return transform_t(invt, t);
   		}

    	/// Concatenate with another transform_t
   		transform_t operator*(const transform_t &_t) const;

    	/// Apply the homogeneous transformation to a 3D vector
    	Vector3d operator*(const Vector3d &_v) const 
    	{
    	    return t.topLeftCorner<3,3>() * _v;
    	}

    	/// Apply the homogeneous transformation to a 3D normal
    	Vector3d transform_normal(const Vector3d &_n) const 
    	{
    	    return invt.topLeftCorner<3, 3>().transpose() * _n;
    	}

   		/// transform_t a point by an arbitrary matrix in homogeneous coordinates
    	Vector3d transform_point(const Vector3d &_p) const 
    	{
     	   Vector4d result = t * Vector4d(_p[0], _p[1], _p[2], 1.0f);
     	   return result.head<3>() / result.w();
    	}

    	// Apply the homogeneous transform_tation to a ray
    	ray_t operator*(const ray_t &_r) const 
    	{
     	   return ray_t(
      	      transform_point(_r.origin), 
        	    operator*(_r.direction));
    	}

        /// Print the transformation to the stream
        void print(std::ostream &stream);
	};
}