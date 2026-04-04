#pragma once

#include "../../Module.hpp"
#include <Geode/ui/NineSlice.hpp>
#include <alphalaneous.alphas-ui-pack/include/API.hpp>
#include <Geode/modify/CreateMenuItem.hpp>

using namespace alpha::prelude;

class $editorModule(ObjectTooltips) {
    void onEditor() override;
};

namespace tinker::ui {
    class TooltipHover : public CCNode, public TouchDelegate {
    public:
        static TooltipHover* create();
        void resetTooltip();
    protected:
        bool init() override;

        bool mouseEntered(TouchEvent* touch) override;
        void mouseMoved(TouchEvent* touch) override;

        bool clickBegan(TouchEvent* touch) override;
        void clickEnded(TouchEvent* touch) override;

        void onEnter() override;
        void onExit() override;

        void showTooltip(CreateMenuItem* item);
        void hideTooltip(CreateMenuItem* item);

        void setButtonOpacity(CreateMenuItem* item, GLubyte opacity);

        bool m_clicking;
        CreateMenuItem* m_activeItem = nullptr;
        geode::NineSlice* m_tooltipBG;
        CCLabelBMFont* m_tooltipLabel;
    };
}
