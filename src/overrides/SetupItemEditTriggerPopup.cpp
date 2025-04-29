#include <Geode/modify/SetupItemEditTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupItemEditTriggerPopupShift, SetupItemEditTriggerPopup) {

	bool init(ItemTriggerGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupItemEditTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto itemId1Label = mainLayer->getChildByType<CCLabelBMFont>(4);
		auto itemId2Label = mainLayer->getChildByType<CCLabelBMFont>(10);
		auto modLabel = mainLayer->getChildByType<CCLabelBMFont>(16);
		auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(17);

		// Create the label buttons
        auto itemId1LabelButton = ShiftPopup::createLabelButton(itemId1Label, this, menu_selector(SetupItemEditTriggerPopupShift::onItemId1Press));
        auto itemId2LabelButton = ShiftPopup::createLabelButton(itemId2Label, this, menu_selector(SetupItemEditTriggerPopupShift::onItemId2Press));
        auto modLabelButton = ShiftPopup::createLabelButton(modLabel, this, menu_selector(SetupItemEditTriggerPopupShift::onModPress));
        auto targetIdLabelButton = ShiftPopup::createLabelButton(targetIdLabel, this, menu_selector(SetupItemEditTriggerPopupShift::onTargetIdPress));

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		itemId1LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		itemId2LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		modLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		targetIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onItemId1Press(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID), $set(obj->m_itemID))->show();
	} // onItemId1Press

	void onItemId2Press(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_itemID2), $set(obj->m_itemID2))->show();
	} // onItemId2Press

	void onModPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data, this,
			$get(static_cast<ItemTriggerGameObject*>(obj)->m_mod1),
			$set(static_cast<ItemTriggerGameObject*>(obj)->m_mod1),
			-9999, 9999
		)->show();
	} // onModPress

	void onTargetIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onTargetIdPress

}; // SetupItemEditTriggerPopupShift