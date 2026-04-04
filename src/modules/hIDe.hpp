#pragma once

#include "../Module.hpp"
#include <Geode/modify/EditLevelLayer.hpp>

class $globalModule(hIDe) {};

class $modify(HDEditLevelLayer, EditLevelLayer){
    $registerGlobalHooks(hIDe, true)

    struct Fields {
        CCLabelBMFont* m_label;
        CCLabelBMFont* m_replacementLabel;
        bool m_shouldSetVisibility = true;
    };

    static void _onModify(auto& self) {
        (void) self.setHookPriority("EditLevelLayer::init", -10000);
    }
    
    bool init(GJGameLevel* p0);
    void setIDVisible(bool visible);
    void checkShift(float dt);
};