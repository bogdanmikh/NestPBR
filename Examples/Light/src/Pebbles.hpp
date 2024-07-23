#pragma once

#include <Nest.hpp>

class Pebbles final: public Layer {
public:
    void start() override;
    void detach() override;
    void update(double deltaTime) override;
private:
    glm::vec2 m_lastViewportSize;
    VertexArray m_va;
    VertexBuffer m_vertexBuffer;
    IndexBuffer m_indexBuffer;
    Shader m_shaderRectangle;
    CubeMap m_skyTexture;
    Texture m_pebblesTexture;
};

