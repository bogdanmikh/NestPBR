#include "Cube.hpp"
#include "glm/ext/matrix_transform.hpp"

Cube::~Cube() {
    delete m_shaderCube;
}

void Cube::init(const glm::vec3 &position, const std::filesystem::path& pathToTexture) {
    m_model = glm::mat4(1);
    m_shaderCube = new Shader;
    m_shaderCube->create("Shaders/vstCube.glsl", "Shaders/fstCube.glsl");

    MyVertex vertices[8] = {
        MyVertex(-1.0f, -1.0f, -1.0f), // 0
        MyVertex(1.0f, -1.0f, -1.0f),  // 1
        MyVertex(-1.0f, 1.0f, -1.0f),  // 2
        MyVertex(1.0f, 1.0f, -1.0f),   // 3

        MyVertex(-1.0f, -1.0f, 1.0f), // 4
        MyVertex(1.0f, -1.0f, 1.0f),  // 5
        MyVertex(-1.0f, 1.0f, 1.0f),  // 6
        MyVertex(1.0f, 1.0f, 1.0f),   // 7
    };

    uint32_t indices[36] = {
        4,  6,  7,  7,  5,  4,  // Front
        0,  2,  3,  3,  1,  0,  // Back
        2,  3,  7,  7,  6,  2,  // Top
        0,  1,  5,  5,  4,  0,  // Bottom
        0, 2, 6, 6, 4, 0, // Left
        1, 5, 7, 7, 3, 1  // Right
    };

    VertexBufferLayout layout;
    layout.pushVec3F();
    m_mesh.create(layout, (float *)vertices, 8 * 3, indices, 36);
    m_texture.create(pathToTexture);
    m_model = glm::translate(m_model, position);
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
    m_texture.bind(0);
    m_shaderCube->setInt("iTexture", 0);
    m_mesh.draw();
}