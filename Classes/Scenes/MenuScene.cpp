#include "MenuScene.h"

using namespace gnh;

MenuScreen::MenuScreen() {
	this->has_mouse = true;
	this->has_touch = true;
	this->has_keyboard = false;
}

MenuScreen::MenuScreen(rapidjson::Value& value) {
	Screen::fromJson(value);

}

short MenuScreen::load() {
	cocos2d::log("Loading MenuScreen...\n");
	this->mouse_listener = cocos2d::EventListenerMouse::create();
	this->touch_listener = cocos2d::EventListenerTouchOneByOne::create();

	this->setupListeners();

	this->node = cocos2d::Node::create();
	this->node->setPosition(this->position);
	this->node->setContentSize(this->size);
	this->node->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

	this->dialogTitleLabel = cocos2d::Label::createWithTTF("Hello World This Is My House", "fonts/Marker Felt.ttf", 24);
	this->dialogTitleLabel->setPosition(cocos2d::Vec2(0, this->node->getContentSize().height));
	this->dialogTitleLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	this->dialogTitleLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->node->addChild(this->dialogTitleLabel);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->mouse_listener, this->node);

	return 1;
}

void MenuScreen::setupListeners() {
	this->mouse_listener->onMouseDown = CC_CALLBACK_1(MenuScreen::onMouseDown, this);
	this->mouse_listener->onMouseUp = CC_CALLBACK_1(MenuScreen::onMouseUp, this);
	this->mouse_listener->onMouseMove = CC_CALLBACK_1(MenuScreen::onMouseMove, this);

	this->touch_listener->onTouchBegan = CC_CALLBACK_2(MenuScreen::onTouchBegan, this);
	this->touch_listener->onTouchMoved = CC_CALLBACK_2(MenuScreen::onTouchMoved, this);
	this->touch_listener->onTouchEnded = CC_CALLBACK_2(MenuScreen::onTouchEnded, this);
}

void MenuScreen::onMouseDown(cocos2d::Event* event) {

}

void MenuScreen::onMouseUp(cocos2d::Event* event) {
	cocos2d::log("MENU SCREEN MOUSE UP");
	ScreenManager::getInstance().changeScene("game");
}

void MenuScreen::onMouseMove(cocos2d::Event* event) {

}

bool MenuScreen::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	return true;
}

void MenuScreen::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void MenuScreen::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void MenuScreen::render() {

}

void MenuScreen::update() {

}

void MenuScreen::input(cocos2d::Event* event, cocos2d::Touch* touch /*= nullptr*/) {

}

void MenuScreen::focus() {

}

void MenuScreen::blur() {

}

short MenuScreen::unload() {
	return 1;
}

MenuScreen::~MenuScreen() {

}