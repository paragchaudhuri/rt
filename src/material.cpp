#include <material.hpp>

using namespace rt;

material_t::material_t(std::string _name)
{ name = _name; }

material_t::~material_t()
{ }

std::string material_t::get_name(void) const
{ return name; }

simplemat_t::simplemat_t(std::string _name, color_t _d, color_t _r, color_t _t, float _eta, float _n, bool _is_r, bool _is_t):
	material_t(_name),d(_d),r(_r),t(_t),eta(_eta),n(_n),is_reflect(_is_r),is_transmit(_is_t)
	{ }

simplemat_t::~simplemat_t()
{ }

color_t simplemat_t::get_diffuse(void) const { return d; }
color_t simplemat_t::get_reflect(void) const { return r; }
color_t simplemat_t::get_transmit(void) const { return t; }

float simplemat_t::get_eta(void) const { return eta; }
float simplemat_t::get_shininess(void) const {return n; }

bool simplemat_t::get_is_reflect(void) const {return is_reflect;}
bool simplemat_t::get_is_transmit(void) const { return is_transmit;}

void simplemat_t::print(std::ostream &stream) const
{
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "[ ", " ]");
	
	stream<<"Material Properties: -------------------------------"<<std::endl;
	stream<<"Name: "<<this->get_name()<<std::endl;
	stream<<"Diffuse: "<<d.format(CommaInitFmt)<<std::endl;
	stream<<"Reflect: "<<r.format(CommaInitFmt)<<std::endl;
	stream<<"Transmit: "<<t.format(CommaInitFmt)<<std::endl;
	stream<<"eta: "<<eta<<std::endl;
	stream<<"Shininess: "<<n<<std::endl;
	stream<<"Is Reflecting: "<<is_reflect<<std::endl;
	stream<<"Is Transmiting: "<<is_transmit<<std::endl<<std::endl;
}