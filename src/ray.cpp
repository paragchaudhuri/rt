#include <ray.hpp>

using namespace rt;

ray_t::ray_t():origin(Vector3d(0.0,0.0,0.0)), direction(Vector3d(0.0,0.0,1.0)), mint(EPSILON), maxt(std::numeric_limits<double>::infinity())
{ }

ray_t::ray_t(const Vector3d& _o, const Vector3d& _d):origin(_o), direction(_d), mint(EPSILON), maxt(std::numeric_limits<double>::infinity())
{ }

ray_t::ray_t(const Vector3d& _o, const Vector3d& _d, const double _mint, const double _maxt):origin(_o), direction(_d), mint(_mint), maxt(_maxt)
{ }

ray_t::ray_t(const ray_t &_ray): origin(_ray.origin), direction(_ray.direction), 
       mint(_ray.mint), maxt(_ray.maxt) 
{ }

ray_t::ray_t(const ray_t &_ray, double _mint, double _maxt): origin(_ray.origin), direction(_ray.direction), 
     	mint(_mint), maxt(_maxt) 
{ }

ray_t::~ray_t()
{ }

const Vector3d ray_t::operator()(const double _t) {return (origin + _t*direction);}