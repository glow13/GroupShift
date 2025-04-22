#include <Geode/modify/SetupItemCompareTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupItemCompareTriggerPopupShift, SetupItemCompareTriggerPopup) {

	bool init(ItemTriggerGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupItemCompareTriggerPopup::init(obj, objs)) return false;
		
		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto itemId1Label = mainLayer->getChildByType<CCLabelBMFont>(4);
		auto itemId2Label = mainLayer->getChildByType<CCLabelBMFont>(10);
		auto mod1Label = mainLayer->getChildByType<CCLabelBMFont>(16);
		auto mod2Label = mainLayer->getChildByType<CCLabelBMFont>(17);
		auto trueIdLabel = mainLayer->getChildByType<CCLabelBMFont>(18);
		auto falseIdLabel = mainLayer->getChildByType<CCLabelBMFont>(19);

		// Create the label buttons
        auto itemId1LabelButton = ShiftPopup::createLabelButton(itemId1Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId1Press));
        auto itemId2LabelButton = ShiftPopup::createLabelButton(itemId2Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId2Press));
        auto mod1LabelButton = ShiftPopup::createLabelButton(mod1Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod1Press));
        auto mod2LabelButton = ShiftPopup::createLabelButton(mod2Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod2Press));
        auto trueIdLabelButton = ShiftPopup::createLabelButton(trueIdLabel, this, menu_selector(SetupItemCompareTriggerPopupShift::onTrueIdPress));
        auto falseIdLabelButton = ShiftPopup::createLabelButton(falseIdLabel, this, menu_selector(SetupItemCompareTriggerPopupShift::onFalseIdPress));
        
		// Add buttons
		buttonMenu->addChild(itemId1LabelButton);
		buttonMenu->addChild(itemId2LabelButton);
		buttonMenu->addChild(mod1LabelButton);
		buttonMenu->addChild(mod2LabelButton);
		buttonMenu->addChild(trueIdLabelButton);
		buttonMenu->addChild(falseIdLabelButton);

		// Remove old labels
		itemId1Label->removeFromParentAndCleanup(true);
		itemId2Label->removeFromParentAndCleanup(true);
		mod1Label->removeFromParentAndCleanup(true);
		mod2Label->removeFromParentAndCleanup(true);
		trueIdLabel->removeFromParentAndCleanup(true);
		falseIdLabel->removeFromParentAndCleanup(true);

		// Get objects
		vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		itemId1LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		itemId2LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		mod1LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		mod2LabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		trueIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		falseIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		
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

	void onMod1Press(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); vector<float> mod1 = { triggerObject->m_mod1 }; return mod1; },
			[](EffectGameObject* obj, vector<float> vals) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); triggerObject->m_mod1 = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onMod1Press

	void onMod2Press(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); vector<float> mod2 = { triggerObject->m_mod2 }; return mod2; },
			[](EffectGameObject* obj, vector<float> vals) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); triggerObject->m_mod2 = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onMod2Press

	void onTrueIdPress(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> trueId = { static_cast<float>(obj->m_targetGroupID) }; return trueId; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onTrueIdPress

	void onFalseIdPress(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> falseId = { static_cast<float>(obj->m_centerGroupID) }; return falseId; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_centerGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onFalseIdPress

}; // SetupItemCompareTriggerPopupShift