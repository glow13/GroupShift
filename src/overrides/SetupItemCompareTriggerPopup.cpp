#include <Geode/modify/SetupItemCompareTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupItemCompareTriggerPopupShift, SetupItemCompareTriggerPopup) {

	bool init(ItemTriggerGameObject* obj, cocos2d::CCArray* objs) {

		if (!SetupItemCompareTriggerPopup::init(obj, objs)) return false;
		
		// Add node ids
		setID("SetupItemCompareTriggerPopup");
		getChildByType<CCLayer>(0)->setID("main-layer");
		getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(4)->setID("item-id-1-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(10)->setID("item-id-2-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(16)->setID("mod-1-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(17)->setID("mod-2-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(18)->setID("true-id-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(19)->setID("false-id-label");

		// Save references
        auto mainLayer = getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto itemId1Label = mainLayer->getChildByID("item-id-1-label");
		auto itemId2Label = mainLayer->getChildByID("item-id-2-label");
		auto mod1Label = mainLayer->getChildByID("mod-1-label");
		auto mod2Label = mainLayer->getChildByID("mod-2-label");
		auto trueIdLabel = mainLayer->getChildByID("true-id-label");
		auto falseIdLabel = mainLayer->getChildByID("false-id-label");
		
		// Create item id 1 button
        auto itemId1LabelSprite = CCLabelBMFont::create("ItemID1", "chatFont.fnt");
        itemId1LabelSprite->setScale(itemId1Label->getScale());
        auto itemId1LabelButton = CCMenuItemSpriteExtra::create(itemId1LabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId1Press));
        itemId1LabelButton->setID("item-id-1-label"_spr);
        itemId1LabelButton->setPosition(itemId1Label->getPositionX() - buttonMenu->getPositionX(), itemId1Label->getPositionY() - buttonMenu->getPositionY());
        itemId1LabelButton->setContentSize({itemId1Label->getContentWidth() * itemId1Label->getScaleX(), itemId1Label->getContentHeight() * itemId1Label->getScaleY()});
        itemId1LabelButton->setAnchorPoint(itemId1Label->getAnchorPoint());

		// Create item id 2 button
        auto itemId2LabelSprite = CCLabelBMFont::create("ItemID2", "chatFont.fnt");
        itemId2LabelSprite->setScale(itemId2Label->getScale());
        auto itemId2LabelButton = CCMenuItemSpriteExtra::create(itemId2LabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId2Press));
        itemId2LabelButton->setID("item-id-2-label"_spr);
        itemId2LabelButton->setPosition(itemId2Label->getPositionX() - buttonMenu->getPositionX(), itemId2Label->getPositionY() - buttonMenu->getPositionY());
        itemId2LabelButton->setContentSize({itemId2Label->getContentWidth() * itemId2Label->getScaleX(), itemId2Label->getContentHeight() * itemId2Label->getScaleY()});
        itemId2LabelButton->setAnchorPoint(itemId2Label->getAnchorPoint());

		// Create mod 1 button
        auto mod1LabelSprite = CCLabelBMFont::create("Mod1", "chatFont.fnt");
        mod1LabelSprite->setScale(mod1Label->getScale());
        auto mod1LabelButton = CCMenuItemSpriteExtra::create(mod1LabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod1Press));
        mod1LabelButton->setID("mod-1-label"_spr);
        mod1LabelButton->setPosition(mod1Label->getPositionX() - buttonMenu->getPositionX(), mod1Label->getPositionY() - buttonMenu->getPositionY());
        mod1LabelButton->setContentSize({mod1Label->getContentWidth() * mod1Label->getScaleX(), mod1Label->getContentHeight() * mod1Label->getScaleY()});
        mod1LabelButton->setAnchorPoint(mod1Label->getAnchorPoint());

		// Create mod 2 button
        auto mod2LabelSprite = CCLabelBMFont::create("Mod2", "chatFont.fnt");
        mod2LabelSprite->setScale(mod2Label->getScale());
        auto mod2LabelButton = CCMenuItemSpriteExtra::create(mod2LabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod2Press));
        mod2LabelButton->setID("mod-2-label"_spr);
        mod2LabelButton->setPosition(mod2Label->getPositionX() - buttonMenu->getPositionX(), mod2Label->getPositionY() - buttonMenu->getPositionY());
        mod2LabelButton->setContentSize({mod2Label->getContentWidth() * mod2Label->getScaleX(), mod2Label->getContentHeight() * mod2Label->getScaleY()});
        mod2LabelButton->setAnchorPoint(mod2Label->getAnchorPoint());

		// Create true id button
        auto trueIdLabelSprite = CCLabelBMFont::create("TrueID", "chatFont.fnt");
        trueIdLabelSprite->setScale(trueIdLabel->getScale());
        auto trueIdLabelButton = CCMenuItemSpriteExtra::create(trueIdLabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onTrueIdPress));
        trueIdLabelButton->setID("true-id-label"_spr);
        trueIdLabelButton->setPosition(trueIdLabel->getPositionX() - buttonMenu->getPositionX(), trueIdLabel->getPositionY() - buttonMenu->getPositionY());
        trueIdLabelButton->setContentSize({trueIdLabel->getContentWidth() * trueIdLabel->getScaleX(), trueIdLabel->getContentHeight() * trueIdLabel->getScaleY()});
        trueIdLabelButton->setAnchorPoint(trueIdLabel->getAnchorPoint());

		// Create false id button
        auto falseIdLabelSprite = CCLabelBMFont::create("FalseID", "chatFont.fnt");
        falseIdLabelSprite->setScale(falseIdLabel->getScale());
        auto falseIdLabelButton = CCMenuItemSpriteExtra::create(falseIdLabelSprite, this, menu_selector(SetupItemCompareTriggerPopupShift::onFalseIdPress));
        falseIdLabelButton->setID("false-id-label"_spr);
        falseIdLabelButton->setPosition(falseIdLabel->getPositionX() - buttonMenu->getPositionX(), falseIdLabel->getPositionY() - buttonMenu->getPositionY());
        falseIdLabelButton->setContentSize({falseIdLabel->getContentWidth() * falseIdLabel->getScaleX(), falseIdLabel->getContentHeight() * falseIdLabel->getScaleY()});
        falseIdLabelButton->setAnchorPoint(falseIdLabel->getAnchorPoint());

		// Add buttons
		buttonMenu->addChild(itemId1LabelButton);
		buttonMenu->addChild(itemId2LabelButton);
		buttonMenu->addChild(mod1LabelButton);
		buttonMenu->addChild(mod2LabelButton);
		buttonMenu->addChild(trueIdLabelButton);
		buttonMenu->addChild(falseIdLabelButton);

		// Remove old labels
		mainLayer->removeChildByID("item-id-1-label");
		mainLayer->removeChildByID("item-id-2-label");
		mainLayer->removeChildByID("mod-1-label");
		mainLayer->removeChildByID("mod-2-label");
		mainLayer->removeChildByID("true-id-label");
		mainLayer->removeChildByID("false-id-label");

		// Get objects
		std::vector<EffectGameObject*> objects;
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
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onItemId1Press

	void onItemId2Press(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID2) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID2 = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onItemId2Press

	void onMod1Press(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); std::vector<float> mod1 = { triggerObject->m_mod1 }; return mod1; },
			[](EffectGameObject* obj, std::vector<float> vals) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); triggerObject->m_mod1 = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onMod1Press

	void onMod2Press(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); std::vector<float> mod2 = { triggerObject->m_mod2 }; return mod2; },
			[](EffectGameObject* obj, std::vector<float> vals) { auto triggerObject = static_cast<ItemTriggerGameObject*>(obj); triggerObject->m_mod2 = vals[0]; },
			-9999, 9999
		);
        popup->setUserObject(this);
        popup->show();
	} // onMod2Press

	void onTrueIdPress(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> trueId = { static_cast<float>(obj->m_targetGroupID) }; return trueId; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onTrueIdPress

	void onFalseIdPress(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> falseId = { static_cast<float>(obj->m_centerGroupID) }; return falseId; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_centerGroupID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
	} // onFalseIdPress

}; // SetupItemCompareTriggerPopupShift