#include <Geode/modify/SetGroupIDLayer.hpp>
#include "GroupShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetGroupIDLayerShift, SetGroupIDLayer) {

	bool init(GameObject* obj, cocos2d::CCArray* objs) {

		if (!SetGroupIDLayer::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByID("main-layer");
		auto actionMenu = mainLayer->getChildByID("actions-menu");
		auto addGroupIdMenu = mainLayer->getChildByID("add-group-id-menu");
		auto addGroupIdLabel = addGroupIdMenu->getChildByID("add-group-id-label");
		auto addGroupIdButtonsMenu = mainLayer->getChildByID("add-group-id-buttons-menu");
		
		// Create add group id button
		auto addGroupIdLabelSprite = CCLabelBMFont::create("Add Group ID", "goldFont.fnt");
		addGroupIdLabelSprite->setScale(addGroupIdLabel->getScale());
		auto addGroupIdLabelButton = CCMenuItemSpriteExtra::create(addGroupIdLabelSprite, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
		addGroupIdLabelButton->setID("add-group-id-label"_spr);
		addGroupIdLabelButton->setPosition(addGroupIdLabel->getPositionX(), addGroupIdLabel->getPositionY());
		addGroupIdLabelButton->setContentSize({addGroupIdLabel->getContentWidth() * addGroupIdLabel->getScaleX(), addGroupIdLabel->getContentHeight() * addGroupIdLabel->getScaleY()});
		addGroupIdLabelButton->setAnchorPoint(addGroupIdLabel->getAnchorPoint());

		// Create group shift button
		auto groupShiftButtonSprite = ButtonSprite::create("Shift", 36, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.28);
		auto groupShiftButton = CCMenuItemSpriteExtra::create(groupShiftButtonSprite, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
		groupShiftButton->setID("shift-button"_spr);

		// Create all parent button
		auto allParentButtonSprite = ButtonSprite::create("A", 30.7, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.7);
		auto allParentButton = CCMenuItemSpriteExtra::create(allParentButtonSprite, this, menu_selector(SetGroupIDLayerShift::onAllParentPress));
		allParentButton->setID("all-parent-button"_spr);

		// Add buttons
		addGroupIdMenu->addChild(addGroupIdLabelButton);
		actionMenu->addChild(groupShiftButton);
		if (objs->count() > 0) addGroupIdButtonsMenu->addChild(allParentButton);

		// Re-order action menu
		if (auto preview = actionMenu->getChildByID("preview-menu")) {
			actionMenu->removeChildByID("preview-menu");
			actionMenu->addChild(preview);
		} // if
		if (auto playback = actionMenu->getChildByID("playback-menu")) {
			actionMenu->removeChildByID("playback-menu");
			actionMenu->addChild(playback);
		} // if
		
		// Remove old label and update layouts
		addGroupIdMenu->removeChildByID("add-group-id-label");
		addGroupIdButtonsMenu->updateLayout();
		actionMenu->updateLayout();
		
		// Get objects
		std::vector<GameObject*> objects;
		if (!m_targetObjects || m_targetObjects->count() == 0) objects.push_back(m_targetObject);
		else for (GameObject* obj : CCArrayExt<GameObject*>(m_targetObjects)) objects.push_back(obj);

		// Set button data
		addGroupIdLabelButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));
		groupShiftButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));
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
		auto num = std::to_string(objects->data.size());
		FLAlertLayer* warning = geode::createQuickPopup(
			"WARNING",
			"You are attempting to make each selected object the parent of every group they are in! This will also overwrite any other current group parents if they exist. You currently have " + num + " objects selected, make sure that they all have unique groups and that this action won't overwrite anything you don't want it to!",
			"Nvmd", "Yep",
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