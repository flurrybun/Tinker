#include "ImprovedLinkControls.hpp"

void ImprovedLinkControls::onEditor() {
    auto zoomMenu = m_editorUI->getChildByID("zoom-menu");
    auto linkMenu = m_editorUI->getChildByID("link-menu");
    linkMenu->setContentSize({ 125.f, zoomMenu->getContentHeight() + 29.f });
    linkMenu->setPosition({linkMenu->getPositionX() - 5, zoomMenu->getPositionY()});
    static_cast<AxisLayout*>(linkMenu->getLayout())->setGap(0.f);
    linkMenu->updateLayout();
    
    // for BetterEdit
    linkMenu->runAction(CallFuncExt::create([linkMenu] {
        linkMenu->setScale(0.8f * linkMenu->getScale());
    }));
}

void ILCEditorUI::onGroupSticky(CCObject* sender) {
    if (m_linkControlsDisabled) return;
    EditorUI::onGroupSticky(sender);
}

void ILCEditorUI::onUngroupSticky(CCObject* sender) {
    if (m_linkControlsDisabled) return;
    EditorUI::onUngroupSticky(sender);
}