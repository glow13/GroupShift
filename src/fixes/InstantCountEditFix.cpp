#include <Geode/modify/EditorUI.hpp>
#include <Geode/Geode.hpp>

using namespace geode::prelude;

class $modify(EditorUIFix, EditorUI) {

    static const int s_instantCountTriggerID = 1811;

    void editObject(CCObject* obj) {

        // Make sure all selected objects are instant count triggers
        bool match = m_selectedObjects->count() > 0;
        for (int i = 0; i < m_selectedObjects->count() && match; i++) {
            auto selectedObject = static_cast<GameObject*>(m_selectedObjects->objectAtIndex(i));
            if (selectedObject->m_objectID != s_instantCountTriggerID) match = false;
        } // for

        // Show popup
        if (match) SetupInstantCountPopup::create(static_cast<CountTriggerGameObject*>(m_selectedObject), m_selectedObjects)->show();
        else EditorUI::editObject(obj);
    } // editObject

}; // EditorUIFix