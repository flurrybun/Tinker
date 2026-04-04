#pragma once

#include "../Module.hpp"
#include <Geode/modify/CreateMenuItem.hpp>

class $globalModule(CenteredObjectButtons) {};

class $modify(COBCreateMenuItem, CreateMenuItem) {
    $registerGlobalHooks(CenteredObjectButtons)

    static CreateMenuItem* create(cocos2d::CCNode* normal, cocos2d::CCNode* selected, cocos2d::CCObject* target, cocos2d::SEL_MenuHandler selector);
};