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
#include <object.hpp>
#include <ray.hpp>
#include <scene.hpp>
#include <utils.hpp>

namespace rt
{
	///Forward Declaration
	class scene_t;

	/**
	 * \brief This is the abstract base class for all integrators.
	 * The integrator computes the radiance estimate along a ray. 
	 **/
	class integrator_t
	{
	public:
		/// Depth of recursion for the integrator.
		/// This may or may not be used by the implementing class
		int depth;

		/// Constructor
		integrator_t():depth(1) { }
		/// Constructor
		integrator_t(int _d):depth(_d) { }
		/// Destructor
		virtual ~integrator_t() { }

		///Returns a name for the integrator.
		virtual std::string get_name(void) const = 0;

		///Returns the radiance estimate along ray _ray, for scene scn, at bounce depth d.
		virtual color_t radiance(const scene_t* scn, ray_t& _ray, int d) const = 0;
	};

	/**
	 * \brief This is the Whitted integrator - this implements standard whitted raytracing.
	 **/
	class whitted_integrator_t : public integrator_t
	{
	public:
		
		/// Constructor
		whitted_integrator_t() { }
		/// Constructor
		whitted_integrator_t(int _d):integrator_t(_d) { } 
		/// Destructor
		virtual ~whitted_integrator_t() { }

		/// Returns the name of the integrator.
		virtual std::string get_name(void) const {return "whitted";}

		/// Returns the radiance estimate along ray _ray, for scene scn, at bounce depth d.
		virtual color_t radiance(const scene_t* scn, ray_t& _ray, int d) const;
	};
}
