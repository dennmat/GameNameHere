#pragma once
#ifndef _GNH__MENU_SCENE_H_
#define _GNH__MENU_SCENE_H_

#include "Screen.h"

namespace gnh {

	class MenuScreen : protected Screen {
	private:

	public:
		cocos2d::Label* dialogTitleLabel = nullptr;
		MenuScreen();
		MenuScreen(rapidjson::Value& value);

		short load();

		void setupListeners();

		void render();
		void update();
		void input(cocos2d::Event* event, cocos2d::Touch* touch = nullptr);

		//Mouse Events
		void onMouseDown(cocos2d::Event* event);
		void onMouseUp(cocos2d::Event* event);
		void onMouseMove(cocos2d::Event* event);

		//Touch Events
		bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
		void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

		void focus();
		void blur();

		short unload();

		~MenuScreen();
	};

}

#endif