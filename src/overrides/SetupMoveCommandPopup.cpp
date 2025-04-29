#include <Geode/modify/SetupMoveCommandPopup.hpp>
#include "PropertyShiftPopup.hpp"

class $modify(SetupMoveCommandPopupShift, SetupMoveCommandPopup) {

	struct Fields {
		CCLabelBMFont* m_moveXLabel;
		CCLabelBMFont* m_moveYLabel;
		CCMenuItemSpriteExtra* m_moveXButton;
		CCMenuItemSpriteExtra* m_moveYButton;
    };

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetupMoveCommandPopup::init(obj, objs)) return false;

        // Save references
		auto mainLayer = getChildByType<CCLayer>(0);
		auto buttonMenu = mainLayer->getChildByType<CCMenu>(0);
		auto moveXLabel = mainLayer->getChildByType<CCLabelBMFont>(4);
		auto moveYLabel = mainLayer->getChildByType<CCLabelBMFont>(5);
		auto moveTimeLabel = mainLayer->getChildByType<CCLabelBMFont>(25);
		auto targetIdLabel = mainLayer->getChildByType<CCLabelBMFont>(28);

        // Create the label buttons
		auto moveXButton = ShiftPopup::createLabelButton(moveXLabel, this, menu_selector(SetupMoveCommandPopupShift::onMoveXPress));
		auto moveYButton = ShiftPopup::createLabelButton(moveYLabel, this, menu_selector(SetupMoveCommandPopupShift::onMoveYPress));
		auto moveTimeButton = ShiftPopup::createLabelButton(moveTimeLabel, this, menu_selector(SetupMoveCommandPopupShift::onMoveTimePress));
        auto targetIdButton = ShiftPopup::createLabelButton(targetIdLabel, this, menu_selector(SetupMoveCommandPopupShift::onTargetIdPress));

        // Add buttons
		buttonMenu->addChild(moveXButton);
		buttonMenu->addChild(moveYButton);
		buttonMenu->addChild(moveTimeButton);
		buttonMenu->addChild(targetIdButton);

		// Set fields
		m_fields->m_moveXLabel = moveXLabel;
		m_fields->m_moveYLabel = moveYLabel;
		m_fields->m_moveXButton = moveXButton;
		m_fields->m_moveYButton = moveYButton;

        // Get objects
		std::vector<EffectGameObject*> objects;
		if (!objs || objs->count() == 0) objects.push_back(obj);
		else for (EffectGameObject* obj2 : CCArrayExt<EffectGameObject*>(objs)) objects.push_back(obj2);

        // Set button data
		moveXButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		moveYButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		moveTimeButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));
		targetIdButton->setUserObject("collection"_spr, new PropertyShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void updateControlVisibility() {
		SetupMoveCommandPopup::updateControlVisibility();
		if (m_fields->m_moveXLabel) m_fields->m_moveXButton->setVisible(m_fields->m_moveXLabel->isVisible());
		if (m_fields->m_moveYLabel) m_fields->m_moveYButton->setVisible(m_fields->m_moveYLabel->isVisible());
	} // updateControlVisibility

	void onMoveXPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		int val = m_smallStep ? 1 : 3;
		PropertyShiftPopup::create(
			objects->data, this,
			[val](EffectGameObject* obj) -> std::vector<float> { return { obj->m_moveOffset.x / val }; },
			[val](EffectGameObject* obj, std::vector<float> vals) { obj->m_moveOffset.x = vals[0] * val; },
			-10000, 10000
		)->show();
	} // onMoveXPress

	void onMoveYPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(
			objects->data, this,
			[](EffectGameObject* obj) -> std::vector<float> { return { obj->m_moveOffset.y / 3 }; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_moveOffset.y = vals[0] * 3; },
			-10000, 10000
		)->show();
	} // onMoveYPress

	void onMoveTimePress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_duration), $set(obj->m_duration), 0, 10000)->show();
	} // onMoveTimePress

	void onTargetIdPress(CCObject* sender) {
		auto objects = $objects(sender, PropertyShiftPopup);
		PropertyShiftPopup::create(objects->data, this, $get(obj->m_targetGroupID), $set(obj->m_targetGroupID))->show();
	} // onTargetIdPress

}; // SetupMoveCommandPopupShift