#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <string>
#include <utility>

#include <material.hpp>
#include<ray.hpp>


namespace rt
{

	class object_t;

	typedef std::pair<const object_t*, float> hit_t; 

	class object_t
	{
	public:
		object_t();
		virtual ~object_t();

		virtual std::string get_name(void) const = 0;

		virtual bool intersect(hit_t& result, const ray_t& _ray) const = 0;

		virtual Vector3f get_normal(Vector3f& _p) const = 0;

		virtual material_t* get_material(void) const = 0; 

		virtual void print(std::ostream &stream) const = 0;
	};
}
#endif