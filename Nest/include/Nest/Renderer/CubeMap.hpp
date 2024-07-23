#pragma once

#include <string>

class CubeMap {
private:
    unsigned int m_RendererID;
public:
    CubeMap(std::array<std::string, 6> paths);
    CubeMap() : m_RendererID(-1) {}
    void create(std::array<std::string, 6> paths);
    ~CubeMap();

    void bind(unsigned int slot = 0) const;
    void unbind() const;
    unsigned int getRendererId() const {
        return m_RendererID;
    }
};
