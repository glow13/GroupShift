#include "PropertyShiftPopup.hpp"

void PropertyShiftPopup::onButtonPress(CCObject*) {

    // Initialize variables
    int val = getValue();
    bool outOfBounds = false;
    LevelEditorLayer* lel = LevelEditorLayer::get();
    auto properties = std::vector<std::vector<float>>(targetedObjectCount);

    // Shift the property
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedTriggerObjects[i];
        properties[i] = getProperty(obj);
        for (int p = 0; p < properties[i].size(); p++) {
            int newProperty = properties[i][p] + val;
            if (inBounds(newProperty, minValue, maxValue)) properties[i][p] = newProperty;
            else outOfBounds = true;
        } // for
    } // for

    // Check if any properties were out of bounds
    if (outOfBounds) {
        badNotification("Failed to shift a property out of bounds!");
        closeParentPopup(this);
        onClose(this);
        return;
    } // if

    // Reassign all properties
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedTriggerObjects[i];
        setProperty(obj, properties[i]);
        lel->updateObjectLabel(obj);
    } // for

    // Success and close popups
    goodNotification("Shifted the property of the selected objects by " + std::to_string(val) + "!");
    closeParentPopup(this);
    onClose(this);
} // onButtonPress

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
        ret->targetedObjectCount = objects.size();
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