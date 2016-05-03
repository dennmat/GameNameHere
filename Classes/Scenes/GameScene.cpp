#include "GameScene.h"

using namespace gnh;

GameScreen::GameScreen() {
	this->has_mouse = true;
	this->has_touch = true;
	this->has_keyboard = false;
}

GameScreen::GameScreen(rapidjson::Value& value) {
	Screen::fromJson(value);

}

short GameScreen::load() {
	cocos2d::log("Loading MenuScreen...\n");
	this->mouse_listener = cocos2d::EventListenerMouse::create();
	this->touch_listener = cocos2d::EventListenerTouchOneByOne::create();

	this->setupListeners();

	this->node = cocos2d::Node::create();
	this->node->setPosition(this->position);
	this->node->setContentSize(this->size);
	this->node->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);

	this->dialogTitleLabel = cocos2d::Label::createWithTTF("This is the game screen mother fucker", "fonts/Marker Felt.ttf", 24);
	this->dialogTitleLabel->setPosition(cocos2d::Vec2(0, this->node->getContentSize().height));
	this->dialogTitleLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	this->dialogTitleLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->node->addChild(this->dialogTitleLabel);

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->mouse_listener, this->node);

	return 1;
}

void GameScreen::setupListeners() {
	this->mouse_listener->onMouseDown = CC_CALLBACK_1(GameScreen::onMouseDown, this);
	this->mouse_listener->onMouseUp = CC_CALLBACK_1(GameScreen::onMouseUp, this);
	this->mouse_listener->onMouseMove = CC_CALLBACK_1(GameScreen::onMouseMove, this);

	this->touch_listener->onTouchBegan = CC_CALLBACK_2(GameScreen::onTouchBegan, this);
	this->touch_listener->onTouchMoved = CC_CALLBACK_2(GameScreen::onTouchMoved, this);
	this->touch_listener->onTouchEnded = CC_CALLBACK_2(GameScreen::onTouchEnded, this);
}

void GameScreen::onMouseDown(cocos2d::Event* event) {

}

void GameScreen::onMouseUp(cocos2d::Event* event) {
	ScreenManager::getInstance().changeScene("main_menu");
}

void GameScreen::onMouseMove(cocos2d::Event* event) {

}

bool GameScreen::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	return true;
}

void GameScreen::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void GameScreen::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void GameScreen::render() {

}

void GameScreen::update() {

}

void GameScreen::input(cocos2d::Event* event, cocos2d::Touch* touch /*= nullptr*/) {

}

void GameScreen::focus() {

}

void GameScreen::blur() {

}

short GameScreen::unload() {
	return 1;
}

GameScreen::~GameScreen() {

}