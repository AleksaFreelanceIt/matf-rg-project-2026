/**
 * Start here...
 */
#include "MainController.hpp"
#include <GuiController.hpp>
#include <engine/core/Engine.hpp>

class MyApp : public engine::core::App {
protected:
    void app_setup() override {
        const auto main_controller = register_controller<app::MainController>();
        auto gui_controller = register_controller<app::GuiController>();
        main_controller->after(
                engine::core::Controller::get<engine::core::EngineControllersEnd>());
        main_controller->before(gui_controller);
    }
};

int main(int argc, char **argv) {
    return std::make_unique<MyApp>()->run(argc, argv);
}
