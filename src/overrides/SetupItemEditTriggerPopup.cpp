#include <Geode/modify/SetupItemEditTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupItemEditTriggerPopupShift, SetupItemEditTriggerPopup) {

	bool init(ItemTriggerGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupItemEditTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto itemId1Label = mainLayer->getChildByType<CCLabelBMFont>(4);
		auto itemId2Label = mainLayer->getChildByType<CCLabelBMFont>(10);
		auto modLabel = mainLayer->getChildByType<CCLabelBMFont>(16);
		auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(17);

		// Create the label buttons
        auto itemId1LabelButton = ShiftPopup::createLabelButton(itemId1Label, this, menu_selector(SetupItemEditTriggerPopupShift::onItemId1Press));
        auto itemId2LabelButton = ShiftPopup::createLabelButton(itemId2Label, this, menu_selector(SetupItemEditTriggerPopupShift::onItemId2Press));
        auto modLabelButton = ShiftPopup::createLabelButton(modLabel, this, menu_selector(SetupItemEditTriggerPopupShift::onModPress));
        auto targetIdLabelButton = ShiftPopup::createLabelButton(targetIdLabel, this, menu_selector(SetupItemEditTriggerPopupShift::onTargetIdPress));

		// Add buttons
		buttonMenu->addChild(itemId1LabelButton);
		buttonMenu->addChild(itemId2LabelButton);
		buttonMenu->addChild(modLabelButton);
		buttonMenu->addChild(targetIdLabelButton);

		// Remove old labels
		itemId1Label->removeFromParentAndCleanup(true);
		itemId2Label->removeFromParentAndCleanup(true);
		modLabel->removeFromParentAndCleanup(true);
		targetIdLabel->removeFromParentAndCleanup(true);

		// Get objects
		vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		itemId1LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		itemId2LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		modLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		targetIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onItemId1Press(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_itemID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onItemId1Press

	void onItemId2Press(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> group = { static_cast<float>(obj->m_itemID2) }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_itemID2 = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onItemId2Press

	void onModPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); vector<float> mod1 = { triggerObject->m_mod1 }; return mod1; },
			[](EffectGameObject* obj, vector<float> vals) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); triggerObject->m_mod1 = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onModPress

	void onTargetIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> trueId = { static_cast<float>(obj->m_targetGroupID) }; return trueId; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onTargetIdPress

}; // SetupItemEditTriggerPopupShift