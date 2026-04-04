#include "ObjectSearch.hpp"
#include <alphalaneous.alphas-ui-pack/include/API.hpp>
#include <alphalaneous.editortab_api/include/EditorTabAPI.hpp>

using namespace alpha::prelude;

bool OSEditorUI::init(LevelEditorLayer* editorLayer) {
    if (!EditorUI::init(editorLayer)) return false;

    alpha::editor_tabs::addTab("all-objects"_spr, alpha::editor_tabs::BUILD, [this] () {
        auto ebb = alpha::editor_tabs::createEditButtonBar({});
        ebb->m_hasCreateItems = true;

        return ebb;
    }, [] () {

        return CCLabelBMFont::create("...", "bigFont.fnt");
    });

    runAction(CallFuncExt::create([this] {
        auto allObjectsBar = static_cast<EditButtonBar*>(alpha::editor_tabs::nodeForTab("all-objects"_spr).unwrap().data());

        log::info("started");

        for (auto tab : alpha::editor_tabs::getAllTabs().unwrap()) {
            auto ebb = typeinfo_cast<EditButtonBar*>(tab);
            if (!ebb || !ebb->m_hasCreateItems || allObjectsBar == ebb) continue;

            for (auto node : ebb->m_buttonArray->asExt<CCNode>()) {
                auto cmi = typeinfo_cast<CreateMenuItem*>(node);
                if (!cmi || cmi->m_objectID < 1 || cmi->m_tabIndex == 13) continue;

                auto buttonSprite = cmi->getChildByType<ButtonSprite*>(0);

                buttonSprite->m_subBGSprite->setOpacity(0);
                auto render = alpha::ui::RenderNode::create(buttonSprite, true);
                render->render();

                auto spr = CCSprite::createWithTexture(render->getTexture(), render->getTextureRect());
                spr->m_sBlendFunc.src = CC_BLEND_SRC;
                spr->m_sBlendFunc.dst = CC_BLEND_DST;
                spr->setOpacityModifyRGB(true);
                spr->setUserObject("render"_spr, render);

                auto btnSprite = ButtonSprite::create(spr, 32, 0, 32.0, 1.0, true, "GJ_button_04.png", true);
                spr->setScale(1);

                auto newCmi = CreateMenuItem::create(btnSprite, nullptr, this, menu_selector(EditorUI::onCreateButton));
                newCmi->m_objectID = cmi->m_objectID;
                newCmi->m_pageIndex = cmi->m_pageIndex;
                newCmi->m_tabIndex = cmi->m_tabIndex;

                cmi->setUserObject("shared"_spr, newCmi);
                newCmi->setUserObject("shared"_spr, cmi);

                newCmi->release();

                allObjectsBar->m_buttonArray->addObject(newCmi);
            }
        }

        auto cols = GameManager::get()->getIntGameVariable(GameVar::EditorButtonsPerRow);
        auto rows = GameManager::get()->getIntGameVariable(GameVar::EditorButtonRows);

        allObjectsBar->reloadItems(cols, rows);

        for (auto tab : alpha::editor_tabs::getAllTabs().unwrap()) {
            auto ebb = typeinfo_cast<EditButtonBar*>(tab);
            if (!ebb || !ebb->m_hasCreateItems || allObjectsBar == ebb) continue;

            for (auto node : ebb->m_buttonArray->asExt<CCNode>()) {
                auto cmi = typeinfo_cast<CreateMenuItem*>(node);
                if (!cmi || cmi->m_objectID < 1 || cmi->m_tabIndex == 13) continue;

                auto buttonSprite = cmi->getChildByType<ButtonSprite*>(0);
                buttonSprite->m_subBGSprite->setOpacity(255);
            }
        }

        log::info("ended");
    }));

    return true;
}

void OSEditorUI::updateCreateMenu(bool selectTab) {
    EditorUI::updateCreateMenu(selectTab);

    auto nodeRes = alpha::editor_tabs::nodeForTab("all-objects"_spr);
    if (!nodeRes) return;

    auto allObjectsBar = static_cast<EditButtonBar*>(nodeRes.unwrap().data());
    if (!allObjectsBar) return;
        
    for (auto node : allObjectsBar->m_buttonArray->asExt<CCNode>()) {
        auto cmi = typeinfo_cast<CreateMenuItem*>(node);
        if (!cmi) continue;

        auto buttonSprite = cmi->getChildByType<ButtonSprite*>(0);

        if (cmi->m_objectID == m_selectedObjectIndex) {
            buttonSprite->m_subBGSprite->setColor({127, 127, 127});
        }
        else {
            buttonSprite->m_subBGSprite->setColor({255, 255, 255});
        }
    }
}