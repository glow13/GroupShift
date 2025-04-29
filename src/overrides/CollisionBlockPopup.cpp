#include <Geode/modify/CollisionBlockPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(CollisionBlockPopupShift, CollisionBlockPopup) {

    bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

        // Initialize popup
        if (!CollisionBlockPopup::init(obj, objs)) return false;

        // Save references
        auto mainLayer = getChildByType<CCLayer>(0);
        auto blockIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

        // Create the label button
        auto blockIdLabelButton = ShiftPopup::createLabelButton(blockIdLabel, this, menu_selector(CollisionBlockPopupShift::onBlockIdPress));

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj);

		// Set button data
		blockIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

        return true;
    } // init

    void onBlockIdPress(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID))->show();
    } // onBlockIdPress

}; // CollisionBlockPopupShift