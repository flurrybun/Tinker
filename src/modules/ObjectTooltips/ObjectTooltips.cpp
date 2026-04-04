#include "ObjectTooltips.hpp"
#include <alphalaneous.editortab_api/include/EditorTabAPI.hpp>
#include "../../ObjectNames.hpp"
#include "../ScrollableObjects.hpp"

using namespace tinker::ui;

void ObjectTooltips::onEditor() {
    auto hover = TooltipHover::create();
    m_editorUI->addChild(hover);
    m_editorUI->m_uiItems->addObject(hover);

    alpha::editor_tabs::addTabSwitchCallback([hover] (auto tab) {
        hover->resetTooltip();
    });

    alpha::editor_tabs::addModeSwitchCallback([hover] (auto mode) {
        hover->resetTooltip();
    });
}

TooltipHover* TooltipHover::create() {
    auto ret = new TooltipHover();
    if (ret->init()) {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool TooltipHover::init() {
    if (!CCNode::init()) return false;

    setAnchorPoint({0, 0});
    setID("tooltip-hover-node"_spr);
    setZOrder(500);
    setContentSize(CCDirector::get()->getWinSize());

    m_tooltipBG = NineSlice::create("square02_001-uhd.png");
    m_tooltipBG->setColor({0, 0, 0});
    m_tooltipBG->setAnchorPoint({0.5f, 0.f});
    m_tooltipBG->setScaleMultiplier(0.4f);
    m_tooltipBG->setVisible(false);
    m_tooltipBG->setOpacity(220);
    m_tooltipBG->setID("tooltip-background"_spr);

    addChild(m_tooltipBG);

    m_tooltipLabel = CCLabelBMFont::create("", "chatFont.fnt");
    m_tooltipLabel->setScale(0.5f);
    m_tooltipLabel->setID("tooltip-label"_spr);

    m_tooltipBG->addChild(m_tooltipLabel);

    return true;
}

void TooltipHover::resetTooltip() {
    hideTooltip(m_activeItem);
    m_activeItem = nullptr;
}

bool TooltipHover::clickBegan(TouchEvent* touch) {
    if (m_activeItem) {
        m_tooltipBG->setVisible(false);
    }
    m_clicking = true;
    return true;
}

void TooltipHover::clickEnded(TouchEvent* touch) {
    if (m_activeItem) {
        m_tooltipBG->setVisible(true);
        auto bb = m_activeItem->boundingBox();

        auto positionWorld = m_activeItem->getParent()->convertToWorldSpace({m_activeItem->getPositionX(), bb.getMaxY() + 2});
        auto positionHere = convertToNodeSpace(positionWorld);

        m_tooltipBG->setPosition(positionHere);
    }
    m_clicking = false;
}

bool TooltipHover::mouseEntered(TouchEvent* touch) {
    return true;
}

void TooltipHover::mouseMoved(TouchEvent* touch) {
    if (LevelEditorLayer::get()->getChildByType<EditorPauseLayer>(0)) return;

    auto origItem = m_activeItem;
    if (origItem) setButtonOpacity(origItem, 255);

    auto tabIDRes = alpha::editor_tabs::getCurrentTab();
    if (!tabIDRes) return;
    auto tabID = tabIDRes.unwrap();

    auto tabRes = alpha::editor_tabs::nodeForTab(tabID);
    if (!tabRes) return;
    auto tab = tabRes.unwrap();

    auto editButtonBar = typeinfo_cast<EditButtonBar*>(tab.data());
    if (!editButtonBar) return;

    if (!editButtonBar->m_hasCreateItems) return;

    if (m_activeItem && (!nodeIsVisible(m_activeItem) || !m_activeItem->getParentByType<EditButtonBar>() || !alpha::utils::isPointInsideNode(m_activeItem, touch->getLocation()))) {
        m_activeItem = nullptr;
    }

    if (ScrollableObjects::isEnabled()) {
        auto scrollEditButtonBar = static_cast<SOEditButtonBar*>(editButtonBar);
        auto soEbbFields = scrollEditButtonBar->m_fields.self();
        bool inScrollBounds = alpha::utils::isPointInsideNode(soEbbFields->m_scrollLayer, touch->getLocation());
        if (!inScrollBounds && m_activeItem) {
            m_activeItem = nullptr;
        }

        if (inScrollBounds) {
            for (auto item : soEbbFields->m_visibleNodes) {
                if (!nodeIsVisible(item)) continue;
                if (!m_activeItem && alpha::utils::isPointInsideNode(item, touch->getLocation())) {
                    m_activeItem = static_cast<CreateMenuItem*>(item.data());
                    break;
                }
            }
        }
    }
    else {
        for (auto item : editButtonBar->m_buttonArray->asExt<CreateMenuItem>()) {
            if (!item->getParentByType<EditButtonBar>() || !nodeIsVisible(item)) continue;
            if (!m_activeItem && alpha::utils::isPointInsideNode(item, touch->getLocation())) {
                m_activeItem = item;
                break;
            }
        }
    }

    if (m_activeItem) {
        setButtonOpacity(m_activeItem, 172);
    }

    if (m_activeItem && m_activeItem != origItem) {
        showTooltip(m_activeItem);
    }
    if (!m_activeItem && origItem) {
        hideTooltip(origItem);
    }
}

void TooltipHover::setButtonOpacity(CreateMenuItem* item, GLubyte opacity) {
    auto buttonSprite = item->getChildByType<ButtonSprite>(0);
    if (buttonSprite) {
        auto spr = buttonSprite->getChildByType<CCSprite>(0);
        if (spr) {
            spr->setOpacity(opacity);
        }
    }
}

void TooltipHover::showTooltip(CreateMenuItem* item) {
    auto nameRes = ObjectNames::get()->getName(item->m_objectID);
    if (!nameRes) return;
    auto name = nameRes.unwrap();

    auto bb = item->boundingBox();

    auto positionWorld = item->getParent()->convertToWorldSpace({item->getPositionX(), bb.getMaxY() + 2});
    auto positionHere = convertToNodeSpace(positionWorld);
    m_tooltipLabel->setString(std::string(name).c_str());

    m_tooltipBG->setPosition(positionHere);
    m_tooltipBG->setContentSize(m_tooltipLabel->getScaledContentSize() + CCSize{5, 5});

    m_tooltipLabel->setPosition(m_tooltipBG->getContentSize() / 2);

    if (!m_clicking) {
        m_tooltipBG->setVisible(true);
    }
}

void TooltipHover::hideTooltip(CreateMenuItem* item) {
    if (!m_clicking) {
        m_tooltipBG->setVisible(false);
    }
}

void TooltipHover::onEnter() {
    CCNode::onEnter();
    CCTouchDispatcher::get()->addTargetedDelegate(this, -530, false);
}

void TooltipHover::onExit() {
    CCNode::onExit();
    CCTouchDispatcher::get()->removeDelegate(this);
}

