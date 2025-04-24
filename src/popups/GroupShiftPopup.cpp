#include "GroupShiftPopup.hpp"

void GroupShiftPopup::onButtonPress(CCObject* obj) {

    // Initialize variables
    int val = getValue();
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

            // Check if the new group is out of bounds
            if (!inBounds(newGroup, 1, 9999)) {
                closeParentPopup(this);
                onClose(this);
                badNotification("Failed to shift a group out of bounds!");
                return;
            } // if

            groups[i][g] = newGroup;
            auto parentObj = CCDictionaryExt<int, GameObject*>(lel->m_parentGroupsDict)[group];
            if (parentObj != nullptr && parentObj->m_uniqueID == obj->m_uniqueID) parents[i] = newGroup;
        } // for
    } // for

    // Remove every parent
    for (short p : parents) if (p > 0) lel->removeGroupParent(p - val);

    // Reassign all groups and parents
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedObjects[i];
        lel->setGroupParent(obj, parents[i]);
        for (short g : groups[i]) obj->removeFromGroup(g - val);
        for (short g : groups[i]) obj->addToGroup(g);
    } // for

    // Success and close popups
    closeParentPopup(this);
    onClose(this);
    goodNotification("Shifted the groups of the selected objects by " + std::to_string(val) + "!");
} // onButtonPress

bool GroupShiftPopup::setup(FLAlertLayer* popup) {
    if (!ShiftPopup::setup(popup)) return false;

    this->setTitle("Shift Groups");
    this->setID("GroupShiftPopup"_spr);

    return true;
} // setup

GroupShiftPopup* GroupShiftPopup::create(std::vector<GameObject*> objects, FLAlertLayer* popup) {
    auto ret = new GroupShiftPopup();
    if (ret->initAnchored(240.f, 160.f, popup)) {
        ret->targetedObjects = objects;
        ret->targetedObjectCount = objects.size();
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create