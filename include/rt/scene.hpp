#ifndef _SCENE_HPP_
#define _SCENE_HPP_

#include <list>
#include <string>
#include <vector>

#include <tinyxml2.hpp>

#include <camera.hpp>
#include <image.hpp>
#include <integrator.hpp>
#include <light.hpp>
#include <material.hpp>
#include <object.hpp>
#include <sphere.hpp>

using namespace tinyxml2;

namespace rt
{
 class light_t;
 class integrator_t;

 class scene_t
 {
   private:
    std::string scenefile;
    tinyxml2::XMLDocument scenexml;

    std::string parse_property(XMLElement* _elm, std::string _property, std::string _type);
    std::string parse_parameter(XMLElement* _elm, std::string _type);
    material_t* find_material(std::string name, const std::list<material_t*> matlist);


    float parse_angle(XMLElement* _elm, std::string _property);
    double parse_angle(XMLElement* _elm);
    double parse_angle(std::string _val);

    color_t parse_color(XMLElement* _elm, std::string _property);
    color_t parse_color(XMLElement* _elm);
    color_t parse_color(std::string _val);

    float parse_float(XMLElement* _elm, std::string property);
    float parse_float(XMLElement* _elm);
    float parse_float(std::string _val);

    bool parse_bool(XMLElement* _elm, std::string property);
    bool parse_bool(XMLElement* _elm);
    bool parse_bool(std::string _val);

    int parse_int(XMLElement* _elm, std::string property);
    int parse_int(XMLElement* _elm);
    int parse_int(std::string _val);

    Eigen::Vector3f parse_vector3(XMLElement* _elm, std::string _property);
    Eigen::Vector3f parse_vector3(XMLElement* _elm);
    Eigen::Vector3f parse_vector3(std::string _val);

    bool parse_scenefile(void);
    camera_t* parse_camera(XMLElement* _elm);
    int parse_objects(XMLElement* _elm, const std::list<material_t*>& matlist);
    object_t* parse_object_sphere(XMLElement* _elm, const std::list<material_t*>& matlist);
    int parse_materials(XMLElement* _elm);
    material_t* parse_simplemat(XMLElement* _elm);
    int parse_lights(XMLElement* _elm);
    light_t* parse_pointlight(XMLElement* _elm);
    image_t* parse_image(XMLElement* _elm);
    integrator_t* parse_integrator(XMLElement* _elm);
    integrator_t* parse_whitted_integrator(XMLElement *_elm);

   public:
    camera_t* cam;
    std::vector<object_t*> objs;
    std::list<material_t*> mats;
    std::list<light_t*> lits;
    integrator_t *intg;

    image_t* img;

    int numobjs, nummats, numlits;

    scene_t() {;}

    scene_t(std::string _scenefile)
    {
     scenefile = _scenefile;
     parse_scenefile();
    }


 };
}

#endif
