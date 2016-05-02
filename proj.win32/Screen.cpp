#include "Screen.h"

using namespace gnh;

ScreenManager::ScreenManager() {

}

void ScreenManager::loadScenes() {
	rapidjson::Document document;

	std::string sceneRawData = "";
	std::string sceneDataPath = "scenes/scenes.json";

	readFileToStr(GNH_RESOURCE_PATH(sceneDataPath), sceneRawData);

	document.Parse(sceneRawData.c_str());

	assert(document.IsArray());

	std::string firstKey;

	for (rapidjson::SizeType i = 0; i < document.Size(); i++) {
		std::string sceneFile = document[i]["sceneconf"].GetString();
		std::string mapKey = document[i]["handle"].GetString();

		if (firstKey.empty()) {
			firstKey = mapKey;
		}

		this->scenes[mapKey] = std::make_unique<Scene>(sceneFile);
	}
	
	if (!firstKey.empty()) {
		this->changeScene(firstKey);
	}
}

void ScreenManager::exitScene() {
	if (this->currentScene == nullptr) return;

	Scene& scene = *this->scenes[this->currentSceneKey];

	//TODO: Unload/Unhook Stuff Fool
	this->currentScene = nullptr;
	this->currentSceneKey = std::string();
}

void ScreenManager::changeScene(std::string sceneName) {
	if (!this->currentSceneKey.empty()) {
		this->exitScene();
	}

	this->scenes[sceneName]->loadSceneFromConf();

	this->currentScene = this->scenes[sceneName].get();
	this->currentSceneKey = sceneName;

	cocos2d::Director* director = cocos2d::Director::getInstance();

	if (director->getRunningScene() != nullptr) {
		director->replaceScene(this->currentScene->cocosScene);
	}
	else {
		director->runWithScene(this->currentScene->cocosScene);
	}
}

short ScreenManager::stackScreen(const ScreenPtr screen) {
	this->screens.push_back(screen);
}

std::unique_ptr<Screen> ScreenManager::popScreen() {
	std::unique_ptr<Screen> screen = std::move(this->screens.at(this->screens.size() - 1));
	
	this->unsetupScreen(screen);

	this->screens.pop_back();

	return screen;
}

void ScreenManager::focusScreen(const ScreenPtr screen) {

}

void ScreenManager::focusScreenAt(const short index) {

}

void ScreenManager::showScreen(const ScreenPtr screen) {

}

void ScreenManager::hideScreen(const ScreenPtr screen) {

}

void ScreenManager::removeScreenAt(const short index) {

}

void ScreenManager::loadScreen(const ScreenPtr screen) {
	this->setupScreen(screen);
}

void ScreenManager::handleEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

bool ScreenManager::propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch/*=nullptr*/) {

}

void ScreenManager::setupScreen(const ScreenPtr screen) {
	screen->setupListeners();

	if (screen->is_modal) {
		//Prevent all other listeners, save current listeners state
	}
}

void ScreenManager::unsetupScreen(const ScreenPtr screen) {
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

Screen* Screen::LoadScreenFromJSON(rapidjson::Value& value) {
	std::string screenType = value["screen_type"].GetString();

	if (screenType == "main_menu") {
		return (Screen*)(new MenuScreen(value));
	}
	
	//Screen Type Not Implemented!
	return nullptr;
}

void Screen::fromJson(rapidjson::Value& value) {
	if (!value["positioning"].IsNull()) {
		std::string _positioning = toLowerCase(value["positioning"].GetString());

		if (_positioning == "block") {
			this->positioning = Screen::PositionTypes::BLOCK;
		}
		else if (_positioning == "overlay") {
			this->positioning = Screen::PositionTypes::OVERLAY;
		}
		else if (_positioning == "fixed") {
			this->positioning = Screen::PositionTypes::FIXED;
		}
	}

	if (!value["position"].IsNull()) {
		assert(value["position"].IsArray());
		this->position.x = value["position"][0].GetInt();
		this->position.y = value["position"][1].GetInt();
	}

	if (!value["size"].IsNull()) {
		assert(value["size"].IsArray());
		//Optimize This: Not really needed but this is gross
		this->size.width = cocos2d::Director::getInstance()->getVisibleSize().width * value["size"][0].GetDouble();
		this->size.height = cocos2d::Director::getInstance()->getVisibleSize().height * value["size"][1].GetDouble();
	}
}

DialogScreen::DialogScreen() {
	this->has_touch = true;
	this->has_mouse = true;
	this->has_keyboard = false;
}

short DialogScreen::load() {
	this->mouse_listener = cocos2d::EventListenerMouse::create();
	this->touch_listener = cocos2d::EventListenerTouchOneByOne::create();

	this->node = cocos2d::Node::create();

	this->dialogTitleLabel = cocos2d::Label::createWithTTF("Hello World This Is My House", "fonts/Marker Felt.ttf", 24);
}

void DialogScreen::setupListeners() {
	this->mouse_listener->onMouseDown = CC_CALLBACK_1(DialogScreen::onMouseDown, this);
	this->mouse_listener->onMouseUp = CC_CALLBACK_1(DialogScreen::onMouseUp, this);
	this->mouse_listener->onMouseMove = CC_CALLBACK_1(DialogScreen::onMouseMove, this);

	this->touch_listener->onTouchBegan = CC_CALLBACK_2(DialogScreen::onTouchBegan, this);
	this->touch_listener->onTouchMoved = CC_CALLBACK_2(DialogScreen::onTouchMoved, this);
	this->touch_listener->onTouchEnded = CC_CALLBACK_2(DialogScreen::onTouchEnded, this);
}

void DialogScreen::onMouseDown(cocos2d::Event* event) {

}

void DialogScreen::onMouseUp(cocos2d::Event* event) {

}

void DialogScreen::onMouseMove(cocos2d::Event* event) {

}

void DialogScreen::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void DialogScreen::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void DialogScreen::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

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

MenuScreen::MenuScreen(rapidjson::Value& value) {
	Screen::fromJson(value);

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

void Scene::loadSceneFromConf() {
	std::string fileData = "";

	std::string filePath = GNH_RESOURCE_PATH(this->configPath);

	readFileToStr(filePath, fileData);

	this->loadedJson.Parse(fileData.c_str());

	assert(this->loadedJson.IsObject());

	this->sceneName = this->loadedJson["handle"].GetString();

	assert(this->loadedJson["screens"].IsArray());
	rapidjson::Value& screens = this->loadedJson["screens"];

	for (rapidjson::SizeType i = 0; i < screens.Size(); i++) {
		std::unique_ptr<Screen> screen = std::make_unique<Screen>(Screen::LoadScreenFromJSON(screens[i]));
		this->loadedScreens.push_back(screen);
	}

	this->cocosScene = cocos2d::Scene::create();
}

void Scene::unload() {

}
