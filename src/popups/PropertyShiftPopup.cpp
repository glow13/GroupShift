#include "PropertyShiftPopup.hpp"

void PropertyShiftPopup::onButtonPress(CCObject*) {
    log::info("Shifting the selected property of {} objects by {}", targetedTriggerObjects.size(), getValue());

    int num = getValue();
    LevelEditorLayer* editor = LevelEditorLayer::get();
    for (EffectGameObject* obj : targetedTriggerObjects) {
        std::vector<float> values = getProperty(obj);
        bool success = true;
        for (int i = 0; i < values.size(); i++) {
            if (inBounds(values[i] + num, maxValue)) values[i] += num;
            else success = false;
        }
        if (success) setProperty(obj, values);
        else log::error("Shifting failed, the values were shifted out of bounds!");
        editor->updateObjectLabel(obj);
    }
    onClose(this);
}

bool PropertyShiftPopup::setup() {
    if (!ShiftPopup::setup()) return false;

    this->setTitle("Shift Property");
    this->setID("PropertyShiftPopup"_spr);

    return true;
}

PropertyShiftPopup* PropertyShiftPopup::create(
	std::vector<EffectGameObject*> objects,
	std::function<std::vector<float>(EffectGameObject*)> getProperty,
	std::function<void(EffectGameObject*, std::vector<float>)> setProperty,
    int maxValue
) {
    auto ret = new PropertyShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedTriggerObjects = objects;
        ret->getProperty = getProperty;
        ret->setProperty = setProperty;
        ret->maxValue = maxValue;
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}