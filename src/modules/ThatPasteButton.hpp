#pragma once

#include "../Module.hpp"

class $editorModule(ThatPasteButton) {
    void onEditor() override;
    void onSetGroupIDLayer(SetGroupIDLayer* setGroupIDLayer, GameObject* obj, CCArray* objs) override;
};