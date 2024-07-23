#include <chrono>

#include "Nest/Application/Application.hpp"
#include "Nest/Logger/Logger.hpp"
#include "Nest/Renderer/Renderer.hpp"
#include "Nest/Window/Events.hpp"
#include "Nest/ImGui/ImGui.hpp"

Application *Application::s_instance = new Application;
std::shared_ptr<spdlog::logger> Logger::s_logger = nullptr;

uint64_t getMillis() {
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
    );
    return now.count();
}

Application::Application()
        : currentLayer(nullptr)
        , fps()
        , timeMillis() {
    Logger::init();
    window = new Window;
    window->init("VivoEditor", 800, 600);

    ImGui_Init(window->getNativeHandle());
    Renderer::init();
//    Renderer::setClearColor(.235f, .235f, .235f, 1.0f);
    Renderer::setClearColor( 1.f, 1.f, 1.f, 1.f);
}

Application::~Application() {
    ImGui_Shutdown();
    delete window;
}

void Application::loop() {
    while (!window->shouldClose()) {
        uint64_t lastTime = timeMillis;
        timeMillis = getMillis();
        deltaTimeMillis += timeMillis - lastTime;
        if (deltaTimeMillis < (1000ul / maximumFps)) {
            continue;
        }
        oneSecondTimeCount += deltaTimeMillis;

        thisSecondFramesCount++;
        if (oneSecondTimeCount >= 1000) {
            fps = thisSecondFramesCount;
            LOG_INFO("FPS: {}", fps);
            thisSecondFramesCount = 0;
            oneSecondTimeCount = 0;
        }

        double deltaTime = deltaTimeMillis / 1000.0;
        deltaTimeMillis = 0;

        Renderer::clear();

        ImGui_NewFrame();
        if (currentLayer) {
            currentLayer->update(deltaTime);
        }
        ImGui_EndFrame();

        Events::resetDropPaths();
        Events::pollEvents();
        window->swapBuffers();
    }
}

void Application::close() {
    window->setShouldClose();
}
