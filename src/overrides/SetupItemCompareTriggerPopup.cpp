#include <Geode/modify/SetupItemCompareTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupItemCompareTriggerPopupShift, SetupItemCompareTriggerPopup) {

	bool init(ItemTriggerGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupItemCompareTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto itemId1Label = mainLayer->getChildByType<CCLabelBMFont>(4);
		auto itemId2Label = mainLayer->getChildByType<CCLabelBMFont>(10);
		auto mod1Label = mainLayer->getChildByType<CCLabelBMFont>(16);
		auto mod2Label = mainLayer->getChildByType<CCLabelBMFont>(17);
		auto trueIdLabel = mainLayer->getChildByType<CCLabelBMFont>(18);
		auto falseIdLabel = mainLayer->getChildByType<CCLabelBMFont>(19);

		// Create the label buttons
        auto itemId1LabelButton = ShiftPopup::createLabelButton(itemId1Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId1Press));
        auto itemId2LabelButton = ShiftPopup::createLabelButton(itemId2Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onItemId2Press));
        auto mod1LabelButton = ShiftPopup::createLabelButton(mod1Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod1Press));
        auto mod2LabelButton = ShiftPopup::createLabelButton(mod2Label, this, menu_selector(SetupItemCompareTriggerPopupShift::onMod2Press));
        auto trueIdLabelButton = ShiftPopup::createLabelButton(trueIdLabel, this, menu_selector(SetupItemCompareTriggerPopupShift::onTrueIdPress));
        auto falseIdLabelButton = ShiftPopup::createLabelButton(falseIdLabel, this, menu_selector(SetupItemCompareTriggerPopupShift::onFalseIdPress));

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

		// Set button data
		itemId1LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		itemId2LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		mod1LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		mod2LabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		trueIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		falseIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

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

	void onMod1Press(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data,
			this,
			$get(static_cast<ItemTriggerGameObject*>(obj)->m_mod1),
			$set(static_cast<ItemTriggerGameObject*>(obj)->m_mod1),
			-9999, 9999
		)->show();
	} // onMod1Press

	void onMod2Press(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data, this,
			$get(static_cast<ItemTriggerGameObject*>(obj)->m_mod2),
			$set(static_cast<ItemTriggerGameObject*>(obj)->m_mod2),
			-9999, 9999
		)->show();
	} // onMod2Press

	void onTrueIdPress(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onTrueIdPress

	void onFalseIdPress(CCObject* sender) {
        auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_centerGroupID), $set(obj->m_centerGroupID))->show();
	} // onFalseIdPress

}; // SetupItemCompareTriggerPopupShift