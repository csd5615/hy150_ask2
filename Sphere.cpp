#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Classes.h"
using namespace std;
class Bad_color{

};
class Sphere
{
    vec3 position;
    vec3 color;
    float radius;

    public:
    vec3 bad_color;

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

        catch (Bad_color &error)
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

        catch (Bad_color &error)
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
            double tmp_dist = (-b-sqrt(discriminant))/2*a;
            if (tmp_dist < distance || distance == 0)
            {
                distance = tmp_dist;
                return true;
            }
        }
        return false;
    };
};