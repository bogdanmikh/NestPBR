#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include <Nest.hpp>

struct SkyVertex {
    glm::vec3 pos;

    SkyVertex(float x, float y, float z)
        : pos(x, y, z) {}
};

class SkyComponent {
public:
    void init();
    void draw();
    ~SkyComponent();
private:
    SkyVertex *m_vertices;
    uint32_t *m_indices;
    Mesh m_mesh;
    CubeMap m_cubeMap;
    Shader m_shaderCubeMap;
};