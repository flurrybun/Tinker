#pragma once

#include "../../Module.hpp"
#include <Geode/modify/EditorUI.hpp>

class $globalModule(ObjectSearch) {};

class $modify(OSEditorUI, EditorUI) {
    $registerGlobalHooks(ObjectSearch)

    bool init(LevelEditorLayer* editorLayer);
    void updateCreateMenu(bool selectTab);
};