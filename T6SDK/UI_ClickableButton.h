#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_ClickableButton
	{
		typedef void func(void);
	private:

		float fadingX = 0.0f;
		bool hoverSoundPlayed = false;
		std::function<void()> OkFunction;
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
		bool cyclingFading = false;
		float Size = 1.5f;
		const char* Text{};
		const char* ToolTip = "";

		float* GetFadingColor(tColor color)
		{
			if (!cyclingFading)
				return color;
			float A = 0.5f;
			float k = 1.6f;
			float w = 0.8f;
			float R = color[0];
			float G = color[1];
			float B = color[2];
			float coef = (A * tanh(k * sin(w * fadingX)) / tanh(k)) + 0.5f;
			float Alpha = 0.5f + (0.5f * coef);
			return tColor{ R, G, B, Alpha };
		}

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
		UI_ClickableButton(const char* text, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, std::function<void()> OkFunc)
		{
			Text = text;
			X = x;
			Y = y;
			DrawRelative = drawRelative;
			this->OkFunction = OkFunc;
			this->Function = 0;
			this->anchorPoint = anchorPoint;
		}
		UI_ClickableButton(const char* text, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, uintptr_t function, bool cyclingFading)
		{
			Text = text;
			X = x;
			Y = y;
			DrawRelative = drawRelative;
			Function = function;
			this->anchorPoint = anchorPoint;
			this->cyclingFading = cyclingFading;
		}
		UI_ClickableButton(const char* text, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, std::function<void()> OkFunc, bool cyclingFading)
		{
			Text = text;
			X = x;
			Y = y;
			DrawRelative = drawRelative;
			this->OkFunction = OkFunc;
			this->Function = 0;
			this->anchorPoint = anchorPoint;
			this->cyclingFading = cyclingFading;
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
		UI_ClickableButton(const char* text, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, std::function<void()> OkFunc)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			this->OkFunction = OkFunc;
			this->Function = 0;
			this->anchorPoint = anchorPoint;
		}
		UI_ClickableButton(const char* text, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, uintptr_t function, bool cyclingFading)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			Function = function;
			this->anchorPoint = anchorPoint;
			this->cyclingFading = cyclingFading;
		}
		UI_ClickableButton(const char* text, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, std::function<void()> OkFunc, bool cyclingFading)
		{
			Text = text;
			GridColumn = gridColumn;
			GridRow = gridRow;
			this->OkFunction = OkFunc;
			this->Function = 0;
			this->anchorPoint = anchorPoint;
			this->cyclingFading = cyclingFading;
		}
		UI_ClickableButton()
		{

		}
	public:

		void Draw()
		{
			if (T6SDK::Input::InputLockedByTextBoxDialog)
				return;
			if (!IsEnabled)
			{
				Hovered = false;
				Pressed = false;
				Clicked = false;
			}
			bool successDraw = false;
			if (DrawRelative)
				successDraw = T6SDK::Drawing::DrawTextRelative(Text, X, Y, Size, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : GetFadingColor(T6SDK::Drawing::WHITECOLOR), anchorPoint, &btnRect);
			else if (GridColumn != -1 && GridRow != -1)
			{
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, coords.x, coords.y, Size, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : GetFadingColor(T6SDK::Drawing::WHITECOLOR), anchorPoint, &btnRect);
			}
			else
				successDraw = T6SDK::Drawing::DrawTextAbsolute(Text, X, Y, Size, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Pressed ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : GetFadingColor(T6SDK::Drawing::WHITECOLOR), anchorPoint, &btnRect);
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
							//T6SDK::ConsoleLog::Log("Clicked!");
							Clicked = true;
							T6SDK::InternalFunctions::PlaySound("uin_main_pause");
							if (OkFunction)
								OkFunction();
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
					hoverSoundPlayed = false;
					Hovered = false;
					Pressed = false;
					Clicked = false;
				}
				fadingX += 0.05f;
				if (fadingX > 8.0f)
					fadingX = 0.0f;
			}
		}
		void Draw(bool isEnabled)
		{
			IsEnabled = isEnabled;
			Draw();
		}
	};
}