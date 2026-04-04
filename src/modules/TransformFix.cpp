#include "TransformFix.hpp"

bool TFGJTransformControl::init() {
    if (!GJTransformControl::init()) return false;

    auto node = m_mainNode->getChildByType<CCNode>(0);
    auto menu = node->getChildByType<CCMenu>(0);

    auto fields = m_fields.self();
    fields->m_menu = menu;

    return true;
}

bool TFGJTransformControl::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    if (GJTransformControl::ccTouchBegan(touch, event)) return true;
    auto fields = m_fields.self();
    auto ret = fields->m_menu->ccTouchBegan(touch, event);
    fields->m_touchInMenu = ret;
    return ret;
}

void TFGJTransformControl::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchMoved(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchMoved(touch, event);
    }
}

void TFGJTransformControl::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchEnded(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchEnded(touch, event);
    }
    fields->m_touchInMenu = false;

}

void TFGJTransformControl::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJTransformControl::ccTouchCancelled(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchCancelled(touch, event);
    }
    fields->m_touchInMenu = false;
}

void TFGJTransformControl::scaleButtons(float scale) {
    GJTransformControl::scaleButtons(scale);
    auto spr = m_warpLockButton->getChildByIndex(0);
    m_warpLockButton->setContentSize(spr->getScaledContentSize());
    spr->setPosition(m_warpLockButton->getContentSize()/2);
}

bool TFGJScaleControl::init() {
    if (!GJScaleControl::init()) return false;

    auto menu = getChildByType<CCMenu>(0);

    auto fields = m_fields.self();
    fields->m_menu = menu;

    return true;
}

bool TFGJScaleControl::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    if (GJScaleControl::ccTouchBegan(touch, event)) return true;
    auto fields = m_fields.self();
    auto ret = fields->m_menu->ccTouchBegan(touch, event);
    fields->m_touchInMenu = ret;
    return ret;
}

void TFGJScaleControl::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchMoved(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchMoved(touch, event);
    }
}

void TFGJScaleControl::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchEnded(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchEnded(touch, event);
    }
    fields->m_touchInMenu = false;

}

void TFGJScaleControl::ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
    GJScaleControl::ccTouchCancelled(touch, event);
    auto fields = m_fields.self();
    if (fields->m_touchInMenu) {
        fields->m_menu->ccTouchCancelled(touch, event);
    }
    fields->m_touchInMenu = false;
}