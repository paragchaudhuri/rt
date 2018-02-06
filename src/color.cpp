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

#include <color.hpp>

using namespace rt;

color_t::color_t(double _val) : base(_val,_val,_val) { }

color_t::color_t(double _r, double _g, double _b): base(_r,_g,_b) { }

color_t color_t::clamp(void) const 
{ 
	return color_t(std::max(r(), 0.0), std::max(g(), 0.0), std::max(b(), 0.0)); 
}

bool color_t::is_valid(void) const
{
	for (int i=0; i<3; ++i) 
	{
        double value = coeff(i);
        if (value < 0 || !std::isfinite(value))
            return false;
    }
    return true;
}

void color_t::print(std::ostream &stream)
{
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "[ ", " ]");
	
	stream<<Eigen::Vector3d(r(),g(),b()).format(CommaInitFmt)<<std::endl;
}