#include <light.hpp>

using namespace rt;

light_t::light_t() { }
light_t::~light_t() { }


point_light_t::point_light_t(const Vector3f& _pos, const Vector3f& _col, const float _ka): pos(_pos), col(_col), ka(_ka) 
{ }

point_light_t::~point_light_t()
{ }

color_t point_light_t::direct(const Vector3f& hitpt, const Vector3f& normal, const material_t* mat, const scene_t* scn) const
{
	color_t col(0.0,1.0,0.0);
	return col;
}
		

void point_light_t::print(std::ostream &stream) const
{
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, ", ", ", ", "", "", "[ ", " ]");
	
	stream<<"Light Properties: -------------------------------"<<std::endl;
	stream<<"Type: Point Light"<<std::endl;
	stream<<"Position: "<<pos.format(CommaInitFmt)<<std::endl;
	stream<<"Color: "<<col.format(CommaInitFmt)<<std::endl;
	stream<<"Ambient Coefficient: "<<ka<<std::endl<<std::endl;
}