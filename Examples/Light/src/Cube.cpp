#include "Cube.hpp"
#include "glm/ext/matrix_transform.hpp"

Cube::~Cube() {
    delete m_shaderCube;
}

void Cube::init(const glm::vec3 &position, const std::filesystem::path &pathToTexture) {
    m_model = glm::mat4(1);
    m_shaderCube = new Shader;
    m_shaderCube->create("Shaders/vstCube.glsl", "Shaders/fstCube.glsl");
    Vertex vertices[24] = {
        // Front
        Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f), // 0
        Vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f),  // 1
        Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),   // 2
        Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f),  // 3
        // Back
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 4
        Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f),  // 5
        Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f),   // 6
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f),  // 7
        // Top
        Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 8
        Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),  // 11
        Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),   // 10
        Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f),  // 9
        // Bottom
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 12
        Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f),  // 13
        Vertex(1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),   // 14
        Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),  // 15
        // Left
        Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 16
        Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f),  // 17
        Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),   // 18
        Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f),  // 19
        // Right
        Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f), // 20
        Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f),  // 23
        Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f),   // 22
        Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f)   // 21
    };
    // clang-format off
    uint32_t indices[36] = {
       0, 1, 2, 2, 3, 0,       // Front
       4, 5, 6, 6, 7, 4,       // Back
       8, 9, 10, 10, 11, 8,    // Top
       12, 13, 14, 14, 15, 12, // Bottom
       16, 17, 18, 18, 19, 16, // Left
       20, 21, 22, 22, 23, 20  // Right
    };
    // clang-format on

    m_mesh.create(vertices, 24 * 5, indices, 36);
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

void Cube::addCubeMap(CubeMap cubeMap) {
    m_cubemap = cubeMap;
}

void Cube::draw() {
    auto camera = Application::getInstance()->getCamera();
    m_shaderCube->use();
    m_shaderCube->setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    m_shaderCube->setVec2("iMouse", Events::getCursorPos());
    m_shaderCube->setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    m_shaderCube->setMat4("u_model", m_model);
    m_shaderCube->setMat4("u_view", camera->getViewMatrix());
    m_shaderCube->setMat4("u_projection", camera->getProjectionMatrix());
    m_texture.bind(0);
    m_shaderCube->setInt("iTexture", 0);
    m_cubemap.bind(1);
    m_shaderCube->setInt("iSky", 1);
    m_mesh.draw();
}