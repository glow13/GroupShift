#include <Geode/modify/SetupRandTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupRandTriggerPopupShift, SetupRandTriggerPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupRandTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto groupId1Label = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto groupId2Label = mainLayer->getChildByType<CCLabelBMFont>(2);
		auto chanceLabel = mainLayer->getChildByType<CCLabelBMFont>(3);

		// Create the label buttons
		auto groupId1LabelButton = ShiftPopup::createLabelButton(groupId1Label, this, menu_selector(SetupRandTriggerPopupShift::onGroupId1Press));
		auto groupId2LabelButton = ShiftPopup::createLabelButton(groupId2Label, this, menu_selector(SetupRandTriggerPopupShift::onGroupId2Press));
		auto chanceLabelButton = ShiftPopup::createLabelButton(chanceLabel, this, menu_selector(SetupRandTriggerPopupShift::onChancePress));

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!m_gameObjects || m_gameObjects->count() == 0) objects.push_back(m_gameObject);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(m_gameObjects)) objects.push_back(obj);

		// Set button data
		groupId1LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		groupId2LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		chanceLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onGroupId1Press(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onGroupId1Press

	void onGroupId2Press(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_centerGroupID), $set(obj->m_centerGroupID))->show();
	} // onGroupId2Press

	void onChancePress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_duration), $set(obj->m_duration), 0, 100)->show();
	} // onChancePress

}; // SetupRandTriggerPopupShift