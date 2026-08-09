//
// Created by rlm on 09/08/2026.
//

#include "../include/MainController.hpp"

#include <engine/platform/PlatformController.hpp>
#include <spdlog/fmt/bundled/compile.h>

namespace app {
    void MainController::initialize() {
    }

    bool MainController::loop() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
            return false;
        }
        return true;
    }
}
