#pragma once

#include "../Module.hpp"
#include <Geode/modify/TextGameObject.hpp>

class $globalModule(FixTextObjectBounds) {};

class $modify(FTOBTextGameObject, TextGameObject) {
    $registerGlobalHooks(FixTextObjectBounds)

    void fixBounds();

    void customObjectSetup(gd::vector<gd::string>& p0, gd::vector<void*>& p1);
    void updateTextObject(gd::string p0, bool p1);
};