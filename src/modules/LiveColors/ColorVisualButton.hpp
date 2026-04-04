#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace tinker::ui {
	class ColorVisualButton : public CCMenuItemSpriteExtra {
	public:
		~ColorVisualButton();

		static ColorVisualButton* create(EditorUI* editorUI);
		bool init(EditorUI* editorUI);
		void setColorData(int id, const ccColor3B& color, bool blending, float opacity, ColorAction* action);
		void openColorPicker(CCObject* obj);
		std::string idToString(int ID);
	protected:
		EditorUI* m_editorUI;
		int m_currentColorID = -1;
		ColorChannelSprite* m_colorChannelSprite;
		ColorAction* m_action;
		CCLabelBMFont* m_IDLabel;
		Ref<GJColorSetupLayer> m_colorSetupLayer;
	};
}
