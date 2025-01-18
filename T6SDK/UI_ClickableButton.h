#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_ClickableButton
	{
		typedef void func(void);
	private:
		bool Hovered = false;
		bool Pressed = false;
		bool Clicked = false;
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
		const char* ToolTip = "";
		/// <summary>
		/// Just a clickable button.
		/// </summary>
		/// <param name="text">Text of the button.</param>
		/// <param name="x">Horizontal position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="y">Vertical position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the button is clicked. void func()</param>
		UI_ClickableButton(const char* text, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			X = x;
			Y = y;
			DrawRelative = drawRelative;
			Function = function;
			this->anchorPoint = anchorPoint;
		}
		/// <summary>
		/// Just a clickable button.
		/// </summary>
		/// <param name="text">Text of the button.</param>
		/// <param name="gridColumn">Number of one of 8 columns to take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows to take Y position from.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Pointer to a function that will be called when the button is clicked. void func()</param>
		UI_ClickableButton(const char* text, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			Function = function;
			this->anchorPoint = anchorPoint;
		}
		UI_ClickableButton()
		{

		}
	public:
		void Draw()
		{
			if (!IsEnabled)
			{
				Hovered = false;
				Pressed = false;
				Clicked = false;
			}
			bool successDraw = false;
			if (DrawRelative)
				successDraw = T6SDK::Drawing::DrawTextRelative(Text, X, Y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, coords.x, coords.y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			else
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, X, Y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			if (successDraw && IsEnabled)
			{
				if (T6SDK::Input::MousePosX() > (float)btnRect.left && T6SDK::Input::MousePosX() < (float)btnRect.right && T6SDK::Input::MousePosY() > (float)btnRect.top && T6SDK::Input::MousePosY() < (float)btnRect.bottom)
				{
					//T6SDK::ConsoleLog::Log("Hovered");
					Hovered = true;
					if (T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						Pressed = true;
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