#include "Screen.h"

using namespace gnh;

ScreenManager::ScreenManager() {

}

short ScreenManager::stackScreen(const Screen* screen) {

}

const gnh::Screen& ScreenManager::popScreen() {

}

void ScreenManager::focusScreen(Screen& screen) {

}

void ScreenManager::focusScreenAt(const short index)
{

}

void ScreenManager::showScreen(Screen& screen)
{

}

void ScreenManager::hideScreen(Screen& screen) {

}

void ScreenManager::removeScreenAt(const short index) {

}

void ScreenManager::loadScreen(Screen& screen) {

}

void ScreenManager::handleEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

bool ScreenManager::propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

ScreenManager::~ScreenManager() {

}

DialogScreen::DialogScreen() {

}

short DialogScreen::load() {

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
