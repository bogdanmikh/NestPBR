#include <Nest.hpp>

#include "Level.hpp"

int main() {
    auto* application = Application::getInstance();
    auto *layer = new Level();
    application->setLayer(layer);
    application->loop();
    layer->detach();
    delete layer;
    delete application;
}
