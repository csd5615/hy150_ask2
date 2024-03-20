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
    int width;
    int height;
    int image_width;
    int image_height;
    float focal_length = 1.0;
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3 viewport_u = vec3(width, 0, 0);
    vec3 viewport_v = vec3(0, -height, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    vec3 pixel_delta_u = viewport_u / image_width;
    vec3 pixel_delta_v = viewport_v / image_height;

public:
    vec3 c() { return center; };
    int w() { return width; };
    int h() { return height; };
    int i_w() { return image_width; };
    int i_h() { return image_height; };
    vec3 vp_u() { return viewport_u; };
    vec3 vp_v() { return viewport_v; };
    vec3 pd_u() { return pixel_delta_u; };
    vec3 pd_v() { return pixel_delta_v; };

    Camera(vec3 center, int width, int height)
    {

        this->height = 2.0;
        this->width = height * (static_cast<double>(image_width) / image_height);
        this->center = point3(0, 0, 0);
    }

public:
    vec3 GetPixelCenter(int coor1, int coor2)
    {

        auto viewport_upper_left = center - vec3(coor1, coor2, focal_length) - viewport_u / 2 - viewport_v / 2;
        auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        return pixel00_loc;
    }
};