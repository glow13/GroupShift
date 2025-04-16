#include <Geode/modify/SetupInstantCollisionTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

const int initAddress = 0x402270;

class $modify(SetupInstantCollisionTriggerPopupShift, SetupInstantCollisionTriggerPopup) {

	static bool init(SetupInstantCollisionTriggerPopup* self, EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Add node ids
		self->setID("SetupInstantCollisionTriggerPopup");
		self->getChildByType<CCLayer>(0)->setID("main-layer");
		self->getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
		self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("block-a-label");
		self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(2)->setID("block-b-label");
        self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(3)->setID("true-id-label");
		self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(4)->setID("false-id-label");
		
		// Save references
        auto mainLayer = self->getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto blockALabel = mainLayer->getChildByID("block-a-label");
		auto blockBLabel = mainLayer->getChildByID("block-b-label");
        auto trueIdLabel = mainLayer->getChildByID("true-id-label");
        auto falseIdLabel = mainLayer->getChildByID("false-id-label");
		
		// Create block A button
        auto blockALabelSprite = CCLabelBMFont::create("BlockA ID", "goldFont.fnt");
        blockALabelSprite->setScale(blockALabel->getScale());
        auto blockALabelButton = CCMenuItemSpriteExtra::create(blockALabelSprite, self, menu_selector(SetupInstantCollisionTriggerPopupShift::onBlockAPress));
        blockALabelButton->setID("block-a-label"_spr);
        blockALabelButton->setPosition(blockALabel->getPositionX() - buttonMenu->getPositionX(), blockALabel->getPositionY() - buttonMenu->getPositionY());
        blockALabelButton->setContentSize({blockALabel->getContentWidth() * blockALabel->getScaleX(), blockALabel->getContentHeight() * blockALabel->getScaleY()});
        blockALabelButton->setAnchorPoint(blockALabel->getAnchorPoint());

		// Create block B button
        auto blockBLabelSprite = CCLabelBMFont::create("BlockB ID", "goldFont.fnt");
        blockBLabelSprite->setScale(blockBLabel->getScale());
        auto blockBLabelButton = CCMenuItemSpriteExtra::create(blockBLabelSprite, self, menu_selector(SetupInstantCollisionTriggerPopupShift::onBlockBPress));
        blockBLabelButton->setID("block-b-label"_spr);
        blockBLabelButton->setPosition(blockBLabel->getPositionX() - buttonMenu->getPositionX(), blockBLabel->getPositionY() - buttonMenu->getPositionY());
        blockBLabelButton->setContentSize({blockBLabel->getContentWidth() * blockBLabel->getScaleX(), blockBLabel->getContentHeight() * blockBLabel->getScaleY()});
        blockBLabelButton->setAnchorPoint(blockBLabel->getAnchorPoint());

        // Create true id button
        auto trueIdLabelSprite = CCLabelBMFont::create("True ID", "goldFont.fnt");
        trueIdLabelSprite->setScale(trueIdLabel->getScale());
        auto trueIdLabelButton = CCMenuItemSpriteExtra::create(trueIdLabelSprite, self, menu_selector(SetupInstantCollisionTriggerPopupShift::onTrueIDPress));
        trueIdLabelButton->setID("true-id-label"_spr);
        trueIdLabelButton->setPosition(trueIdLabel->getPositionX() - buttonMenu->getPositionX(), trueIdLabel->getPositionY() - buttonMenu->getPositionY());
        trueIdLabelButton->setContentSize({trueIdLabel->getContentWidth() * trueIdLabel->getScaleX(), trueIdLabel->getContentHeight() * trueIdLabel->getScaleY()});
        trueIdLabelButton->setAnchorPoint(trueIdLabel->getAnchorPoint());

        // Create false id button
        auto falseIdLabelSprite = CCLabelBMFont::create("False ID", "goldFont.fnt");
        falseIdLabelSprite->setScale(falseIdLabel->getScale());
        auto falseIdLabelButton = CCMenuItemSpriteExtra::create(falseIdLabelSprite, self, menu_selector(SetupInstantCollisionTriggerPopupShift::onFalseIDPress));
        falseIdLabelButton->setID("false-id-label"_spr);
        falseIdLabelButton->setPosition(falseIdLabel->getPositionX() - buttonMenu->getPositionX(), falseIdLabel->getPositionY() - buttonMenu->getPositionY());
        falseIdLabelButton->setContentSize({falseIdLabel->getContentWidth() * falseIdLabel->getScaleX(), falseIdLabel->getContentHeight() * falseIdLabel->getScaleY()});
        falseIdLabelButton->setAnchorPoint(falseIdLabel->getAnchorPoint());

		// Add buttons
		buttonMenu->addChild(blockALabelButton);
		buttonMenu->addChild(blockBLabelButton);
        buttonMenu->addChild(trueIdLabelButton);
        buttonMenu->addChild(falseIdLabelButton);

		// Remove old labels
		mainLayer->removeChildByID("block-a-label");
		mainLayer->removeChildByID("block-b-label");
        mainLayer->removeChildByID("true-id-label");
        mainLayer->removeChildByID("false-id-label");

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		blockALabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		blockALabelButton->setUserData(self);
		blockBLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		blockBLabelButton->setUserData(self);
        trueIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		trueIdLabelButton->setUserData(self);
        falseIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		falseIdLabelButton->setUserData(self);
	
		return true;
	} // init

	void onBlockAPress(CCObject* sender) {
		auto self = static_cast<SetupInstantCollisionTriggerPopup*>(static_cast<CCNode*>(sender)->getUserData());
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		);
		popup->setUserData(self);
		popup->show();
	} // onBlockAPress

	void onBlockBPress(CCObject* sender) {
		auto self = static_cast<SetupInstantCollisionTriggerPopup*>(static_cast<CCNode*>(sender)->getUserData());
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID2) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID2 = vals[0]; }
		);
		popup->setUserData(self);
		popup->show();
	} // onBlockBPress

    void onTrueIDPress(CCObject* sender) {
		auto self = static_cast<SetupInstantCollisionTriggerPopup*>(static_cast<CCNode*>(sender)->getUserData());
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
		popup->setUserData(self);
		popup->show();
	} // onTrueIDPress

    void onFalseIDPress(CCObject* sender) {
		auto self = static_cast<SetupInstantCollisionTriggerPopup*>(static_cast<CCNode*>(sender)->getUserData());
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_centerGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_centerGroupID = vals[0]; }
		);
		popup->setUserData(self);
		popup->show();
	} // onFalseIDPress

	void onClose(SetupInstantCollisionTriggerPopup* self) {
		static tulip::hook::WrapperMetadata metadata;
        metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Fastcall);
        metadata.m_abstract = tulip::hook::AbstractFunction::from(&onClose_hook);
        auto original = geode::hook::createWrapper(reinterpret_cast<void*>(geode::base::get() + 0x09b8c0), metadata).unwrap();
        reinterpret_cast<void(*)(CCObject*)>(original)(self); // SetupInstantCollisionTriggerPopup::onClose
	} // onClose

}; // SetupInstantCollisionTriggerPopupShift

bool SetupInstantCollisionTriggerPopup_init(SetupInstantCollisionTriggerPopup* self, EffectGameObject* obj, cocos2d::CCArray* objs) {
    tulip::hook::WrapperMetadata metadata;
    metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Thiscall);
    metadata.m_abstract = tulip::hook::AbstractFunction::from(&SetupInstantCollisionTriggerPopup_init);
    auto original = geode::hook::createWrapper(reinterpret_cast<bool*>(geode::base::get() + initAddress), metadata).unwrap();

    bool success = reinterpret_cast<bool(*)(SetupInstantCollisionTriggerPopup*, EffectGameObject*, cocos2d::CCArray*)>(original)(self, obj, objs);
    if (!success) return false;
    
    return SetupInstantCollisionTriggerPopupShift::init(self, obj, objs);
}

// Manual hooks are not fun :/
$execute {
    auto result = Mod::get()->hook(
        reinterpret_cast<void*>(geode::base::get() + initAddress),
        &SetupInstantCollisionTriggerPopup_init,
        "SetupInstantCollisionTriggerPopup::init",
        tulip::hook::TulipConvention::Thiscall
    );
}