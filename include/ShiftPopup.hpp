#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>

using namespace geode;
using namespace cocos;
using namespace cocos2d;
using namespace std;

class ShiftPopup : public geode::Popup<> {
public:
    using Popup::initAnchored;
    
    Slider* slider = Slider::create(this, menu_selector(ShiftPopup::onSlider), 0.75);
	TextInput* textInput = TextInput::create(50, "num");
    vector<GameObject*> targetedObjects;
    vector<EffectGameObject*> targetedTriggerObjects;
    int targetedObjectCount = 0;

    bool setup();
    int getValue();
    static bool inBounds(int num, int min, int max) { return num >= min && num <= max; }
    virtual void onButtonPress(CCObject* obj) { log::info("value = {}", getValue()); onClose(this); }
    void onAutoPress(CCObject* obj);
    void onSlider(CCObject* obj);
    void onTextInput(string text);
    void onLeftArrow(CCObject* obj);
    void onRightArrow(CCObject* obj);
    void goodNotification(string text);
    void badNotification(string text);
    void closeParentPopup(CCObject* sender);
    static ShiftPopup* create(vector<GameObject*> objects);
    static CCMenuItemSpriteExtra* createLabelButton(CCLabelBMFont* label, FLAlertLayer* popup, SEL_MenuHandler callback);
};