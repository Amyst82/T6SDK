#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_CheckBoxButtonInversed
	{
		typedef void func(UI_CheckBoxButtonInversed*);
	private:
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

		bool internalCheckedValue = false;

	public:
		bool* isChecked = &internalCheckedValue;
		const char* UnCheckedText{};
		const char* CheckedText{};
		bool ValueReadOnly = false;
		const char* ToolTip = "";
		UI_CheckBoxButtonInversed()
		{

		}
		/// <summary>
		/// Check box.
		/// </summary>
		/// <param name="uncheckedtext">Text to display when in unchecked state.</param>
		/// <param name="checkedtext">Text to display when in checked state.</param>
		/// <param name="x">Horizontal position in pixels, otherwise relative to screen size if drawRelative is true.</param>
		/// <param name="y">Vertical position in pixels, otherwise relative to screen size if drawRelative is true.</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="value">Pointer to a bool value.</param>
		/// <param name="function"> Function to call when checked state is changed. void func(UI_CheckBoxButtonInversed*)</param>

		UI_CheckBoxButtonInversed(const char* uncheckedtext, const char* checkedtext, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, bool* value, uintptr_t function)
		{
			UnCheckedText = uncheckedtext;
			CheckedText = checkedtext;
			X = x;
			Y = y;
			Function = function;
			this->anchorPoint = anchorPoint;
			isChecked = value ? value : &internalCheckedValue;
			DrawRelative = drawRelative;
		}
		/// <summary>
		/// Check box.
		/// </summary>
		/// <param name="uncheckedtext">Text to display when in unchecked state.</param>
		/// <param name="checkedtext">Text to display when in checked state.</param>
		/// <param name="gridColumn">Number of one of 8 columns that the check box will take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows that the check box will take Y position from.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="value">Pointer to a bool value.</param>
		/// <param name="function"> Function to call when checked state is changed. void func(UI_CheckBoxButtonInversed*)</param>
		UI_CheckBoxButtonInversed(const char* uncheckedtext, const char* checkedtext, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, bool* value, uintptr_t function)
		{
			UnCheckedText = uncheckedtext;
			CheckedText = checkedtext;
			Function = function;
			GridColumn = gridColumn;
			GridRow = gridRow;
			this->anchorPoint = anchorPoint;
			isChecked = value ? value : &internalCheckedValue;
		}

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
				successDraw = T6SDK::Drawing::DrawTextRelative(*isChecked ? UnCheckedText : CheckedText, X, Y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : !*isChecked ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(*isChecked ? UnCheckedText : CheckedText, coords.x, coords.y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : !*isChecked ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
			}
			else
				successDraw = T6SDK::Drawing::DrawTextAbsolute(*isChecked ? UnCheckedText : CheckedText, X, Y, 1.5f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : !*isChecked ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : T6SDK::Drawing::WHITECOLOR, anchorPoint, &btnRect);
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
							if (!ValueReadOnly)
								*isChecked = !*isChecked;
							//T6SDK::ConsoleLog::LogFormatted(12, "Checked: %s", *isChecked ? "true" : "false");
							if (Function)
							{
								func* f = (func*)Function;
								f(this);
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