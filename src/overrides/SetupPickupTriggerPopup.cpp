#include <Geode/modify/SetupPickupTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupPickupTriggerPopupShift, SetupPickupTriggerPopup) {

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

        // Remove old labels
		itemIdLabel->removeFromParentAndCleanup(true);
		countLabel->removeFromParentAndCleanup(true);

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		itemIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		countLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onItemIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onItemIdPress

    void onCountPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto pickupTriggerObj = static_cast<CountTriggerGameObject*>(obj); std::vector<float> group = { static_cast<float>(pickupTriggerObj->m_pickupCount) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { auto pickupTriggerObj = static_cast<CountTriggerGameObject*>(obj); pickupTriggerObj->m_pickupCount = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onCountPress

}; // SetupPickupTriggerPopupShift