#include <scene.hpp>

using namespace rt;

std::string scene_t::parse_property(XMLElement* _elm, std::string _property, std::string _type) 
{
	XMLElement* subelm = _elm->FirstChildElement(_property.c_str());
	if (!subelm)
		throw std::invalid_argument("Scene file property expected property");
	return parse_parameter(subelm, _type);
}

std::string scene_t::parse_parameter(XMLElement* _elm, std::string _type) 
{
	const char *value = _elm->Attribute(_type.c_str());
	if (!value)
		throw std::invalid_argument("Scene file parameter expected type");
	return std::string(value);
}

material_t* scene_t::find_material(std::string name, const std::list<material_t*> matlist) 
{
	std::list<material_t*>::const_iterator it;
	for (it = matlist.begin(); it != matlist.end(); it++)
	{
		if((*it)->get_name() == name) return (*it);
	}
	
	throw std::invalid_argument("Material from object not found in scene file.");
}


int scene_t::parse_int(XMLElement* _elm, std::string property)
{
	return parse_int(parse_property(_elm, property, "int"));
}

int scene_t::parse_int(XMLElement* _elm)
{
	return parse_int(parse_parameter(_elm, "int"));
}

int scene_t::parse_int(std::string _val)
{
	std::istringstream stream(_val);

	int val;
	stream >> val;

	return val;
}

double scene_t::parse_double(XMLElement* _elm, std::string property) 
{
	return parse_double(parse_property(_elm, property, "double"));
}

double scene_t::parse_double(XMLElement* _elm) 
{
	return parse_double(parse_parameter(_elm, "double"));
}

double scene_t::parse_double(std::string _val) 
{
	std::istringstream stream(_val);

	double val;
	stream >> val;

	return val;
}

bool scene_t::parse_bool(XMLElement* _elm, std::string property) 
{
	return parse_bool(parse_property(_elm, property, "bool"));
}

bool scene_t::parse_bool(XMLElement* _elm) 
{
	return parse_bool(parse_parameter(_elm, "bool"));
}

bool scene_t::parse_bool(std::string _val) 
{
	std::istringstream stream(_val);

	bool val;
	stream >> val;

	return val;
}


double scene_t::parse_angle(XMLElement* _elm, std::string _property) 
{
	return parse_angle(parse_property(_elm, _property, "angle"));
}

double scene_t::parse_angle(XMLElement* _elm) 
{
	return parse_angle(parse_parameter(_elm, "angle"));
}

double scene_t::parse_angle(std::string _val) 
{
	std::istringstream stream(_val);	

	double val;
	std::string unit;
	stream >> val >> unit;

	if (unit == "deg")
		val *= M_PI / 180.0;
	else if (unit != "rad")
		throw std::invalid_argument("Angle must have units either \"deg\" or \"rad\"");

	return val;
}

color_t scene_t::parse_color(XMLElement* _elm, std::string _property) 
{
	return parse_color(parse_property(_elm, _property, "color"));
}

color_t scene_t::parse_color(XMLElement* _elm) 
{
	return parse_color(parse_parameter(_elm, "color"));
}

color_t scene_t::parse_color(std::string _val) 
{
	std::istringstream stream(_val);

	double x, y, z;
	stream >> x >> y >> z;

	color_t res(x,y,z);

	return res;
}

Eigen::Vector3d scene_t::parse_vector3(XMLElement* _elm, std::string _property) 
{
	return parse_vector3(parse_property(_elm, _property, "vector3"));
}

Eigen::Vector3d scene_t::parse_vector3(XMLElement* _elm) 
{
	return parse_vector3(parse_parameter(_elm, "vector3"));
}

Eigen::Vector3d scene_t::parse_vector3(std::string _val) 
{
	std::istringstream stream(_val);

	double x, y, z;
	stream >> x >> y >> z;

	Eigen::Vector3d res(x,y,z);

	return res;
}




bool scene_t::parse_scenefile(void)
{
	XMLError load_okay = scenexml.LoadFile(scenefile.c_str());

	if (load_okay!= tinyxml2::XML_SUCCESS)
	{
		throw std::runtime_error("Cannot read scene file.");
	}

	XMLElement* doc_root = scenexml.RootElement();
	if (!doc_root || !XMLUtil::StringEqual(doc_root->Name(), "rt-scene"))
		throw std::runtime_error("Scene file is not a valid scene description");

	cam = parse_camera(doc_root);
	cam->print(std::cerr);

	img = parse_image(doc_root);
	img->print(std::cerr);

	cam->set_aspect(img->get_aspect());

	intg = parse_integrator(doc_root);

	nummats = parse_materials(doc_root);
	std::list<material_t*>::iterator it;
	for (it=mats.begin(); it!=mats.end(); it++)
	{
		(*it)->print(std::cerr);
	}

	numobjs = parse_objects(doc_root, mats);
	std::vector<object_t*>::iterator oit;
	for (oit=objs.begin(); oit!=objs.end(); oit++)
	{
		(*oit)->print(std::cerr);
	}

	numlits = parse_lights(doc_root);
	std::list<light_t*>::iterator lit;
	for (lit=lits.begin(); lit!=lits.end(); lit++)
	{
		(*lit)->print(std::cerr);
	}

	return true;

}

camera_t* scene_t::parse_camera(XMLElement* _elm) 
{
	XMLElement* elm_camera = _elm->FirstChildElement("camera");
	if (!elm_camera)
		throw std::runtime_error("Scene file does not contain a camera.");

	return (new camera_t(
					parse_vector3(elm_camera, "lookat"),
					parse_vector3(elm_camera, "eye"),
					parse_vector3(elm_camera, "up"),
					parse_angle(elm_camera, "fov"),
					parse_double(elm_camera,"near"),
					parse_double(elm_camera,"far")
				));
}

int scene_t::parse_objects(XMLElement* _elm, const std::list<material_t*>& matlist)
{
	objs.clear();

	XMLElement* elm_obj = _elm->FirstChildElement("objects");
	if (!elm_obj)
		throw std::runtime_error("No objects found in scene file.");

	int numobj=1;
	XMLElement* elm_child = elm_obj->FirstChildElement();
	while (elm_child)
	{
		std::string name(elm_child->Name());

		if (name == "sphere")
			objs.push_back(parse_object_sphere(elm_child, matlist));
		else
			throw std::invalid_argument("Invalid object in scene file.");

		elm_child = elm_child->NextSiblingElement();
		numobj++;
	}

	if (objs.empty())
		throw std::invalid_argument("Could not parse object.");
	else 
		return numobj;
}

object_t* scene_t::parse_object_sphere(XMLElement* _elm, const std::list<material_t*>& matlist) 
{
	return (object_t*)(new sphere_t(find_material(parse_parameter(_elm, "material"),	matlist),
									parse_vector3(_elm,  "center"),
									parse_double(_elm, "radius")));
}

int scene_t::parse_materials(XMLElement* _elm) 
{
	mats.clear();

	XMLElement* elm_mat = _elm->FirstChildElement("materials");
	if (!elm_mat)
		throw std::runtime_error("No materials found in scene file.");

	int nummat=1;
	XMLElement* elm_child = elm_mat->FirstChildElement();
	while (elm_child) 
	{
		
		mats.push_back(parse_simplemat(elm_child));
		
		elm_child = elm_child->NextSiblingElement();

		nummat++;
	}

	return nummat;
}

material_t* scene_t::parse_simplemat(XMLElement* _elm) 
{
	return (material_t*)(new simplemat_t(
			parse_parameter(_elm, "id"),
			parse_color(_elm, "diffuse"),
			parse_color(_elm, "specular"),
			parse_color(_elm, "reflect"),
			parse_color(_elm, "transmit"),
			parse_double(_elm, "eta"),
			parse_double(_elm, "n"),
			parse_bool(_elm, "isreflect"),
			parse_bool(_elm, "istransmit")));
}


image_t* scene_t::parse_image(XMLElement* _elm)
{
	XMLElement* elm_img = _elm->FirstChildElement("image");
	if (!elm_img)
		throw std::runtime_error("No image found in scene file.");

	color_t bgc = parse_color(elm_img, "bgcolor");
	return new image_t(	
					parse_double(elm_img, "width"),
					parse_double(elm_img, "height"),
					bgc);

}

int scene_t::parse_lights(XMLElement* _elm) 
{
	lits.clear();

	XMLElement* elm_lit = _elm->FirstChildElement("lights");
	if (!elm_lit)
		throw std::runtime_error("No lights found in scene file.");

	int numlit=1;
	XMLElement* elm_child = elm_lit->FirstChildElement();
	while (elm_child) 
	{
		std::string name(elm_child->Name());

		if (name == "pointlight")
			lits.push_back(parse_pointlight(elm_child));
		else
			throw std::invalid_argument("Invalid light in scene file.");
		
		elm_child = elm_child->NextSiblingElement();

		numlit++;
	}

	return numlit;
}

light_t* scene_t::parse_pointlight(XMLElement* _elm) 
{
	return (light_t*)(new point_light_t(
			parse_vector3(_elm, "position"),
			parse_color(_elm, "color"),
			parse_double(_elm, "ka")));
}

integrator_t* scene_t::parse_integrator(XMLElement* _elm)
{
	XMLElement* elm_intg = _elm->FirstChildElement("integrator");
	if (!elm_intg)
		throw std::runtime_error("Scene file does not contain an integrator.");

	XMLElement* elm_child = elm_intg->FirstChildElement();

	std::string name(elm_child->Name());
	if (name == "whitted")
	{
		return parse_whitted_integrator(elm_child);
	}
	else
		throw std::invalid_argument("Invalid integrator in scene file.");
	
		
}

integrator_t* scene_t::parse_whitted_integrator(XMLElement *_elm)
{
	return (integrator_t*)(new whitted_integrator_t(
								parse_int(_elm, "depth-of-recursion")));
}
