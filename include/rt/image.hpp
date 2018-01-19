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
	class image_t
	{
	private:
		int width, height;
		float aspect;

		color_t bgcolor;

		char *data;

	public:
		image_t(int width, int height, color_t _bgc);
		virtual ~image_t();

		int get_width(void) const;
		int get_height(void) const;
		float get_aspect(void) const;
		
		color_t get_bgcolor(void) const;

		Eigen::Vector2f sample_pixel(unsigned int _x, unsigned int _y) const;

		color_t get_pixel(unsigned int _x, unsigned int _y) const;
		void set_pixel(unsigned int _x, unsigned int _y, color_t _col);

		void write(std::string filename);

		void print(std::ostream &stream);
	};
}