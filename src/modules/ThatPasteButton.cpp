#include "ThatPasteButton.hpp"
#include "../Utils.hpp"

void ThatPasteButton::onEditor() {
    auto buttons = m_editorUI->getChildByID("editor-buttons-menu");
    if (!buttons) return;

    if (getSetting<bool, "toggle-paste-state">()) {
        if (auto pasteStateButton = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->getChildByID("paste-state-button"))) {
            tinker::utils::hijackButton(pasteStateButton, [this, pasteStateButton] (auto orig, auto sender) {
                bool alwaysShow = getSetting<bool, "always-show">();
                bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;

                if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple)) && pasteStateButton->getOpacity() == 255) {
                    createQuickPopup("Paste State?", "Pasting state is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                        if (yes) orig(sender);
                    });
                }
                else orig(sender);
            });
        }
    }

    if (getSetting<bool, "toggle-paste-color">()) {
        if (auto pasteColorButton = typeinfo_cast<CCMenuItemSpriteExtra*>(buttons->getChildByID("paste-color-button"))) {
            tinker::utils::hijackButton(pasteColorButton, [this, pasteColorButton] (auto orig, auto sender) {
                bool alwaysShow = getSetting<bool, "always-show">();
                bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;
                
                if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple)) && pasteColorButton->getOpacity() == 255) {
                    createQuickPopup("Paste Color?", "Pasting color is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                        if (yes) orig(sender);
                    });
                } 
                else orig(sender);
            });
        }
    }
}

void ThatPasteButton::onSetGroupIDLayer(SetGroupIDLayer* setGroupIDLayer, GameObject* obj, CCArray* objs) {
    if (!getSetting<bool, "toggle-paste-state-group">()) return;

    auto actions = setGroupIDLayer->m_mainLayer->getChildByID("actions-menu");
    if (!actions) return;

    auto pasteButton = typeinfo_cast<CCMenuItemSpriteExtra*>(actions->getChildByID("paste-button"));
    if (!pasteButton) return;

    tinker::utils::hijackButton(pasteButton, [this] (auto orig, auto sender) {
        bool alwaysShow = getSetting<bool, "always-show">();
        bool hasMultiple = m_editorUI->m_selectedObjects && m_editorUI->m_selectedObjects->count() > 1;
                
        if (((alwaysShow && m_editorUI->m_selectedObject || hasMultiple) || (!alwaysShow && hasMultiple))) {
            createQuickPopup("Paste State?", "Pasting state is <cr>dangerous</c>! Are you sure?", "Cancel", "Yes", [this, orig, sender] (FLAlertLayer*, bool yes) {
                if (yes) orig(sender);
            });
        } 
        else orig(sender);
    });
}
