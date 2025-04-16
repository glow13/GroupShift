#include <Geode/modify/SetGroupIDLayer.hpp>
#include "GroupShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetGroupIDLayerShift, SetGroupIDLayer) {

	bool init(GameObject* obj, cocos2d::CCArray* objs) {

		if (!SetGroupIDLayer::init(obj, objs)) return false;

		// Create button sprites
		ButtonSprite* shiftButtonSprite = ButtonSprite::create("Shift", 36, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.277777778);
		ButtonSprite* parentButtonSprite = ButtonSprite::create("A", 36, false, "goldFont.fnt", "GJ_button_04.png", 25, 0.7);
		
		// Create group shift button
		auto groupShiftButton = CCMenuItemSpriteExtra::create(shiftButtonSprite, this, menu_selector(SetGroupIDLayerShift::onShiftButton));
		groupShiftButton->setID("shift-button"_spr);
		auto actionMenu = getChildByID("main-layer")->getChildByID("actions-menu");
		actionMenu->addChild(groupShiftButton);
		
		// Create group parent button
		auto groupParentButton = CCMenuItemSpriteExtra::create(parentButtonSprite, this, menu_selector(SetGroupIDLayerShift::onParentButton));
		groupParentButton->setID("parent-button"_spr);
		auto addGroupIDMenu = getChildByID("main-layer")->getChildByID("add-group-id-buttons-menu");
		addGroupIDMenu->addChild(groupParentButton);
		
		// Re-order action menu
		if (auto preview = actionMenu->getChildByID("preview-menu")) {
			actionMenu->removeChildByID("preview-menu");
			actionMenu->addChild(preview);
		}
		if (auto playback = actionMenu->getChildByID("playback-menu")) {
			actionMenu->removeChildByID("playback-menu");
			actionMenu->addChild(playback);
		}
		actionMenu->updateLayout();
		addGroupIDMenu->updateLayout();
		
		// Get objects
		std::vector<GameObject*> objects;
		if (!m_targetObjects || m_targetObjects->count() == 0) objects.push_back(m_targetObject);
		else for (GameObject* obj : CCArrayExt<GameObject*>(m_targetObjects)) objects.push_back(obj);

		// Set button data
		groupShiftButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));
		groupParentButton->setUserObject(new GroupShiftPopup::ObjectCollection(objects));

		return true;
	} // init

	void onShiftButton(CCObject* sender) {
		auto objects = static_cast<GroupShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

		GroupShiftPopup::create(objects->data)->show();
		onClose(this);
	} // onShiftButton

	void onParentButton(CCObject* sender) {
		auto objects = static_cast<GroupShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());

		int groupCount = 0;
		for (GameObject* obj : objects->data) groupCount += obj->m_groupCount;

		FLAlertLayer* warning = geode::createQuickPopup(
			"WARNING",
			"You are about to set " + std::to_string(objects->data.size()) + " selected objects the parent of " + std::to_string(groupCount) + " groups!",
			"No", "OK",
			[=, objs = objects->data](auto, bool btn2) {
				if (btn2) {
					LevelEditorLayer* lel = LevelEditorLayer::get();

					int groupCount = 0;
					for (GameObject* obj : objs) {
						for (short group : *(obj->m_groups)) lel->setGroupParent(obj, group);
						groupCount += obj->m_groupCount;
					}
					log::info("Setting {} selected objects the parent of {} groups", objs.size(), groupCount);
				}
			}
		);

		onClose(this);
	} // onParentButton
	
}; // SetGroupIDLayerShift