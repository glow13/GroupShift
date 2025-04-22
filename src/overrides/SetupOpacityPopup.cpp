#include <Geode/modify/SetupOpacityPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupOpacityPopupShift, SetupOpacityPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupOpacityPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto groupIdLabel = mainLayer->getChildByType<CCLabelBMFont>(1);
		auto fadeTimeLabel = mainLayer->getChildByType<CCLabelBMFont>(2);

        // Create the label buttons
        auto groupIdLabelButton = ShiftPopup::createLabelButton(groupIdLabel, this, menu_selector(SetupOpacityPopupShift::onGroupIdPress));
        auto fadeTimeLabelButton = ShiftPopup::createLabelButton(fadeTimeLabel, this, menu_selector(SetupOpacityPopupShift::onFadeTimePress));

        // Add buttons
		buttonMenu->addChild(groupIdLabelButton);
		buttonMenu->addChild(fadeTimeLabelButton);

        // Remove old labels
		groupIdLabel->removeFromParentAndCleanup(true);
		fadeTimeLabel->removeFromParentAndCleanup(true);

        // Get objects
		vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		groupIdLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));
		fadeTimeLabelButton->setUserObject(new PropertyShiftPopup::ObjectCollection(objects));

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

    void onFadeTimePress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
        auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { vector<float> time = { static_cast<float>(obj->m_duration) }; return time; },
			[](EffectGameObject* obj, vector<float> vals) { obj->m_duration = vals[0]; },
			0, 10000
		);
        popup->setUserObject(this);
        popup->show();
	} // onFadeTimePress

}; // SetupOpacityPopupShift