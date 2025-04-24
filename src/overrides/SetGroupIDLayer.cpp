#include <Geode/modify/SetGroupIDLayer.hpp>
#include "GroupShiftPopup.hpp"

class $modify(SetGroupIDLayerShift, SetGroupIDLayer) {

	bool init(GameObject* obj, cocos2d::CCArray* objs) {

		// Initialize popup
		if (!SetGroupIDLayer::init(obj, objs)) return false;

		// Save references
		auto mainLayer = getChildByID("main-layer");
		auto actionMenu = mainLayer->getChildByID("actions-menu");
		auto addGroupIdMenu = mainLayer->getChildByID("add-group-id-menu");
		auto addGroupIdLabel = addGroupIdMenu->getChildByID("add-group-id-label");
		auto addGroupIdButtonsMenu = mainLayer->getChildByID("add-group-id-buttons-menu");

		// Create add group id button
		auto addGroupIdLabelButton = ShiftPopup::createLabelButton((CCLabelBMFont*) addGroupIdLabel, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
		addGroupIdLabelButton->setPosition(addGroupIdLabel->getPositionX(), addGroupIdLabel->getPositionY());

		// Create group shift button
		auto groupShiftButtonSprite = ButtonSprite::create("Shift", 36, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.28);
		auto groupShiftButton = CCMenuItemSpriteExtra::create(groupShiftButtonSprite, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
		groupShiftButton->setID("shift-button"_spr);

		// Create all parent button
		auto allParentButtonSprite = ButtonSprite::create("A", 30, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.7);
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
		addGroupIdLabel->removeFromParentAndCleanup(true);
		addGroupIdButtonsMenu->updateLayout();
		actionMenu->updateLayout();

		// Get objects
		std::vector<GameObject*> objects;
		if (!m_targetObjects || m_targetObjects->count() == 0) objects.push_back(m_targetObject);
		else for (GameObject* obj : CCArrayExt<GameObject*>(m_targetObjects)) objects.push_back(obj);

		// Set button data
		addGroupIdLabelButton->setUserObject("collection"_spr, new GroupShiftPopup::ObjectCollection(objects));
		groupShiftButton->setUserObject("collection"_spr, new GroupShiftPopup::ObjectCollection(objects));
		allParentButton->setUserObject("collection"_spr, new GroupShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onAddGroupIdPress(CCObject* sender) {
		auto objects = $objects(sender, GroupShiftPopup);
		GroupShiftPopup::create(objects->data, this)->show();
	} // onAddGroupIdPress

	void onAllParentPress(CCObject* sender) {
		auto objects = $objects(sender, GroupShiftPopup);
		FLAlertLayer* warning = geode::createQuickPopup(
			"WARNING",
			"You are attempting to make each selected object the parent of every group they are in! "
			"This will also overwrite any other current group parents if they exist. You currently "
			"have " + std::to_string(objects->data.size()) + " objects selected, make sure that they "
			"all have unique groups and that this action won't overwrite anything you don't want it to!",
			"Nvmd", "Yep",
			[objects, this](auto, bool btn2) {
				if (btn2) {
					LevelEditorLayer* lel = LevelEditorLayer::get();
					for (GameObject* obj : objects->data) if (obj->m_groups != NULL) {
						for (short group : *(obj->m_groups)) lel->setGroupParent(obj, group);
					} // for

					// Success and close popup
					std::string notif = "Set " + std::to_string(objects->data.size()) + " selected objects as the parent of their groups!";
					Notification::create(notif, NotificationIcon::Success, 2)->show();
    				log::info("{}", notif);
					onClose(this);
				} // if
			}
		);
	} // onAllParentPress

}; // SetGroupIDLayerShift