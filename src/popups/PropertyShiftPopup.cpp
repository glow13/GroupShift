#include "PropertyShiftPopup.hpp"

void PropertyShiftPopup::onButtonPress(CCObject*) {
    log::info("Shifting the selected property of {} objects by {}", targetedTriggerObjects.size(), getValue());

    int num = getValue();
    LevelEditorLayer* editor = LevelEditorLayer::get();
    for (EffectGameObject* obj : targetedTriggerObjects) {
        std::vector<float> values = getProperty(obj);
        bool success = true;
        for (int i = 0; i < values.size(); i++) {
            if (inBounds(values[i] + num, minValue, maxValue)) values[i] += num;
            else success = false;
        } // for
        if (success) setProperty(obj, values);
        else log::error("Shifting failed, the values were shifted out of bounds!");
        editor->updateObjectLabel(obj);
    } // for

    onClose(this);
    closeParentPopup(this);
} // onButtonPress

void PropertyShiftPopup::closeParentPopup(cocos2d::CCObject* sender) {
    auto obj = getUserObject();
    if (auto popup = dynamic_cast<SetupTriggerPopup*>(obj)) popup->onClose(sender);
    else if (auto popup = dynamic_cast<CollisionBlockPopup*>(obj)) popup->onClose(sender);
} // closeParentPopup

bool PropertyShiftPopup::setup() {
    if (!ShiftPopup::setup()) return false;

    this->setTitle("Shift Property");
    this->setID("PropertyShiftPopup"_spr);

    return true;
} // setup

PropertyShiftPopup* PropertyShiftPopup::create(
	std::vector<EffectGameObject*> objects,
	std::function<std::vector<float>(EffectGameObject*)> getProperty,
	std::function<void(EffectGameObject*, std::vector<float>)> setProperty,
    int minValue, int maxValue
) {
    auto ret = new PropertyShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedTriggerObjects = objects;
        ret->getProperty = getProperty;
        ret->setProperty = setProperty;
        ret->minValue = minValue;
        ret->maxValue = maxValue;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create