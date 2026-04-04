#pragma once

#include "../../Module.hpp"
#include <Geode/modify/LevelSettingsLayer.hpp>

class $editorModule(ObjectSummary) {};

class $modify(OSLevelSettingsLayer, LevelSettingsLayer) {
    $registerEditorHooks(ObjectSummary)

	bool init(LevelSettingsObject* p0, LevelEditorLayer* p1);
};
