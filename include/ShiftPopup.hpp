#pragma once

#include <Geode/Geode.hpp>
#include <Geode/ui/Notification.hpp>
#include <vector>

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
    static bool inBounds(int num, int min, int max) { return num >= min && num <= max; }
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
};

void onClose_hook(CCObject* sender);