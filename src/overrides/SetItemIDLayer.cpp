#include <Geode/modify/SetItemIDLayer.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetItemIDLayerShift, SetItemIDLayer) {
    
    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
        if (!SetItemIDLayer::init(obj, objs)) return false;

        // Save references
        auto mainLayer = getChildByType<CCLayer>(0);
        auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
        auto itemIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

        // Create the label button
        auto itemIdLabelButton = ShiftPopup::createLabelButton(itemIdLabel, this, menu_selector(SetItemIDLayerShift::onItemIdPress));

        // Add button
		buttonMenu->addChild(itemIdLabelButton);

        // Remove old label
		itemIdLabel->removeFromParentAndCleanup(true);

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