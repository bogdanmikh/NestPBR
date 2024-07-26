#pragma once

#include <Nest.hpp>
#define SPHERE1
#ifdef SPHERE1
struct SphereVertex {
    // position
    glm::vec3 Position;
    // texCoords
    glm::vec2 TexCoords;
    // normal
    glm::vec3 Normal;

    SphereVertex()
        : Position(0, 0, 0)
        , TexCoords(0, 0)
        , Normal(0, 0, 0) {};

    SphereVertex(glm::vec3 aPosition, glm::vec2 aTexCoord, glm::vec3 aNormal)
        : Position(aPosition)
        , TexCoords(aTexCoord)
        , Normal(aNormal) {};

    SphereVertex(
        float x,
        float y,
        float z,
        float aTexCoordX,
        float aTexCoordY,
        float aNormalX,
        float aNormalY,
        float aNormalZ
    )
        : Position(x, y, z)
        , TexCoords(aTexCoordX, aTexCoordY)
        , Normal(aNormalX, aNormalY, aNormalZ) {};
};
#else
struct SphereVertex {
    glm::vec3 pos;

    SphereVertex(float x, float y, float z)
        : pos(x, y, z) {}
};
#endif

class Sphere {
public:
    void init(glm::vec3 position);
    void draw();

private:
    int m_lats, m_longs;
    Mesh m_mesh;
    Shader m_sphereShader;
    glm::mat4 m_model;
};