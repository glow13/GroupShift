#include <Geode/modify/CollisionBlockPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(CollisionBlockPopupShift, CollisionBlockPopup) {
    
    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
        if (!CollisionBlockPopup::init(obj, objs)) return false;

        // Save references
        auto mainLayer = getChildByType<CCLayer>(0);
        auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
        auto blockIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

        // Create the label button
        auto blockIdLabelButton = ShiftPopup::createLabelButton(blockIdLabel, this, menu_selector(CollisionBlockPopupShift::onBlockIdPress));

        // Add button
		buttonMenu->addChild(blockIdLabelButton);

        // Remove old label
		blockIdLabel->removeFromParentAndCleanup(true);

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