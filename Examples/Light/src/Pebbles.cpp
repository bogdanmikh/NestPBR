#include "Pebbles.hpp"
#include <imgui.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

void Pebbles::start() {
    m_skyComponent.init();
    m_cameraMove.init();
}

void Pebbles::detach() {
    m_skyTexture.destroy();
}

void Pebbles::update(double deltaTime) {
    glm::vec2 currSize = Application::getInstance()->getWindow()->getSize();
    if (m_lastViewportSize != currSize) {
        m_lastViewportSize = currSize;
        Renderer::setRenderBufferSize(currSize.x, currSize.y);
    }
    m_skyTexture.bind(1);
    m_cameraMove.update(deltaTime);
    m_skyComponent.draw();
    Renderer::checkForErrors();
}