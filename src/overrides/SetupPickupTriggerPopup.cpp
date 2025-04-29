#include <Geode/modify/SetupPickupTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupPickupTriggerPopupShift, SetupPickupTriggerPopup) {

	struct Fields {
		CCLabelBMFont* m_countLabel;
		CCMenuItemSpriteExtra* m_countButton;
    };

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupPickupTriggerPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto itemIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto countLabel = mainLayer->getChildByType<CCLabelBMFont>(4);

        // Create the label buttons
        auto itemIdLabelButton = ShiftPopup::createLabelButton(itemIdLabel, this, menu_selector(SetupPickupTriggerPopupShift::onItemIdPress));
        auto countLabelButton = ShiftPopup::createLabelButton(countLabel, this, menu_selector(SetupPickupTriggerPopupShift::onCountPress));

        // Add buttons
		buttonMenu->addChild(itemIdLabelButton);
		buttonMenu->addChild(countLabelButton);

		// Set fields
		m_fields->m_countLabel = countLabel;
		m_fields->m_countButton = countLabelButton;

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		itemIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		countLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void updateState() {
		SetupPickupTriggerPopup::updateState();
		if (m_fields->m_countLabel) m_fields->m_countButton->setVisible(m_fields->m_countLabel->isVisible());
	} // updateState

	void onItemIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID))->show();
	} // onItemIdPress

    void onCountPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(
			objects->data, this,
			$get(static_cast<CountTriggerGameObject*>(obj)->m_pickupCount),
			$set(static_cast<CountTriggerGameObject*>(obj)->m_pickupCount),
			-9999, 9999
		)->show();
	} // onCountPress

}; // SetupPickupTriggerPopupShift