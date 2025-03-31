#include <Geode/modify/SetItemIDLayer.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetItemIDLayerShift, SetItemIDLayer) {
    
    static bool init(SetItemIDLayer* self, EffectGameObject* obj, cocos2d::CCArray* objs) {
        log::info("Hooking SetItemIDLayer::init!");

        // Add node ids
        self->setID("SetItemIDLayer");
        self->getChildByType<CCLayer>(0)->setID("main-layer");
        self->getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
        self->getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("item-id-label");

        // Save references
        auto mainLayer = self->getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto itemIdLabel = mainLayer->getChildByID("item-id-label");

        // Create block id button
        auto itemIdLabelSprite = CCLabelBMFont::create("ItemID", "goldFont.fnt");
        itemIdLabelSprite->setScale(itemIdLabel->getScale());
        auto itemIdLabelButton = CCMenuItemSpriteExtra::create(itemIdLabelSprite, self, menu_selector(SetItemIDLayerShift::onItemIdPress));
        itemIdLabelButton->setID("item-id-label"_spr);
        itemIdLabelButton->setPosition(itemIdLabel->getPositionX() - buttonMenu->getPositionX(), itemIdLabel->getPositionY() - buttonMenu->getPositionY());
        itemIdLabelButton->setContentSize({itemIdLabel->getContentWidth() * itemIdLabel->getScaleX(), itemIdLabel->getContentHeight() * itemIdLabel->getScaleY()});
        itemIdLabelButton->setAnchorPoint(itemIdLabel->getAnchorPoint());

        // Add button
		buttonMenu->addChild(itemIdLabelButton);
		mainLayer->removeChildByID("item-id-label");

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
		itemIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

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
};
 
bool SetItemIDLayer_init(SetItemIDLayer* self, EffectGameObject* obj, cocos2d::CCArray* objs) {
    tulip::hook::WrapperMetadata metadata;
    metadata.m_convention = geode::hook::createConvention(tulip::hook::TulipConvention::Thiscall);
    metadata.m_abstract = tulip::hook::AbstractFunction::from(&SetItemIDLayer_init);
    auto original = geode::hook::createWrapper(reinterpret_cast<bool*>(geode::base::get() + 0x3e94e0), metadata).unwrap();

    bool success = reinterpret_cast<bool(*)(SetItemIDLayer*, EffectGameObject*, cocos2d::CCArray*)>(original)(self, obj, objs);
    if (!success) return false;
    
    return SetItemIDLayerShift::init(self, obj, objs);
}

// Manual hooks are not fun :/
$execute {
    auto result = Mod::get()->hook(
        reinterpret_cast<void*>(geode::base::get() + 0x3e94e0), // address
        &SetItemIDLayer_init, // detour
        "SetItemIDLayer::init", // display name, shows up on the console
        tulip::hook::TulipConvention::Thiscall // calling convention
    );
}