#include <Geode/modify/SetItemIDLayer.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetItemIDLayerShift, SetItemIDLayer) {

    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
        if (!SetItemIDLayer::init(obj, objs)) return false;

        // Save references
        auto mainLayer = getChildByType<CCLayer>(0);
        auto itemIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

        // Create the label button
        auto itemIdLabelButton = ShiftPopup::createLabelButton(itemIdLabel, this, menu_selector(SetItemIDLayerShift::onItemIdPress));

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj);

		// Set button data
		itemIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

        return true;
    } // init

    void onItemIdPress(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID))->show();
    } // onItemIdPress

}; // SetItemIDLayerShift