#pragma once

#ifndef _RAY_HPP_
#define _RAY_HPP_

#include <Eigen/Dense>

#include <utils.hpp>


using namespace Eigen;

namespace rt
{
	class ray_t
	{
	public:
		Vector3f origin;
		Vector3f direction;
		float mint, maxt;

		ray_t();
		ray_t(const Vector3f& _o, const Vector3f& _d);
		ray_t(const Vector3f& _o, const Vector3f& _d, const float _mint, const float _maxt);
		ray_t(const ray_t &_ray);
		ray_t(const ray_t &_ray, float _mint, float _maxt);

		virtual ~ray_t();

		const Vector3f operator()(const float _t);
	};
}

#endif