#pragma once

#include "../Module.hpp"
#include <Geode/modify/GJTransformControl.hpp>
#include <Geode/modify/GJScaleControl.hpp>

class $globalModule(TransformFix) {};

class $modify(TFGJTransformControl, GJTransformControl) {
    $registerGlobalHooks(TransformFix);

    struct Fields {
        CCMenu* m_menu;
        bool m_touchInMenu = false;
    };

    bool init();
    void scaleButtons(float scale);

    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};

class $modify(TFGJScaleControl, GJScaleControl) {
    $registerGlobalHooks(TransformFix);

    struct Fields {
        CCMenu* m_menu;
        bool m_touchInMenu = false;
    };

    bool init();
    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
};