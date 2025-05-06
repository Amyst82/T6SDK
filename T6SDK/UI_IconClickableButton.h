#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_IconClickableButton
	{
	private:
		float fadingX = 0.0f;
		bool hoverSoundPlayed = false;
		std::function<void()> Function;
		bool Hovered = false;
		bool Pressed = false;
		bool Clicked = false;
		bool IsEnabled = true;
		RECT iconRect{};
		RECT baseRect{};
		bool CyclingFading = false;
		T6SDK::AnchorPoint anchorPoint{};
		bool DrawRelative = false;
		int GridColumn = -1;
		int GridRow = -1;
		float X = 0.0f;
		float Y = 0.0f;
		float WIDTH = 300.0f;
		float HEIGHT = 60.0f;
		const char* IconMaterial{};
	public:
		const char* Text{};
		const char* ToolTip = "";
		UI_IconClickableButton()
		{

		}
		/// <summary>
		/// Clickable button with icon
		/// </summary>
		/// <param name="text"></param>
		/// <param name="x"></param>
		/// <param name="y"></param>
		/// <param name="drawRelative"></param>
		/// <param name="anchorPoint"></param>
		UI_IconClickableButton(const char* text, const char* iconMaterial, float x, float y, bool drawRelative, T6SDK::AnchorPoint anchorPoint, bool cyclingFading, std::function<void()> Func)
		{
			Text = text;
			IconMaterial = iconMaterial;
			X = x;
			Y = y;
			CyclingFading = cyclingFading;
			Function = Func;
			DrawRelative = drawRelative;
			this->anchorPoint = anchorPoint;
		}
		/// <summary>
		/// Clickable button with icon
		/// </summary>
		/// <param name="text"></param>
		/// <param name="gridColumn"></param>
		/// <param name="gridRow"></param>
		/// <param name="anchorPoint"></param>
		UI_IconClickableButton(const char* text, const char* iconMaterial, int gridColumn, int gridRow, T6SDK::AnchorPoint anchorPoint, bool cyclingFading, std::function<void()> Func)
		{
			Text = text;
			IconMaterial = iconMaterial;
			GridColumn = gridColumn;
			GridRow = gridRow;
			CyclingFading = cyclingFading;
			Function = Func;
			this->anchorPoint = anchorPoint;
		}
		float* GetFadingColor(tColor color)
		{
			if (!CyclingFading)
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
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
				successDraw = T6SDK::Drawing::DrawRectCoordsRelative(X, Y, WIDTH * scale, HEIGHT * scale, T6SDK::Drawing::T_BLACKCOLOR, anchorPoint, &baseRect);
			}
			else if (GridColumn != -1 && GridRow != -1)
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawRectAbsolute(coords.x, coords.y, WIDTH * scale, HEIGHT * scale, T6SDK::Drawing::T_BLACKCOLOR, anchorPoint, &baseRect);
			}
			else
			{
				float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
				float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
				vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn, GridRow);
				successDraw = T6SDK::Drawing::DrawRectAbsolute(X, Y, WIDTH * scale, HEIGHT * scale, T6SDK::Drawing::T_BLACKCOLOR, anchorPoint, &baseRect);
			}
			//If we got the common bounds
			if (successDraw)
			{
				//Drawing icon
				if (T6SDK::Drawing::DrawRectAbsolute((float)baseRect.left, (float)baseRect.top, (float)baseRect.bottom - (float)baseRect.top, (float)baseRect.bottom - (float)baseRect.top, Clicked ? T6SDK::Drawing::ORANGECOLOR : T6SDK::Drawing::REDCOLOR, T6SDK::AnchorPoint::TopLeft, &iconRect))
				{
					float w = (float)baseRect.bottom - (float)baseRect.top;
					vec2_t coords = T6SDK::Drawing::EvaluateAnchorPoint(T6SDK::AnchorPoint::Center, (float)baseRect.left + w / 2.0f, (float)baseRect.top + w / 2.0f, w, w);
					T6SDK::Typedefs::R_AddCmdDrawStretchPicRotateXYInternal(coords.x + 2.0f, coords.y + 2.0f, 0.9f * w, 0.9f * w, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, T6SDK::Drawing::WHITECOLOR, T6SDK::InternalFunctions::DB_FindXAssetHeader(T6SDK::XAssetType::MATERIAL, IconMaterial));
				}
				//Drawing text
				float textX = (float)iconRect.right + (((float)baseRect.right - (float)iconRect.right) / 2.0f);
				float textY = (float)baseRect.top + (((float)baseRect.bottom - (float)baseRect.top) / 2.0f);
				T6SDK::Drawing::DrawTextAbsolute(Text, textX, textY, 1.2f, !IsEnabled ? T6SDK::Drawing::GRAYCOLOR : Clicked ? T6SDK::Drawing::ORANGECOLOR : Hovered ? T6SDK::Drawing::YELLOWCOLOR : GetFadingColor(T6SDK::Drawing::WHITECOLOR), T6SDK::AnchorPoint::Center, 0x00);
				//If mouse pointer is inside the whole button
				if (!IsEnabled)
					return;
				if (T6SDK::Input::MousePosX() > (float)baseRect.left && T6SDK::Input::MousePosX() < (float)baseRect.right && T6SDK::Input::MousePosY() > (float)baseRect.top && T6SDK::Input::MousePosY() < (float)baseRect.bottom)
				{
					//T6SDK::ConsoleLog::Log("Hovered");
					Hovered = true;
					if (hoverSoundPlayed == false)
					{
						T6SDK::InternalFunctions::PlaySound("uin_unlock_window");
						//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "CHECKBOX", "Hover sound played!");
						hoverSoundPlayed = true;
					}
					if (T6SDK::Input::Keys::LMB.IsAnyPressState())
					{
						Pressed = true;
						if (Clicked == false)
						{
							//T6SDK::ConsoleLog::Log("Clicked!");
							T6SDK::InternalFunctions::PlaySound("uin_main_pause");
							Clicked = true;
							if (Function)
								Function();
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