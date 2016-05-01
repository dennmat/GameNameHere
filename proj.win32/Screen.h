#pragma once
#ifndef _GNH__SCREEN_H_
#define _GNH__SCREEN_H_

#include "cocos2d.h"

#include <vector>
#include <memory>

namespace gnh {
	
	class Screen {
	public:
		bool is_modal = false;
		bool is_visible = true;
		bool is_focused = false;

		cocos2d::Vec2 position;
		cocos2d::Vec2 size;

		cocos2d::EventListenerTouchOneByOne* touch_listener = nullptr;
		cocos2d::EventListenerKeyboard* keyboard_listener = nullptr;
		cocos2d::EventListenerMouse* mouse_listener = nullptr;

		bool has_touch = true;
		bool has_keyboard = false;
		bool has_mouse = true;

		virtual short load();

		virtual void setupListeners();

		virtual void render()=0;
		virtual void update();
		virtual void input(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);

		virtual void focus();
		virtual void blur();

		virtual short unload();

		virtual ~Screen(){};
	};

	class MenuScreen : protected Screen {
	public:
		MenuScreen();

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
	public:
		DialogScreen();

		short load();

		void setupListeners();

		void render();
		void update();
		void input(cocos2d::Event* event, cocos2d::Touch* touch = nullptr);

		void focus();
		void blur();

		//Mouse Events
		void onMouseDown(const cocos2d::Event* event);
		void onMouseUp(const cocos2d::Event* event);
		void onMouseMove(const cocos2d::Event* event);

		//Touch Events
		void onTouchBegan(const cocos2d::Touch* touch, const cocos2d::Event* event);
		void onTouchMoved(const cocos2d::Touch* touch, const cocos2d::Event* event);
		void onTouchEnded(const cocos2d::Touch* touch, const cocos2d::Event* event);

		short unload();

		~DialogScreen();
	};


	class ScreenManager {
	private:
		using ScreenList = std::vector<std::unique_ptr<Screen>>;

		ScreenManager::ScreenList screens;

		void setupScreen(Screen* screen);
		void unsetupScreen(const std::unique_ptr<Screen>& screen);

		void loadScreen(Screen* screen);

	public:
		ScreenManager();

		short stackScreen(std::unique_ptr<Screen> screen);
		std::unique_ptr<Screen> popScreen();

		void focusScreen(Screen* screen);
		void focusScreenAt(short index);

		void showScreen(Screen* screen);
		void hideScreen(Screen* screen);

		void removeScreenAt(const short index);

		void handleEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);
		bool propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);

		void update();
		void render();

		~ScreenManager();
	};

};

#endif