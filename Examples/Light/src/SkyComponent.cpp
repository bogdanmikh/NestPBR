#include "SkyComponent.hpp"

SkyComponent::~SkyComponent() {
    delete[] m_indices;
    delete[] m_vertices;
}

void SkyComponent::init() {
    m_shaderCubeMap.create("Shaders/vstCM.glsl", "Shaders/fstCM.glsl");

    m_vertices = new SkyVertex[24]{
        // Front
        SkyVertex(-1.0f, -1.0f, 1.0f), // 0
        SkyVertex(1.0f, -1.0f, 1.0f),  // 1
        SkyVertex(1.0f, 1.0f, 1.0f),   // 2
        SkyVertex(-1.0f, 1.0f, 1.0f),  // 3
        // Back
        SkyVertex(-1.0f, -1.0f, -1.0f), // 4
        SkyVertex(-1.0f, 1.0f, -1.0f),  // 5
        SkyVertex(1.0f, 1.0f, -1.0f),   // 6
        SkyVertex(1.0f, -1.0f, -1.0f),  // 7
        // Top
        SkyVertex(-1.0f, 1.0f, -1.0f), // 8
        SkyVertex(-1.0f, 1.0f, 1.0f),  // 11
        SkyVertex(1.0f, 1.0f, 1.0f),   // 10
        SkyVertex(1.0f, 1.0f, -1.0f),  // 9
        // Bottom
        SkyVertex(-1.0f, -1.0f, -1.0f), // 12
        SkyVertex(1.0f, -1.0f, -1.0f),  // 13
        SkyVertex(1.0f, -1.0f, 1.0f),   // 14
        SkyVertex(-1.0f, -1.0f, 1.0f),  // 15
        // Left
        SkyVertex(-1.0f, -1.0f, -1.0f), // 16
        SkyVertex(-1.0f, -1.0f, 1.0f),  // 17
        SkyVertex(-1.0f, 1.0f, 1.0f),   // 18
        SkyVertex(-1.0f, 1.0f, -1.0f),  // 19
        // Right
        SkyVertex(1.0f, -1.0f, -1.0f), // 20
        SkyVertex(1.0f, 1.0f, -1.0f),  // 23
        SkyVertex(1.0f, 1.0f, 1.0f),   // 22
        SkyVertex(1.0f, -1.0f, 1.0f)   // 21
    };

    m_indices = new uint32_t[36]{
        0,  1,  2,  2,  3,  0,  // Front
        4,  5,  6,  6,  7,  4,  // Back
        8,  9,  10, 10, 11, 8,  // Top
        12, 13, 14, 14, 15, 12, // Bottom
        16, 17, 18, 18, 19, 16, // Left
        20, 21, 22, 22, 23, 20  // Right
    };
    VertexBufferLayout layout;
    layout.pushVec3F();
    m_mesh.create(layout, (float *)m_vertices, 24, m_indices, 36);
    std::array<std::string, 6> skyTextureAsset = {
        "Textures/skybox/px.png",
        "Textures/skybox/nx.png",
        "Textures/skybox/py.png",
        "Textures/skybox/ny.png",
        "Textures/skybox/pz.png",
        "Textures/skybox/nz.png"
    };
    m_cubeMap.create(skyTextureAsset);
}
void SkyComponent::draw() {
    m_cubeMap.bind(0);
    m_shaderCubeMap.use();
    m_shaderCubeMap.setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    m_shaderCubeMap.setVec2("iMouse", Events::getCursorPos());
    m_shaderCubeMap.setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    m_mesh.draw();
}