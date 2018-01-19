#include <iostream>

#include <integrator.hpp>

using namespace rt;

color_t whitted_integrator_t::radiance(const scene_t* _scn, ray_t& _ray, int& d) const
{
	bool found_intersection=false;
	std::vector<object_t*>::const_iterator oit;
	hit_t hit, minhit;
	Eigen::Vector3f hitpt, normal;

	for (oit=_scn->objs.begin(); oit!=_scn->objs.end(); oit++)
	{
		if ((*oit)->intersect(hit, _ray))
		{
		  _ray.maxt = hit.second;
		  minhit = hit;
		  
		  hitpt = _ray.origin+_ray.maxt*_ray.direction;
		  normal = (*oit)->get_normal(hitpt);

		  found_intersection=true;
		}
		
	}
	
	color_t d_col(0.0);
	if(found_intersection)
	{
		std::list<light_t*>::const_iterator lit;
		for(lit=_scn->lits.begin(); lit!=_scn->lits.end(); lit++)
		{
			d_col += (*lit)->direct(hitpt, normal, minhit.first->get_material(), _scn);
		}
	}
	else d_col = _scn->img->get_bgcolor();

	return d_col;
}