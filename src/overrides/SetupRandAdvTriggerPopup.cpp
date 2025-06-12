#include <Geode/modify/SetupRandAdvTriggerPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupRandAdvTriggerPopupShift, SetupRandAdvTriggerPopup) {

	bool init(RandTriggerGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupRandAdvTriggerPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(0);
		auto chanceLabel = mainLayer->getChildByType<CCLabelBMFont>(1);

		// Create the label buttons
		auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupRandAdvTriggerPopupShift::onGroupIdPress));
		auto chanceLabelButton = ShiftPopup::createLabelButton(chanceLabel, this, menu_selector(SetupRandAdvTriggerPopupShift::onChancePress));

		// Get objects
		std::vector<EffectGameObject*> objects;
		if (!m_gameObjects || m_gameObjects->count() == 0) objects.push_back(m_gameObject);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(m_gameObjects)) objects.push_back(obj);

		// Set button data
		groupIdLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		chanceLabelButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onGroupIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data, this,
			[](EffectGameObject* obj) {
				std::vector<float> ids;
				for (ChanceObject remap : static_cast<ChanceTriggerGameObject*>(obj)->m_chanceObjects)
					ids.push_back(remap.m_groupID); 
				return ids;
			},
			[](EffectGameObject* obj, std::vector<float> vals) {
				auto spawnObject = static_cast<ChanceTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_chanceObjects.size(); i++)
					spawnObject->m_chanceObjects[i].m_groupID = vals[i];
			}
		)->show();
	} // onGroupIdPress

	void onChancePress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data, this,
			[](EffectGameObject* obj) {
				std::vector<float> ids;
				for (ChanceObject remap : static_cast<ChanceTriggerGameObject*>(obj)->m_chanceObjects)
					ids.push_back(remap.m_chance); 
				return ids;
			},
			[](EffectGameObject* obj, std::vector<float> vals) {
				auto spawnObject = static_cast<ChanceTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_chanceObjects.size(); i++)
					spawnObject->m_chanceObjects[i].m_chance = vals[i];
			}
		)->show();
	} // onChancePress

}; // SetupRandAdvTriggerPopupShift