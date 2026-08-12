//
// Created by rlm on 12/08/2026.
//
#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>

#include <GuiController.hpp>
#include <imgui.h>

namespace app {
    void GuiController::initialize() {
        set_enable(false);
    }

    void GuiController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_E).state() == engine::platform::Key::State::JustPressed) {
            set_enable(!is_enabled());
        }
    }

    void GuiController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->begin_gui();
        ImGui::Begin("A");

        ImGui::End();

        graphics->end_gui();
    }
}
