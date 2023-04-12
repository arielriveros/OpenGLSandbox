#pragma once

#include <RenderEngineCore.h>
#include <vector>

std::vector<Vertex> square_vertices
{
    Vertex({glm::vec3(-0.5, -0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)}),
    Vertex({glm::vec3(0.5,  0.5, 0.0),  glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 1.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)}),
    Vertex({glm::vec3(0.5, -0.5, 0.0),  glm::vec3(0.0, 0.0, 1.0), glm::vec2(0.0, 1.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)}),
    Vertex({glm::vec3(-0.5,  0.5, 0.0), glm::vec3(0.0, 0.0, 1.0), glm::vec2(1.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0)})
};

std::vector<unsigned int> square_indices = { 0, 2, 1, 0, 1, 3 };

std::vector<Vertex> pyramid_vertices =
{
	Vertex({glm::vec3(-0.5f, 0.0f,  0.5f),	glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)}),
	Vertex({glm::vec3(-0.5f, 0.0f, -0.5f),	glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}),
	Vertex({glm::vec3( 0.5f, 0.0f, -0.5f),	glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}),
	Vertex({glm::vec3( 0.5f, 0.0f,  0.5f),	glm::vec3( 0.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)}),
    
	Vertex({glm::vec3(-0.5f, 0.0f,  0.5f),	glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(0.0f, 0.0f)}),
    Vertex({glm::vec3(-0.5f, 0.0f, -0.5f),	glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(1.0f, 0.0f)}),
    Vertex({glm::vec3(0.0f, 0.8f,  0.0f),	glm::vec3(-0.8f, 0.5f,  0.0f), glm::vec2(0.5f, 1.0f)}),
    
	Vertex({glm::vec3(-0.5f, 0.0f, -0.5f),	glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(1.0f, 0.0f)}),
    Vertex({glm::vec3(0.5f, 0.0f, -0.5f),	glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.0f, 0.0f)}),
    Vertex({glm::vec3(0.0f, 0.8f,  0.0f),	glm::vec3(0.0f, 0.5f, -0.8f), glm::vec2(0.5f, 1.0f)}),

    Vertex({glm::vec3(0.5f, 0.0f, -0.5f),	glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(0.0f, 0.0f)}),
    Vertex({glm::vec3(0.5f, 0.0f,  0.5f),	glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(1.0f, 0.0f)}),
    Vertex({glm::vec3(0.0f, 0.8f,  0.0f),	glm::vec3(0.8f, 0.5f,  0.0f), glm::vec2(0.5f, 1.0f)}),

    Vertex({glm::vec3(0.5f, 0.0f,  0.5f),	glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(1.0f, 0.0f)}),
    Vertex({glm::vec3(-0.5f, 0.0f,  0.5f),	glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(0.0f, 0.0f)}),
    Vertex({glm::vec3(0.0f, 0.8f,  0.0f),	glm::vec3(0.0f, 0.5f,  0.8f), glm::vec2(0.5f, 1.0f)})
};

std::vector<unsigned int> pyramid_indices = { 0, 1, 2, 0, 2, 3, 4, 6, 5, 7, 9, 8, 10, 12, 11, 13, 15, 14 };


std::vector<Vertex> cube_vertices =
{
        Vertex({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(1.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec2(0.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(1.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec2(0.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(1.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  1.0f)}),
        Vertex({glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec2(0.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  0.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 1.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec2( 0.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 0.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 1.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 1.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec2( 0.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 0.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 1.0f,  1.0f)}),
        Vertex({glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 1.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 0.0f,  0.0f)}),
        Vertex({glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec2( 0.0f,  1.0f)})
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