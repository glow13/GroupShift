#include <Geode/modify/SetupInstantCollisionTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupInstantCollisionTriggerPopupShift, SetupInstantCollisionTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupInstantCollisionTriggerPopup::init(obj, objs)) return false;
		setID("SetupInstantCollisionTriggerPopup");
		
		// Save references
		auto buttonMenu = getChildByType<CCLayer>(0)->getChildByType<CCMenu>(0);
		auto blockALabel = getChildByType<CCLayer>(0)->getChildByType<CCLabelBMFont>(1);
		auto blockBLabel = getChildByType<CCLayer>(0)->getChildByType<CCLabelBMFont>(2);
        auto trueIdLabel = getChildByType<CCLayer>(0)->getChildByType<CCLabelBMFont>(3);
		auto falseIdLabel = getChildByType<CCLayer>(0)->getChildByType<CCLabelBMFont>(4);
		
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
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		);
		popup->setUserObject(this);
		popup->show();
	} // onBlockAPress

	void onBlockBPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID2) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID2 = vals[0]; }
		);
		popup->setUserObject(this);
		popup->show();
	} // onBlockBPress

    void onTrueIDPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
		popup->setUserObject(this);
		popup->show();
	} // onTrueIDPress

    void onFalseIDPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_centerGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_centerGroupID = vals[0]; }
		);
		popup->setUserObject(this);
		popup->show();
	} // onFalseIDPress

}; // SetupInstantCollisionTriggerPopupShift