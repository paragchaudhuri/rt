#include <ray.hpp>

using namespace rt;

ray_t::ray_t():origin(Vector3f(0.0f,0.0f,0.0f)), direction(Vector3f(0.0f,0.0f,1.0f)), mint(EPSILON), maxt(std::numeric_limits<float>::infinity())
{ }

ray_t::ray_t(const Vector3f& _o, const Vector3f& _d):origin(_o), direction(_d), mint(EPSILON), maxt(std::numeric_limits<float>::infinity())
{ }

ray_t::ray_t(const Vector3f& _o, const Vector3f& _d, const float _mint, const float _maxt):origin(_o), direction(_d), mint(_mint), maxt(_maxt)
{ }

ray_t::ray_t(const ray_t &_ray): origin(_ray.origin), direction(_ray.direction), 
       mint(_ray.mint), maxt(_ray.maxt) 
{ }

ray_t::ray_t(const ray_t &_ray, float _mint, float _maxt): origin(_ray.origin), direction(_ray.direction), 
     	mint(_mint), maxt(_maxt) 
{ }

ray_t::~ray_t()
{ }

const Vector3f ray_t::operator()(const float _t) {return (origin + _t*direction);}