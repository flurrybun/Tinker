#include "OldColorTriggers.hpp"

std::unordered_map<int, std::string> OldColorTriggers::s_textureMap = {
    {29, "edit_eTintBGBtn_001.png"_spr},
    {30, "edit_eTintGBtn_001.png"_spr},
    {105, "edit_eTintObjBtn_001.png"_spr},
    {744, "edit_eTint3DLBtn_001.png"_spr},
    {900, "edit_eTintG2Btn_001.png"_spr},
    {915, "edit_eTintLBtn_001.png"_spr},
};

void OCTEffectGameObject::customSetup() {
    EffectGameObject::customSetup();
    if (!OldColorTriggers::s_textureMap.contains(m_objectID)) return;

    if (auto newSpr = CCSprite::create(OldColorTriggers::s_textureMap[m_objectID].c_str())) {
        m_addToNodeContainer = true;
        setTexture(newSpr->getTexture());
        setTextureRect(newSpr->getTextureRect());
    }
}