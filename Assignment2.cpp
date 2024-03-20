/**
 * @file Assignment2.cpp
 *
 * @brief Assignment 2 - HY-150
 *
 * @author: csd5615
 */

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Sphere
{
    vec3 position;
    vec3 color;
    float radius;

public:
    vec3 p() const { return position; };
    void p(vec3 position) { this->position = position; };

    vec3 c() const { return color; };
    void c(vec3 color)
    {
        try
        {
            for (int i = 0; i < 3; i++)
            {
                if (color.e[i] >= 0 && color.e[i] < 255)
                {
                    this->color = color;
                }
                else
                {
                    throw(color);
                }
            }
        }

        catch (vec3 bad_color)
        {
            cout << "Oops! Colors must be between 0-255.";
        }
    };

    float r() { return radius; };
    void r(float radius) { this->radius = radius; };

    Sphere(vec3 position, vec3 color, float radius)
    {
        this->position = position;
        try
        {
            for (int i = 0; i < 3; i++)
            {
                if (color.e[i] >= 0 && color.e[i] < 255)
                {
                    this->color = color;
                }
                else
                {
                    throw(color);
                }
            }
        }

        catch (vec3 bad_color)
        {
            cout << "Oops! Colors must be between 0-255.";
        }
        this->radius = radius;
    }

    bool hit_sphere(const ray &ray_hit, double &distance)
    {
        vec3 oc = ray_hit.origin() - position;
        auto a = dot(ray_hit.direction(), ray_hit.direction());
        auto b = 2.0 * dot(oc, ray_hit.direction());
        auto c = dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;

        if (discriminant >= 0)
        {
            double tmp_dist = oc.length() - radius;
            if (tmp_dist > distance)
            {
                distance = tmp_dist;
                return true;
            }
        }
        return false;
    };
};

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

class World
{
    vector<Sphere> Spheres;
    vec3 SkyColor;
    string file_name;
    int image_height;
    int image_width;

    World(vec3 SkyColor, string file_name)
    {
        this->SkyColor = SkyColor;
        this->file_name = file_name;
    }

    void add_sphere(Sphere &new_sphere)
    {
        Spheres.push_back(new_sphere);
    }

    void Render(Camera &new_camera)
    {

        for (int j = 0; j < image_height; ++j) // y coordinates
        {
            for (int i = 0; i < image_width; ++i) // x coordinates
            {
                color pixel_color;
                auto pixel_center = new_camera.GetPixelCenter(i, j) + (i * new_camera.pd_u()) + (j * new_camera.pd_v());
                auto ray_direction = pixel_center - new_camera.c();
                ray r(new_camera.c(), ray_direction);
                double distance = 5000000000;
                for (int a = 0; a < Spheres.size(); a++)
                {
                    if (Spheres[a].hit_sphere(r, distance))
                    {
                        pixel_color = color(Spheres[a].c());
                    }
                }
                if (distance == 5000000000)
                {
                    pixel_color = color(SkyColor);
                }

                write_color(std::cout, pixel_color);
            }
        };
    }
};

int main()
{
}