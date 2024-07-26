#include "NestPBR.hpp"
#include <imgui.h>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>

namespace fs = std::filesystem;

void NestPBR::start() {
    m_lastViewportSize = Application::getInstance()->getWindow()->getSize();
    std::array<std::string, 6> skyTextureAssetNotBlur = {
        "Textures/skybox/notblur/px.png",
        "Textures/skybox/notblur/nx.png",
        "Textures/skybox/notblur/py.png",
        "Textures/skybox/notblur/ny.png",
        "Textures/skybox/notblur/pz.png",
        "Textures/skybox/notblur/nz.png"
    };
    std::array<std::string, 6> skyTextureAssetBlur = {
        "Textures/skybox/blur/px.png",
        "Textures/skybox/blur/nx.png",
        "Textures/skybox/blur/py.png",
        "Textures/skybox/blur/ny.png",
        "Textures/skybox/blur/pz.png",
        "Textures/skybox/blur/nz.png"
    };
    m_skyComponent.init(skyTextureAssetNotBlur);
    m_cube.init(glm::vec3(0., 0., 0.), "Textures/Dubil.png", skyTextureAssetNotBlur);
    m_sphere.init(glm::vec3(0., 0., 0.));
    m_cameraMove.init();
}

void NestPBR::detach() {}

void NestPBR::update(double deltaTime) {
    glm::vec2 currSize = Application::getInstance()->getWindow()->getSize();
    if (m_lastViewportSize != currSize) {
        m_lastViewportSize = currSize;
        Renderer::setRenderBufferSize(currSize.x, currSize.y);
    }
    m_cameraMove.update(deltaTime);
    m_skyComponent.draw();
    m_cube.rotateZ(0.5);
    //    m_cube.rotateY(0.5);
//    m_cube.draw();
    m_sphere.draw();
    Renderer::checkForErrors();
}