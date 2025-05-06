#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_KeyReactiveText
	{
		typedef void func(void);
	private:
		bool Clicked = false;
		bool Pressed = false;
		bool IsEnabled = true;
		uintptr_t Function = 0;
		RECT btnRect{};
		T6SDK::AnchorPoint anchorPoint{};
		float X = 0.0f;
		float Y = 0.0f;
		bool DrawRelative = false;
		int GridColumn = -1;
		int GridRow = -1;

	public:
		const char* Text{};
		T6SDK::Input::InputKey* key = 0;
		T6SDK::Input::InputKey* modifierKey = 0;

		/// <summary>
		/// Text on display that turns orange when the key is pressed or held.
		/// </summary>
		/// <param name="text">Text.</param>
		/// <param name="x">Horizontal position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="y">Vertical position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="key">Pointer to an InputKey.</param>
		/// <param name="modifierKey">Pointer to an InputKey that can be used as a modifier. Might be 0x00.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the selected keys are pressed. void func()</param>
		UI_KeyReactiveText(const char* text, float x, float y, bool drawRelative, T6SDK::Input::InputKey* key, T6SDK::Input::InputKey* modifierKey, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			X = x;
			Y = y;
			Function = function;
			this->anchorPoint = anchorPoint;
			this->key = key;
			this->modifierKey = modifierKey;
			DrawRelative = drawRelative;
		}
		/// <summary>
		/// Text on display that turns orange when the key is pressed or held.
		/// </summary>
		/// <param name="text">Text.</param>
		/// <param name="gridColumn">Number of one of 8 columns to take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows to take Y position from.</param>
		/// <param name="key">Pointer to an InputKey.</param>
		/// <param name="modifierKey">Pointer to an InputKey that can be used as a modifier. Might be 0x00.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the selected keys are pressed. void func()</param>
		UI_KeyReactiveText(const char* text, int gridColumn, int gridRow, T6SDK::Input::InputKey* key, T6SDK::Input::InputKey* modifierKey, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			Function = function;
			this->anchorPoint = anchorPoint;
			this->key = key;
			this->modifierKey = modifierKey;
		}
		UI_KeyReactiveText()
		{

		}
		void Draw()
		{
			if (T6SDK::Input::InputLockedByTextBoxDialog)
				return;
			if (!IsEnabled)
			{
				Clicked = false;
				Pressed = false;
			}
			bool successDraw = false;
			if (DrawRelative)
				successDraw = T6SDK::Drawing::DrawTextRelative(Text, X, Y, 1.1f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, coords.x, coords.y, 1.1f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			else
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, X, Y, 1.1f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);

			if (successDraw && IsEnabled)
			{
				if (modifierKey && key)
					Pressed = ((T6SDK::Input::InputKey*)modifierKey)->Hold() && ((T6SDK::Input::InputKey*)key)->IsAnyPressState();
				else if(key)
					Pressed = ((T6SDK::Input::InputKey*)key)->IsAnyPressState();
				if (Pressed)
				{
					if (Clicked == false)
					{
						//T6SDK::ConsoleLog::Log("Clicked!");
						Clicked = true;
						if (Function)
						{
							func* f = (func*)Function;
							f();
						}
					}
				}
				else
					Clicked = false;
			}
		}
		void Draw(bool isEnabled)
		{
			IsEnabled = isEnabled;
			Draw();
		}
	};
}