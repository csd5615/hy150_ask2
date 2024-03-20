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
#include "Classes.h"
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ifstream inputFile("input_data.txt");
    fstream fout;

    string picture_name;
    vec3 cam_center;
    int image_width;
    int image_height;
    vec3 SkyColor;
    int sphere_number;
    vec3 sphere_color;
    vec3 sphere_position;
    float sphere_radius;

    string line;

    getline(inputFile, line);
    picture_name = line;
    fout.open(picture_name + ".ppm", ios::out | ios::trunc); // naming the file

    getline(inputFile, line);
    istringstream iss(line);
    double e0, e1, e2;
    iss >> e0 >> e1 >> e2;
    cam_center.e[0] = e0;
    cam_center.e[1] = e1;
    cam_center.e[2] = e2;

    getline(inputFile, line);
    istringstream iss(line);
    iss >> image_width;

    getline(inputFile, line);
    istringstream iss(line);
    iss >> image_height;

    Camera my_camera(cam_center, image_width, image_height);

    getline(inputFile, line);
    istringstream iss(line);
    double e0, e1, e2;
    iss >> e0 >> e1 >> e2;
    SkyColor.e[0] = e0;
    SkyColor.e[1] = e1;
    SkyColor.e[2] = e2;

    World my_world(SkyColor, picture_name);

    getline(inputFile, line);
    istringstream iss(line);
    iss >> sphere_number;

    for (int i = 0; i < sphere_number; i++)
    {
        getline(inputFile, line);
        istringstream iss(line);
        double tmp1, tmp2, tmp3;
        float tmpRad;
        iss >> e0 >> e1 >> e2 >> tmp1 >> tmp2 >> tmp3 >> tmpRad;
        sphere_color.e[0] = e0;
        sphere_color.e[1] = e1;
        sphere_color.e[1] = e1;
        sphere_position.e[0] = tmp1;
        sphere_position.e[1] = tmp2;
        sphere_position.e[2] = tmp3;
        sphere_radius = tmpRad;
        Sphere my_sphere(sphere_position, sphere_color, sphere_radius);
        my_world.add_sphere(my_sphere);
    }
    my_world.Render(my_camera);
    inputFile.close();
}