#include <Geode/modify/SetGroupIDLayer.hpp>
#include "GroupShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetGroupIDLayerShift, SetGroupIDLayer) {

	bool init(GameObject* obj, cocos2d::CCArray* objs) {

		if (!SetGroupIDLayer::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByID("main-layer");
		auto addGroupIdMenu = mainLayer->getChildByID("add-group-id-menu");
		auto addGroupIdLabel = addGroupIdMenu->getChildByID("add-group-id-label");
		auto addGroupIdButtonsMenu = mainLayer->getChildByID("add-group-id-buttons-menu");
		auto addGroupIdButton = addGroupIdButtonsMenu->getChildByID("add-group-id-button");
		auto addGroupIdButtonSprite = addGroupIdButton->getChildByType<ButtonSprite>(0);

		// Create add group id button
		auto addGroupIdLabelSprite = CCLabelBMFont::create("Add Group ID", "goldFont.fnt");
		addGroupIdLabelSprite->setScale(addGroupIdLabel->getScale());
		auto addGroupIdLabelButton = CCMenuItemSpriteExtra::create(addGroupIdLabelSprite, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
		addGroupIdLabelButton->setID("add-group-id-label"_spr);
		addGroupIdLabelButton->setPosition(addGroupIdLabel->getPositionX(), addGroupIdLabel->getPositionY());
		addGroupIdLabelButton->setContentSize({addGroupIdLabel->getContentWidth() * addGroupIdLabel->getScaleX(), addGroupIdLabel->getContentHeight() * addGroupIdLabel->getScaleY()});
		addGroupIdLabelButton->setAnchorPoint(addGroupIdLabel->getAnchorPoint());

		// Create all parent button
		auto allParentButtonSprite = ButtonSprite::create("A", 30.7, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.7);
		auto allParentButton = CCMenuItemSpriteExtra::create(allParentButtonSprite, this, menu_selector(SetGroupIDLayerShift::onAllParentPress));
		allParentButton->setID("all-parent-button"_spr);

		// Add buttons
		addGroupIdMenu->addChild(addGroupIdLabelButton);
		if (objs->count() > 0) addGroupIdButtonsMenu->addChild(allParentButton);
		
		// Remove old label and update layout
		addGroupIdMenu->removeChildByID("add-group-id-label");
		addGroupIdButtonsMenu->updateLayout();
		
		// Get objects
		std::vector<GameObject*> objects;
		if (!m_targetObjects || m_targetObjects->count() == 0) objects.push_back(m_targetObject);
		else for (GameObject* obj : CCArrayExt<GameObject*>(m_targetObjects)) objects.push_back(obj);

		// Set button data
		addGroupIdLabelButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));
		allParentButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));
		
		return true;
	} // init

	void onAddGroupIdPress(CCObject* sender) {
		auto objects = static_cast<GroupShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto shiftPopup = GroupShiftPopup::create(objects->data);
		shiftPopup->setUserObject(this);
		shiftPopup->show();
	} // onAddGroupIdPress

	void onAllParentPress(CCObject* sender) {
		auto objects = static_cast<GroupShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		FLAlertLayer* warning = geode::createQuickPopup(
			"WARNING",
			"You are about to set " + std::to_string(objects->data.size()) + " selected objects as a group parent!",
			"No", "OK",
			[objects, this](auto, bool btn2) {
				if (btn2) {
					LevelEditorLayer* lel = LevelEditorLayer::get();
					int groupCount = 0;
					for (GameObject* obj : objects->data) if (obj->m_groups != NULL) {
						for (short group : *(obj->m_groups)) lel->setGroupParent(obj, group);
						groupCount += obj->m_groupCount;
					} // for
					log::info("Setting {} selected objects the parent of {} groups", objects->data.size(), groupCount);
					onClose(this);
				} // if
			}
		);
	} // onAllParentPress
	
}; // SetGroupIDLayerShift