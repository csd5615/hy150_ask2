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

class Sphere
{
    vec3 position;
    vec3 color;
    float radius;

    Sphere(vec3 position, vec3 color, float radius)
    {
        this->position = position;
        this->color = color;
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
            double tmp_dist= oc.length()-radius;
            if (tmp_dist>distance){
                distance=tmp_dist;
                return true;
            }
            
        }
        return false;
    };
};

int main()
{
}