#include "ObjectSummary.hpp"
#include "ObjectPopup.hpp"

using namespace tinker::ui;

bool OSLevelSettingsLayer::init(LevelSettingsObject* p0, LevelEditorLayer* p1) {
    if (!LevelSettingsLayer::init(p0, p1)) return false;

    if (p0->m_startsWithStartPos) return true;

    auto newMenu = CCMenu::create();
    newMenu->setID("object-summary-menu"_spr);
    newMenu->ignoreAnchorPointForPosition(false);
    m_mainLayer->addChild(newMenu);

    auto spr = CircleButtonSprite::createWithSprite(
        "object_summary.png"_spr, 0.75f,
        CircleBaseColor::Green
    );
    spr->setScale(0.85f);

    auto summaryButton = CCMenuItemExt::createSpriteExtra(spr, [this] (auto sender) {
        ObjectPopup::create(m_editorLayer)->show();
    });

    auto winSize = CCDirector::get()->getWinSize();
    summaryButton->setPosition({winSize.width/2 - 185, winSize.height/2 - 115});

    newMenu->addChild(summaryButton);

    handleTouchPriority(this);

    return true;
}

