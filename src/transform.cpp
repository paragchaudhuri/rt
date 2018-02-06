#include <transform.hpp>

using namespace rt;

transform_t::transform_t(const Eigen::Matrix4d &_t)
    : t(_t), invt(_t.inverse()) { }

transform_t transform_t::operator*(const transform_t &_t) const 
{
    return transform_t(t * _t.t, _t.invt * invt);
}

void transform_t::print(std::ostream &stream)
{
	stream << t.format(Eigen::IOFormat(4, 0, ", ", ";\n", "", "", "[", "]"));
}