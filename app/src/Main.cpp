/**
 * Start here...
 */
#include <engine/core/Engine.hpp>
#include "MainController.hpp"

class MyApp : public engine::core::App {
protected:
    void app_setup() override {
        const auto main_controller = register_controller<app::MainController>();
        main_controller->after(
            engine::core::Controller::get<engine::core::EngineControllersEnd>());
    }
};

int main(int argc, char **argv) {
    return std::make_unique<MyApp>()->run(argc, argv);
}
