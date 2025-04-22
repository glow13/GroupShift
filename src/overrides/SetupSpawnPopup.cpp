#include <Geode/modify/SetupSpawnPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupSpawnPopupShift, SetupSpawnPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupSpawnPopup::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto originalIdLabel = mainLayer->getChildByType<CCLabelBMFont>(7);
		auto newIdLabel = mainLayer->getChildByType<CCLabelBMFont>(8);

		// Create the label buttons
		auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupSpawnPopupShift::onGroupIdPress));
		auto originalIdLabelButton = ShiftPopup::createLabelButton(originalIdLabel, this, menu_selector(SetupSpawnPopupShift::onOriginalIdPress));
		auto newIdLabelButton = ShiftPopup::createLabelButton(newIdLabel, this, menu_selector(SetupSpawnPopupShift::onNewIdPress));
		
		// Add buttons
		buttonMenu->addChild(groupIdLabelButton);
		buttonMenu->addChild(originalIdLabelButton);
		buttonMenu->addChild(newIdLabelButton);

		// Remove old labels
		groupIdLabel->removeFromParentAndCleanup(true);
		originalIdLabel->removeFromParentAndCleanup(true);
		newIdLabel->removeFromParentAndCleanup(true);

		// Configure pages
		addObjectToPage(groupIdLabelButton, 0);
		addObjectToPage(originalIdLabelButton, 1);
		addObjectToPage(newIdLabelButton, 1);

		// Hide the buttons on the other page
		originalIdLabelButton->setVisible(false);
		newIdLabelButton->setVisible(false);

		// Get objects
		vector<EffectGameObject*> objects;
		if (!m_gameObjects || m_gameObjects->count() == 0) objects.push_back(m_gameObject);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(m_gameObjects)) objects.push_back(obj);

		// Set button data
		groupIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		originalIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		newIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onGroupIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
		popup->setUserObject(this);
		popup->show();
	} // onGroupIdPress

	void onOriginalIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> ids; for (ChanceObject remap : static_cast<SpawnTriggerGameObject*>(obj)->m_remapObjects) ids.push_back(remap.m_groupID); return ids; },
			[](EffectGameObject* obj, vector<float> vals) {
				auto spawnObject = static_cast<SpawnTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_remapObjects.size(); i++) {
					spawnObject->m_remapObjects[i].m_groupID = vals[i];
					spawnObject->m_remapObjects[i].m_oldGroupID = vals[i];
				} // for
			}
		);
		popup->setUserObject(this);
		popup->show();
	} // onOriginalIdPress

	void onNewIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> ids; for (ChanceObject remap : static_cast<SpawnTriggerGameObject*>(obj)->m_remapObjects) ids.push_back(remap.m_chance); return ids; },
			[](EffectGameObject* obj, vector<float> vals) {
				auto spawnObject = static_cast<SpawnTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_remapObjects.size(); i++) 
					spawnObject->m_remapObjects[i].m_chance = vals[i];
			}
		);
		popup->setUserObject(this);
		popup->show();
	} // onNewIdPress

}; // SetupSpawnPopupShift