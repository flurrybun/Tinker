#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

namespace tinker::ui {
	class DurationControl;

	enum class ThumbType {
		Default,
		FadeIn,
		FadeOut,
		Multi
	};

	class DurationThumb : public CCNodeRGBA, public CCTouchDelegate {
	public:
		static DurationThumb* create(CCNode* parent, EffectGameObject* object, ThumbType thumbType = ThumbType::Default);

		bool init(CCNode* parent, EffectGameObject* object, ThumbType thumbType);
		void resetText();
		void hideText(float dt);
		void showText(float dt);
		CCRect getTouchBounds();
		void positionPulseSlider();
		void update(float dt) override;
		void checkFreeMoving();
		void select(bool select);
		void checkForNewLongest();

		bool ccTouchBegan(CCTouch* touch, CCEvent* event) override;
		void ccTouchMoved(CCTouch* touch, CCEvent* event) override;
		void ccTouchEnded(CCTouch* touch, CCEvent* event) override;
		void ccTouchCancelled(CCTouch* touch, CCEvent* event) override;

		void registerWithTouchDispatcher();
		void onEnter() override;
		void onExit() override;

		ThumbType m_thumbType = ThumbType::Default;

		float m_labelY = 0.f;
		float m_labelPosMultiplier = 1.f;
		CCNodeRGBA* m_thumbContainer = nullptr;
		CCSprite* m_thumbSpr = nullptr;
		CCSprite* m_thumbSelectedSpr = nullptr;
		CCNode* m_centerNode = nullptr;
		CCNode* m_parent = nullptr;
		DurationControl* m_control = nullptr;
		EffectGameObject* m_object = nullptr;
		CCLabelBMFont* m_durationLabel = nullptr;
		Ref<CCAction> m_fadeInAction = nullptr;
		Ref<CCAction> m_fadeOutAction = nullptr;

		CCPoint m_startingEndPos = {0, 0};
		CCPoint m_start = {0, 0};

		bool m_disabled = false;
		bool m_dragging = false;
		bool m_overlapping = false;

		float m_startingDuration = 0.f;
		float m_startingHoldDuration = 0.f;
		std::unordered_map<EffectGameObject*, float> m_selectedStartingDurations;
	};
}
