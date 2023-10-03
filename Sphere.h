#pragma once

#ifndef SPHERE_CLASS_H
#define SPHERE_CLASS_H

#include <glm/glm.hpp>
#include <utility>
#include <vector>

// 3D sphere class
class Sphere {
public:
    float radius;
    // const int sectorCount = 80; // increasing this value can slow down all!!!!
    int sectorCount = 80;
    int stackCount = static_cast<int>(sectorCount / 2);
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec4 color = glm::vec4(1.0f);  // default color (white)

    // transformation default valuess
    glm::vec3 Position = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);
    glm::vec3 Orientation = glm::vec3(0.0f);

    // frame default values
    glm::vec3 FPosition = glm::vec3(0.0f);
    glm::vec3 FScale = glm::vec3(1.0f);
    glm::vec3 FOrientation = glm::vec3(0.0f);

    float* create();
};

int buildVertices(double r, int sectorCount, float*& vrtx, unsigned int*& indices);

#endif