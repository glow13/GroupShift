#include "PropertyShiftPopup.hpp"

void PropertyShiftPopup::onButtonPress(CCObject*) {

    // Initialize variables
    int val = getValue();
    LevelEditorLayer* editor = LevelEditorLayer::get();

    // Shift the property
    for (EffectGameObject* obj : targetedTriggerObjects) {
        std::vector<float> values = getProperty(obj);
        bool outOfBounds = false;
        for (int i = 0; i < values.size(); i++) {
            if (inBounds(values[i] + val, minValue, maxValue)) values[i] += val;
            else outOfBounds = true;
        } // for

        // Check if out of bounds
        if (!outOfBounds) setProperty(obj, values);
        else badNotification("Failed to shift a property out of bounds!");

        // Update the label
        editor->updateObjectLabel(obj);
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