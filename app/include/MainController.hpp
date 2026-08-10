//
// Created by rlm on 09/08/2026.
//

#ifndef MATF_RG_PROJECT_MAINCONTROLLER_HPP
#define MATF_RG_PROJECT_MAINCONTROLLER_HPP
#include <engine/core/Controller.hpp>

namespace app {
    class MainController : public engine::core::Controller {
    protected:
        void initialize() override;

        bool loop() override;

        void draw_dungeon();

        void begin_draw() override;

        void update_camera();

        void update() override;

        void draw() override;

        void end_draw() override;
    };
}
#endif //MATF_RG_PROJECT_MAINCONTROLLER_HPP
