#include "GroupShiftPopup.hpp"

void GroupShiftPopup::onButtonPress(CCObject* obj) {

    // Initialize variables
    int val = getValue();
    bool outOfBounds = false;
    LevelEditorLayer* lel = LevelEditorLayer::get();
    auto groups = std::vector<std::array<short,10>>(targetedObjectCount);
    auto parents = std::vector<short>(targetedObjectCount);

    // Find all groups and parents
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedObjects[i];
        groups[i] = std::array<short,10>();
        for (int g = 0; g < obj->m_groupCount; g++) {
            int group = obj->m_groups->at(g);
            int newGroup = group + val;
            if (inBounds(newGroup, 1, 9999)) {
                groups[i][g] = newGroup;
                auto parentObj = CCDictionaryExt<int, GameObject*>(lel->m_parentGroupsDict)[group];
                if (parentObj != NULL && parentObj->m_uniqueID == obj->m_uniqueID) parents[i] = newGroup;
            } else outOfBounds = true;
        } // for
    } // for

    // Check if any groups were out of bounds
    if (outOfBounds) {
        badNotification("Failed to shift a group out of bounds!");
        closeParentPopup(this);
        onClose(this);
        return;
    } // if

    // Remove every parent
    for (short p : parents) lel->removeGroupParent(p);

    // Reassign all groups and parents
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedObjects[i];
        lel->setGroupParent(obj, parents[i]);
        for (int g = 0; g < obj->m_groupCount; g++) {
            obj->removeFromGroup(groups[i][g] - val);
            obj->addToGroup(groups[i][g]);
        } // for
    } // for

    // Success and close popups
    goodNotification("Shifted the groups of the selected objects by " + std::to_string(val) + "!");
    closeParentPopup(this);
    onClose(this);
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
        ret->targetedObjectCount = objects.size();
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create