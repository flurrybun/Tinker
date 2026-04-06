#include "SingleDeselect.hpp"

void SDEditorUI::deselectSpecificObject() {
    auto pos = getMousePos();
    auto mousePosToNode = m_editorLayer->m_objectLayer->convertToNodeSpace(pos);

    for (GameObject* obj : CCArrayExt<GameObject*>(m_selectedObjects)) {
        auto objPos = obj->getPosition();
        auto objSize = obj->getScaledContentSize();
        auto objRect = CCRect {objPos.x - std::abs(objSize.width)/2, objPos.y - std::abs(objSize.height)/2, std::abs(objSize.width), std::abs(objSize.height)};

        auto levelEditorLayer = this->m_editorLayer;
        int currentLayer = levelEditorLayer->m_currentLayer;

        bool isOnCurrentEditorLayer1 = obj->m_editorLayer == levelEditorLayer->m_currentLayer;
        bool isOnCurrentEditorLayer2 = (obj->m_editorLayer2 == levelEditorLayer->m_currentLayer) && obj->m_editorLayer2 != 0;

        if (objRect.containsPoint(mousePosToNode) && (currentLayer == -1 || (isOnCurrentEditorLayer1 || isOnCurrentEditorLayer2))) {
            deselectObject(obj);
            break;
        }
    }
}

void SDEditorUI::selectObject(GameObject* p0, bool p1) {
    if (!getKeyPressed()) {
        EditorUI::selectObject(p0, p1);
    }
}

void SDEditorUI::selectObjects(CCArray* p0, bool p1) {
    if (!getKeyPressed()) {
        EditorUI::selectObjects(p0, p1);
    }
    else {
        for (GameObject* obj : geode::cocos::CCArrayExt<GameObject*>(p0)) {
            deselectObject(obj);
        }
    }
}

void SDEditorUI::ccTouchEnded(CCTouch* p0, CCEvent* p1) {
    if (m_selectedMode == 3) {
        if (getKeyPressed()) {
            deselectSpecificObject();
        }
    }
    EditorUI::ccTouchEnded(p0, p1);
}

bool SDEditorUI::getKeyPressed() {
    return SingleDeselect::get()->m_keyHeld;
}

void SingleDeselect::onEditor() {
    m_editorUI->addEventListener(
        KeybindSettingPressedEventV3(Mod::get(), "SingleDeselect-key"),
        [this](Keybind const& keybind, bool down, bool repeat, double timestamp) {
            m_keyHeld = down;
        }
    );
}