#pragma once

#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include <fstream>
#include <Eigen/Dense>

#include <ray.hpp>
#include <utils.hpp>

namespace rt
{
	class transform_t
	{
	private:
		Eigen::Matrix4f t;
    	Eigen::Matrix4f invt;
	public:
		transform_t(): 
        t(Eigen::Matrix4f::Identity()), invt(Eigen::Matrix4f::Identity()) { }

    	/// Create a new transform_t instance for the given matrix 
    	transform_t(const Eigen::Matrix4f &_t);

    	/// Create a new transform_t instance for the given matrix and its inverse
    	transform_t(const Eigen::Matrix4f &_t, const Eigen::Matrix4f &_invt) 
        : t(_t), invt(_invt) { }

    	/// Return the underlying matrix
    	const Eigen::Matrix4f &get_matrix() const 
    	{
   		    return t;
    	}

    	/// Return the inverse of the underlying matrix
    	const Eigen::Matrix4f &get_inverse_matrix() const 
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
    	Vector3f operator*(const Vector3f &_v) const 
    	{
    	    return t.topLeftCorner<3,3>() * _v;
    	}

    	/// Apply the homogeneous transformation to a 3D normal
    	Vector3f transform_normal(const Vector3f &_n) const 
    	{
    	    return invt.topLeftCorner<3, 3>().transpose() * _n;
    	}

   		/// transform_t a point by an arbitrary matrix in homogeneous coordinates
    	Vector3f transform_point(const Vector3f &_p) const 
    	{
     	   Vector4f result = t * Vector4f(_p[0], _p[1], _p[2], 1.0f);
     	   return result.head<3>() / result.w();
    	}

    	// Apply the homogeneous transform_tation to a ray
    	ray_t operator*(const ray_t &_r) const 
    	{
     	   return ray_t(
      	      transform_point(_r.origin), 
        	    operator*(_r.direction));
    	}

   
        void print(std::ostream &stream);
	};
}

#endif