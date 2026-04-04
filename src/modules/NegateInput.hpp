#pragma once

#include "../Module.hpp"
#include <Geode/modify/CCTextInputNode.hpp>

class $editorModule(NegateInput) {};

class $modify(NECCTextInputNode, CCTextInputNode) {
    $registerEditorHooks(NegateInput)

	bool allowedInput();
    bool init(float p0, float p1, char const* p2, char const* p3, int p4, char const* p5);
    bool onTextFieldInsertText(CCTextFieldTTF* pSender, char const* text, int nLen, enumKeyCodes keyCodes);
	void onNegate();
};