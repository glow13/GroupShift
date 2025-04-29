#include <Geode/modify/ColorSelectPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(ColorSelectPopupShift, ColorSelectPopup) {

	struct Fields {
        CCMenuItemSpriteExtra* m_channelIdButton = nullptr;
    };

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs, ColorAction* action) {

        // Initialize popup
		if (!ColorSelectPopup::init(obj, objs, action)) return false;
		if (action != nullptr) return true;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto hsvWidget = getChildByType<ConfigureHSVWidget>(0);
		auto channelIdLabel = getChildByType<CCLabelBMFont>(1);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto fadeTimeLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto colorIdLabel = mainLayer->getChildByType<CCLabelBMFont>(11);

        // Create the label buttons
        auto channelIdLabelButton = ShiftPopup::createLabelButton(channelIdLabel, this, menu_selector(ColorSelectPopupShift::onChannelIdPress));
        auto fadeTimeLabelButton = ShiftPopup::createLabelButton(fadeTimeLabel, this, menu_selector(ColorSelectPopupShift::onFadeTimePress));
        auto colorIdLabelButton = ShiftPopup::createLabelButton(colorIdLabel, this, menu_selector(ColorSelectPopupShift::onColorIdPress));

		// Set fields
		m_fields->m_channelIdButton = channelIdLabelButton;

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		channelIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		fadeTimeLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
        colorIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onToggleHSVMode(CCObject* sender) {
		ColorSelectPopup::onToggleHSVMode(sender);
		m_fields->m_channelIdButton->setVisible(m_showCopyObjects);
	} // onToggleHSVMode

	void onChannelIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_copyColorID), $set(obj->m_copyColorID), 1, 999)->show();
	} // onChannelIdPress

    void onFadeTimePress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_duration), $set(obj->m_duration), 0, 10000)->show();
	} // onFadeTimePress

    void onColorIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetColor), $set(obj->m_targetColor), 1, 999)->show();
	} // onColorIdPress

}; // ColorSelectPopupShift