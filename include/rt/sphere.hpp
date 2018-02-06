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

#include <material.hpp>
#include <object.hpp>
#include <ray.hpp>
#include <utils.hpp>


namespace rt
{
	/**
	 * \brief The sphere object class.
	 **/
	class sphere_t : public object_t
	{
	private:
		/// Sphere center
		Eigen::Vector3d center;

		/// Sphere radius
		double radius;

		/// Sphere material
		material_t* mat;

	public:
		/// Constructor
		sphere_t(material_t* _mat);
		/// Constructor
		sphere_t(material_t* _mat, Eigen::Vector3d _c, double _r);
		/// Destuctor
		virtual ~sphere_t();

		/// Returns the mandatory object name
		std::string get_name(void) const { return std::string("sphere"); }

		/**
		* Returns true if the _ray hits this object. The hit information is returned in result. 
		* This is not valid if there is no intersection and the function returns false.
		**/
		bool intersect(hit_t& result, const ray_t& _ray) const;

		/// Returns the normal to the surface at point _p.
		Eigen::Vector3d get_normal(Eigen::Vector3d& _p) const;

		/// Returns the material for the sphere.
		material_t* get_material(void) const;

		/// Prints information about the sphere. to stream.
		virtual void print(std::ostream &stream) const;
	};
}
