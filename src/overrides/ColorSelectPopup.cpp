#include <Geode/modify/ColorSelectPopup.hpp>
#include "PropertyShiftPopup.hpp"

CCMenuItemSpriteExtra* channelId;

class $modify(ColorSelectPopupShift, ColorSelectPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs, ColorAction* idk) {

        // Initialize popup
		if (!ColorSelectPopup::init(obj, objs, idk)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto hsvWidget = getChildByType<ConfigureHSVWidget>(0);
		auto channelIdLabel = getChildByType<CCLabelBMFont>(1);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto fadeTimeLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto colorIdLabel = mainLayer->getChildByType<CCLabelBMFont>(11);        

        // Create the label buttons
        auto channelIdButton = ShiftPopup::createLabelButton(channelIdLabel, this, menu_selector(ColorSelectPopupShift::onChannelIdPress));
        auto fadeTimeButton = ShiftPopup::createLabelButton(fadeTimeLabel, this, menu_selector(ColorSelectPopupShift::onFadeTimePress));
        auto colorIdButton = ShiftPopup::createLabelButton(colorIdLabel, this, menu_selector(ColorSelectPopupShift::onColorIdPress));

        // Add buttons
		buttonMenu->addChild(channelIdButton);
		buttonMenu->addChild(fadeTimeButton);
        buttonMenu->addChild(colorIdButton);

        // Remove old labels
		channelIdLabel->removeFromParentAndCleanup(true);
        fadeTimeLabel->removeFromParentAndCleanup(true);
        colorIdLabel->removeFromParentAndCleanup(true);

		// Make sure the channel id behaves correctly
		channelIdButton->setVisible(m_showCopyObjects);
		channelId = channelIdButton;

        // Get objects
		vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		channelIdButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		fadeTimeButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
        colorIdButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onToggleHSVMode(CCObject* sender) {
		ColorSelectPopup::onToggleHSVMode(sender);
		channelId->setVisible(m_showCopyObjects);
	} // onToggleHSVMode

	void onChannelIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> group = { static_cast<float>(obj->m_copyColorID) }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_copyColorID = vals[0]; },
			1, 999
		);
        popup->setUserObject(this);
        popup->show();
	} // onChannelIdPress

    void onFadeTimePress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> group = { obj->m_duration }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_duration = vals[0]; },
			0, 10000
		);
        popup->setUserObject(this);
        popup->show();
	} // onFadeTimePress

    void onColorIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj); vector<float> group = { static_cast<float>(countTriggerObj->m_targetColor) }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj); countTriggerObj->m_targetColor = vals[0]; },
			1, 999
		);
        popup->setUserObject(this);
        popup->show();
	} // onColorIdPress

}; // ColorSelectPopupShift