#include <rt.hpp>

using namespace rt;

void render(const rt::scene_t* scn)
{
	unsigned int w=scn->img->get_width();
	unsigned int h=scn->img->get_height();

	for (unsigned int i=0; i<w; i++)
	{
		for (unsigned int j=0; j<h; j++)
		{
			rt::ray_t ray;
			int d;
			Eigen::Vector2f psample=scn->img->sample_pixel(i,j);
			rt::color_t col = scn->cam->sample_ray(ray, psample);

			col *= scn->intg->radiance(scn, ray, d);

			scn->img->set_pixel(i,j,col);
		}

	}
}

int main(int argc, char **argv)
{
	try
	{
		std::string scene_filename("myscene.xml");
  		rt::scene_t scn(scene_filename);

  		render(&scn);

		std::string img_filename = scene_filename;
    	size_t lastdot = img_filename.find_last_of(".");
    	if (lastdot != std::string::npos)
     		img_filename.erase(lastdot, std::string::npos);
   		img_filename += ".ppm";
  	
  		scn.img->write(img_filename);
  } 
  catch (const std::exception &e)
  {
  	std::cerr<<"Error: "<<e.what()<<std::endl;
  	return -1;
  }
  	
  return 0;
}
