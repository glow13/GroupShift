#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>

/*
    Definitions to simplify creating the shift popups
    I know they're ugly, but they are sooo helpful so I don't really care lol
*/ 
#define $get(val) [](EffectGameObject* obj) { std::vector<float> v = { static_cast<float>(val) }; return v; }
#define $set(val) [](EffectGameObject* obj, std::vector<float> vals) { val = vals[0]; }
#define $objects(val, c) static_cast<c::ObjectCollection*>(static_cast<CCNode*>(val)->getUserObject())

using namespace geode::prelude;

class ShiftPopup : public geode::Popup<> {
public:
    using Popup::initAnchored;

    Slider* slider = Slider::create(this, menu_selector(ShiftPopup::onSlider), 0.75);
	TextInput* textInput = TextInput::create(50, "num");
    std::vector<GameObject*> targetedObjects;
    std::vector<EffectGameObject*> targetedTriggerObjects;
    int targetedObjectCount = 0;

    bool setup();
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
    static ShiftPopup* create(std::vector<GameObject*> objects);
    static CCMenuItemSpriteExtra* createLabelButton(CCLabelBMFont* label, FLAlertLayer* popup, SEL_MenuHandler callback);
};