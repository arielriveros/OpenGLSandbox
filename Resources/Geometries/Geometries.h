#include <vector>
#include "../../Source/Mesh/Mesh.h"

#pragma once
std::vector<float> square_vertices = {
	  -0.5, -0.5, 0.0,	0.0, 0.0, -1.0,	0.0, 0.0,
	   0.5,  0.5, 0.0,	0.0, 0.0, -1.0,	1.0, 1.0,
	   0.5, -0.5, 0.0,	0.0, 0.0, -1.0,	0.0, 1.0,
	  -0.5,  0.5, 0.0,	0.0, 0.0, -1.0,	1.0, 0.0
};

std::vector<unsigned int> square_indices = { 0, 1, 2, 1, 3, 0 };


std::vector<float> pyramid_vertices =
{
	-0.5f, 0.0f,  0.5f,	 0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,	 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,
	 0.5f, 0.0f, -0.5f,	 0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
	 0.5f, 0.0f,  0.5f,	 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,

	-0.5f, 0.0f,  0.5f,	-0.8f, 0.5f,  0.0f, 0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,	-0.8f, 0.5f,  0.0f, 1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,	-0.8f, 0.5f,  0.0f, 0.5f, 1.0f,

	-0.5f, 0.0f, -0.5f,	0.0f, 0.5f, -0.8f, 1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,	0.0f, 0.5f, -0.8f, 0.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,	0.0f, 0.5f, -0.8f, 0.5f, 1.0f,

	 0.5f, 0.0f, -0.5f,	0.8f, 0.5f,  0.0f, 0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,	0.8f, 0.5f,  0.0f, 1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,	0.8f, 0.5f,  0.0f, 0.5f, 1.0f,

	 0.5f, 0.0f,  0.5f,	0.0f, 0.5f,  0.8f, 1.0f, 0.0f,
	-0.5f, 0.0f,  0.5f,	0.0f, 0.5f,  0.8f, 0.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,	0.0f, 0.5f,  0.8f, 0.5f, 1.0f
};

std::vector<unsigned int> pyramid_indices = { 0, 1, 2, 0, 2, 3, 4, 6, 5, 7, 9, 8, 10, 12, 11, 13, 15, 14 };


std::vector<float> cube_vertices =
{
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, //0
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f, //1
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f, //2
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f, //3

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f, //4
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f, //5
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f, //6
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f, //7

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, //8
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, //9
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f, //10
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f, //11

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f, //12
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, //13
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f, //14
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f, //15

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f, //16
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f, //17
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f, //18
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f, //19

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f, //20
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f, //21
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f, //22
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f, //23
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f  //24
};

std::vector<unsigned int> cube_indices =
{
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 24
};

Geometry squareGeometry = { square_vertices, square_indices };
Geometry cubeGeometry = { cube_vertices, cube_indices };
Geometry pyramidGeometry = { pyramid_vertices, pyramid_indices };