#include "GroupShiftPopup.hpp"

void GroupShiftPopup::onButtonPress(CCObject* obj) {

    // Initialize variables
    int val = getValue();
    LevelEditorLayer* lel = LevelEditorLayer::get();
    auto parentDict = CCDictionaryExt<int, GameObject*>(lel->m_parentGroupsDict);
    auto groups = std::vector<std::vector<short>>(targetedObjectCount);
    auto parents = std::map<short, int>(); // map<group, objIndex>

    // Find all groups and parents
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedObjects[i];
        groups[i] = std::vector<short>(obj->m_groupCount);
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
            if (parentDict.contains(group) && parentDict[group]->m_uniqueID == obj->m_uniqueID) parents[newGroup] = i;
            else if (i == 0) parents[newGroup] = -1; // avoid bug with the first index
        } // for
    } // for

    // Check if this will overwrite an existing group parent
    for (std::pair<short, int> p : parents) if (p.second > -1 && parentDict.contains(p.first)) {
        GameObject* parentObj = parentDict[p.first];

        // If a group parent will be overwritten, is it an already selected object?
        auto parentIsSelected = false;
        for (std::pair<short, int> g : parents)  if (g.second > -1) {
            auto obj = targetedObjects[g.second];
            if (obj->m_uniqueID == parentObj->m_uniqueID) parentIsSelected = true;
        } // for

        // If it isn't selected, we will overwrite it if we don't stop
        if (!parentIsSelected) {
            closeParentPopup(this);
            onClose(this);
            badNotification("Failed to overwrite an existing parent of group " + std::to_string(p.first) + "!");
            return;
        } // if
    } // for

    // Remove every group parent
    for (std::pair<short, int> p : parents) lel->removeGroupParent(p.first - val);

    // Reassign all groups and group parents
    for (int i = 0; i < targetedObjectCount; i++) {
        auto obj = targetedObjects[i];
        for (short g : groups[i]) obj->removeFromGroup(g - val);
        for (short g : groups[i]) {
            obj->addToGroup(g);
            if (parents[g] == i) lel->setGroupParent(obj, g);
        } // for
    } // for

    // Success and close popups
    closeParentPopup(this);
    onClose(this);
    goodNotification("Shifted the groups of the selected objects by " + std::to_string(val) + "!");
} // onButtonPress

bool GroupShiftPopup::init(FLAlertLayer* popup) {
    if (!ShiftPopup::init(popup)) return false;

    this->setTitle("Shift Groups");
    this->setID("GroupShiftPopup"_spr);

    return true;
} // setup

GroupShiftPopup* GroupShiftPopup::create(std::vector<GameObject*> objects, FLAlertLayer* popup) {
    auto ret = new GroupShiftPopup();
    if (ret->init(popup)) {
        ret->targetedObjects = objects;
        ret->targetedObjectCount = objects.size();
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create