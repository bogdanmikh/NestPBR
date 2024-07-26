#include <chrono>

#include "Nest/Application/Application.hpp"
#include "Nest/Logger/Logger.hpp"
#include "Nest/Renderer/Renderer.hpp"
#include "Nest/Window/Events.hpp"
#include "Nest/ImGui/ImGui.hpp"
#include "imgui.h"

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
    window->init("Light", 1200, 800, false);

    camera = new Camera;
    camera->setFieldOfView(glm::radians(60.f));
    camera->setRotation(0.f, 50.f, 0.f);

    ImGui_Init(window->getNativeHandle());
    Renderer::init();
    Renderer::setClearColor(.235f, .235f, .235f, 1.0f);
}

Application::~Application() {
    ImGui_Shutdown();
    delete camera;
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

        if (Events::isJustKeyPressed(Key::ESCAPE)) {
            close();
        }
        if (Events::isJustKeyPressed(Key::TAB)) {
            Events::toggleCursorLock();
        }

        Renderer::clear();

        ImGui_NewFrame();
        camera->update();
        if (currentLayer) {
            deltaTime = std::min(deltaTime, 10.);
            currentLayer->update(deltaTime);
        }
        ImGui::Begin("Stats");
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
        ImGui::Text("FPS: %d", fps);
        ImGui::PopStyleColor();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.9f, 0.0f, 1.0f));
        ImGui::Text(
            "X: %f, Y: %f, Z: %f",
            camera->getPosition().x,
            camera->getPosition().y,
            camera->getPosition().z
        );
        ImGui::PopStyleColor();
        ImGui::End();
        ImGui_EndFrame();

        Events::resetDropPaths();
        Events::pollEvents();
        window->swapBuffers();
    }
}

void Application::close() {
    window->setShouldClose();
}