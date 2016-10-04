/*******************************************************************************
 * Open Settlers - A Game Engine to run the Settlers 1-4
 * Copyright (C) 2016   Gary The Brown
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; ONLY version 2
 * of the License.
 *******************************************************************************/

#pragma once

#include <utility>
namespace SystemInterface {
	class Events {
	protected:
		std::pair<int,int> windowResizeSize = {0,0};
	public:
		enum eKeyboardMod{
			KEYBOARDMOD_NONE = 0x0000,
			KEYBOARDMOD_LSHIFT = 0x0001,
			KEYBOARDMOD_RSHIFT = 0x0002,
			KEYBOARDMOD_LCTRL = 0x0040,
			KEYBOARDMOD_RCTRL = 0x0080,
			KEYBOARDMOD_LALT = 0x0100,
			KEYBOARDMOD_RALT = 0x0200,
			KEYBOARDMOD_LGUI = 0x0400,
			KEYBOARDMOD_RGUI = 0x0800,
			KEYBOARDMOD_NUM = 0x1000,
			KEYBOARDMOD_CAPS = 0x2000,
			KEYBOARDMOD_MODE = 0x4000,
			KEYBOARDMOD_RESERVED = 0x8000,
			KEYBOARDMOD_CTRL = (KEYBOARDMOD_LCTRL|KEYBOARDMOD_RCTRL),
			KEYBOARDMOD_SHIFT = (KEYBOARDMOD_LSHIFT|KEYBOARDMOD_RSHIFT),
			KEYBOARDMOD_ALT = (KEYBOARDMOD_LALT|KEYBOARDMOD_RALT),
			KEYBOARDMOD_GUI = (KEYBOARDMOD_LGUI|KEYBOARDMOD_RGUI)
		};
		//CONTROLS
		enum eKeyboardKey{
			KEYBOARD_UNKNOWN = 0,

			KEYBOARD_A = 4,
			KEYBOARD_B = 5,
			KEYBOARD_C = 6,
			KEYBOARD_D = 7,
			KEYBOARD_E = 8,
			KEYBOARD_F = 9,
			KEYBOARD_G = 10,
			KEYBOARD_H = 11,
			KEYBOARD_I = 12,
			KEYBOARD_J = 13,
			KEYBOARD_K = 14,
			KEYBOARD_L = 15,
			KEYBOARD_M = 16,
			KEYBOARD_N = 17,
			KEYBOARD_O = 18,
			KEYBOARD_P = 19,
			KEYBOARD_Q = 20,
			KEYBOARD_R = 21,
			KEYBOARD_S = 22,
			KEYBOARD_T = 23,
			KEYBOARD_U = 24,
			KEYBOARD_V = 25,
			KEYBOARD_W = 26,
			KEYBOARD_X = 27,
			KEYBOARD_Y = 28,
			KEYBOARD_Z = 29,

			KEYBOARD_1 = 30,
			KEYBOARD_2 = 31,
			KEYBOARD_3 = 32,
			KEYBOARD_4 = 33,
			KEYBOARD_5 = 34,
			KEYBOARD_6 = 35,
			KEYBOARD_7 = 36,
			KEYBOARD_8 = 37,
			KEYBOARD_9 = 38,
			KEYBOARD_0 = 39,

			KEYBOARD_RETURN = 40,
			KEYBOARD_ESCAPE = 41,
			KEYBOARD_BACKSPACE = 42,
			KEYBOARD_TAB = 43,
			KEYBOARD_SPACE = 44,

			KEYBOARD_MINUS = 45,
			KEYBOARD_EQUALS = 46,
			KEYBOARD_LEFTBRACKET = 47,
			KEYBOARD_RIGHTBRACKET = 48,
			KEYBOARD_BACKSLASH = 49,
			KEYBOARD_HASH = 50,  //# not on us keyboard
			KEYBOARD_SEMICOLON = 51,
			KEYBOARD_APOSTROPHE = 52,
			KEYBOARD_GRAVE = 53,
			KEYBOARD_COMMA = 54,
			KEYBOARD_PERIOD = 55,
			KEYBOARD_SLASH = 56,

			KEYBOARD_CAPSLOCK = 57,

			KEYBOARD_F1 = 58,
			KEYBOARD_F2 = 59,
			KEYBOARD_F3 = 60,
			KEYBOARD_F4 = 61,
			KEYBOARD_F5 = 62,
			KEYBOARD_F6 = 63,
			KEYBOARD_F7 = 64,
			KEYBOARD_F8 = 65,
			KEYBOARD_F9 = 66,
			KEYBOARD_F10 = 67,
			KEYBOARD_F11 = 68,
			KEYBOARD_F12 = 69,

			KEYBOARD_PRINTSCREEN = 70,
			KEYBOARD_SCROLLLOCK = 71,
			KEYBOARD_PAUSE = 72,
			KEYBOARD_INSERT = 73,
			KEYBOARD_HOME = 74,
			KEYBOARD_PAGEUP = 75,
			KEYBOARD_DELETE = 76,
			KEYBOARD_END = 77,
			KEYBOARD_PAGEDOWN = 78,
			KEYBOARD_RIGHT = 79,
			KEYBOARD_LEFT = 80,
			KEYBOARD_DOWN = 81,
			KEYBOARD_UP = 82,

			KEYBOARD_NUMLOCK = 83,
			KEYPAD_DIVIDE = 84,
			KEYPAD_MULTIPLY = 85,
			KEYPAD_MINUS = 86,
			KEYPAD_PLUS = 87,
			KEYPAD_ENTER = 88,
			KEYPAD_1 = 89,
			KEYPAD_2 = 90,
			KEYPAD_3 = 91,
			KEYPAD_4 = 92,
			KEYPAD_5 = 93,
			KEYPAD_6 = 94,
			KEYPAD_7 = 95,
			KEYPAD_8 = 96,
			KEYPAD_9 = 97,
			KEYPAD_0 = 98,
			KEYPAD_PERIOD = 99,
			KEYBOARD_NONUSBACKSLASH = 100,
			KEYBOARD_APPLICATION = 101
		};

		enum eMouseButton{MBNone,MouseButtonLeft,MouseButtonMiddle,MouseButtonRight};
		enum eEvent{eNone,eQuit,eWindow,eWindowResized,eWindowMinimized,eWindowMaximized,eWindowRestored,eKeyboardDown,eKeyboardUp,eMouseMotion,eMouseButtonDown,eMouseButtonUp,eMouseWheel};
		Events(){};
		virtual ~Events(){};

		virtual bool GetNextEvent() = 0;
		virtual eEvent GetEvent() = 0;
		virtual eKeyboardKey GetKey() = 0;
		virtual eKeyboardMod GetKeyMod() = 0;
		virtual eMouseButton GetMouseButton() = 0;
		virtual std::pair<int,int> GetMouseLocation() = 0;



		std::pair<int,int> GetResizedWindowSize(){return this->windowResizeSize;}
	};
}
