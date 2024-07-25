#include "Cube.hpp"
#include "glm/ext/matrix_transform.hpp"

Cube::~Cube() {
    delete m_shaderCube;
}

void Cube::init(const glm::vec3 &position) {
    m_model = glm::mat4(1);
    m_shaderCube = new Shader;
    m_shaderCube->create("Shaders/vstCube.glsl", "Shaders/fstCube.glsl");

    MyVertex vertices[24] = {
        // Front
        MyVertex(-1.0f, -1.0f, 1.0f), // 0
        MyVertex(1.0f, -1.0f, 1.0f),  // 1
        MyVertex(1.0f, 1.0f, 1.0f),   // 2
        MyVertex(-1.0f, 1.0f, 1.0f),  // 3
        // Back
        MyVertex(-1.0f, -1.0f, -1.0f), // 4
        MyVertex(-1.0f, 1.0f, -1.0f),  // 5
        MyVertex(1.0f, 1.0f, -1.0f),   // 6
        MyVertex(1.0f, -1.0f, -1.0f),  // 7
        // Top
        MyVertex(-1.0f, 1.0f, -1.0f), // 8
        MyVertex(-1.0f, 1.0f, 1.0f),  // 11
        MyVertex(1.0f, 1.0f, 1.0f),   // 10
        MyVertex(1.0f, 1.0f, -1.0f),  // 9
        // Bottom
        MyVertex(-1.0f, -1.0f, -1.0f), // 12
        MyVertex(1.0f, -1.0f, -1.0f),  // 13
        MyVertex(1.0f, -1.0f, 1.0f),   // 14
        MyVertex(-1.0f, -1.0f, 1.0f),  // 15
        // Left
        MyVertex(-1.0f, -1.0f, -1.0f), // 16
        MyVertex(-1.0f, -1.0f, 1.0f),  // 17
        MyVertex(-1.0f, 1.0f, 1.0f),   // 18
        MyVertex(-1.0f, 1.0f, -1.0f),  // 19
        // Right
        MyVertex(1.0f, -1.0f, -1.0f), // 20
        MyVertex(1.0f, 1.0f, -1.0f),  // 23
        MyVertex(1.0f, 1.0f, 1.0f),   // 22
        MyVertex(1.0f, -1.0f, 1.0f)   // 21
    };
    
    uint32_t indices[36] = {
        0, 1, 2, 2, 3, 0,       // Front
        4, 5, 6, 6, 7, 4,       // Back
        8, 9, 10, 10, 11, 8,    // Top
        12, 13, 14, 14, 15, 12, // Bottom
        16, 17, 18, 18, 19, 16, // Left
        20, 21, 22, 22, 23, 20  // Right
    };
    
    VertexBufferLayout layout;
    layout.pushVec3F();
    m_mesh.create(layout, (float *)vertices, 24 * 3, indices, 36);
    
    std::array<std::string, 6> skyTextureAsset = {
        "Textures/Dubil.png",
        "Textures/Dubil.png",
        "Textures/Dubil.png",
        "Textures/Dubil.png",
        "Textures/Dubil.png",
        "Textures/Dubil.png"
    };
    m_cubeMap.create(skyTextureAsset);
}

void Cube::rotateX(float degrees) {
    m_model = glm::rotate(m_model, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
}

void Cube::rotateY(float degrees) {
    m_model = glm::rotate(m_model, glm::radians(degrees), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Cube::rotateZ(float degrees) {
    m_model = glm::rotate(m_model, glm::radians(degrees), glm::vec3(0.0f, 0.0f, 1.0f));
}

void Cube::draw() {
    Application::getInstance()->getCamera()->setShader(m_shaderCube);
    m_shaderCube->use();
    m_shaderCube->setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    m_shaderCube->setVec2("iMouse", Events::getCursorPos());
    m_shaderCube->setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    m_shaderCube->setMat4("u_model", m_model);
    m_cubeMap.bind(0);
    m_shaderCube->setInt("iCube", 0);
    m_mesh.draw();
}