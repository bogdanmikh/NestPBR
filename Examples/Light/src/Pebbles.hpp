#pragma once

#include <Nest.hpp>
#include "SkyComponent.hpp"
#include "CameraMove.hpp"

class Pebbles final: public Layer {
public:
    void start() override;
    void detach() override;
    void update(double deltaTime) override;
private:
    glm::vec2 m_lastViewportSize;
    CubeMap m_skyTexture;
    SkyComponent m_skyComponent;
    CameraMove m_cameraMove;
};

