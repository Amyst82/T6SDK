#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_Slider
	{
		typedef void func(float);
	private:
		bool Hovered = false;
		bool Pressed = false;
		bool Clicked = false;
		bool IsEnabled = true;
		bool MouseHold = false;
		uintptr_t Function = 0;
		T6SDK::AnchorPoint anchorPoint{};
		bool DrawRelative = false;
		int GridColumn = -1;
		int GridRow = -1;
		RECT baseRect{};
		RECT sliderRect{};
		RECT textRect{};
		float X = 0.0f;
		float Y = 0.0f;
		float* clr;
		float GetCoordByValue(float value, float x, float y, float width, float min, float max)
		{
			float res = 0.0f;
			float coef = (max - min) / width;
			res = ((value - min) / coef) + x;
			return res;
		}
		float defaultValue = 0.0f;

		float internalDefaultValue = 0.0f;
		float internalValue = 0.0f;

		float WIDTH = 210.0f;
		float HEIGHT = 15.0f;
		const char* Text{};
		std::string StringText{};
	public:
		float* value = &internalValue;
		float Min = 0.0f;
		float Max = 1.0f;
		const char* ToolTip = "";
		void Reset()
		{
			*value = internalDefaultValue;
			defaultValue = GetCoordByValue(internalDefaultValue, X, Y, WIDTH, Min, Max);
			if (Function)
			{
				func* f = (func*)Function;
				f(*value);
			}
		}

	public:
		UI_Slider()
		{

		}
		/// <summary>
		/// Slider.
		/// </summary>
		/// <param name="text">Text to be displayed in format "Text: %.3f".</param>
		/// <param name="_value">Pointer to a float value.</param>
		/// <param name="_defaultValue">Default value to reset the slider to.</param>
		/// <param name="min">Minimum value.</param>
		/// <param name="max">Maximum value.</param>
		/// <param name="x">Horizontal position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="y">Vertical position in pixels, otherwise if drawRelative is true, this is relative to the screen size [0.0f - 1.0f].</param>
		/// <param name="drawRelative">Describes will x and y values will be treated as relative to the screen size.</param>
		/// <param name="color">tColor struct with four [0.0 - 1.0] values</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Function to be called when the slider is dragged.</param>
		UI_Slider(const char* text, float* _value, float _defaultValue, float min, float max, float x, float y, bool drawRelative, tColor color, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			X = x;
			Y = y;
			Function = function;
			this->anchorPoint = anchorPoint;
			if (value)
				value = _value;
			Min = min;
			Max = max;
			clr = color;
			internalDefaultValue = _defaultValue;
			defaultValue = GetCoordByValue(_defaultValue, X, Y, WIDTH, min, max);
			Text = text;
			DrawRelative = drawRelative;
		}
		UI_Slider(std::string& text, float* _value, float _defaultValue, float min, float max, float x, float y, bool drawRelative, tColor color, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			X = x;
			Y = y;
			Function = function;
			this->anchorPoint = anchorPoint;
			if (value)
				value = _value;
			Min = min;
			Max = max;
			clr = color;
			internalDefaultValue = _defaultValue;
			defaultValue = GetCoordByValue(_defaultValue, X, Y, WIDTH, min, max);
			StringText = text;
			DrawRelative = drawRelative;
		}
		/// <summary>
		/// Slider.
		/// </summary>
		/// <param name="text">Text to be displayed in format "Text: %.3f".</param>
		/// <param name="_value">Pointer to a float value.</param>
		/// <param name="_defaultValue">Default value to reset the slider to.</param>
		/// <param name="min">Minimum value.</param>
		/// <param name="max">Maximum value.</param>
		/// <param name="gridColumn">Number of one of 8 columns that the slider will take X position from.</param>
		/// <param name="gridRow">Number of one of 21 rows that the slider will take Y position from.</param>
		/// <param name="color">tColor struct with four [0.0 - 1.0] values</param>
		/// <param name="anchorPoint"></param>
		/// <param name="function">Function to be called when the slider is dragged.</param>
		UI_Slider(const char* text, float* _value, float _defaultValue, float min, float max, int GridColumn, int GridRow, tColor color, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Function = function;
			this->anchorPoint = anchorPoint;
			if(value)
				value = _value;
			Min = min;
			Max = max;
			clr = color;
			internalDefaultValue = _defaultValue;
			defaultValue = GetCoordByValue(_defaultValue, X, Y, WIDTH, min, max);
			Text = text;
			this->GridColumn = GridColumn;
			this->GridRow = GridRow;
		}
		UI_Slider(std::string& text, float* _value, float _defaultValue, float min, float max, int GridColumn, int GridRow, tColor color, T6SDK::AnchorPoint anchorPoint, uintptr_t function)
		{
			Function = function;
			this->anchorPoint = anchorPoint;
			if (value)
				value = _value;
			Min = min;
			Max = max;
			clr = color;
			internalDefaultValue = _defaultValue;
			defaultValue = GetCoordByValue(_defaultValue, X, Y, WIDTH, min, max);
			StringText = text;
			this->GridColumn = GridColumn;
			this->GridRow = GridRow;
		}

		void Draw()
		{
			if (T6SDK::Input::InputLockedByTextBoxDialog)
				return;
			if (!T6SDK::Drawing::CheckResources())
				return;
			
			//Getting the base rect bounds (combined rect for text + slider underneath)
			bool successDraw = false;
			if(DrawRelative)
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale; 
				successDraw = T6SDK::Drawing::DrawRectCoordsRelative(X, Y, WIDTH, 2.0f + HEIGHT + h, T6SDK::Drawing::TRANSPARENTCOLOR, anchorPoint, &baseRect);
			}
			else if (GridColumn != -1 && GridRow != -1)
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawRectAbsolute(coords.x, coords.y, WIDTH, 2.0f + HEIGHT + h, T6SDK::Drawing::TRANSPARENTCOLOR, anchorPoint, &baseRect);
			}
			else
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawRectAbsolute(X, Y, WIDTH, 2.0f + HEIGHT + h, T6SDK::Drawing::TRANSPARENTCOLOR, anchorPoint, &baseRect);
			}
			//If we got the common bounds
			if (successDraw)
			{
				#pragma region Slider text

				tColor* color{};
				if (Pressed)
					color = &T6SDK::Drawing::ORANGECOLOR;
				else if (Hovered)
					color = &T6SDK::Drawing::YELLOWCOLOR;
				else if (!IsEnabled)
					color = &T6SDK::Drawing::GRAYCOLOR;
				else
					color = &T6SDK::Drawing::WHITECOLOR;

				//Draw the slider text

				char buffer[250];
				if (StringText.empty() == false)
				{
					sprintf_s(buffer, 250, "%s: %.3f", StringText.c_str(), *value);
				}
				else
				{
					sprintf_s(buffer, 250, "%s: %.3f", Text, *value);
				}
				
				if (T6SDK::Drawing::DrawTextAbsolute(buffer, (float)baseRect.left, (float)baseRect.top, 1.0f, *color, T6SDK::AnchorPoint::TopLeft, &textRect))
				{
					if (IsEnabled && T6SDK::Input::MousePosX() > (float)textRect.left && T6SDK::Input::MousePosX() < (float)textRect.right && T6SDK::Input::MousePosY() > (float)textRect.top && T6SDK::Input::MousePosY() < (float)textRect.bottom)
					{
						//T6SDK::ConsoleLog::Log("Hovered");
						Hovered = true;
						if (T6SDK::Input::Keys::LMB.IsAnyPressState() && MouseHold == false)
						{
							Pressed = true;
							if (Clicked == false)
							{
								//T6SDK::ConsoleLog::Log("Clicked!");
								Clicked = true;
								Reset();
							}
						}
						else
						{
							Pressed = false;
							Clicked = false;
						}
						if (strlen(ToolTip) > 1)
						{
							char buffer[64];
							sprintf(buffer, "Click to reset ^5%s", Text);
							T6SDK::Drawing::ShowToolTip(buffer);
						}
					}
					else
					{
						Hovered = false;
						Pressed = false;
						Clicked = false;
					}
				}

#pragma endregion
				//Drawing the slider
				if (T6SDK::Drawing::DrawRectAbsolute((float)baseRect.left, (float)baseRect.bottom - HEIGHT, WIDTH, HEIGHT, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopLeft, &sliderRect)) //drawing the background of slider
				{
					defaultValue = GetCoordByValue(*value, (float)sliderRect.left, (float)sliderRect.top, WIDTH, Min, Max);
					float clickx = defaultValue - T6SDK::Input::MousePosX();
					float moveto = defaultValue - clickx;
					if (T6SDK::Input::MousePosX() > (float)sliderRect.left && T6SDK::Input::MousePosX() < (float)sliderRect.right && T6SDK::Input::MousePosY() > (float)sliderRect.top && T6SDK::Input::MousePosY() < (float)sliderRect.bottom)
					{
						if (T6SDK::Input::Keys::LMB.IsAnyPressState())
						{
							MouseHold = true;
						}
						if (strlen(ToolTip) > 1)
						{
							T6SDK::Drawing::ShowToolTip(ToolTip);
						}
					}
					else
					{
						//MouseHold = false;
					}
					if (!T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						MouseHold = false;
					}
					if (MouseHold == true && IsEnabled)
					{
						defaultValue = moveto;
						float coef = (Max - Min) / WIDTH;
						*value = Min + coef * (defaultValue - (float)sliderRect.left);
						if (*value < Min)
						{
							*value = Min;
						}
						if (*value > Max)
						{
							*value = Max;
						}
						if (GetCoordByValue(*value, (float)sliderRect.left, (float)sliderRect.top, WIDTH, Min, Max) != defaultValue)
						{
							
						}
						if (Function)
						{
							func* f = (func*)Function;
							f(*value);
						}

					}
					if(MouseHold)
					{
						if (defaultValue < (float)sliderRect.left)
						{
							defaultValue = (float)sliderRect.left;
							*value = Min;
						}
						if (defaultValue > (float)sliderRect.right)
						{
							defaultValue = (float)sliderRect.right;
							*value = Max;
						}
					}
					//Drawing the slider
					T6SDK::Drawing::DrawRectAbsolute((float)sliderRect.left, (float)sliderRect.top, defaultValue - (float)sliderRect.left, HEIGHT, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : clr, T6SDK::AnchorPoint::TopLeft, 0x00);
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