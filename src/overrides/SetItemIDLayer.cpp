#include <Geode/modify/SetItemIDLayer.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetItemIDLayerShift, SetItemIDLayer) {
    
    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        if (!SetItemIDLayer::init(obj, objs)) return false;
        
        // Add node ids
        setID("SetItemIDLayer");
        getChildByType<CCLayer>(0)->setID("main-layer");
        getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
        getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("item-id-label");

        // Save references
        auto mainLayer = getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto itemIdLabel = mainLayer->getChildByID("item-id-label");

        // Create block id button
        auto itemIdLabelSprite = CCLabelBMFont::create("ItemID", "goldFont.fnt");
        itemIdLabelSprite->setScale(itemIdLabel->getScale());
        auto itemIdLabelButton = CCMenuItemSpriteExtra::create(itemIdLabelSprite, this, menu_selector(SetItemIDLayerShift::onItemIdPress));
        itemIdLabelButton->setID("item-id-label"_spr);
        itemIdLabelButton->setPosition(itemIdLabel->getPositionX() - buttonMenu->getPositionX(), itemIdLabel->getPositionY() - buttonMenu->getPositionY());
        itemIdLabelButton->setContentSize({itemIdLabel->getContentWidth() * itemIdLabel->getScaleX(), itemIdLabel->getContentHeight() * itemIdLabel->getScaleY()});
        itemIdLabelButton->setAnchorPoint(itemIdLabel->getAnchorPoint());

        // Add button
		buttonMenu->addChild(itemIdLabelButton);
		mainLayer->removeChildByID("item-id-label");

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj);

		// Set button data
		itemIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

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
    
}; // SetItemIDLayerShift