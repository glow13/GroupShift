#include <Geode/modify/SetupCountTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupCountTriggerPopupShift, SetupCountTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
		if (!SetupCountTriggerPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto itemIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
        auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(3);
		auto targetCountLabel = mainLayer->getChildByType<CCLabelBMFont>(2);

        // Create the label buttons
        auto itemIdLabelButton = ShiftPopup::createLabelButton(itemIdLabel, this, menu_selector(SetupCountTriggerPopupShift::onItemIdPress));
        auto targetIdLabelButton = ShiftPopup::createLabelButton(targetIdLabel, this, menu_selector(SetupCountTriggerPopupShift::onTargetIdPress));
        auto targetCountLabelButton = ShiftPopup::createLabelButton(targetCountLabel, this, menu_selector(SetupCountTriggerPopupShift::onTargetCountPress));

        // Add buttons
		buttonMenu->addChild(itemIdLabelButton);
		buttonMenu->addChild(targetIdLabelButton);
        buttonMenu->addChild(targetCountLabelButton);

        // Remove old labels
		itemIdLabel->removeFromParentAndCleanup(true);
        targetIdLabel->removeFromParentAndCleanup(true);
        targetCountLabel->removeFromParentAndCleanup(true);

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		itemIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		targetIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
        targetCountLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onItemIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        auto popup = PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID));
        popup->show();
	} // onItemIdPress

    void onTargetIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		auto popup = PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID));
        popup->show();
	} // onTargetIdPress

    void onTargetCountPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		auto popup = PropertyShiftPopup::create(
			objects->data,
			this,
			$get(static_cast<CountTriggerGameObject*>(obj)->m_pickupCount),
			$set(static_cast<CountTriggerGameObject*>(obj)->m_pickupCount),
			-9999, 9999
		);
        popup->show();
	} // onTargetCountPress

}; // SetupCountTriggerPopupShift