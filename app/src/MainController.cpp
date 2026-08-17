//
// Created by rlm on 09/08/2026.
//

#include "../include/MainController.hpp"

#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>
#include <spdlog/fmt/bundled/compile.h>
#include <engine/graphics/OpenGL.hpp>
#include <GuiController.hpp>

namespace app {
    class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
        void on_mouse_move(engine::platform::MousePosition position) override;
    };

    void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
        auto gui_controller = engine::core::Controller::get<GuiController>();
        if (!gui_controller->is_enabled()) {
            auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
            camera->rotate_camera(position.dx, position.dy);
        }
    }

    void MainController::initialize() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
        engine::graphics::OpenGL::enable_depth_testing();
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
            return false;
        }
        return true;
    }

    void MainController::update_camera() {
        auto gui_controller = engine::core::Controller::get<GuiController>();
        if (gui_controller->is_enabled()) {
            return;
        }
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera   = graphics->camera();
        float dt      = platform->dt();
        if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_SPACE).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::UP, dt);
        }
        if (platform->key(engine::platform::KeyId::KEY_LEFT_CONTROL).is_down()) {
            camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt);
        }
    }

    void MainController::update() {
        update_camera();
    }

    void MainController::begin_draw() {
        engine::graphics::OpenGL::clear_buffers();
    }

    void MainController::draw_skybox() {
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto skybox    = resources->skybox("textures");
        auto shader    = resources->shader("skybox");
        auto graphics  = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->draw_skybox(shader, skybox);
    }

    void MainController::draw_statue() {
        auto resources                    = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics                     = engine::core::Controller::get<engine::graphics::GraphicsController>();
        engine::resources::Model *statue  = resources->model("statue");
        //shaders
        engine::resources::Shader *shader = resources->shader("spotlight");
        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(0.45f, 0, 0.75f));
        model           = glm::scale(model, glm::vec3(0.012f));
        model           = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 1, 0));
        shader->set_mat4("model", model);
        //Lighting
        glm::vec3 lightPos(0.45f, 2, 0.75f);
        glm::vec3 target(0.45f, 0.8f, 0.75f);
        glm::vec3 lightDirection = glm::normalize(target - lightPos);
        shader->set_vec3("lightPos", lightPos);
        shader->set_vec3("lightDirection", lightDirection);
        shader->set_vec3("lightColor", glm::vec3(0, 0.7f, 1.0f));
        shader->set_float("ambientStrength", 0.08f);
        shader->set_float("specularStrength", 0.25f);
        shader->set_float("cutOff", glm::cos(glm::radians(20.0f)));
        shader->set_float("outerCutOff", glm::cos(glm::radians(30.0f)));
        statue->draw(shader);
    }

    void MainController::draw_halo() {
        auto resources                 = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics                  = engine::core::Controller::get<engine::graphics::GraphicsController>();
        engine::resources::Model *halo = resources->model("halo");

        //shaders
        engine::resources::Shader *shader = resources->shader("basic");
        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::translate(model, glm::vec3(0.45f, 0, 0.75f));
        model           = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
        model           = glm::scale(model, glm::vec3(0.04f));

        shader->set_mat4("model", model);
        halo->draw(shader);
    }

    void MainController::draw_dungeon() {
        auto resources                    = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto graphics                     = engine::core::Controller::get<engine::graphics::GraphicsController>();
        engine::resources::Model *dungeon = resources->model("dungeon");

        //shaders
        engine::resources::Shader *shader = resources->shader("spotlight");
        shader->use();
        shader->set_mat4("projection", graphics->projection_matrix());
        shader->set_mat4("view", graphics->camera()->view_matrix());
        glm::mat4 model = glm::mat4(1.0f);
        model           = glm::scale(model, glm::vec3(0.3f));
        model           = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1, 0, 0));

        glm::vec3 lightPos(0.45f, 2, 0.75f);
        glm::vec3 target(0.45f, 0.8f, 0.75f);
        glm::vec3 lightDirection = glm::normalize(target - lightPos);
        shader->set_vec3("lightPos", lightPos);
        shader->set_vec3("lightDirection", lightDirection);
        shader->set_vec3("lightColor", glm::vec3(0, 0.7f, 1.0f));
        shader->set_float("ambientStrength", 0.08f);
        shader->set_float("specularStrength", 0.25f);
        shader->set_float("cutOff", glm::cos(glm::radians(20.0f)));
        shader->set_float("outerCutOff", glm::cos(glm::radians(30.0f)));
        shader->set_mat4("model", model);
        dungeon->draw(shader);
    }

    void MainController::draw() {
        draw_statue();
        draw_halo();
        draw_dungeon();
        draw_skybox();
    }

    void MainController::end_draw() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        platform->swap_buffers();
    }
}
