#include "Screen.h"

#include "Scenes/MenuScene.h"
#include "Scenes/GameScene.h"

using namespace gnh;

ScreenManager::ScreenManager() {}

void ScreenManager::loadScenes() {
	rapidjson::Document document;

	std::string sceneRawData = "";
	std::string sceneDataPath = "scenes/scenes.json";

	readFileToStr(GNH_RESOURCE_PATH(sceneDataPath), sceneRawData);

	document.Parse(sceneRawData.c_str());

	cocos2d::log("Pre Assert Scenes Array");
	assert(document.IsArray());
	cocos2d::log("Post Assert Scenes Array");

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
	this->screens.empty();
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

	for (auto& screen : this->currentScene->loadedScreens) {
		screen->load();
		this->currentScene->cocosScene->addChild(screen->node);

		this->screens.push_back(std::move(screen));
		screen.reset(nullptr);
	}

	if (director->getRunningScene() != nullptr) {
		cocos2d::log("Replacing Scene...\n");
		director->replaceScene(this->currentScene->cocosScene);
	} else {
		cocos2d::log("New Scene...\n");
		director->runWithScene(this->currentScene->cocosScene);
	}
}

short ScreenManager::stackScreen(const ScreenPtr screen) {
	this->screens.push_back(std::move(screen));

	return 1;
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
	return true;
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
	else if (screenType == "game") {
		return (Screen*)(new GameScreen(value));
	}
	
	//Screen Type Not Implemented!
	return nullptr;
}

void Screen::fromJson(rapidjson::Value& value) {
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	if (value.HasMember("positioning")) {
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

	if (value.HasMember("position")) {
		assert(value["position"].IsArray());
		this->position.x = visibleSize.width * value["position"][0].GetInt();
		this->position.y = visibleSize.height - visibleSize.height * value["position"][1].GetInt();
	}

	if (value.HasMember("size")) {
		assert(value["size"].IsArray());
		//Optimize This: Not really needed but this is gross
		this->size.width = visibleSize.width * value["size"][0].GetDouble();
		this->size.height = visibleSize.height * value["size"][1].GetDouble();
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
	this->dialogTitleLabel->setPosition(cocos2d::Vec2::ZERO);// this->position);
	this->dialogTitleLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->node->addChild(this->dialogTitleLabel);

	return 1;
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

bool DialogScreen::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	return true;
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
	return 1;
}

DialogScreen::~DialogScreen() {

}

void Scene::loadSceneFromConf() {
	std::string fileData = "";

	std::string filePath = GNH_RESOURCE_PATH(this->configPath);

	readFileToStr(filePath, fileData);

	this->loadedJson.Parse(fileData.c_str());

	assert(this->loadedJson.IsObject());

	this->sceneName = this->loadedJson["handle"].GetString();

	assert(this->loadedJson["default_screens"].IsArray());
	rapidjson::Value& screens = this->loadedJson["default_screens"];

	this->loadedScreens.clear();

	for (rapidjson::SizeType i = 0; i < screens.Size(); i++) {
		std::unique_ptr<Screen> screen{ std::move(Screen::LoadScreenFromJSON(screens[i])) };

		if (screen == nullptr) {
			continue;
		}

		this->loadedScreens.push_back(std::move(screen));
	}

	this->cocosScene = cocos2d::Scene::create();
}

void Scene::unload() {

}
