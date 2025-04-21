#include <Geode/modify/SetupInstantCountPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupInstantCountPopupShift, SetupInstantCountPopup) {

	bool init(CountTriggerGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
		if (!SetupInstantCountPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto itemIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
        auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(3);
		auto targetCountLabel = mainLayer->getChildByType<CCLabelBMFont>(2);

        // Create the label buttons
        auto itemIdLabelButton = CCMenuItemSpriteExtra::create(itemIdLabel, this, menu_selector(SetupInstantCountPopupShift::onItemIdPress));
        auto targetIdLabelButton = CCMenuItemSpriteExtra::create(targetIdLabel, this, menu_selector(SetupInstantCountPopupShift::onTargetIdPress));
        auto targetCountLabelButton = CCMenuItemSpriteExtra::create(targetCountLabel, this, menu_selector(SetupInstantCountPopupShift::onTargetCountPress));

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
		itemIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		targetIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
        targetCountLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

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

    void onTargetIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onTargetIdPress

    void onTargetCountPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj); std::vector<float> group = { static_cast<float>(countTriggerObj->m_pickupCount) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj); countTriggerObj->m_pickupCount = vals[0]; },
            -9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onTargetCountPress

}; // SetupInstantCountPopupShift