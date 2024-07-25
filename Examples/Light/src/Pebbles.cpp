#include "Pebbles.hpp"
#include <imgui.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

void Pebbles::start() {
    m_lastViewportSize = Application::getInstance()->getWindow()->getSize();
    m_skyComponent.init();
    m_cube.init(glm::vec3(0., 0., 0.), "Textures/Dubil.png");
    m_cameraMove.init();
}

void Pebbles::detach() {}

void Pebbles::update(double deltaTime) {
    glm::vec2 currSize = Application::getInstance()->getWindow()->getSize();
    if (m_lastViewportSize != currSize) {
        m_lastViewportSize = currSize;
        Renderer::setRenderBufferSize(currSize.x, currSize.y);
    }
    m_cameraMove.update(deltaTime);
    m_cube.rotateX(2);
    m_cube.rotateY(2);
    m_cube.draw();
    m_skyComponent.draw();
    Renderer::checkForErrors();
}