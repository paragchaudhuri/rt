#ifndef _MATERIAL_HPP_
#define _MATERIAL_HPP_

#include <string>

#include <Eigen/Dense>

#include <color.hpp>

namespace rt
{
	class material_t
	{
	private:
		std::string name;
	public:
		material_t(std::string _name);
		virtual ~material_t();

		std::string get_name(void) const;

		virtual color_t get_diffuse(void) const = 0;
		virtual color_t get_reflect(void) const = 0;
		virtual color_t get_transmit(void) const = 0;

		virtual float get_eta(void) const = 0;
		virtual float get_shininess(void) const = 0;

		virtual void print(std::ostream &stream) const = 0;
	};

	class simplemat_t : public material_t
	{
	private:
		color_t d, r, t;
		float eta, n;

		bool is_reflect;
		bool is_transmit;

	public:
		simplemat_t(std::string _name, color_t _d, color_t _r, color_t _t, float _eta, float _n, bool _is_r, bool _is_t);
		virtual ~simplemat_t();

		virtual color_t get_diffuse(void) const;
		virtual color_t get_reflect(void) const;
		virtual color_t get_transmit(void) const;

		virtual float get_eta(void) const;
		virtual float get_shininess(void) const;

		bool get_is_reflect(void) const;
		bool get_is_transmit(void) const;

		virtual void print(std::ostream &stream) const;
	};
}

#endif