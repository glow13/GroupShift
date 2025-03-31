#include <Geode/modify/SetupInstantCountPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupInstantCountPopupShift, SetupInstantCountPopup) {

	bool init(CountTriggerGameObject* obj, cocos2d::CCArray* objs) {

		if (!SetupInstantCountPopup::init(obj, objs)) return false;

        // Add node ids
		this->setID("SetupInstantCountPopup");
		this->getChildByType<CCLayer>(0)->setID("main-layer");
		this->getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
		this->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("item-id-label");
        this->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(3)->setID("target-id-label");
		this->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(2)->setID("target-count-label");

        // Save references
        auto mainLayer = this->getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto itemIdLabel = mainLayer->getChildByID("item-id-label");
        auto targetIdLabel = mainLayer->getChildByID("target-id-label");
		auto targetCountLabel = mainLayer->getChildByID("target-count-label");
		
        // Create item id button
        auto itemIdLabelSprite = CCLabelBMFont::create("Item ID", "goldFont.fnt");
        itemIdLabelSprite->setScale(itemIdLabel->getScale());
        auto itemIdLabelButton = CCMenuItemSpriteExtra::create(itemIdLabelSprite, this, menu_selector(SetupInstantCountPopupShift::onItemIdPress));
        itemIdLabelButton->setID("item-id-label"_spr);
        itemIdLabelButton->setPosition(itemIdLabel->getPositionX() - buttonMenu->getPositionX(), itemIdLabel->getPositionY() - buttonMenu->getPositionY());
        itemIdLabelButton->setContentSize({itemIdLabel->getContentWidth() * itemIdLabel->getScaleX(), itemIdLabel->getContentHeight() * itemIdLabel->getScaleY()});
        itemIdLabelButton->setAnchorPoint(itemIdLabel->getAnchorPoint());

        // Create target id button
        auto targetIdLabelSprite = CCLabelBMFont::create("Target ID", "goldFont.fnt");
        targetIdLabelSprite->setScale(targetIdLabel->getScale());
        auto targetIdLabelButton = CCMenuItemSpriteExtra::create(targetIdLabelSprite, this, menu_selector(SetupInstantCountPopupShift::onTargetIdPress));
        targetIdLabelButton->setID("target-id-label"_spr);
        targetIdLabelButton->setPosition(targetIdLabel->getPositionX() - buttonMenu->getPositionX(), targetIdLabel->getPositionY() - buttonMenu->getPositionY());
        targetIdLabelButton->setContentSize({targetIdLabel->getContentWidth() * targetIdLabel->getScaleX(), targetIdLabel->getContentHeight() * targetIdLabel->getScaleY()});
        targetIdLabelButton->setAnchorPoint(targetIdLabel->getAnchorPoint());

        // Create target count button
        auto targetCountLabelSprite = CCLabelBMFont::create("Target Count", "goldFont.fnt");
        targetCountLabelSprite->setScale(targetCountLabel->getScale());
        auto targetCountLabelButton = CCMenuItemSpriteExtra::create(targetCountLabelSprite, this, menu_selector(SetupInstantCountPopupShift::onTargetCountPress));
        targetCountLabelButton->setID("target-count-label"_spr);
        targetCountLabelButton->setPosition(targetCountLabel->getPositionX() - buttonMenu->getPositionX(), targetCountLabel->getPositionY() - buttonMenu->getPositionY());
        targetCountLabelButton->setContentSize({targetCountLabel->getContentWidth() * targetCountLabel->getScaleX(), targetCountLabel->getContentHeight() * targetCountLabel->getScaleY()});
        targetCountLabelButton->setAnchorPoint(targetCountLabel->getAnchorPoint());

        // Add buttons
		buttonMenu->addChild(itemIdLabelButton);
		buttonMenu->addChild(targetIdLabelButton);
        buttonMenu->addChild(targetCountLabelButton);

        // Remove old labels
		mainLayer->removeChildByID("item-id-label");
		mainLayer->removeChildByID("target-id-label");
        mainLayer->removeChildByID("target-count-label");

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
		targetIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
        targetCountLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

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

    void onTargetIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

        PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		)->show();
        
		onClose(this);
	}

    void onTargetCountPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

        PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) {
                auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj);
                std::vector<float> group = { static_cast<float>(countTriggerObj->m_pickupCount) }; return group;
            },
			[](EffectGameObject* obj, std::vector<float> vals) {
                auto countTriggerObj = static_cast<CountTriggerGameObject*>(obj);
                countTriggerObj->m_pickupCount = vals[0];
            },
            999999
		)->show();
        
		onClose(this);
	}

    void onClose(SetupInstantCountPopup* self) {
		static tulip::hook::WrapperMetadata metadata;
        metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Fastcall);
        metadata.m_abstract = tulip::hook::AbstractFunction::from(&onClose_hook);
        auto original = geode::hook::createWrapper(reinterpret_cast<void*>(geode::base::get() + 0x09b8c0), metadata).unwrap();
        reinterpret_cast<void(*)(CCObject*)>(original)(self); // SetupInstantCountPopup::onClose
	}
};