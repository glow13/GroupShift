#include "PropertyShiftPopup.hpp"

void PropertyShiftPopup::onButtonPress(CCObject*) {

    // Initialize variables
    int val = getValue();
    LevelEditorLayer* lel = LevelEditorLayer::get();
    auto properties = std::vector<std::vector<float>>(targetedObjectCount);

    // Shift the property
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedTriggerObjects[i];
        properties[i] = getProperty(obj);
        for (int p = 0; p < properties[i].size(); p++) {
            float newProperty = properties[i][p] + val;

            // Check if any properties were out of bounds
            if (!inBounds(newProperty, minValue, maxValue)) {
                closeParentPopup(this);
                onClose(this);
                badNotification("Failed to shift a property out of bounds!");
                return;
            } // if

            properties[i][p] = newProperty;
        } // for
    } // for

    // Reassign all properties
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedTriggerObjects[i];
        setProperty(obj, properties[i]);
        lel->updateObjectLabel(obj);
    } // for

    // Success and close popups
    closeParentPopup(this);
    onClose(this);
    goodNotification("Shifted the property of the selected triggers by " + std::to_string(val) + "!");
} // onButtonPress

bool PropertyShiftPopup::init(FLAlertLayer* popup) {
    if (!ShiftPopup::init(popup)) return false;

    setTitle("Shift Property");
    setID("PropertyShiftPopup"_spr);

    return true;
} // setup

PropertyShiftPopup* PropertyShiftPopup::create(
	std::vector<EffectGameObject*> objects,
    FLAlertLayer* popup,
	std::function<std::vector<float>(EffectGameObject*)> getProperty,
	std::function<void(EffectGameObject*, std::vector<float>)> setProperty,
    int minValue, int maxValue) {

    auto ret = new PropertyShiftPopup();
    if (ret->init(popup)) {
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