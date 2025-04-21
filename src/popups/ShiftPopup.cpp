#include "ShiftPopup.hpp"

using namespace geode::prelude;

bool ShiftPopup::setup() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    // Setup the window
    setTitle("Shift Groups");
    setID("GroupShiftPopup"_spr);
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
    
    // Get menu reference
    auto menu = popup->getChildByType<CCLayer>(0)->getChildByType<CCMenu>(0);

    // Create button sprite
    auto labelSprite = CCLabelBMFont::create(label->getString(), label->getFntFile());
    labelSprite->setScale(label->getScale());

    // Create button
    auto labelButton = CCMenuItemSpriteExtra::create(labelSprite, popup, callback);
    labelButton->setPosition(label->getPositionX() - menu->getPositionX(), label->getPositionY() - menu->getPositionY());
    labelButton->setContentSize(label->getScaledContentSize());
    labelButton->setAnchorPoint(label->getAnchorPoint());
    labelButton->setID(label->getID().empty() ? "" : ""_spr + label->getID());

    return labelButton;
} // createLabelButton

int ShiftPopup::getValue() {
    return std::stoi(textInput->getString());
} // getValue

void ShiftPopup::onLeftArrow(CCObject* obj) {
    int value = getValue();
    if (value > -100) {
        textInput->setString(std::to_string(value - 1));
        slider->setValue((value + 99.0f) / 200.0f);
    } // if
} // onLeftArrow

void ShiftPopup::onRightArrow(CCObject* obj) {
    int value = getValue();
    if (value < 100) {
        textInput->setString(std::to_string(value + 1));
        slider->setValue((value + 101.0f) / 200.0f);
    } // if
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
        int num = std::stoi(text);
        if (num > 100) slider->setValue(1);
        else if (num < -100) slider->setValue(0);
        else slider->setValue((std::stoi(text) + 100.0f) / 200.0f);
    } else slider->setValue(0.5);

    textInput->setString(text);
    slider->updateBar();
} // onTextInput

void ShiftPopup::goodNotification(std::string text) {
    Notification::create(text, NotificationIcon::Success, 2)->show();
    log::info("{}", text);
} // errorNotification

void ShiftPopup::badNotification(std::string text) {
    Notification::create(text, NotificationIcon::Error, 2)->show();
    log::error("{}", text);
} // errorNotification

void ShiftPopup::closeParentPopup(cocos2d::CCObject* sender) {
    auto obj = getUserObject();
    if (obj == NULL) return;
    
    if (auto popup = dynamic_cast<SetGroupIDLayer*>(obj)) popup->onClose(sender);
    else if (auto popup = dynamic_cast<SetupTriggerPopup*>(obj)) popup->onClose(sender);
    else if (auto popup = dynamic_cast<CollisionBlockPopup*>(obj)) popup->onClose(sender);
} // closeParentPopup

static ShiftPopup* create(std::vector<GameObject*> objects) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedObjects = objects;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create

static ShiftPopup* create(std::vector<EffectGameObject*> objects) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedTriggerObjects = objects;
        ret->autorelease();
        return ret;
    } // if

    delete ret;
    return nullptr;
} // create