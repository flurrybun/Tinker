#pragma once

#include "../Module.hpp"
#include <alphalaneous.alphas-ui-pack/include/API.hpp>
#include <Geode/modify/EditButtonBar.hpp>
#include <Geode/modify/EditorOptionsLayer.hpp>
#include <Geode/modify/EditorUI.hpp>

class $globalModule(ScrollableObjects) {};

class $modify(SOEditorUI, EditorUI) {
    $registerGlobalHooks(ScrollableObjects)

    bool init(LevelEditorLayer* editorLayer);
    void updateCreateMenu(bool selectTab);
    void scrollWheel(float y, float x);
};

class $modify(SOEditButtonBar, EditButtonBar) {
    $registerGlobalHooks(ScrollableObjects, true)

    struct Fields {
        alpha::ui::AdvancedScrollLayer* m_scrollLayer;
        alpha::ui::AdvancedScrollBar* m_scrollBar;
        RowLayout* m_scrollLayout;
        CCMenu* m_objectsMenu;
        CCMenu* m_extrasMenu;
        CCNode* m_extrasMenuContainer;

        CCSprite* m_separator;
        ColumnLayout* m_extrasLayout;

        float m_widthOffset;
        int m_rows;
        int m_cols;

        CCRect m_world;

        std::vector<Ref<CCNode>> m_visibleNodes;
        std::vector<Ref<CCMenuItemSpriteExtra>> m_extrasButtons;
        std::vector<Ref<CCNode>> m_pages;
    };

    void loadFromItems(cocos2d::CCArray* objects, int rows, int columns, bool keepPage);
    void goToPage(int page);
    void cull(SOEditButtonBar::Fields* fields, float x);

    void createExtrasMenu();
    void addToExtrasMenu(CCMenuItemSpriteExtra* button);

    static void _onModify(auto& self) {
        (void) self.setHookPriorityAfterPost("EditButtonBar::loadFromItems", "alphalaneous.editortab_api");
    }
};

class $modify(SOEditorOptionsLayer, EditorOptionsLayer) {
    $registerGlobalHooks(ScrollableObjects)

    void onButtonRows(cocos2d::CCObject* sender);
    void setupOptions();
};