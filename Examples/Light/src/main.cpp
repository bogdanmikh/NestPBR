#include <Nest.hpp>

#include "NestPBR.hpp"

int main() {
    auto *application = Application::getInstance();
    auto *layer = new NestPBR();
    application->setLayer(layer);
    application->loop();
    layer->detach();
    delete layer;
    delete application;
}
