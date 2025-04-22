#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{

	class UI_RadioButton
	{
		typedef void func(UI_RadioButton*);
	private:
		bool Hovered = false;
		bool Pressed = false;
		bool Clicked = false;
		bool IsEnabled = true;
		int GroupIndex = 0;
		uintptr_t Function = 0;
		RECT btnRect{};
		T6SDK::AnchorPoint anchorPoint{};
		bool DrawRelative = false;
		int GridColumn = -1;
		int GridRow = -1;

		bool internalCheckedValue = false;

		float X = 0.0f;
		float Y = 0.0f;

	public:
		bool* isChecked = &internalCheckedValue;
		const char* Text{};
		const char* ToolTip = "";

		UI_RadioButton()
		{

		}
		/// <summary>
		/// Radio button.
		/// </summary>
		/// <param name="text">Text.</param>
		/// <param name="groupIndex">Index of a group of radio buttons/</param>
		/// <param name="x">Horizontal position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="y">Vertical position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">OnChecked function. void func(UI_RadioButton*)</param>
		UI_RadioButton(const char* text, int groupIndex, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			X = x;
			Y = y;
			Function = function;
			this->anchorPoint = anchorPoint;
			DrawRelative = drawRelative;
			this->GroupIndex = groupIndex;
			T6SDK::MAIN::RegisteredRadioButtons.push_back((uintptr_t)this);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "RADIO BUTTON", "Registered radio button: %s in group %i; Address: 0x%X; Total radio buttons registered: %i", text, groupIndex, (uintptr_t)this, T6SDK::MAIN::RegisteredRadioButtons.size());
		}
		/// <summary>
		/// Radio button.
		/// </summary>
		/// <param name="text">Text.</param>
		/// <param name="groupIndex">Index of a group of radio buttons/</param>
		/// <param name="gridColumn">Number of one of 8 columns that the radio button will take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows that the radio button will take Y position from.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">OnChecked function. void func(UI_RadioButton*)</param>
		UI_RadioButton(const char* text, int groupIndex, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Text = text;
			Function = function;
			this->anchorPoint = anchorPoint;
			GridColumn = gridColumn;
			GridRow = gridRow;
			this->GroupIndex = groupIndex;
			T6SDK::MAIN::RegisteredRadioButtons.push_back((uintptr_t)this);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "RADIO BUTTON", "Registered radio button: %s in group %i; Address: 0x%X; Total radio buttons registered: %i", text, groupIndex, (uintptr_t)this, T6SDK::MAIN::RegisteredRadioButtons.size());
		}
		void SetChecked()
		{
			if (*isChecked == false)
				*isChecked = true;

			//Radio behavior
			if (*isChecked)
			{
				for (int i = 0; i < T6SDK::MAIN::RegisteredRadioButtons.size(); i++)
				{
					if (T6SDK::MAIN::RegisteredRadioButtons[i] != (uintptr_t)this)
					{
						if (GroupIndex == ((UI_RadioButton*)T6SDK::MAIN::RegisteredRadioButtons[i])->GroupIndex)
						{
							*((UI_RadioButton*)T6SDK::MAIN::RegisteredRadioButtons[i])->isChecked = false;
						}
					}
				}
			}

			if (Function)
			{
				func* f = (func*)Function;
				f(this);
			}
		}
		void Draw()
		{
			if (!IsEnabled)
			{
				Hovered = false;
				Pressed = false;
				Clicked = false;
			}
			tColor* color{};
			if(*isChecked)
				color = &T6SDK::Drawing::ORANGECOLOR;
			else if (Hovered)
				color = &T6SDK::Drawing::YELLOWCOLOR;
			else if(!IsEnabled)
				color = &T6SDK::Drawing::GRAYCOLOR;
			else
				color = &T6SDK::Drawing::WHITECOLOR;

			bool successDraw = false;
			if (DrawRelative)
				successDraw = T6SDK::Drawing::DrawTextRelative(Text, X, Y, 1.5f, *color, anchorPoint, &btnRect);
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, coords.x, coords.y, 1.5f, *color, anchorPoint, &btnRect);
			}
			else
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, X, Y, 1.5f, *color, anchorPoint, &btnRect);

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
							SetChecked();
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