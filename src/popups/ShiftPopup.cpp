#include "ShiftPopup.hpp"

bool ShiftPopup::setup(FLAlertLayer* popup) {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    m_popup = popup;

    // Setup the window
    setTitle("Shift Groups");
    setID("ShiftPopup"_spr);
    m_noElasticity = true;

    // Create the slider
    slider->setPosition(winSize.width / 2, winSize.height / 2 - 15);
    slider->setID("shift-slider"_spr);
    slider->setValue(0.5);
    slider->updateBar();
    addChild(slider);

    // Create the text input field
    textInput->setPosition(winSize.width / 2, winSize.height / 2 + 15);
    textInput->setID("shift-text"_spr);
    textInput->setString("0");
    textInput->setFilter("-0123456789");
    textInput->setMaxCharCount(8);
    textInput->setCallback([&](std::string const& text) { ShiftPopup::onTextInput(text); });
    addChild(textInput);

    // Create the confirm button
    auto okButton = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(ShiftPopup::onButtonPress));
    m_buttonMenu->addChildAtPosition(okButton, Anchor::Bottom, CCPointMake(0, 25));
    okButton->setID("shift-ok"_spr);

    // Create the auto button
    auto autoButtonSprite = CCSprite::createWithSpriteFrameName("difficulty_auto_btn_001.png");
    autoButtonSprite->setScale(0.65);
    auto autoButton = CCMenuItemSpriteExtra::create(autoButtonSprite, this, menu_selector(ShiftPopup::onAutoPress));
    m_buttonMenu->addChildAtPosition(autoButton, Anchor::BottomLeft, CCPointMake(25, 25));
    autoButton->setID("shift-auto"_spr);

    // Create the left arrow selector
    auto leftArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_leftBtn_001.png"), this, menu_selector(ShiftPopup::onLeftArrow));
    leftArrow->setID("left-arrow"_spr);
    leftArrow->setPositionX((m_buttonMenu->getContentWidth() - textInput->getContentWidth()) / 2 - leftArrow->getContentWidth() * 1.5);
    leftArrow->setPositionY(textInput->getPositionY() - m_buttonMenu->getPositionY());
    m_buttonMenu->addChild(leftArrow);

    // Create the right arrow selector
    auto rightArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_rightBtn_001.png"), this, menu_selector(ShiftPopup::onRightArrow));
    rightArrow->setID("right-arrow"_spr);
    rightArrow->setPositionX((m_buttonMenu->getContentWidth() + textInput->getContentWidth()) / 2 +  leftArrow->getContentWidth() * 1.5);
    rightArrow->setPositionY(textInput->getPositionY() - m_buttonMenu->getPositionY());
    m_buttonMenu->addChild(rightArrow);

    return true;
} // setup

CCMenuItemSpriteExtra* ShiftPopup::createLabelButton(CCLabelBMFont* label, FLAlertLayer* popup, SEL_MenuHandler callback) {
    return createLabelButton(label, true, popup, callback);
} // createLabelButton

CCMenuItemSpriteExtra* ShiftPopup::createLabelButton(CCLabelBMFont* label, bool underline, FLAlertLayer* popup, SEL_MenuHandler callback) {

    // Get menu reference
    auto menu = popup->getChildByType<CCLayer>(0)->getChildByType<CCMenu>(0);

    // Check for errors, this should hopefully prevent more crashes
    if (!menu || !label) {
        log::error("Failed to create shift button, this could cause a crash, please report this issue!");
        auto fail = CCMenuItemSpriteExtra::create(CCLabelBMFont::create("error", "chatFont.fnt"), popup, nullptr);
        fail->setVisible(false);
        fail->setScale(0);
        return fail;
    } // if

    // Create button sprite
    std::string labelString = label->getString();
    labelString.erase(labelString.find_last_not_of(' ') + 1);
    auto labelSprite = CCLabelBMFont::create(labelString.c_str(), label->getFntFile());
    labelSprite->setScale(label->getScale());

    // Create button
    auto labelButton = CCMenuItemSpriteExtra::create(labelSprite, popup, callback);
    labelButton->setPosition(label->getPositionX() - menu->getPositionX(), label->getPositionY() - menu->getPositionY());
    labelButton->setContentSize(label->getScaledContentSize());
    labelButton->setAnchorPoint(label->getAnchorPoint());
    labelButton->setVisible(label->isVisible());

    // Create underline sprite
    if (underline && Mod::get()->getSettingValue<bool>("show-underlines")) {
        auto underlineSprite = CCSprite::createWithSpriteFrameName("gridLine01_001.png");
        underlineSprite->setScaleX(labelSprite->getScaledContentWidth() / underlineSprite->getContentWidth() * 0.93f);
        underlineSprite->setPositionX(labelSprite->getPositionX());
        underlineSprite->setAnchorPoint(CCPoint(0.5f, 0.0f));
        underlineSprite->setScaleY(0.7f);
        underlineSprite->setZOrder(-1);
        underlineSprite->setColor(
            (std::strcmp(label->getFntFile(), "goldFont.fnt") == 0) ?
            ccc3(255, 218, 64) :
            ccc3(255, 255, 255)
        );
        labelButton->addChild(underlineSprite);
    } // if

    // Set button id
    std::string id = "shift-button-"_spr + std::to_string(menu->getChildrenCount());
    labelButton->setID(label->getID().empty() ? id : ""_spr + label->getID());

    // Hide old label and add the new button
    label->setScale(0);
    label->setVisible(false);
    menu->addChild(labelButton);

    return labelButton;
} // createLabelButton

int ShiftPopup::getValue() {
    auto text = textInput->getString();
    return (text != "-") ? stoi(text) : 0;
} // getValue

void ShiftPopup::onLeftArrow(CCObject* obj) {
    int value = getValue();
    if (value > -100 && value < 100) onTextInput(std::to_string(value - 1));
    else onTextInput((value <= -100) ? "-100" : "99");
} // onLeftArrow

void ShiftPopup::onRightArrow(CCObject* obj) {
    int value = getValue();
    if (value > -100 && value < 100) onTextInput(std::to_string(value + 1));
    else onTextInput((value >= 100) ? "100" : "-99");
} // onRightArrow

void ShiftPopup::onAutoPress(CCObject* obj) {
    onTextInput(std::to_string(targetedObjectCount));
} // onAutoPress

void ShiftPopup::onSlider(CCObject* obj) {
    textInput->setString(std::to_string(int(slider->getValue() * 200 - 100)));
} // onSlider

void ShiftPopup::onTextInput(std::string text) {
    if ((int) text.find("-") > 0) text = "0";

    if (text != "" && text != "-") {
        int num = stoi(text);
        if (num > 100) slider->setValue(1);
        else if (num < -100) slider->setValue(0);
        else slider->setValue((num + 100.0f) / 200.0f);
    } else slider->setValue(0.5);

    textInput->setString(text);
    slider->updateBar();
} // onTextInput

void ShiftPopup::goodNotification(std::string text) {
    log::info("{}", text);
    if (!Mod::get()->getSettingValue<bool>("show-notifications")) return;
    Notification::create(text, NotificationIcon::Success, 2)->show();
} // goodNotification

void ShiftPopup::badNotification(std::string text) {
    log::warn("{}", text);
    Notification::create(text, NotificationIcon::Error, 2)->show();
} // badNotification

void ShiftPopup::closeParentPopup(cocos2d::CCObject* sender) {
    if (auto popup = typeinfo_cast<SetGroupIDLayer*>(m_popup)) popup->onClose(sender);
    else if (auto popup = typeinfo_cast<SetupTriggerPopup*>(m_popup)) popup->onClose(sender);
    else if (auto popup = typeinfo_cast<CollisionBlockPopup*>(m_popup)) popup->onClose(sender);
} // closeParentPopup

static ShiftPopup* create(std::vector<GameObject*> objects, FLAlertLayer* popup) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f, popup)) {
        ret->targetedObjects = objects;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create

static ShiftPopup* create(std::vector<EffectGameObject*> objects, FLAlertLayer* popup) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f, popup)) {
        ret->targetedTriggerObjects = objects;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create