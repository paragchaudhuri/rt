#ifndef _SPHERE_HPP_
#define _SPHERE_HPP_

#include <string>
#include <Eigen/Dense>

#include <material.hpp>
#include <object.hpp>
#include <ray.hpp>
#include <utils.hpp>


namespace rt
{
	class sphere_t : public object_t
	{
	private:
		Eigen::Vector3f center;
		float radius;
		material_t* mat;

	public:
		sphere_t(material_t* _mat);
		sphere_t(material_t* _mat, Eigen::Vector3f _c, float _r);

		virtual ~sphere_t();

		std::string get_name(void) const { return std::string("sphere"); }

		bool intersect(hit_t& result, const ray_t& _ray) const;

		Eigen::Vector3f get_normal(Eigen::Vector3f& _p) const;

		material_t* get_material(void) const;

		virtual void print(std::ostream &stream) const;
	};
}

#endif