#include <Geode/modify/SetupPickupTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupPickupTriggerPopupShift, SetupPickupTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		if (!SetupPickupTriggerPopup::init(obj, objs)) return false;

        // Add node ids
		this->setID("SetupPickupTriggerPopup");
		this->getChildByType<CCLayer>(0)->setID("main-layer");
		this->getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
		this->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("item-id-label");
		this->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(4)->setID("count-label");

        // Save references
        auto mainLayer = this->getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto itemIdLabel = mainLayer->getChildByID("item-id-label");
		auto countLabel = mainLayer->getChildByID("count-label");
		
        // Create item id button
        auto itemIdLabelSprite = CCLabelBMFont::create("ItemID", "goldFont.fnt");
        itemIdLabelSprite->setScale(itemIdLabel->getScale());
        auto itemIdLabelButton = CCMenuItemSpriteExtra::create(itemIdLabelSprite, this, menu_selector(SetupPickupTriggerPopupShift::onItemIdPress));
        itemIdLabelButton->setID("item-id-label"_spr);
        itemIdLabelButton->setPosition(itemIdLabel->getPositionX() - buttonMenu->getPositionX(), itemIdLabel->getPositionY() - buttonMenu->getPositionY());
        itemIdLabelButton->setContentSize({itemIdLabel->getContentWidth() * itemIdLabel->getScaleX(), itemIdLabel->getContentHeight() * itemIdLabel->getScaleY()});
        itemIdLabelButton->setAnchorPoint(itemIdLabel->getAnchorPoint());

        // Create count button
        auto countLabelSprite = CCLabelBMFont::create("Count", "goldFont.fnt");
        countLabelSprite->setScale(countLabel->getScale());
        auto countLabelButton = CCMenuItemSpriteExtra::create(countLabelSprite, this, menu_selector(SetupPickupTriggerPopupShift::onCountPress));
        countLabelButton->setID("count-label"_spr);
        countLabelButton->setPosition(countLabel->getPositionX() - buttonMenu->getPositionX(), countLabel->getPositionY() - buttonMenu->getPositionY());
        countLabelButton->setContentSize({countLabel->getContentWidth() * countLabel->getScaleX(), countLabel->getContentHeight() * countLabel->getScaleY()});
        countLabelButton->setAnchorPoint(countLabel->getAnchorPoint());

        // Add buttons
		buttonMenu->addChild(itemIdLabelButton);
		buttonMenu->addChild(countLabelButton);

        // Remove old labels
		mainLayer->removeChildByID("item-id-label");
		mainLayer->removeChildByID("count-label");

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) {
			objects.push_back(obj);
		}
		else {
			for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) {
				objects.push_back(obj2);
			}
		}

        // Set button data
		itemIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		countLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	}

	void onItemIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

        PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; },
			999999
		)->show();

		onClose(this);
	}

    void onCountPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

        PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) {
                auto pickupTriggerObj = static_cast<CountTriggerGameObject*>(obj);
                std::vector<float> group = { static_cast<float>(pickupTriggerObj->m_pickupCount) }; return group;
            },
			[](EffectGameObject* obj, std::vector<float> vals) {
                auto pickupTriggerObj = static_cast<CountTriggerGameObject*>(obj);
                pickupTriggerObj->m_pickupCount = vals[0];
            }
		)->show();

		onClose(this);
	}
};