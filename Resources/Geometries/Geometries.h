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


Geometry squareGeometry = { square_vertices, square_indices };
Geometry pyramidGeometry = { pyramid_vertices, pyramid_indices };