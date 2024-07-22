#pragma once

#include "Nest/Window/Window.hpp"
#include "Nest/NestObjects/Layer.hpp"

class Application final {
public:
    ~Application();
    inline static Application *getInstance() {
        return s_instance;
    }

    inline Window *getWindow() {
        return window;
    }

    inline int getMaxFps() const {
        return maximumFps;
    }

    inline int getFps() const {
        return fps;
    }

    void loop();
    void close();

    inline void setLayer(Layer *layer) {
        if (currentLayer) {
            currentLayer->detach();
        }
        currentLayer = layer;
        currentLayer->start();
    }

private:
    Application();
    static Application *s_instance;

    Window *window;
    Layer *currentLayer;

    int fps;
    int maximumFps = 60;
    uint64_t deltaTimeMillis = 0;
    int thisSecondFramesCount = 0;
    uint64_t timeMillis;
    uint64_t oneSecondTimeCount = 0;
};