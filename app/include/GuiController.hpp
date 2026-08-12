//
// Created by rlm on 12/08/2026.
//

#ifndef MATF_RG_PROJECT_GUICONTROLLER_HPP
#define MATF_RG_PROJECT_GUICONTROLLER_HPP
#include <engine/core/Controller.hpp>

namespace app {
    class GuiController : public engine::core::Controller {
    public:
        std::string_view name() const override {
            return "app::GuiController";
        }

    private:
        void initialize() override;

        void draw() override;

        void poll_events() override;
    };
}

#endif //MATF_RG_PROJECT_GUICONTROLLER_HPP
