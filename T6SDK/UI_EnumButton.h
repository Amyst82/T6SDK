#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_EnumButton
	{
		typedef void func(int);
	private:
		bool hoverSoundPlayed = false;
		bool Hovered = false;
		bool Pressed = false;
		bool Clicked = false;
		bool IsEnabled = true;
		uintptr_t Function = 0;
		RECT btnRect{};
		T6SDK::AnchorPoint anchorPoint{};
		bool DrawRelative = false;
		int GridColumn = -1;
		int GridRow = -1;
		float X = 0.0f;
		float Y = 0.0f;
		int value = 0;
	public:
		const char* Text{};
		int* SelectedValue = &value;
		int MinValue = 0;
		int MaxValue = 0;
		const char* ToolTip = "";

		UI_EnumButton()
		{

		}
		/// <summary>
		/// Enum button with increase/decrease by 1 function.
		/// </summary>
		/// <param name="text">Text to be displayed. Leave empty to have default text ("Selected value: %i").</param>
		/// <param name="minValue">Minimum value.</param>
		/// <param name="maxValue">Maximum value.</param>
		/// <param name="value">Pointer to an int value. Might be 0x00. The control has its own internal value.</param>
		/// <param name="x">Horizontal position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="y">Vertical position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the button is clicked. void func(int)</param>
		UI_EnumButton(const char* text, int minValue, int maxValue, int* value, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			X = x;
			Y = y;
			if(value)
				SelectedValue = value;
			MinValue = minValue;
			MaxValue = maxValue;
			Function = function;
			this->anchorPoint = anchorPoint;
			DrawRelative = drawRelative;

		}
		/// <summary>
		/// Enum button with increase/decrease by 1 function.
		/// </summary>
		/// <param name="text">Text to be displayed. Leave empty to have default text ("Selected value: %i").</param>
		/// <param name="minValue">Minimum value.</param>
		/// <param name="maxValue">Maximum value.</param>
		/// <param name="value">Pointer to an int value. Might be 0x00. The control has its own internal value.</param>
		/// <param name="gridColumn">Number of one of 8 columns to take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows to take Y position from.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the button is clicked. void func(int)</param>
		UI_EnumButton(const char* text, int minValue, int maxValue, int* value, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			if (value)
				SelectedValue = value;
			MinValue = minValue;
			MaxValue = maxValue;
			Function = function;
			this->anchorPoint = anchorPoint;
		}
		
		void Draw()
		{
			if (T6SDK::Input::InputLockedByTextBoxDialog)
				return;
			const char* internalText = Text;
			if(strlen(Text) <= 1)
			{
				char buffer1[64];
				sprintf(buffer1, "Selected value: %i", *SelectedValue);
				internalText = buffer1;
			}
			char buffer[100];
			sprintf(buffer, "^7%s %s%s ^7%s", T6SDK::InternalFunctions::UI_SafeTranslateString("PLATFORM_FOLLOWNEXTPLAYER_MOUSE"), !IsEnabled ? "^9" : Pressed ? "^3" : Hovered ? "^3" : "^7", internalText, T6SDK::InternalFunctions::UI_SafeTranslateString("PLATFORM_FOLLOWPREVPLAYER_MOUSE"));
			internalText = buffer;
			if (!IsEnabled)
			{
				Hovered = false;
				Pressed = false;
				Clicked = false;
			}

			bool successDraw = false;
			if(DrawRelative)
			{
				successDraw = T6SDK::Drawing::DrawTextRelative(internalText, X, Y, 1.5f, T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(internalText, coords.x, coords.y, 1.5f, T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			else 
			{
				successDraw = T6SDK::Drawing::DrawTextAbsolute(internalText, X, Y, 1.5f, T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			if (successDraw && IsEnabled)
			{
				if (T6SDK::Input::MousePosX() > (float)btnRect.left && T6SDK::Input::MousePosX() < (float)btnRect.right && T6SDK::Input::MousePosY() > (float)btnRect.top && T6SDK::Input::MousePosY() < (float)btnRect.bottom)
				{
					//T6SDK::ConsoleLog::Log("Hovered");
					Hovered = true;
					if (hoverSoundPlayed == false)
					{
						T6SDK::InternalFunctions::PlaySound("uin_unlock_window");
						hoverSoundPlayed = true;
					}
					if (T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						Pressed = true;
						if (Clicked == false)
						{
							T6SDK::InternalFunctions::PlaySound("uin_main_pause");
							//T6SDK::ConsoleLog::Log("Clicked!");
							Clicked = true;
							if (*SelectedValue < MaxValue)
								(*SelectedValue)++;
							else
								(*SelectedValue) = MinValue;

							if (Function)
							{
								func* f = (func*)Function;
								f(*SelectedValue);
							}
						}
					}
					else if (T6SDK::Input::Keys::RMB.IsAnyPressState())
					{
						Pressed = true;
						if (Clicked == false)
						{
							//T6SDK::ConsoleLog::Log("Clicked!");
							Clicked = true;
							if (*SelectedValue > MinValue)
								(*SelectedValue)--;
							else
								(*SelectedValue) = MaxValue;

							if (Function)
							{
								func* f = (func*)Function;
								f(*SelectedValue);
							}
						}
					}
					else
					{
						Pressed = false;
						Clicked = false;
					}
					if (strlen(ToolTip) > 1)
					{
						T6SDK::Drawing::ShowToolTip(ToolTip);
					}
				}
				else
				{
					Hovered = false;
					Pressed = false;
					Clicked = false;
				}
			}
			
		}

		void Draw(bool isEnabled)
		{
			IsEnabled = isEnabled;
			Draw();
		}
	};
}