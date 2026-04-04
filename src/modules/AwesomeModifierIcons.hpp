#pragma once

#include "../Module.hpp"
#include <Geode/modify/EffectGameObject.hpp>
#include <Geode/modify/EditorUI.hpp>

class $globalModule(AwesomeModifierIcons) {
    static std::unordered_map<int, std::string> s_textureMap;
};

class $modify(AMIEffectGameObject, EffectGameObject) {
    $registerGlobalHooks(AwesomeModifierIcons)

	void customSetup();
};

class $modify(AMIEditorUI, EditorUI) {
    $registerGlobalHooks(AwesomeModifierIcons)

    bool init(LevelEditorLayer* editorLayer);
};