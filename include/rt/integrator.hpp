#ifndef _ITEGRATOR_HPP_
#define _ITEGRATOR_HPP_

#include <string>
#include <Eigen/Dense>

#include <color.hpp>
#include <object.hpp>
#include <ray.hpp>
#include <scene.hpp>


namespace rt
{
	class scene_t;

	class integrator_t
	{
	public:
		int depth;

		integrator_t():depth(1) { }
		integrator_t(int _d):depth(_d) { }
		virtual ~integrator_t() { }

		virtual std::string get_name(void) const = 0;

		virtual color_t radiance(const scene_t* scn, ray_t& _ray, int& d) const = 0;
	};

	class whitted_integrator_t : public integrator_t
	{
	public:
		
		whitted_integrator_t() { }
		whitted_integrator_t(int _d):integrator_t(_d) { } 
		virtual ~whitted_integrator_t() { }

		virtual std::string get_name(void) const {return "whitted";}

		virtual color_t radiance(const scene_t* scn, ray_t& _ray, int& d) const;
	};
}
#endif