#include <Nest.hpp>

#include "Pebbles.hpp"

int main() {
    auto *application = Application::getInstance();
    auto *layer = new Pebbles();
    application->setLayer(layer);
    application->loop();
    layer->detach();
    delete layer;
    delete application;
}
