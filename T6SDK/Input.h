#pragma once
#include "StdInclude.h"
namespace T6SDK
{
	namespace Input
	{
		inline static bool BlankMenuOpened = false;
		
		inline static float MouseWheelDelta = 0.0f;
		static void PreventScoreboardOpen(bool state)
		{
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

		namespace Keys
		{
			inline static T6SDK::Input::InputKey TAB(T6SDK::Addresses::KeyboardKeysBase, 0x08);
			inline static T6SDK::Input::InputKey ENTER(T6SDK::Addresses::KeyboardKeysBase+0x0040, 0x0C);
			inline static T6SDK::Input::InputKey ESCAPE(T6SDK::Addresses::KeyboardKeysBase+0x0120, 0x1A);
			inline static T6SDK::Input::InputKey SPACE(T6SDK::Addresses::KeyboardKeysBase+0x0170, 0x1F);
			inline static T6SDK::Input::InputKey APOSTROPHE(T6SDK::Addresses::KeyboardKeysBase+0x01E0, 0x26);
			inline static T6SDK::Input::InputKey COMMA(T6SDK::Addresses::KeyboardKeysBase+0x0230, 0x2B);
			inline static T6SDK::Input::InputKey MINUS(T6SDK::Addresses::KeyboardKeysBase+ 0x0240, 0x2C);
			inline static T6SDK::Input::InputKey PERIOD(T6SDK::Addresses::KeyboardKeysBase+ 0x0250, 0x2D);
			inline static T6SDK::Input::InputKey QUESTIONMARK(T6SDK::Addresses::KeyboardKeysBase+ 0x0260, 0x2E);
			inline static T6SDK::Input::InputKey NUM_0(T6SDK::Addresses::KeyboardKeysBase+0x0270, 0x2F);
			inline static T6SDK::Input::InputKey NUM_1(T6SDK::Addresses::KeyboardKeysBase+0x0280, 0x30);
			inline static T6SDK::Input::InputKey NUM_2(T6SDK::Addresses::KeyboardKeysBase+0x0290, 0x31);
			inline static T6SDK::Input::InputKey NUM_3(T6SDK::Addresses::KeyboardKeysBase+0x02A0, 0x32);
			inline static T6SDK::Input::InputKey NUM_4(T6SDK::Addresses::KeyboardKeysBase+0x02B0, 0x33);
			inline static T6SDK::Input::InputKey NUM_5(T6SDK::Addresses::KeyboardKeysBase+0x02C0, 0x34);
			inline static T6SDK::Input::InputKey NUM_6(T6SDK::Addresses::KeyboardKeysBase+0x02D0, 0x35);
			inline static T6SDK::Input::InputKey NUM_7(T6SDK::Addresses::KeyboardKeysBase+0x02E0, 0x36);
			inline static T6SDK::Input::InputKey NUM_8(T6SDK::Addresses::KeyboardKeysBase+0x02F0, 0x37);
			inline static T6SDK::Input::InputKey NUM_9(T6SDK::Addresses::KeyboardKeysBase+0x0300, 0x38);
			inline static T6SDK::Input::InputKey SEMICOLON(T6SDK::Addresses::KeyboardKeysBase+0x0320, 0x3A);
			inline static T6SDK::Input::InputKey PLUS(T6SDK::Addresses::KeyboardKeysBase+0x0340, 0x3C);
			inline static T6SDK::Input::InputKey A(T6SDK::Addresses::KeyboardKeysBase+0x0580, 0x60);
			inline static T6SDK::Input::InputKey B(T6SDK::Addresses::KeyboardKeysBase+0x0590, 0x61);
			inline static T6SDK::Input::InputKey C(T6SDK::Addresses::KeyboardKeysBase+0x05A0, 0x62);
			inline static T6SDK::Input::InputKey D(T6SDK::Addresses::KeyboardKeysBase+0x05B0, 0x63);
			inline static T6SDK::Input::InputKey E(T6SDK::Addresses::KeyboardKeysBase+0x05C0, 0x64);
			inline static T6SDK::Input::InputKey F(T6SDK::Addresses::KeyboardKeysBase+0x05D0, 0x65);
			inline static T6SDK::Input::InputKey G(T6SDK::Addresses::KeyboardKeysBase+0x05E0, 0x66);
			inline static T6SDK::Input::InputKey H(T6SDK::Addresses::KeyboardKeysBase+0x05F0, 0x67);
			inline static T6SDK::Input::InputKey I(T6SDK::Addresses::KeyboardKeysBase+0x0600, 0x68);
			inline static T6SDK::Input::InputKey J(T6SDK::Addresses::KeyboardKeysBase+0x0610, 0x69);
			inline static T6SDK::Input::InputKey K(T6SDK::Addresses::KeyboardKeysBase+0x0620, 0x6A);
			inline static T6SDK::Input::InputKey L(T6SDK::Addresses::KeyboardKeysBase+0x0630, 0x6B);
			inline static T6SDK::Input::InputKey M(T6SDK::Addresses::KeyboardKeysBase+0x0640, 0x6C);
			inline static T6SDK::Input::InputKey N(T6SDK::Addresses::KeyboardKeysBase+0x0650, 0x6D);
			inline static T6SDK::Input::InputKey O(T6SDK::Addresses::KeyboardKeysBase+0x0660, 0x6E);
			inline static T6SDK::Input::InputKey P(T6SDK::Addresses::KeyboardKeysBase+0x0670, 0x6F);
			inline static T6SDK::Input::InputKey Q(T6SDK::Addresses::KeyboardKeysBase+0x0680, 0x70);
			inline static T6SDK::Input::InputKey R(T6SDK::Addresses::KeyboardKeysBase+0x0690, 0x71);
			inline static T6SDK::Input::InputKey S(T6SDK::Addresses::KeyboardKeysBase+0x06A0, 0x72);
			inline static T6SDK::Input::InputKey T(T6SDK::Addresses::KeyboardKeysBase+0x06B0, 0x73);
			inline static T6SDK::Input::InputKey U(T6SDK::Addresses::KeyboardKeysBase+0x06C0, 0x74);
			inline static T6SDK::Input::InputKey V(T6SDK::Addresses::KeyboardKeysBase+0x06D0, 0x75);
			inline static T6SDK::Input::InputKey W(T6SDK::Addresses::KeyboardKeysBase+0x06E0, 0x76);
			inline static T6SDK::Input::InputKey X(T6SDK::Addresses::KeyboardKeysBase+0x06F0, 0x77);
			inline static T6SDK::Input::InputKey Y(T6SDK::Addresses::KeyboardKeysBase+0x0700, 0x78);
			inline static T6SDK::Input::InputKey Z(T6SDK::Addresses::KeyboardKeysBase+0x0710, 0x79);
			inline static T6SDK::Input::InputKey TILDA(T6SDK::Addresses::KeyboardKeysBase+0x0750, 0x7D);
			inline static T6SDK::Input::InputKey BACKSPACE(T6SDK::Addresses::KeyboardKeysBase+0x0760, 0x7E);
			inline static T6SDK::Input::InputKey CAPSLOCK(T6SDK::Addresses::KeyboardKeysBase + 0x08E0, 0x96);
			inline static T6SDK::Input::InputKey UP(T6SDK::Addresses::KeyboardKeysBase + 0x0910, 0x99);
			inline static T6SDK::Input::InputKey DOWN(T6SDK::Addresses::KeyboardKeysBase + 0x0920, 0x9A);
			inline static T6SDK::Input::InputKey LEFT(T6SDK::Addresses::KeyboardKeysBase + 0x0930, 0x9B);
			inline static T6SDK::Input::InputKey RIGHT(T6SDK::Addresses::KeyboardKeysBase + 0x0940, 0x9C);
			inline static T6SDK::Input::InputKey ALT(T6SDK::Addresses::KeyboardKeysBase + 0x0950, 0x9D);
			inline static T6SDK::Input::InputKey CTRL(T6SDK::Addresses::KeyboardKeysBase + 0x0960, 0x9E);
			inline static T6SDK::Input::InputKey SHIFT(T6SDK::Addresses::KeyboardKeysBase + 0x0970, 0x9F);
			inline static T6SDK::Input::InputKey DELETE_KEY(T6SDK::Addresses::KeyboardKeysBase + 0x0990, 0xA1);
			inline static T6SDK::Input::InputKey PAGEDOWN(T6SDK::Addresses::KeyboardKeysBase + 0x09A0, 0xA2);
			inline static T6SDK::Input::InputKey PAGEUP(T6SDK::Addresses::KeyboardKeysBase + 0x09B0, 0xA3);
			inline static T6SDK::Input::InputKey HOME(T6SDK::Addresses::KeyboardKeysBase + 0x09C0, 0xA4);
			inline static T6SDK::Input::InputKey F1(T6SDK::Addresses::KeyboardKeysBase + 0x09E0, 0xA6);
			inline static T6SDK::Input::InputKey F2(T6SDK::Addresses::KeyboardKeysBase + 0x09F0, 0xA7);
			inline static T6SDK::Input::InputKey F3(T6SDK::Addresses::KeyboardKeysBase + 0x0A00, 0xA8);
			inline static T6SDK::Input::InputKey F4(T6SDK::Addresses::KeyboardKeysBase + 0x0A10, 0xA9);
			inline static T6SDK::Input::InputKey F5(T6SDK::Addresses::KeyboardKeysBase + 0x0A20, 0xAA);
			inline static T6SDK::Input::InputKey F6(T6SDK::Addresses::KeyboardKeysBase + 0x0A30, 0xAB);
			inline static T6SDK::Input::InputKey F7(T6SDK::Addresses::KeyboardKeysBase + 0x0A40, 0xAC);
			inline static T6SDK::Input::InputKey F8(T6SDK::Addresses::KeyboardKeysBase + 0x0A50, 0xAD);
			inline static T6SDK::Input::InputKey F9(T6SDK::Addresses::KeyboardKeysBase + 0x0A60, 0xAE);
			inline static T6SDK::Input::InputKey F10(T6SDK::Addresses::KeyboardKeysBase + 0x0A70, 0xAF);
			inline static T6SDK::Input::InputKey F11(T6SDK::Addresses::KeyboardKeysBase + 0x0A80, 0xB0);
			inline static T6SDK::Input::InputKey F12(T6SDK::Addresses::KeyboardKeysBase + 0x0A90, 0xB1);
			inline static T6SDK::Input::InputKey LMB(T6SDK::Addresses::KeyboardKeysBase + 0x0BF0, 0xC7);
			inline static T6SDK::Input::InputKey RMB(T6SDK::Addresses::KeyboardKeysBase + 0x0C00, 0xC8);
		}
	}
}