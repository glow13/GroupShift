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
		auto addGroupIdLabelButton = ShiftPopup::createLabelButton((CCLabelBMFont*) addGroupIdLabel, false, this, menu_selector(SetGroupIDLayerShift::onAddGroupIdPress));
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
		addGroupIdLabelButton->removeFromParent();
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

		// Update menu layouts
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
			"You are about to make each selected object the parent of all of their groups! You "
			"currently have " + std::to_string(objects->data.size()) + " objects selected, make sure that "
			"they all have unique groups and that this action won't overwrite any existing group parents!",
			"Nvmd", "Yep",
			[objects, this](auto, bool btn2) {
				if (btn2) {
					LevelEditorLayer* lel = LevelEditorLayer::get();
					auto parents = CCDictionaryExt<int, GameObject*>(lel->m_parentGroupsDict);

					// Make sure that we won't overwrite an existing parent
					for (GameObject* obj : objects->data) if (obj->m_groups != NULL) {
						for (int g = 0; g < obj->m_groupCount; g++) {
							short group = obj->m_groups->at(g);
							if (parents.contains(group) && parents[group]->m_uniqueID != obj->m_uniqueID) {
								std::string notif = "Failed to overwrite an existing parent of group " + std::to_string(group) + "!";
								Notification::create(notif, NotificationIcon::Error, 2)->show();
								log::error("{}", notif);
								onClose(this);
								return;
							} // if
						} // for
					} // for

					// Set the group parents
					for (GameObject* obj : objects->data) if (obj->m_groups != NULL) {
						for (int g = 0; g < obj->m_groupCount; g++) {
							short group = obj->m_groups->at(g);
							lel->setGroupParent(obj, group);
						} // for
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