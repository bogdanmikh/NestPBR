#pragma once

class VertexBuffer {
private:
    unsigned int m_RendererID;

public:
    void create(const void *data, unsigned int size);
    void destroy();

    void bind() const;
    void unbind() const;
};
