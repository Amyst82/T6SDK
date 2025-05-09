#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_TextBoxDialog
	{
	private:
		//okbutton
		bool OkHoverSoundPlayed = false;
		bool OkHovered = false;
		bool OkPressed = false;
		bool OkClicked = false;
		RECT okBtnRect{};
		//cancel button
		bool CancelHoverSoundPlayed = false;
		bool CancelHovered = false;
		bool CancelPressed = false;
		bool CancelClicked = false;
		RECT cancelBtnRect{};

		std::function<void(std::string)> OkFunction;
		bool isShown = false;
		std::string Text{};
		const char* Title{};
		T6SDK::AnchorPoint anchorPoint{};
		uintptr_t Function = 0;
		RECT baseRect{};
		RECT textBoxRect{};
		RECT textRect{};

		inline static float CaretBlink = 1.0f;
		inline static bool CaretBlinkDirectionTowards = false;
		inline static int CaretIndex = 0;
		inline static float charWidth = 8.0f;

	public:
		#pragma region Constructors
		UI_TextBoxDialog(const char* title)
		{
			Title = title;
		}
		UI_TextBoxDialog()
		{
		}
#pragma endregion
		void OnInputKey(BYTE key)
		{
			if (!T6SDK::MAIN::ENABLED)
				return;
			//Getting InputKey by key
			T6SDK::Input::InputKey* keyPointer = 0x00;
			try
			{
				keyPointer = (T6SDK::Input::InputKey*)T6SDK::MAIN::CharKeys[key];
			}
			catch (const char* errorMessage)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "TEXTBOXDIALOG", errorMessage);
				keyPointer = 0x00;
			}
			if (!keyPointer)
				return;
			if (!isShown)
				return;
			if (key == T6SDK::Input::Keys::LEFT.KeyCode) // Left
			{
				if (CaretIndex > 0)
					CaretIndex--;
			}
			if (key == T6SDK::Input::Keys::RIGHT.KeyCode) // Right
			{
				if (CaretIndex < Text.length())
					CaretIndex++;
			}
			if (key == T6SDK::Input::Keys::ESCAPE.KeyCode) // Escape
			{
				isShown = false;
				T6SDK::Input::InputLockedByTextBoxDialog = false;
			}
			if (keyPointer->KeyChar == '\b' && !Text.empty()) // Backspace
			{
				if (CaretIndex > 0)
				{
					Text.erase(CaretIndex - 1, 1);
					CaretIndex--;
				}
			}
			if (key == T6SDK::Input::Keys::DELETE_KEY.KeyCode && !Text.empty()) // Delete
			{
				if (CaretIndex < Text.length())
				{
					Text.erase(CaretIndex, 1);
				}
			}
			else if (keyPointer->KeyChar == '\r') // Enter
			{
				if (OkFunction)
					OkFunction(Text);
				else
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "TEXTBOXDIALOG", "OkFunction is not set!");
				CaretIndex = 0;
				isShown = false;
				T6SDK::Input::InputLockedByTextBoxDialog = false;
			}

			else if (keyPointer->Printable)
			{
				float textRectWidth = (float)textRect.right - (float)textRect.left;
				if (textRectWidth > (float)textBoxRect.right - (float)textBoxRect.left-10.0f)
					return;
				if (keyPointer->KeyChar == 'c') //for copy
				{
					if (T6SDK::Input::Keys::CTRL.Hold())
					{
						if (Text.empty())
							return;
						T6SDK::InternalFunctions::SetClipboardText(Text);
						T6SDK::MAIN::UI_ShowNotification("DIALOG", "^2Copied to clipboard", 200);
						return;
					}
				}
				if (keyPointer->KeyChar == 'v') //for pasting
				{
					if (T6SDK::Input::Keys::CTRL.Hold())
					{
						if (T6SDK::InternalFunctions::GetClipboardText().empty())
							return;
						Text = T6SDK::InternalFunctions::GetClipboardText();
						CaretIndex = Text.length();
						return;
					}
				}
				//If uppercase
				if (T6SDK::Input::Keys::SHIFT.IsAnyPressState())
					Text += std::toupper(keyPointer->UpperCasedKeyChar);
				else
					Text += keyPointer->KeyChar;
				CaretIndex = Text.length();
			}
		}

		void Draw()
		{
			if (!T6SDK::MAIN::ENABLED)
				return;
			if (!isShown)
				return;
			//Drawing fullscreen background
			T6SDK::Drawing::DrawRectRelative(0.0f, 0.0f, 1.0f, 1.0f, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
			//Drawing dialog box
			T6SDK::Drawing::DrawRectRelative(0.5f, 0.5f, 0.4f, 0.1f, T6SDK::Drawing::TRANSPARENTCOLOR, T6SDK::AnchorPoint::Center, &baseRect); //Getting base rect to place textbox and etc inside
			//Drawing title
			T6SDK::Drawing::DrawTextAbsolute(Title, (float)baseRect.left + 5.0f, (float)baseRect.top + 2.0f, 1.0f, T6SDK::Drawing::GRAYCOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
			float scale = 1.5f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
			float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
			//Drawing textbox border
			T6SDK::Drawing::DrawRectAbsolute((float)baseRect.left + 5.0f, (float)baseRect.top + h + 5.0f, (float)baseRect.right - (float)baseRect.left - 10.0f, h+5.0f, T6SDK::Drawing::GRAYCOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
			//Drawing textbox
			T6SDK::Drawing::DrawRectAbsolute((float)baseRect.left + 6.0f, (float)baseRect.top + h + 6.0f, (float)baseRect.right - (float)baseRect.left - 12.0f, h+3.0f, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopLeft, &textBoxRect);
			//Drawing text

			T6SDK::Drawing::DrawTextAbsolute(Text.c_str(), (float)textBoxRect.left + 5.0f, (float)textBoxRect.top + 2.0f, 1.5f, T6SDK::Drawing::WHITECOLOR, T6SDK::AnchorPoint::TopLeft, &textRect);
			charWidth = ((float)textRect.right - (float)textRect.left)/(float)Text.length();
			if (charWidth < 0.0f)
				charWidth = 0.0f;
			
			//Drawing caret
			float blinkDuration = 50.0f;

			if (CaretBlinkDirectionTowards)//increase opacity
			{
				CaretBlink += (1.0f / blinkDuration);
				if (CaretBlink >= 1.0f)
				{
					CaretBlink = 1.0f;
					CaretBlinkDirectionTowards = false;
				}
			}
			else //decrease opacity
			{
				CaretBlink -= (1.0f / blinkDuration);
				if (CaretBlink <= 0.0f)
				{
					CaretBlink = 0.0f;
					CaretBlinkDirectionTowards = true;
				}
			}
			float x = textBoxRect.left + 5.0f + CaretIndex * charWidth;
			if(std::isinf(x) || std::isnan(x))
				x = textBoxRect.left + 5.0f;
			float y = textBoxRect.top + 5.0f;
			//T6SDK::ConsoleLog::LogSameLineFormatted("CaretIndex: %i, x: %.3f", CaretIndex, x);
			T6SDK::Drawing::DrawRectAbsolute(x, y, 2.0f, h-8.0f, tColor{ 1.0f, 1.0f, 1.0f, CaretBlink }, T6SDK::AnchorPoint::TopLeft, 0x00);

			//Draw ok button
			float okButtonWidth = (float)T6SDK::InternalFunctions::R_TextWidth("OK", 2, T6SDK::Drawing::normalFont) * 1.5f;
			if (T6SDK::Drawing::DrawTextAbsolute("OK", (float)textBoxRect.right - okButtonWidth, (float)textBoxRect.bottom + 5.0f, 1.5f, OkPressed ? T6SDK::Drawing::ORANGECOLOR : OkHovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &okBtnRect))
			{
				if (T6SDK::Input::MousePosX() > (float)okBtnRect.left && T6SDK::Input::MousePosX() < (float)okBtnRect.right && T6SDK::Input::MousePosY() > (float)okBtnRect.top && T6SDK::Input::MousePosY() < (float)okBtnRect.bottom)
				{
					//T6SDK::ConsoleLog::Log("Hovered");
					OkHovered = true;
					if (OkHoverSoundPlayed == false)
					{
						T6SDK::InternalFunctions::PlaySound("uin_unlock_window");
						OkHoverSoundPlayed = true;
					}
					if (T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						OkPressed = true;
						if (OkClicked == false)
						{
							//T6SDK::ConsoleLog::Log("Clicked!");
							OkClicked = true;
							T6SDK::InternalFunctions::PlaySound("uin_main_pause");
							if (OkFunction)
								OkFunction(Text);
							isShown = false;
							CaretIndex = 0;
							T6SDK::Input::InputLockedByTextBoxDialog = false;
						}
					}
					else
					{
						OkPressed = false;
						OkClicked = false;
					}
				}
				else
				{
					OkHoverSoundPlayed = false;
					OkHovered = false;
					OkPressed = false;
					OkClicked = false;
				}
			}

			//Drawing cancel button
			if (T6SDK::Drawing::DrawTextAbsolute("CANCEL", (float)textBoxRect.left, (float)textBoxRect.bottom + 5.0f, 1.5f, CancelPressed ? T6SDK::Drawing::ORANGECOLOR : CancelHovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &cancelBtnRect))
			{
				if (T6SDK::Input::MousePosX() > (float)cancelBtnRect.left && T6SDK::Input::MousePosX() < (float)cancelBtnRect.right && T6SDK::Input::MousePosY() > (float)cancelBtnRect.top && T6SDK::Input::MousePosY() < (float)cancelBtnRect.bottom)
				{
					//T6SDK::ConsoleLog::Log("Hovered");
					CancelHovered = true;
					if (CancelHoverSoundPlayed == false)
					{
						T6SDK::InternalFunctions::PlaySound("uin_unlock_window");
						CancelHoverSoundPlayed = true;
					}
					if (T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						CancelPressed = true;
						if (CancelClicked == false)
						{
							//T6SDK::ConsoleLog::Log("Clicked!");
							CancelClicked = true;
							T6SDK::InternalFunctions::PlaySound("uin_main_pause");
							isShown = false;
							T6SDK::Input::InputLockedByTextBoxDialog = false;
						}
					}
					else
					{
						CancelPressed = false;
						CancelClicked = false;
					}
				}
				else
				{
					CancelHoverSoundPlayed = false;
					CancelHovered = false;
					CancelPressed = false;
					CancelClicked = false;
				}
			}

		}
		void Show(std::function<void(std::string)> OkFunc)
		{
			Text = "";
			this->isShown = true;
			this->OkFunction = OkFunc;
			T6SDK::Input::InputLockedByTextBoxDialog = true;
		}
	};
}