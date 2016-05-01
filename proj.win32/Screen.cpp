#include "Screen.h"

using namespace gnh;

ScreenManager::ScreenManager() {

}

short ScreenManager::stackScreen(std::unique_ptr<Screen> screen) {
	this->screens.push_back(screen);
}

std::unique_ptr<Screen> ScreenManager::popScreen() {
	std::unique_ptr<Screen> screen = std::move(this->screens.at(this->screens.size() - 1));
	
	this->unsetupScreen(screen);

	this->screens.pop_back();

	return screen;
}

void ScreenManager::focusScreen(Screen* screen) {

}

void ScreenManager::focusScreenAt(const short index) {

}

void ScreenManager::showScreen(Screen* screen) {

}

void ScreenManager::hideScreen(Screen* screen) {

}

void ScreenManager::removeScreenAt(const short index) {

}

void ScreenManager::loadScreen(Screen* screen) {
	this->setupScreen(screen);
}

void ScreenManager::handleEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

bool ScreenManager::propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

void ScreenManager::setupScreen(Screen* screen) {
	screen->setupListeners();

	if (screen->is_modal) {
		//Prevent all other listeners, save current listeners state
	}
}

void ScreenManager::unsetupScreen(const std::unique_ptr<Screen>& screen) {
	if (screen->is_modal) {
		//Return listeners to state before screen was setup
	}

	screen->unload();
}

void ScreenManager::update() {
	for (const auto& screen : this->screens) {
		screen->update();
	}
}

void ScreenManager::render() {
	for (const auto& screen : this->screens) {
		if (screen->is_visible) {
			screen->render();
		}
	}
}

ScreenManager::~ScreenManager() {}

DialogScreen::DialogScreen() {
	this->has_touch = true;
	this->has_mouse = true;
	this->has_keyboard = false;
}

short DialogScreen::load() {
	this->mouse_listener = cocos2d::EventListenerMouse::create();
	this->touch_listener = cocos2d::EventListenerTouchOneByOne::create();
}

void DialogScreen::setupListeners() {
	this->mouse_listener->onMouseDown = CC_CALLBACK_1(DialogScreen::onMouseDown, this);
	this->mouse_listener->onMouseUp = CC_CALLBACK_1(DialogScreen::onMouseUp, this);
	this->mouse_listener->onMouseMove = CC_CALLBACK_1(DialogScreen::onMouseMove, this);

	this->touch_listener->onTouchBegan = CC_CALLBACK_2(DialogScreen::onTouchBegan, this);
	this->touch_listener->onTouchMoved = CC_CALLBACK_2(DialogScreen::onTouchMoved, this);
	this->touch_listener->onTouchEnded = CC_CALLBACK_2(DialogScreen::onTouchEnded, this);
}

void DialogScreen::onMouseDown(const cocos2d::Event* event) {

}

void DialogScreen::onMouseUp(const cocos2d::Event* event) {

}

void DialogScreen::onMouseMove(const cocos2d::Event* event) {

}

void DialogScreen::onTouchBegan(const cocos2d::Touch* touch, const cocos2d::Event* event) {

}

void DialogScreen::onTouchMoved(const cocos2d::Touch* touch, const cocos2d::Event* event) {

}

void DialogScreen::onTouchEnded(const cocos2d::Touch* touch, const cocos2d::Event* event) {

}

void DialogScreen::render() {

}

void DialogScreen::update() {

}

void DialogScreen::input(cocos2d::Event* event, cocos2d::Touch* touch /*= nullptr*/) {

}

void DialogScreen::focus() {

}

void DialogScreen::blur() {

}

short DialogScreen::unload() {

}

DialogScreen::~DialogScreen() {

}

MenuScreen::MenuScreen() {

}

short MenuScreen::load() {

}

void MenuScreen::setupListeners() {

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

}

MenuScreen::~MenuScreen() {

}
