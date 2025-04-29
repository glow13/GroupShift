#include <Geode/modify/SetupOpacityPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupOpacityPopupShift, SetupOpacityPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupOpacityPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto fadeTimeLabel = mainLayer->getChildByType<CCLabelBMFont>(2);

        // Create the label buttons
        auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupOpacityPopupShift::onGroupIdPress));
        auto fadeTimeLabelButton = ShiftPopup::createLabelButton(fadeTimeLabel, this, menu_selector(SetupOpacityPopupShift::onFadeTimePress));

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		groupIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		fadeTimeLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onGroupIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onGroupIdPress

    void onFadeTimePress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
        PropertyShiftPopup::create(objects->data, this, $get(obj->m_duration), $set(obj->m_duration), 0, 10000)->show();
	} // onFadeTimePress

}; // SetupOpacityPopupShift