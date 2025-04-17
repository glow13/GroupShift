#include <Geode/modify/CollisionBlockPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(CollisionBlockPopupShift, CollisionBlockPopup) {
    
    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        if (!CollisionBlockPopup::init(obj, objs)) return false;
        
        // Add node ids
        setID("CollisionBlockPopup");
        getChildByType<CCLayer>(0)->setID("main-layer");
        getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
        getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("block-id-label");

        // Save references
        auto mainLayer = getChildByID("main-layer");
        auto buttonMenu = mainLayer->getChildByID("button-menu");
        auto blockIdLabel = mainLayer->getChildByID("block-id-label");

        // Create block id button
        auto blockIdLabelSprite = CCLabelBMFont::create("Block ID", "goldFont.fnt");
        blockIdLabelSprite->setScale(blockIdLabel->getScale());
        auto blockIdLabelButton = CCMenuItemSpriteExtra::create(blockIdLabelSprite, this, menu_selector(CollisionBlockPopupShift::onBlockIdPress));
        blockIdLabelButton->setID("block-id-label"_spr);
        blockIdLabelButton->setPosition(blockIdLabel->getPositionX() - buttonMenu->getPositionX(), blockIdLabel->getPositionY() - buttonMenu->getPositionY());
        blockIdLabelButton->setContentSize({blockIdLabel->getContentWidth() * blockIdLabel->getScaleX(), blockIdLabel->getContentHeight() * blockIdLabel->getScaleY()});
        blockIdLabelButton->setAnchorPoint(blockIdLabel->getAnchorPoint());

        // Add button
		buttonMenu->addChild(blockIdLabelButton);
		mainLayer->removeChildByID("block-id-label");

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj);

		// Set button data
		blockIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

        return true;
    } // init

    void onBlockIdPress(CCObject* sender) {
        auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_itemID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_itemID = vals[0]; }
		);
        popup->setUserObject(this);
        popup->show();
    } // onBlockIdPress
    
}; // CollisionBlockPopupShift