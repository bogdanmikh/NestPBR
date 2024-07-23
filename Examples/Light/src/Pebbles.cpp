#include "Pebbles.hpp"
#include <imgui.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

void Pebbles::start() {
    m_shaderRectangle.create("Shaders/vst.glsl", "Shaders/fst.glsl");
    Vertex* vertices = new Vertex[4];
    vertices[0].Position = {-1, -1, 0};
    vertices[1].Position = {-1, 1, 0};
    vertices[2].Position = {1, -1, 0};
    vertices[3].Position = {1, 1, 0};
    vertices[0].TexCoords = {0, 1};
    vertices[1].TexCoords = {0, 0};
    vertices[2].TexCoords = {1, 1};
    vertices[3].TexCoords = {1, 0};
    m_vertexBuffer.create(vertices, sizeof(Vertex) * 4);
    delete[] vertices;
    uint32_t* ind = new uint32_t[6] {
        0, 2, 1, 1, 2, 3
    };
    m_indexBuffer.create(ind, 6);
    delete[] ind;
    VertexBufferLayout layout;
    layout.pushVertex();
    m_va.addBuffer(m_vertexBuffer, layout);
    m_skyTexture.create({
        "Textures/skybox/px.png",
        "Textures/skybox/nx.png",
        "Textures/skybox/py.png",
        "Textures/skybox/ny.png",
        "Textures/skybox/pz.png",
        "Textures/skybox/nz.png"
    });
    m_pebblesTexture.create("Textures/pebbles.png");
}

void Pebbles::detach() {
    m_shaderRectangle.destroy();
    m_indexBuffer.destroy();
    m_vertexBuffer.destroy();
    m_skyTexture.destroy();
    m_pebblesTexture.destroy();
}

void Pebbles::update(double deltaTime) {
    glm::vec2 currSize = Application::getInstance()->getWindow()->getSize();
    if (m_lastViewportSize != currSize) {
        m_lastViewportSize = currSize;
        Renderer::setRenderBufferSize(currSize.x, currSize.y);
    }
    m_shaderRectangle.use();
    m_shaderRectangle.setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    m_shaderRectangle.setVec2("iMouse", Events::getCursorPos());
    m_shaderRectangle.setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    m_skyTexture.bind(0);
    m_shaderRectangle.setInt("iSky", 0);
    m_va.bind();
    m_indexBuffer.bind();
    Renderer::drawIndexed(m_indexBuffer.getSize());
    Renderer::checkForErrors();
}