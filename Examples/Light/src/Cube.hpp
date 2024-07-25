#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include <Nest.hpp>

struct MyVertex {
    glm::vec3 pos;

    MyVertex(float x, float y, float z)
        : pos(x, y, z) {}
};

class Cube {
public:
    ~Cube();
    void init(const glm::vec3& position);
    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);
    void draw();
private:
    glm::mat4 m_model;
    Shader *m_shaderCube;
    Mesh m_mesh;
    CubeMap m_cubeMap;
};