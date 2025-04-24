#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>

/*
    Definitions to simplify creating the shift popups
    I know they're ugly, but they are sooo helpful so I don't really care lol
*/ 
#define $get(val) [](EffectGameObject* obj) -> std::vector<float> { return { static_cast<float>(val) }; }
#define $set(val) [](EffectGameObject* obj, std::vector<float> vals) { val = vals[0]; }
#define $objects(val, c) static_cast<c::ObjectCollection*>(static_cast<CCNode*>(val)->getUserObject("collection"_spr))

using namespace geode::prelude;

class ShiftPopup : public geode::Popup<FLAlertLayer*> {
public:
    using Popup::initAnchored;

    FLAlertLayer* m_popup;
    Slider* slider = Slider::create(this, menu_selector(ShiftPopup::onSlider), 0.75);
	TextInput* textInput = TextInput::create(50, "num");
    std::vector<GameObject*> targetedObjects;
    std::vector<EffectGameObject*> targetedTriggerObjects;
    int targetedObjectCount = 0;

    bool setup(FLAlertLayer* popup) override;
    int getValue();
    static bool inBounds(float num, int min, int max) { return num >= min && num <= max; }
    virtual void onButtonPress(CCObject* obj) { log::info("value = {}", getValue()); onClose(this); }
    void onAutoPress(CCObject* obj);
    void onSlider(CCObject* obj);
    void onTextInput(std::string text);
    void onLeftArrow(CCObject* obj);
    void onRightArrow(CCObject* obj);
    void goodNotification(std::string text);
    void badNotification(std::string text);
    void closeParentPopup(CCObject* sender);
    static ShiftPopup* create(std::vector<GameObject*> objects, FLAlertLayer* popup);
    static CCMenuItemSpriteExtra* createLabelButton(CCLabelBMFont* label, FLAlertLayer* popup, SEL_MenuHandler callback);
};