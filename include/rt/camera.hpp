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
#include <transform.hpp>
#include <utils.hpp>

/**
 * \brief Everything in rt is a part of this namespace.
 */ 
namespace rt
{
	/**
	 * \brief A camera class that implements a perspective camera.
	 */
	class camera_t
	{
	private:	
		/// Since the cam2world is set to identity by default, these are not used.
		/// To use these, add the computation of cam2world to init()
		/// Default eye is at (0,0,0), lookat is (0,0,1), up is (0,1,0)
		Vector3d lookat, eye, up;

		/// Horizontal field of view
		double fov;

		/// Distance to near plane along lookat
		double near;

		/// Distance to far plane along lookat
		double far;

		/// Aspect ration of the image on the near plane
		double aspect;

		/// VCS to CCS transform
		transform_t image2cam;
		/// WCS to VCS transform
		transform_t cam2world;

		/// Compute the transforms from parameters
		void init(void);

	public:

		/// Default constructor
		camera_t();
		
		/// Constructor
		camera_t(const Vector3d _lat, const Vector3d _eye, const Vector3d _up, double _fov=30.0, double near=1e-4f, double far=1e4f);
		
		/// Copy Constructor
		camera_t(const camera_t &_cam);

		/// Default destructor
		~camera_t();

		/// Return the lookat
		const Vector3d get_lookat(void);
		
		/// Return the eye
		const Vector3d get_eye(void);

		/// Returns the up vector
		const Vector3d get_up(void);

		/// Returns the fov
		const double get_fov(void);

		/// Sets the aspect ratio, and recomputes transforms.
		void set_aspect(double _a) { aspect=_a; init(); }

		/// Generate a ray from the camera center in the direction of _pixelpos
		color_t sample_ray(ray_t &ray, const Vector2f& _pixelpos) const;

		/// Print the camera to a stream
		void print(std::ostream &stream);

	};
}
