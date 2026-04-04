#include "QuickExtras.hpp"

void QuickExtras::onEditor() {
    if (auto editorButtonsMenu = m_editorUI->getChildByID("editor-buttons-menu")) {
        auto spr = CCSprite::create("edit_extras.png"_spr);
        
        m_editExtrasBtn = CCMenuItemExt::createSpriteExtra(spr, [this] (auto sender) {
            onEditExtras();
        });

        m_editExtrasBtn->setContentSize({40, 40});
        m_editExtrasBtn->setOpacity(175);
        m_editExtrasBtn->setColor({166, 166, 166});
        m_editExtrasBtn->m_animationEnabled = false;
        m_editExtrasBtn->setID("edit-extras-button"_spr);

        spr->setAnchorPoint({0, 0});
        spr->setPosition({1, 0});

        m_editorUI->m_uiItems->addObject(m_editExtrasBtn);

        editorButtonsMenu->insertBefore(m_editExtrasBtn, m_editorUI->m_editSpecialBtn);

        m_editorUI->m_editSpecialBtn->setVisible(false);

        editorButtonsMenu->updateLayout();
    }
}

void QuickExtras::onUpdateButtons() {
    if (m_editExtrasBtn) {
        m_editExtrasBtn->setVisible(!m_editorUI->m_editSpecialBtn->m_animationEnabled);
        m_editorUI->m_editSpecialBtn->setVisible(m_editorUI->m_editSpecialBtn->m_animationEnabled);

        if (m_editorUI->m_selectedObject || m_editorUI->m_selectedObjects->count() > 0) {
            m_editExtrasBtn->setOpacity(255);
            m_editExtrasBtn->setColor({255, 255, 255});
            m_editExtrasBtn->m_animationEnabled = true;
        }
        else {
            m_editExtrasBtn->setOpacity(175);
            m_editExtrasBtn->setColor({166, 166, 166});
            m_editExtrasBtn->m_animationEnabled = false;
        }
    }

    if (auto editorButtonsMenu = m_editorUI->getChildByID("editor-buttons-menu")) {
        editorButtonsMenu->updateLayout();
    }
}

void QuickExtras::onEditExtras() {
    if (m_editorUI->m_selectedObject || m_editorUI->m_selectedObjects->count() > 0) {
        auto idLayer = SetGroupIDLayer::create(m_editorUI->m_selectedObject, m_editorUI->m_selectedObjects);
        auto popup = SetupObjectOptionsPopup::create(m_editorUI->m_selectedObject, m_editorUI->m_selectedObjects, idLayer);
        popup->show();
    }
}

void QEEditorUI::showUI(bool show) {
    EditorUI::showUI(show);

    if (auto qeBtn = QuickExtras::get()->m_editExtrasBtn) {
        qeBtn->setVisible(!m_editSpecialBtn->m_animationEnabled && show);
        m_editSpecialBtn->setVisible(m_editSpecialBtn->m_animationEnabled && show);
    }
}