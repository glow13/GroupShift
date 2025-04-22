#include <Geode/modify/SetupObjectTogglePopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupObjectTogglePopupShift, SetupObjectTogglePopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs, bool idk) {

		// Initialize popup
		if (!SetupObjectTogglePopup::init(obj, objs, idk)) return false;

		// Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		
		// Create the label button
		auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupObjectTogglePopupShift::onGroupIdPress));

		// Add button
		buttonMenu->addChild(groupIdLabelButton);

		// Remove old label
		groupIdLabel->removeFromParentAndCleanup(true);

		// Get objects
		vector<EffectGameObject*> objects;
		if (!m_gameObjects || m_gameObjects->count() == 0) objects.push_back(m_gameObject);
		else for (EffectGameObject* obj : CCArrayExt<EffectGameObject*>(m_gameObjects)) objects.push_back(obj);

		// Set button data
		groupIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		
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

}; // SetupObjectTogglePopupShift