#pragma once

#include <Nest.hpp>

class Level final: public Layer {
public:
    Level() = default;
    ~Level() = default;
    void start() override;
    void detach() override;
    void update(double deltaTime) override;
private:
    Shader* m_shaderRectangle;
    CubeMap m_skyTexture;
};

