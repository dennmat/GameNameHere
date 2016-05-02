#pragma once
#ifndef _GNH__SCREEN_H_
#define _GNH__SCREEN_H_

#include "Util.h"

#include <json/document.h>

#include "cocos2d.h"

#include <map>
#include <vector>
#include <memory>
#include <string>
#include <cstdint>

namespace gnh {
	
	class Screen {
	public:
		enum class PositionTypes : std::uint8_t {FIXED, OVERLAY, BLOCK};

		PositionTypes positioning = Screen::PositionTypes::BLOCK;

		bool is_modal = false;
		bool is_visible = true;
		bool is_focused = false;

		cocos2d::Vec2 position;
		cocos2d::Size size;

		cocos2d::EventListenerTouchOneByOne* touch_listener = nullptr;
		cocos2d::EventListenerKeyboard* keyboard_listener = nullptr;
		cocos2d::EventListenerMouse* mouse_listener = nullptr;

		bool has_touch = true;
		bool has_keyboard = false;
		bool has_mouse = true;

		cocos2d::Node* node = nullptr;

		virtual short load();

		virtual void setupListeners();

		virtual void render()=0;
		virtual void update();
		virtual void input(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);

		virtual void focus();
		virtual void blur();

		virtual short unload();

		static Screen* LoadScreenFromJSON(rapidjson::Value& value);
		void fromJson(rapidjson::Value& value);

		virtual ~Screen(){};
	};

	class MenuScreen : protected Screen {
	public:
		MenuScreen();
		MenuScreen(rapidjson::Value& value);

		short load();

		void setupListeners();

		void render();
		void update();
		void input(cocos2d::Event* event, cocos2d::Touch* touch = nullptr);

		void focus();
		void blur();

		short unload();

		~MenuScreen();
	};

	class DialogScreen : protected Screen {
	private:
		//I think cocos cleans this up after it's added to a scene
		cocos2d::Label* dialogTitleLabel = nullptr;
	
	public:
		PositionTypes positioning = Screen::PositionTypes::OVERLAY;

		DialogScreen();

		short load();

		void setupListeners();

		void render();
		void update();
		void input(cocos2d::Event* event, cocos2d::Touch* touch = nullptr);

		void focus();
		void blur();

		//Mouse Events
		void onMouseDown(cocos2d::Event* event);
		void onMouseUp(cocos2d::Event* event);
		void onMouseMove(cocos2d::Event* event);

		//Touch Events
		void onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

		short unload();

		~DialogScreen();
	};

	class Scene {
	private:
		using ScreenList = std::vector<std::unique_ptr<Screen>>;
		using ScreenPtr = std::unique_ptr<Screen>&;

		std::string sceneName;
		std::string configPath;

		rapidjson::Document loadedJson;

		ScreenList loadedScreens; //These get handed off to ScreenManager
								  //so they really only live here immediately
								  //after a load
	
	public:
		cocos2d::Scene* cocosScene = nullptr;

		Scene();
		Scene(std::string configPath) : configPath(configPath) {}

		void loadSceneFromConf();

		void unload();

		~Scene() {}
	};

	class ScreenManager {
	private:
		using ScreenList = std::vector<std::unique_ptr<Screen>>;
		using ScreenPtr = std::unique_ptr<Screen>&;

		using SceneMap = std::map <std::string, std::unique_ptr<Scene>>;
		using ScenePtr = std::unique_ptr<Scene>&;

		std::string currentSceneKey;
		Scene* currentScene = nullptr;
		
		ScreenManager::SceneMap scenes;

		void exitScene();

		ScreenManager::ScreenList screens;

		void setupScreen(const ScreenPtr screen);
		void unsetupScreen(const ScreenPtr screen);

		void loadScreen(const ScreenPtr screen);

	public:
		ScreenManager();

		void loadScenes();
		void changeScene(std::string sceneName);

		short stackScreen(const ScreenPtr screen);
		std::unique_ptr<Screen> popScreen();

		void focusScreen(const ScreenPtr screen);
		void focusScreenAt(short index);

		void showScreen(const ScreenPtr screen);
		void hideScreen(const ScreenPtr screen);

		void removeScreenAt(const short index);

		void handleEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);
		bool propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);

		void update();
		void render();

		~ScreenManager();
	};

};

#endif