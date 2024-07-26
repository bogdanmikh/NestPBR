#pragma once

#include <cstdint>
#include <filesystem>
#include <glm/glm.hpp>

#include <Nest.hpp>

struct VertexCube {
    // position
    glm::vec3 Position;
    // texCoords
    glm::vec2 TexCoords;
    // normal
    glm::vec3 Normal;

    VertexCube()
        : Position(0, 0, 0)
        , TexCoords(0, 0)
        , Normal(0, 0, 0) {};

    VertexCube(glm::vec3 aPosition, glm::vec2 aTexCoord, glm::vec3 aNormal)
        : Position(aPosition)
        , TexCoords(aTexCoord)
        , Normal(aNormal) {};

    VertexCube(
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

class Cube {
public:
    ~Cube();
    void init(
        const glm::vec3 &position,
        const std::filesystem::path &pathToTexture,
        const std::array<std::string, 6> &skyTextureAsset
    );
    void rotateX(float degrees);
    void rotateY(float degrees);
    void rotateZ(float degrees);
    void draw();

private:
    CubeMap m_cubeMap;
    glm::mat4 m_model;
    Shader *m_shaderCube;
    Mesh m_mesh;
    Texture m_texture;
};