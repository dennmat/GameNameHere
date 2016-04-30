#pragma once
#ifndef _GNH__SCREEN_H_
#define _GNH__SCREEN_H_

#include "cocos2d.h"

#include <vector>

namespace gnh {
	
	class Screen {
	public:
		bool is_modal = false;
		bool is_visible = true;
		bool is_focused = false;

		cocos2d::Vec2 position;
		cocos2d::Vec2 size;

		virtual short load();

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

		void render();
		void update();
		void input(cocos2d::Event* event, cocos2d::Touch* touch = nullptr);

		void focus();
		void blur();

		short unload();

		~DialogScreen();
	};


	class ScreenManager {
	private:
		typedef std::vector<Screen> ScreenList;
		typedef ScreenList::iterator ScreenListIt;

		ScreenManager::ScreenList screens;

	public:
		ScreenManager();

		short stackScreen(const Screen* screen);
		const Screen& popScreen();

		void focusScreen(Screen& screen);
		void focusScreenAt(const short index);

		void showScreen(Screen& screen);
		void hideScreen(Screen& screen);

		void removeScreenAt(const short index);
		void loadScreen(Screen& screen);

		void handleEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);
		bool propagateEvent(cocos2d::Event* event, cocos2d::Touch* touch=nullptr);

		~ScreenManager();
	};

};

#endif