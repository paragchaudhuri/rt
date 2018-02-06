#include <material.hpp>

using namespace rt;

material_t::material_t(std::string _name)
{ name = _name; }

material_t::~material_t()
{ }

std::string material_t::get_name(void) const
{ return name; }

simplemat_t::simplemat_t(std::string _name, color_t _kd, color_t _ks, color_t _kr, color_t _kt, double _eta, double _n, bool _is_r, bool _is_t):
	material_t(_name),kd(_kd),ks(_ks),kr(_kr),kt(_kt),eta(_eta),n(_n),is_reflect(_is_r),is_transmit(_is_t)
	{ }

simplemat_t::~simplemat_t()
{ }

color_t simplemat_t::get_diffuse(void) const { return kd; }
color_t simplemat_t::get_specular(void) const { return ks; }
color_t simplemat_t::get_reflect(void) const { return kr; }
color_t simplemat_t::get_transmit(void) const { return kt; }

double simplemat_t::get_eta(void) const { return eta; }
double simplemat_t::get_shininess(void) const {return n; }

bool simplemat_t::get_is_reflect(void) const {return is_reflect;}
bool simplemat_t::get_is_transmit(void) const { return is_transmit;}

void simplemat_t::print(std::ostream &stream) const
{
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "[ ", " ]");
	
	stream<<"Material Properties: -------------------------------"<<std::endl;
	stream<<"Name: "<<this->get_name()<<std::endl;
	stream<<"kd: "<<kd.format(CommaInitFmt)<<std::endl;
	stream<<"ks: "<<ks.format(CommaInitFmt)<<std::endl;
	stream<<"kr: "<<kr.format(CommaInitFmt)<<std::endl;
	stream<<"kt: "<<kt.format(CommaInitFmt)<<std::endl;
	stream<<"eta: "<<eta<<std::endl;
	stream<<"Shininess: "<<n<<std::endl;
	stream<<"Is Reflecting: "<<is_reflect<<std::endl;
	stream<<"Is Transmiting: "<<is_transmit<<std::endl<<std::endl;
}