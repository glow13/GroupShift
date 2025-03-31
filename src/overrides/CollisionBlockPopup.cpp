#include <Geode/modify/CollisionBlockPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(CollisionBlockPopupShift, CollisionBlockPopup) {
    
    static bool init(CollisionBlockPopup* self, EffectGameObject* obj, cocos2d::CCArray* objs) {
        log::info("Hooking CollisionBlockPopup::init!");

        // Add node ids
        self->setID("CollisionBlockPopup");
        self->getChildByType<CCLayer>(0)->setID("main-layer");
        self->getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
        self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("block-id-label");

        // Save references
        auto mainLayer = self->getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto blockIdLabel = mainLayer->getChildByID("block-id-label");

        // Create block id button
        auto blockIdLabelSprite = CCLabelBMFont::create("Block ID", "goldFont.fnt");
        blockIdLabelSprite->setScale(blockIdLabel->getScale());
        auto blockIdLabelButton = CCMenuItemSpriteExtra::create(blockIdLabelSprite, self, menu_selector(CollisionBlockPopupShift::onBlockIdPress));
        blockIdLabelButton->setID("block-id-label"_spr);
        blockIdLabelButton->setPosition(blockIdLabel->getPositionX() - buttonMenu->getPositionX(), blockIdLabel->getPositionY() - buttonMenu->getPositionY());
        blockIdLabelButton->setContentSize({blockIdLabel->getContentWidth() * blockIdLabel->getScaleX(), blockIdLabel->getContentHeight() * blockIdLabel->getScaleY()});
        blockIdLabelButton->setAnchorPoint(blockIdLabel->getAnchorPoint());

        // Add button
		buttonMenu->addChild(blockIdLabelButton);
		mainLayer->removeChildByID("block-id-label");

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) {
			objects.push_back(obj);
		}
		else {
			for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(objs)) {
				objects.push_back(obj);
			}
		}

		// Set button data
		blockIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
        blockIdLabelButton->setUserData(self);

        return true;
    }

    void onBlockIdPress(CCObject* sender) {
        auto self = static_cast<CollisionBlockPopup*>(static_cast<CCNode*>(sender)->getUserData());
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		
		PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		)->show();

        // Call CollisionBlockPopup::onClose
        static tulip::hook::WrapperMetadata metadata;
        metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Fastcall);
        metadata.m_abstract = tulip::hook::AbstractFunction::from(&onClose_hook);
        auto original = geode::hook::createWrapper(reinterpret_cast<void*>(geode::base::get() + 0x08ba80), metadata).unwrap();
        reinterpret_cast<void(*)(CCObject*)>(original)(self); // onClose
    }
};

bool CollisionBlockPopup_init(CollisionBlockPopup* self, EffectGameObject* obj, cocos2d::CCArray* objs) {
    tulip::hook::WrapperMetadata metadata;
    metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Thiscall);
    metadata.m_abstract = tulip::hook::AbstractFunction::from(&CollisionBlockPopup_init);
    auto original = geode::hook::createWrapper(reinterpret_cast<bool*>(geode::base::get() + 0x08a9f0), metadata).unwrap();

    bool success = reinterpret_cast<bool(*)(CollisionBlockPopup*, EffectGameObject*, cocos2d::CCArray*)>(original)(self, obj, objs);
    if (!success) return false;
    
    return CollisionBlockPopupShift::init(self, obj, objs);
}

// Manual hooks are not fun :/
$execute {
    auto result = Mod::get()->hook(
        reinterpret_cast<void*>(geode::base::get() + 0x08a9f0), // address
        &CollisionBlockPopup_init, // detour
        "CollisionBlockPopup::init", // display name, shows up on the console
        tulip::hook::TulipConvention::Thiscall // calling convention
    );
}