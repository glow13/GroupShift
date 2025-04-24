#include <Geode/modify/SetupCollisionTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupCollisionTriggerPopupShift, SetupCollisionTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupCollisionTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto blockALabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto blockBLabel = mainLayer->getChildByType<CCLabelBMFont>(2);
        auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(3);

		// Create the label buttons
        auto blockALabelButton = ShiftPopup::createLabelButton(blockALabel, this, menu_selector(SetupCollisionTriggerPopupShift::onBlockAPress));
		auto blockBLabelButton = ShiftPopup::createLabelButton(blockBLabel, this, menu_selector(SetupCollisionTriggerPopupShift::onBlockBPress));
		auto targetIdLabelButton = ShiftPopup::createLabelButton(targetIdLabel, this, menu_selector(SetupCollisionTriggerPopupShift::onTargetIDPress));

		// Add buttons
		buttonMenu->addChild(blockALabelButton);
		buttonMenu->addChild(blockBLabelButton);
        buttonMenu->addChild(targetIdLabelButton);

		// Remove old labels
		blockALabel->removeFromParentAndCleanup(true);
		blockBLabel->removeFromParentAndCleanup(true);
		targetIdLabel->removeFromParentAndCleanup(true);

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		blockALabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		blockBLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		targetIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onBlockAPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID))->show();
	} // onBlockAPress

	void onBlockBPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID2), $set(obj->m_itemID2))->show();
	} // onBlockBPress

    void onTargetIDPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onTargetIDPress

}; // SetupCollisionTriggerPopupShift