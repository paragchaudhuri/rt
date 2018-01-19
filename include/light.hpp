#ifndef _LIGHT_HPP_
#define _LIGHT_HPP_

#include <Eigen/Dense>

#include <color.hpp>
#include <material.hpp>
#include <scene.hpp>

using namespace Eigen;


namespace rt
{
	class scene_t;

	class light_t
	{
	private:

	public:
		light_t();
		virtual ~light_t();

		virtual color_t direct(const Vector3f& hitpt, const Vector3f& normal, const material_t* mat, const scene_t* scn) const = 0;

		virtual void print(std::ostream &stream) const = 0;
	};

	class point_light_t : public light_t
	{
	private:
		Vector3f pos;
		Vector3f col;

		float ka;

	public:
		point_light_t(const Vector3f& _pos, const Vector3f& _col, const float _ka);
		virtual ~point_light_t();

		virtual color_t direct(const Vector3f& hitpt, const Vector3f& normal, const material_t* mat, const scene_t* scn) const;

		virtual void print(std::ostream &stream) const;
	};
}
#endif