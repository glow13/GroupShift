#include "GroupShiftPopup.hpp"

void GroupShiftPopup::onButtonPress(CCObject* obj) {
    log::info("Shifting the groups of {} selected objects by {}", targetedObjects.size(), getValue());

    LevelEditorLayer* lel = LevelEditorLayer::get();

    for (GameObject* obj : targetedObjects) {
        std::vector<int> groups;
        if (obj->m_groups) groups = std::vector<int>{obj->m_groups->begin(), obj->m_groups->end()};

        auto newGroups = new short[10];
        memset(newGroups, 0, 10 * sizeof(short));
        for (int i = 0; i < obj->m_groupCount; i++) {
            if (groups[i] > 0 && inBounds(groups[i] + getValue(), 0, 9999)) newGroups[i] = static_cast<short>(groups[i] + getValue());
            else newGroups[i] = static_cast<short>(groups[i]);
        } // for

        obj->m_groups = reinterpret_cast<decltype(obj->m_groups)>(newGroups);

        auto parents = CCDictionaryExt<int, CCArray*>(lel->m_unknownE40);
        for (auto [key, values] : parents) {
            if (key == obj->m_uniqueID && values->count() > 0) {
                CCArray* newValues = new CCArray();
                for (auto value : CCArrayExt<CCInteger*>(values)) {
                    int num = value->getValue();
                    if (num > 0 && num + getValue() > 0) newValues->addObject(new CCInteger(num + getValue()));
                } // for
                parents[obj->m_uniqueID] = newValues;
            } // if
        } // for
    } // for
    
    onClose(this);
    static_cast<SetGroupIDLayer*>(getUserObject())->onClose(this);
} // onButtonPress

bool GroupShiftPopup::setup() {
    if (!ShiftPopup::setup()) return false;

    this->setTitle("Shift Groups");
    this->setID("GroupShiftPopup"_spr);

    return true;
} // setup

GroupShiftPopup* GroupShiftPopup::create(std::vector<GameObject*> objects) {
    auto ret = new GroupShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedObjects = objects;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create