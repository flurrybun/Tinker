#pragma once

#include <Geode/loader/Event.hpp>

namespace tinker::api::improved_group_view {

    struct UpdateGroupView final : geode::Event<UpdateGroupView, bool()> {};

    inline void updateGroupView() {
        UpdateGroupView().send();
    }
}