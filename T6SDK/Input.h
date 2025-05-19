#pragma once
#include "StdInclude.h"
namespace T6SDK
{
	namespace Input
	{
		inline static bool InputLockedByTextBoxDialog = false;
		inline static bool BlankMenuOpened = false;
		
		inline static float MouseWheelDelta = 0.0f;
		static void PreventScoreboardOpen(bool state)
		{
			//T6SDK::Addresses::Patches::PreventDemoScoreboardOpen.IsActive = state;
			state ? T6SDK::Addresses::Patches::PreventDemoScoreboardOpen.Patch() : T6SDK::Addresses::Patches::PreventDemoScoreboardOpen.UnPatch();
		}
		static void SetInputLocked(bool state)
		{
			T6SDK::Addresses::IsInputLocked.Value() = state;
		}
		static bool IsInputLocked()
		{
			return T6SDK::Addresses::IsInputLocked.Value();
		}

		static void OpenBlankMenu()
		{
			if (InputLockedByTextBoxDialog)
				return;
			if (T6SDK::MAIN::DevConsoleOpened == true)
				return;
			T6SDK::InternalFunctions::UI_CloseAll();
			T6SDK::Addresses::DemoPlayback.Value()->DemoHudHidden = true;
			T6SDK::Addresses::DemoPlayback.Value()->GameHudHidden = true;
			T6SDK::Addresses::IsDemoPaused.Value() = true;
			T6SDK::InternalFunctions::Key_SetCatcher(17);
			SetInputLocked(true);
			BlankMenuOpened = true;
		}
		static void CloseBlankMenu()
		{
			if (InputLockedByTextBoxDialog)
				return;
			if (T6SDK::MAIN::DevConsoleOpened == true)
				return;
			T6SDK::Addresses::DemoPlayback.Value()->DemoHudHidden = false;
			T6SDK::Addresses::DemoPlayback.Value()->GameHudHidden = true;
			T6SDK::Addresses::IsDemoPaused.Value() = true;
			SetInputLocked(false);
			T6SDK::InternalFunctions::Key_SetCatcher(0);
			BlankMenuOpened = false;
		}
		static float MousePosX()
		{
			if(!T6SDK::Addresses::ScreenWidth.IsValid() || !T6SDK::Addresses::UiContext.IsValid())
				return 0.0f;
			return ((T6SDK::Addresses::ScreenWidth.Value() / 1280.0f) * T6SDK::Addresses::UiContext.Value().cursor.x) * 2.0f;
		}
		static float MousePosY()
		{
			if (!T6SDK::Addresses::ScreenHeight.IsValid() || !T6SDK::Addresses::UiContext.IsValid())
				return 0.0f;
			return ((T6SDK::Addresses::ScreenHeight.Value() / 960.0f) * T6SDK::Addresses::UiContext.Value().cursor.y) * 2.0f;
		}
		static T6SDK::Input::InputKey* GetKeyByCode(int code)
		{
			return (T6SDK::Input::InputKey*)T6SDK::MAIN::CharKeys[code];
		}
		namespace Keys
		{
			inline static T6SDK::Input::InputKey TAB(T6SDK::Addresses::KeyboardKeysBase, 0x08, '\t', '\t', false);
			inline static T6SDK::Input::InputKey ENTER(T6SDK::Addresses::KeyboardKeysBase+0x0040, 0x0C, '\r', '\r', false);
			inline static T6SDK::Input::InputKey ESCAPE(T6SDK::Addresses::KeyboardKeysBase+0x0120, 0x1A, '\x1B', '\x1B', false);
			inline static T6SDK::Input::InputKey SPACE(T6SDK::Addresses::KeyboardKeysBase+0x0170, 0x1F, ' ', ' ', true);
			inline static T6SDK::Input::InputKey APOSTROPHE(T6SDK::Addresses::KeyboardKeysBase+0x01E0, 0x26, '\'', '\"', true);
			inline static T6SDK::Input::InputKey COMMA(T6SDK::Addresses::KeyboardKeysBase+0x0230, 0x2B, ',', '<', true);
			inline static T6SDK::Input::InputKey MINUS(T6SDK::Addresses::KeyboardKeysBase+ 0x0240, 0x2C, '-', '_', true);
			inline static T6SDK::Input::InputKey PERIOD(T6SDK::Addresses::KeyboardKeysBase+ 0x0250, 0x2D, '.', '>', true);
			inline static T6SDK::Input::InputKey QUESTIONMARK(T6SDK::Addresses::KeyboardKeysBase + 0x0260, 0x2E, '/', '?', true);
			inline static T6SDK::Input::InputKey NUM_0(T6SDK::Addresses::KeyboardKeysBase+0x0270, 0x2F, '0', ')', true, std::string("NUM 0"), true);
			inline static T6SDK::Input::InputKey NUM_1(T6SDK::Addresses::KeyboardKeysBase+0x0280, 0x30, '1', '!', true, std::string("NUM 1"), true);
			inline static T6SDK::Input::InputKey NUM_2(T6SDK::Addresses::KeyboardKeysBase+0x0290, 0x31, '2', '@', true, std::string("NUM 2"), true);
			inline static T6SDK::Input::InputKey NUM_3(T6SDK::Addresses::KeyboardKeysBase+0x02A0, 0x32, '3', '#', true, std::string("NUM 3"), true);
			inline static T6SDK::Input::InputKey NUM_4(T6SDK::Addresses::KeyboardKeysBase+0x02B0, 0x33, '4', '$', true, std::string("NUM 4"), true);
			inline static T6SDK::Input::InputKey NUM_5(T6SDK::Addresses::KeyboardKeysBase+0x02C0, 0x34, '5', '%', true, std::string("NUM 5"), true);
			inline static T6SDK::Input::InputKey NUM_6(T6SDK::Addresses::KeyboardKeysBase+0x02D0, 0x35, '6', '^', true, std::string("NUM 6"), true);
			inline static T6SDK::Input::InputKey NUM_7(T6SDK::Addresses::KeyboardKeysBase+0x02E0, 0x36, '7', '&', true, std::string("NUM 7"), true);
			inline static T6SDK::Input::InputKey NUM_8(T6SDK::Addresses::KeyboardKeysBase+0x02F0, 0x37, '8', '*', true, std::string("NUM 8"), true);
			inline static T6SDK::Input::InputKey NUM_9(T6SDK::Addresses::KeyboardKeysBase+0x0300, 0x38, '9', '(', true, std::string("NUM 9"), true);
			inline static T6SDK::Input::InputKey SEMICOLON(T6SDK::Addresses::KeyboardKeysBase+0x0320, 0x3A, ';', ':', true);
			inline static T6SDK::Input::InputKey PLUS(T6SDK::Addresses::KeyboardKeysBase+0x0340, 0x3C, '=', '+', true);
			inline static T6SDK::Input::InputKey A(T6SDK::Addresses::KeyboardKeysBase+0x0580, 0x60, 'a', 'A', true, std::string("A"), true);
			inline static T6SDK::Input::InputKey B(T6SDK::Addresses::KeyboardKeysBase+0x0590, 0x61, 'b', 'B', true, std::string("B"), true);
			inline static T6SDK::Input::InputKey C(T6SDK::Addresses::KeyboardKeysBase+0x05A0, 0x62,	'c', 'C', true, std::string("C"), true);
			inline static T6SDK::Input::InputKey D(T6SDK::Addresses::KeyboardKeysBase+0x05B0, 0x63, 'd', 'D', true, std::string("D"), true);
			inline static T6SDK::Input::InputKey E(T6SDK::Addresses::KeyboardKeysBase+0x05C0, 0x64, 'e', 'E', true, std::string("E"), true);
			inline static T6SDK::Input::InputKey F(T6SDK::Addresses::KeyboardKeysBase+0x05D0, 0x65, 'f', 'F', true, std::string("F"), true);
			inline static T6SDK::Input::InputKey G(T6SDK::Addresses::KeyboardKeysBase+0x05E0, 0x66, 'g', 'G', true, std::string("G"), true);
			inline static T6SDK::Input::InputKey H(T6SDK::Addresses::KeyboardKeysBase+0x05F0, 0x67,	'h', 'H', true, std::string("H"), true);
			inline static T6SDK::Input::InputKey I(T6SDK::Addresses::KeyboardKeysBase+0x0600, 0x68, 'i', 'I', true, std::string("I"), true);
			inline static T6SDK::Input::InputKey J(T6SDK::Addresses::KeyboardKeysBase+0x0610, 0x69,	'j', 'J', true, std::string("J"), true);
			inline static T6SDK::Input::InputKey K(T6SDK::Addresses::KeyboardKeysBase+0x0620, 0x6A, 'k', 'J', true, std::string("K"), true);
			inline static T6SDK::Input::InputKey L(T6SDK::Addresses::KeyboardKeysBase+0x0630, 0x6B, 'l', 'L', true, std::string("L"), true);
			inline static T6SDK::Input::InputKey M(T6SDK::Addresses::KeyboardKeysBase+0x0640, 0x6C,	'm', 'M', true, std::string("M"), true);
			inline static T6SDK::Input::InputKey N(T6SDK::Addresses::KeyboardKeysBase+0x0650, 0x6D, 'n', 'N', true, std::string("N"), true);
			inline static T6SDK::Input::InputKey O(T6SDK::Addresses::KeyboardKeysBase+0x0660, 0x6E, 'o', 'O', true, std::string("O"), true);
			inline static T6SDK::Input::InputKey P(T6SDK::Addresses::KeyboardKeysBase+0x0670, 0x6F, 'p', 'P', true, std::string("P"), true);
			inline static T6SDK::Input::InputKey Q(T6SDK::Addresses::KeyboardKeysBase+0x0680, 0x70, 'q', 'Q', true, std::string("Q"), true);
			inline static T6SDK::Input::InputKey R(T6SDK::Addresses::KeyboardKeysBase+0x0690, 0x71, 'r', 'R', true, std::string("R"), true);
			inline static T6SDK::Input::InputKey S(T6SDK::Addresses::KeyboardKeysBase+0x06A0, 0x72, 's', 'S', true, std::string("S"), true);
			inline static T6SDK::Input::InputKey T(T6SDK::Addresses::KeyboardKeysBase+0x06B0, 0x73, 't', 'T', true, std::string("T"), true);
			inline static T6SDK::Input::InputKey U(T6SDK::Addresses::KeyboardKeysBase+0x06C0, 0x74, 'u', 'U', true, std::string("U"), true);
			inline static T6SDK::Input::InputKey V(T6SDK::Addresses::KeyboardKeysBase+0x06D0, 0x75, 'v', 'V', true, std::string("V"), true);
			inline static T6SDK::Input::InputKey W(T6SDK::Addresses::KeyboardKeysBase+0x06E0, 0x76, 'w', 'W', true, std::string("W"), true);
			inline static T6SDK::Input::InputKey X(T6SDK::Addresses::KeyboardKeysBase+0x06F0, 0x77, 'x', 'X', true, std::string("X"), true);
			inline static T6SDK::Input::InputKey Y(T6SDK::Addresses::KeyboardKeysBase+0x0700, 0x78, 'y', 'Y', true, std::string("Y"), true);
			inline static T6SDK::Input::InputKey Z(T6SDK::Addresses::KeyboardKeysBase+0x0710, 0x79, 'z', 'Z', true, std::string("Z"), true);
			inline static T6SDK::Input::InputKey TILDA(T6SDK::Addresses::KeyboardKeysBase+0x0750, 0x7D, '`', '~', false);
			inline static T6SDK::Input::InputKey BACKSPACE(T6SDK::Addresses::KeyboardKeysBase+0x0760, 0x7E, '\b', '\b', false);
			inline static T6SDK::Input::InputKey CAPSLOCK(T6SDK::Addresses::KeyboardKeysBase + 0x08E0, 0x96, '\0', '\0', false);
			inline static T6SDK::Input::InputKey UP(T6SDK::Addresses::KeyboardKeysBase + 0x0910, 0x99, '\0', '\0', false);
			inline static T6SDK::Input::InputKey DOWN(T6SDK::Addresses::KeyboardKeysBase + 0x0920, 0x9A, '\0', '\0', false);
			inline static T6SDK::Input::InputKey LEFT(T6SDK::Addresses::KeyboardKeysBase + 0x0930, 0x9B, '\0', '\0', false);
			inline static T6SDK::Input::InputKey RIGHT(T6SDK::Addresses::KeyboardKeysBase + 0x0940, 0x9C, '\0', '\0', false);
			inline static T6SDK::Input::InputKey ALT(T6SDK::Addresses::KeyboardKeysBase + 0x0950, 0x9D, '\0', '\0', false);
			inline static T6SDK::Input::InputKey CTRL(T6SDK::Addresses::KeyboardKeysBase + 0x0960, 0x9E, '\0', '\0', false);
			inline static T6SDK::Input::InputKey SHIFT(T6SDK::Addresses::KeyboardKeysBase + 0x0970, 0x9F, '\0', '\0', false);
			inline static T6SDK::Input::InputKey DELETE_KEY(T6SDK::Addresses::KeyboardKeysBase + 0x0990, 0xA1, '\0', '\0', false);
			inline static T6SDK::Input::InputKey PAGEDOWN(T6SDK::Addresses::KeyboardKeysBase + 0x09A0, 0xA2, '\0', '\0', false, std::string("PAGEDOWN"), true);
			inline static T6SDK::Input::InputKey PAGEUP(T6SDK::Addresses::KeyboardKeysBase + 0x09B0, 0xA3, '\0', '\0', false, std::string("PAGEUP"), true);
			inline static T6SDK::Input::InputKey HOME(T6SDK::Addresses::KeyboardKeysBase + 0x09C0, 0xA4, '\0', '\0', false, std::string("HOME"), true);
			inline static T6SDK::Input::InputKey F1(T6SDK::Addresses::KeyboardKeysBase + 0x09E0, 0xA6, '\0', '\0', false, std::string("F1"), true);
			inline static T6SDK::Input::InputKey F2(T6SDK::Addresses::KeyboardKeysBase + 0x09F0, 0xA7, '\0', '\0', false, std::string("F2"), true);
			inline static T6SDK::Input::InputKey F3(T6SDK::Addresses::KeyboardKeysBase + 0x0A00, 0xA8, '\0', '\0', false, std::string("F3"), true);
			inline static T6SDK::Input::InputKey F4(T6SDK::Addresses::KeyboardKeysBase + 0x0A10, 0xA9, '\0', '\0', false, std::string("F4"), true);
			inline static T6SDK::Input::InputKey F5(T6SDK::Addresses::KeyboardKeysBase + 0x0A20, 0xAA, '\0', '\0', false, std::string("F5"), true);
			inline static T6SDK::Input::InputKey F6(T6SDK::Addresses::KeyboardKeysBase + 0x0A30, 0xAB, '\0', '\0', false, std::string("F6"), true);
			inline static T6SDK::Input::InputKey F7(T6SDK::Addresses::KeyboardKeysBase + 0x0A40, 0xAC, '\0', '\0', false, std::string("F7"), true);
			inline static T6SDK::Input::InputKey F8(T6SDK::Addresses::KeyboardKeysBase + 0x0A50, 0xAD, '\0', '\0', false, std::string("F8"), true);
			inline static T6SDK::Input::InputKey F9(T6SDK::Addresses::KeyboardKeysBase + 0x0A60, 0xAE, '\0', '\0', false, std::string("F9"), true);
			inline static T6SDK::Input::InputKey F10(T6SDK::Addresses::KeyboardKeysBase + 0x0A70, 0xAF, '\0', '\0', false, std::string("F10"), true);
			inline static T6SDK::Input::InputKey F11(T6SDK::Addresses::KeyboardKeysBase + 0x0A80, 0xB0, '\0', '\0', false, std::string("F11"), true);
			inline static T6SDK::Input::InputKey F12(T6SDK::Addresses::KeyboardKeysBase + 0x0A90, 0xB1, '\0', '\0', false, std::string("F12"), true);
			inline static T6SDK::Input::InputKey LMB(T6SDK::Addresses::KeyboardKeysBase + 0x0BF0, 0xC7, '\0', '\0', false);
			inline static T6SDK::Input::InputKey RMB(T6SDK::Addresses::KeyboardKeysBase + 0x0C00, 0xC8, '\0', '\0', false);
		}
	}
}