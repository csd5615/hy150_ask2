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
vector<Sphere> S(){return Spheres;};
    void add_sphere(Sphere &new_sphere)
    {
        Spheres.push_back(new_sphere);
    }

    void Render(Camera &new_camera, fstream* fout)
    {
        *fout << "P3\n"
         << new_camera.i_w() << ' ' << new_camera.i_h() << "\n255\n";
        
        for (int j = 0; j < new_camera.i_h(); j++) // y coordinates
        {
            for (int i = 0; i < new_camera.i_w(); i++) // x coordinates
            {
                color pixel_color = color(SkyColor);
                auto pixel_center = new_camera.GetPixelCenter(i, j);
                auto ray_direction = pixel_center - new_camera.c();
                ray r(new_camera.c(), ray_direction);
                double distance = 0;
                for (int a = 0; a < Spheres.size(); a++)
                {
                    
                    if (Spheres[a].hit_sphere(r, distance))
                    {
                        //cout << "hello";
                        pixel_color = color(Spheres[a].c());
                    }
                }
                
                //cout<<" "<<j;
                 write_color(*fout, pixel_color);
            }
        };
        cout<< "DONE!";
    }
};