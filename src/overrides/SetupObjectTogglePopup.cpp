#include <Geode/modify/SetupObjectTogglePopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupObjectTogglePopupShift, SetupObjectTogglePopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs, bool idk) {

		// Initialize popup
		if (!SetupObjectTogglePopup::init(obj, objs, idk)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

		// Create the label button
		auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupObjectTogglePopupShift::onGroupIdPress));

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!m_gameObjects || m_gameObjects->count() == 0) objects.push_back(m_gameObject);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(m_gameObjects)) objects.push_back(obj);

		// Set button data
		groupIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onGroupIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onGroupIdPress

}; // SetupObjectTogglePopupShift