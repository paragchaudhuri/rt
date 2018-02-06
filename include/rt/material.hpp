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

#include <color.hpp>
#include <utils.hpp>

namespace rt
{
	/**
	* \brief This is the abstract base class for all materials in rt.
	**/
	class material_t
	{
	private:
		/// Name of the material.
		std::string name;
	public:
		/// Constructor.
		material_t(std::string _name);

		/// Destructor.
		virtual ~material_t();

		/// Returns the name of the material.
		std::string get_name(void) const;

		/// Returns the diffuse coefficient (kd) for direct illumination.
		virtual color_t get_diffuse(void) const = 0;
		/// Returns the specular reflection coefficient (ks) for direct illumination.
		virtual color_t get_specular(void) const = 0;
		/// Returns the transmission coefficient (kt). The reflection coefficient  (kr) can be 1-kt.
		virtual color_t get_transmit(void) const = 0;
		/// Returns the reflection coefficient (kr), which can be 1-kt.
		virtual color_t get_reflect(void) const = 0;

		/// Returns the coefficient of refraction
		virtual double get_eta(void) const = 0;
		/// Returns the shininess value
		virtual double get_shininess(void) const = 0;

	        /// Returns true if surface reflects, else returns false.
	        virtual bool get_is_reflect(void) const = 0;
	        /// Returns false if surface transmits, else returns false.
	        virtual bool get_is_transmit(void) const = 0;

		/// Prints information about the material to the stream.
		virtual void print(std::ostream &stream) const = 0;
	};


	/**
	* \brief This implements a class to represent simple solid surface materials.
	**/
	class simplemat_t : public material_t
	{
	private:
		/// Material Coefficients
		color_t kd, ks, kr, kt;
		///  Material Coefficients
		double eta, n;

		/// Does the surface reflect any illumination.
		bool is_reflect;
		/// Does the surface transmit any illumination.
		bool is_transmit;

	public:
		/// Constructor.
		simplemat_t(std::string _name, color_t _kd, color_t _ks, color_t _kr, color_t _kt, double _eta, double _n, bool _is_r, bool _is_t);
		/// Destructor.
		virtual ~simplemat_t();

		/// Returns the diffuse coefficient (kd) for direct illumination.
		virtual color_t get_diffuse(void) const;
		/// Returns the specular reflection coefficient (ks) for direct illumination.
		virtual color_t get_specular(void) const;
		/// Returns the transmission coefficient (kt). The reflection coefficient  (kr) can be 1-kt.
		virtual color_t get_transmit(void) const;
		/// Returns the reflection coefficient (kr), which can be 1-kt.
		virtual color_t get_reflect(void) const;

		/// Returns the coefficient of refraction
		virtual double get_eta(void) const;
		/// Returns the shininess value
		virtual double get_shininess(void) const;

		/// Returns true if surface reflects, else returns false.
		bool get_is_reflect(void) const;
		/// Returns false if surface transmits, else returns false.
		bool get_is_transmit(void) const;

		/// Prints information to streams.
		virtual void print(std::ostream &stream) const;
	};
}
