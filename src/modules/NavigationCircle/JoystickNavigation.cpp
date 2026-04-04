#include "JoystickNavigation.hpp"
#include "NavigationControl.hpp"

using namespace tinker::ui;

void JoystickNavigation::onEditor() {
    auto navControl = NavigationControl::create(m_editorUI, getSetting<float, "opacity">(), getSetting<float, "scale">());
    navControl->setID("navigation-control"_spr);

    m_editorUI->m_uiItems->addObject(navControl);
    m_editorUI->addChild(navControl);
}