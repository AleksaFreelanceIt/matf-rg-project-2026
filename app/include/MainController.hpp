//
// Created by rlm on 09/08/2026.
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include <engine/core/Controller.hpp>
#include <engine/resources/ShaderCompiler.hpp>

namespace app {
    class MainController : public engine::core::Controller {
    protected:
        void initialize() override;

        bool loop() override;

        void draw_skybox();

        void draw_statue();

        void draw_halo();

        void draw_dungeon();

        void begin_draw() override;

        void update_camera();

        void update() override;

        void draw() override;

        void end_draw() override;

    private:
        float pulseTime = 0;

        enum class CameraEventStep {
            None,
            Shot1,
            Shot2,
            Shot3,
            Return
        };

        CameraEventStep camera_event_step = CameraEventStep::None;

        float camera_event_timer = 0.0f;
        bool camera_event_active = false;

        glm::vec3 camera_start_position;
        glm::vec3 camera_start_front;
        float camera_start_yaw   = 0.0f;
        float camera_start_pitch = 0.0f;

        void start_camera_event();

        void update_camera_event();
    };
} // namespace app
#endif//MATF_RG_PROJECT_MAINCONTROLLER_HPP
