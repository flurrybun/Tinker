#pragma once

#include "../../Module.hpp"
#include <Geode/ui/NineSlice.hpp>
#include <Geode/modify/EditorUI.hpp>
#include "SearchField.hpp"

class $globalModule(ObjectSearch) {};

class $modify(OSEditorUI, EditorUI) {
    $registerGlobalHooks(ObjectSearch)

    struct Fields {
        EditButtonBar* m_searchBar;
        tinker::ui::SearchField* m_searchField;
        std::map<unsigned int, tinker::ui::SearchField::ItemInformation> m_items;
        std::vector<tinker::ui::SearchField::ItemInformation*> m_orderedItems;
    };

    bool init(LevelEditorLayer* editorLayer);
    void updateCreateMenu(bool selectTab);
    CreateMenuItem* getCreateBtn(int id, int bg);
    void onPause(CCObject* sender);

};