#include "Level.hpp"
#include <imgui.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

//Texture* texture;
Vertex *vertices;
uint32_t *ind;
Mesh *mesh;
glm::vec2 lastViewportSize;

void Level::start() {
    shader = new Shader("Shaders/vst.glsl", "Shaders/fst.glsl");
    vertices = new Vertex[4];
    vertices[0].Position = {-1, -1, 0};
    vertices[1].Position = {-1, 1, 0};
    vertices[2].Position = {1, -1, 0};
    vertices[3].Position = {1, 1, 0};
    vertices[0].TexCoords = {0, 1};
    vertices[1].TexCoords = {0, 0};
    vertices[2].TexCoords = {1, 1};
    vertices[3].TexCoords = {1, 0};
    ind = new uint32_t[6] {
        0, 2, 1, 1, 2, 3
    };
    mesh = new Mesh(vertices, 4, ind, 6);
    mesh->addTexture("Textures/noise.jpeg");
//    mesh->addTexture("Textures/pebbles.png");
}

void Level::detach() {
    delete shader;
    delete vertices;
    delete ind;
    delete mesh;
}

void Level::update(double deltaTime) {
    glm::vec2 currSize = Application::getInstance()->getWindow()->getSize();
    if (lastViewportSize != currSize) {
        lastViewportSize = currSize;
        Renderer::setRenderBufferSize(currSize.x, currSize.y);
    }
    shader->use();
    shader->setFloat("iTime", Application::getInstance()->getWindow()->getTime());
    shader->setVec2("iMouse", Events::getCursorPos());
    shader->setVec2("iResolution", Application::getInstance()->getWindow()->getSize());
    mesh->draw();
}
