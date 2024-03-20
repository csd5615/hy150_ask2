#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "Classes.h"
using namespace std;

class World
{
    vector<Sphere> Spheres;
    vec3 SkyColor;
    string file_name;
    int image_height;
    int image_width;
public:
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
        fstream fout;
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

                 write_color(fout, pixel_color);
            }
        };
    }
};