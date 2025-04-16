#include <Geode/modify/SetupSpawnPopup.hpp>
#include "PropertyShiftPopup.hpp"

using namespace geode::prelude;

class $modify(SetupSpawnPopupShift, SetupSpawnPopup) {

	bool init(EffectGameObject* obj, cocos2d::CCArray* objs) {

		if (!SetupSpawnPopup::init(obj, objs)) return false;

		// Add node ids
		setID("SetupSpawnPopup");
		getChildByType<CCLayer>(0)->setID("main-layer");
		getChildByID("main-layer")->getChildByType<CCMenu>(0)->setID("button-menu");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(1)->setID("group-id-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(7)->setID("original-id-label");
		getChildByID("main-layer")->getChildByType<CCLabelBMFont>(8)->setID("new-id-label");

		// Save references
		auto mainLayer = getChildByID("main-layer");
		auto buttonMenu = mainLayer->getChildByID("button-menu");
		auto groupIdLabel = mainLayer->getChildByID("group-id-label");
		auto originalIdLabel = mainLayer->getChildByID("original-id-label");
		auto newIdLabel = mainLayer->getChildByID("new-id-label");

		// Create group id button
		auto groupIdLabelSprite = CCLabelBMFont::create("Group ID", "goldFont.fnt");
		groupIdLabelSprite->setScale(groupIdLabel->getScale());
		auto groupIdLabelButton = CCMenuItemSpriteExtra::create(groupIdLabelSprite, this, menu_selector(SetupSpawnPopupShift::onGroupIdPress));
		groupIdLabelButton->setID("group-id-label"_spr);
		groupIdLabelButton->setPosition(groupIdLabel->getPositionX() - buttonMenu->getPositionX(), groupIdLabel->getPositionY() - buttonMenu->getPositionY());
		groupIdLabelButton->setContentSize({groupIdLabel->getContentWidth() * groupIdLabel->getScaleX(), groupIdLabel->getContentHeight() * groupIdLabel->getScaleY()});
		groupIdLabelButton->setAnchorPoint(groupIdLabel->getAnchorPoint());

		// Create original id button
		auto originalIdLabelSprite = CCLabelBMFont::create("OriginalID:", "goldFont.fnt");
		originalIdLabelSprite->setScale(originalIdLabel->getScale());
		auto originalIdLabelButton = CCMenuItemSpriteExtra::create(originalIdLabelSprite, this, menu_selector(SetupSpawnPopupShift::onOriginalIdPress));
		originalIdLabelButton->setID("original-id-label"_spr);
		originalIdLabelButton->setPosition(originalIdLabel->getPositionX() - buttonMenu->getPositionX(), originalIdLabel->getPositionY() - buttonMenu->getPositionY());
		originalIdLabelButton->setContentSize({originalIdLabel->getContentWidth() * originalIdLabel->getScaleX(), originalIdLabel->getContentHeight() * originalIdLabel->getScaleY()});
		originalIdLabelButton->setAnchorPoint(originalIdLabel->getAnchorPoint());
		originalIdLabelButton->setVisible(false);

		// Create new id button
		auto newIdLabelSprite = CCLabelBMFont::create("NewID:", "goldFont.fnt");
		newIdLabelSprite->setScale(newIdLabel->getScale());
		auto newIdLabelButton = CCMenuItemSpriteExtra::create(newIdLabelSprite, this, menu_selector(SetupSpawnPopupShift::onNewIdPress));
		newIdLabelButton->setID("new-id-label"_spr);
		newIdLabelButton->setPosition(newIdLabel->getPositionX() - buttonMenu->getPositionX(), newIdLabel->getPositionY() - buttonMenu->getPositionY());
		newIdLabelButton->setContentSize({newIdLabel->getContentWidth() * newIdLabel->getScaleX(), newIdLabel->getContentHeight() * newIdLabel->getScaleY()});
		newIdLabelButton->setAnchorPoint(newIdLabel->getAnchorPoint());
		newIdLabelButton->setVisible(false);

		// Add buttons
		buttonMenu->addChild(groupIdLabelButton);
		buttonMenu->addChild(originalIdLabelButton);
		buttonMenu->addChild(newIdLabelButton);

		// Remove old labels
		mainLayer->removeChildByID("group-id-label");
		mainLayer->removeChildByID("original-id-label");
		mainLayer->removeChildByID("new-id-label");

		// Configure pages
		addObjectToPage(groupIdLabelButton, 0);
		addObjectToPage(originalIdLabelButton, 1);
		addObjectToPage(newIdLabelButton, 1);

		// Get objects
		std::vector<EffectGameObject*> objects;
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
			[](EffectGameObject* obj) { std::vector<float> group = { static_cast<float>(obj->m_targetGroupID) }; return group; },
			[](EffectGameObject* obj, std::vector<float> vals) { obj->m_targetGroupID = vals[0]; }
		);
		popup->setUserData(this);
		popup->show();
	} // onGroupIdPress

	void onOriginalIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> ids; for (ChanceObject remap : static_cast<SpawnTriggerGameObject*>(obj)->m_remapObjects) ids.push_back(remap.m_groupID); return ids; },
			[](EffectGameObject* obj, std::vector<float> vals) {
				auto spawnObject = static_cast<SpawnTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_remapObjects.size(); i++) {
					spawnObject->m_remapObjects[i].m_groupID = vals[i];
					spawnObject->m_remapObjects[i].m_oldGroupID = vals[i];
				} // for
			}
		);
		popup->setUserData(this);
		popup->show();
	} // onOriginalIdPress

	void onNewIdPress(CCObject* sender) {
		auto objects = static_cast<PropertyShiftPopup::ObjectCollection*>(static_cast<CCNode*>(sender)->getUserObject());
		auto popup = PropertyShiftPopup::create(
			objects->data,
			[](EffectGameObject* obj) { std::vector<float> ids; for (ChanceObject remap : static_cast<SpawnTriggerGameObject*>(obj)->m_remapObjects) ids.push_back(remap.m_chance); return ids; },
			[](EffectGameObject* obj, std::vector<float> vals) {
				auto spawnObject = static_cast<SpawnTriggerGameObject*>(obj);
				for (int i = 0; i < spawnObject->m_remapObjects.size(); i++) 
					spawnObject->m_remapObjects[i].m_chance = vals[i];
			}
		);
		popup->setUserData(this);
		popup->show();
	} // onNewIdPress

}; // SetupSpawnPopupShift