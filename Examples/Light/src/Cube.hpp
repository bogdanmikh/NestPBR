#pragma once

#include <cstdint>
#include <filesystem>
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
    void init(const glm::vec3 &position, const std::filesystem::path &pathToTexture);
    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);
    void addCubeMap(CubeMap cubeMap);
    void draw();

private:
    CubeMap m_cubemap;
    glm::mat4 m_model;
    Shader *m_shaderCube;
    Mesh m_mesh;
    Texture m_texture;
};