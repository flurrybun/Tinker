#pragma once

#include "../Module.hpp"
#include <Geode/modify/EditorUI.hpp>

class $editorModule(AutoBuildHelper) {
    CCMenuItemToggler* m_bhToggler;
    bool m_autoBuildHelperEnabled = false;

    void onEditor() override;
    void onEditorPauseLayer(EditorPauseLayer* editorPauseLayer) override;

    void onToggleAutoBuildHelper(CCObject* sender);
};

class $modify(ABHEditorUI, EditorUI) {
    $registerEditorHooks(AutoBuildHelper)

    CCArray* pasteObjects(gd::string p0, bool p1, bool p2);
};