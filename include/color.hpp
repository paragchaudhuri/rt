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

#include<utils.hpp>

namespace rt
{
    /**
     * \brief Class to represent a Red, Green, Blue color value.
     */
	class color_t : public Eigen::Array3f 
	{
	public:
		typedef Eigen::Array3f base;

        ///Constructor to initialize color value to a constant for all components.
		color_t(float _val=0.f);

        ///Constructor to initialize color value to desired values for the components.
		color_t(float _r, float _g, float _b);

		/// Construct a color vector from ArrayBase (needed to play nice with Eigen).
    	template <typename Derived> color_t(const Eigen::ArrayBase<Derived>& p): base(p) { }

    	/// Assign a color vector from ArrayBase (needed to play nice with Eigen).
    	template <typename Derived> color_t &operator=(const Eigen::ArrayBase<Derived>& p) 
    	{
        	this->base::operator=(p);
        	return *this;
    	}

    	/// Return the red channel.
    	float &r() { return x(); }
        /// Return the red channel (const).
    	const float &r() const { return x(); }
    	/// Return the green channel.
    	float &g() { return y(); }
        /// Return the green channel (const).
    	const float &g() const { return y(); }
    	/// Return the blue channel.
    	float &b() { return z(); }
        /// Return the blue channel (const).
    	const float &b() const { return z(); }
        
        ///Clamp the color value to a non-negative float on each channel.
        color_t clamp(void) const;

    	/// Check if the color vector contains a NaN/Inf/negative value.
    	bool is_valid(void) const;

        ///Print the color value to a stream.
        void print(std::ostream &stream);
		
	};

}