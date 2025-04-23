#include <Geode/modify/SetupInstantCollisionTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupInstantCollisionTriggerPopupShift, SetupInstantCollisionTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupInstantCollisionTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto blockALabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto blockBLabel = mainLayer->getChildByType<CCLabelBMFont>(2);
        auto trueIdLabel = mainLayer->getChildByType<CCLabelBMFont>(3);
		auto falseIdLabel = mainLayer->getChildByType<CCLabelBMFont>(4);

		// Create the label buttons
        auto blockALabelButton = ShiftPopup::createLabelButton(blockALabel, this, menu_selector(SetupInstantCollisionTriggerPopupShift::onBlockAPress));
		auto blockBLabelButton = ShiftPopup::createLabelButton(blockBLabel, this, menu_selector(SetupInstantCollisionTriggerPopupShift::onBlockBPress));
		auto trueIdLabelButton = ShiftPopup::createLabelButton(trueIdLabel, this, menu_selector(SetupInstantCollisionTriggerPopupShift::onTrueIDPress));
		auto falseIdLabelButton = ShiftPopup::createLabelButton(falseIdLabel, this, menu_selector(SetupInstantCollisionTriggerPopupShift::onFalseIDPress));

		// Add buttons
		buttonMenu->addChild(blockALabelButton);
		buttonMenu->addChild(blockBLabelButton);
        buttonMenu->addChild(trueIdLabelButton);
        buttonMenu->addChild(falseIdLabelButton);

		// Remove old labels
		blockALabel->removeFromParentAndCleanup(true);
		blockBLabel->removeFromParentAndCleanup(true);
		trueIdLabel->removeFromParentAndCleanup(true);
		falseIdLabel->removeFromParentAndCleanup(true);

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		blockALabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		blockBLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		trueIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		falseIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onBlockAPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        auto popup = PropertyShiftPopup::create(objects->data, $get(obj->m_itemID), $set(obj->m_itemID));
		popup->setUserObject(this);
		popup->show();
	} // onBlockAPress

	void onBlockBPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		auto popup = PropertyShiftPopup::create(objects->data, $get(obj->m_itemID2), $set(obj->m_itemID2));
		popup->setUserObject(this);
		popup->show();
	} // onBlockBPress

    void onTrueIDPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		auto popup = PropertyShiftPopup::create(objects->data, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID));
		popup->setUserObject(this);
		popup->show();
	} // onTrueIDPress

    void onFalseIDPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		auto popup = PropertyShiftPopup::create(objects->data, $get(obj->m_centerGroupID), $set(obj->m_centerGroupID));
		popup->setUserObject(this);
		popup->show();
	} // onFalseIDPress

}; // SetupInstantCollisionTriggerPopupShift