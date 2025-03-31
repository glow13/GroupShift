#include "ShiftPopup.hpp"

using namespace geode::prelude;

bool ShiftPopup::setup() {
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setTitle("Shift Groups");
    this->setID("GroupShiftPopup"_spr);
    this->m_noElasticity = true;
    
    slider->setPosition(winSize.width / 2, winSize.height / 2 - 15);
    slider->setID("shift-slider"_spr);
    slider->setValue(0.5);
    slider->updateBar();
    this->addChild(slider);

    textInput->setPosition(winSize.width / 2, winSize.height / 2 + 15);
    textInput->setID("shift-text"_spr);
    textInput->setString("0");
    textInput->setFilter("-0123456789");
    textInput->setCallback([&](std::string const& text) { ShiftPopup::onTextInput(text); });
    this->addChild(textInput);

    auto okButton = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(ShiftPopup::onButtonPress));
    m_buttonMenu->addChildAtPosition(okButton, Anchor::Bottom);
    okButton->setID("shift-ok"_spr);
    okButton->setPositionY(25);

    auto leftArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_leftBtn_001.png"), this, menu_selector(ShiftPopup::onLeftArrow));
    leftArrow->setID("left-arrow"_spr);
    leftArrow->setPositionX((m_buttonMenu->getContentWidth() - textInput->getContentWidth()) / 2 - leftArrow->getContentWidth() * 1.5);
    leftArrow->setPositionY(textInput->getPositionY() - m_buttonMenu->getPositionY());
    m_buttonMenu->addChild(leftArrow);
    
    auto rightArrow = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("edit_rightBtn_001.png"), this, menu_selector(ShiftPopup::onRightArrow));
    rightArrow->setID("right-arrow"_spr);
    rightArrow->setPositionX((m_buttonMenu->getContentWidth() + textInput->getContentWidth()) / 2 +  leftArrow->getContentWidth() * 1.5);
    rightArrow->setPositionY(textInput->getPositionY() - m_buttonMenu->getPositionY());
    m_buttonMenu->addChild(rightArrow);

    return true;
}

int ShiftPopup::getValue() {
    return std::stoi(this->textInput->getString());
}

void ShiftPopup::onLeftArrow(CCObject* obj) {
    int value = getValue();
    if (value > -100) {
        this->textInput->setString(std::to_string(value - 1));
        this->slider->setValue((value + 99.0f) / 200.0f);
    }
}

void ShiftPopup::onRightArrow(CCObject* obj) {
    int value = getValue();
    if (value < 100) {
        this->textInput->setString(std::to_string(value + 1));
        this->slider->setValue((value + 101.0f) / 200.0f);
    }
}

void ShiftPopup::onSlider(CCObject* obj) {
    this->textInput->setString(std::to_string(int(this->slider->getValue() * 200 - 100)));
}

void ShiftPopup::onTextInput(std::string text) {
    int pos = text.find("-");
    if (pos > 0) text = "0";
    
    if (text.compare("") != 0 && text.compare("-") != 0) {
        int num = std::stoi(text);
        //if (num > 100) text = "100";
        //else if (num < -100) text = "-100";
        if (num > 100) this->slider->setValue(1);
        else if (num < -100) this->slider->setValue(0);
        else this->slider->setValue((std::stoi(text) + 100.0f) / 200.0f);
    } else this->slider->setValue(0.5);

    this->textInput->setString(text);
    this->slider->updateBar();
}

static ShiftPopup* create(std::vector<GameObject*> objects) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedObjects = objects;
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

static ShiftPopup* create(std::vector<EffectGameObject*> objects) {
    auto ret = new ShiftPopup();
    if (ret->initAnchored(240.f, 160.f)) {
        ret->targetedTriggerObjects = objects;
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}