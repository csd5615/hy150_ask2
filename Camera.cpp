#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Classes.h"
using namespace std;

class Camera
{
    vec3 center;
    double viewport_height;
    double viewport_width;
    int width;
    int height;
    float focal_length = 1.0;
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u;
    vec3 viewport_v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

public:
    vec3 c() { return center; };
    double w() { return width; };
    double h() { return height; };
    int i_w() { return width; };
    int i_h() { return height; };
    vec3 vp_u() { return viewport_u; };
    vec3 vp_v() { return viewport_v; };
    vec3 pd_u() { return pixel_delta_u; };
    vec3 pd_v() { return pixel_delta_v; };

    Camera(vec3 center, int width, int height)
    {
        this->height=height;
        this->width=width;
        this->viewport_height = 2;
        this->viewport_width = viewport_height * (static_cast<double>(width) / height);
        this->center = center;
        viewport_u = vec3(viewport_width, 0, 0);
        viewport_v = vec3(0, -viewport_height, 0);
        pixel_delta_u = viewport_u / width;
        pixel_delta_v = viewport_v / height;
        
    }

public:
    vec3 GetPixelCenter(int coor1, int coor2)
    {

        auto viewport_upper_left = center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        auto pixel_center = pixel00_loc + (coor1 * pixel_delta_u) + (coor2 * pixel_delta_v);
        return pixel_center;
    }
};