#pragma once
#include "StdInclude.h"
namespace T6SDK::Drawing
{
	class UI_Notification
	{
	private:
		RECT BaseRect{};
		bool Shown = false;
		int Duration = 50;
		int FadeIn = 10;
		int FadeOut = 10;
		int CurFadeIn = 0;
		int CurFadeOut = 0;
		int CurDuration = 0;
		float Y = 0.0f;
		float HEIGHT = 0.0f;
		float WIDTH = 0.0f;
		const char* DisplayingText{};
		const char* Title{};
		const char* Text{};

	public:

		UI_Notification(const char* title, const char* text, int duration)
		{
			this->Title = title;
			this->Text = text;
			this->Duration = duration;
		}
		UI_Notification()
		{
			DisplayingText = "teama";
		}

		void Show()
		{
			this->Shown = true;

			this->CurDuration = 0;
			this->CurFadeIn = 0;
			this->CurFadeOut = 0;
			float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
			float h = (float)T6SDK::Drawing::normalFont->pixelHeight * scale;
			this->HEIGHT = h + 4.0f;
			this->WIDTH = this->WIDTH * scale;
		}

		void Draw()
		{
			if (!Shown)
				return;
			char buffer[256];
			sprintf(buffer, "^5> %s ^7%s", Title, Text);
			this->DisplayingText = buffer;
			//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "T6SDK", "Notification text: %s", DisplayingText);
			float scale = 1.0f / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
			this->WIDTH = ((float)T6SDK::InternalFunctions::R_TextWidth(DisplayingText, strlen(DisplayingText), T6SDK::Drawing::normalFont)) + 10.0f;
			this->WIDTH = this->WIDTH * scale;
			//Fade in animation
			if (CurFadeIn < FadeIn)
			{
				//Anim fade in
				vec2_t pos = T6SDK::Drawing::GetGridCellCoords(8, 0);
				float yPos = -HEIGHT + ((CurFadeIn / (float)FadeIn) * (HEIGHT+10.0f));
				if (T6SDK::Drawing::DrawRectAbsolute(pos.x, yPos, WIDTH, HEIGHT, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopCenter, &BaseRect))
				{
					float textX = (float)BaseRect.left + 5.0f;
					float textY = (float)BaseRect.top + 2.0f;
					T6SDK::Drawing::DrawTextAbsolute(DisplayingText, textX, textY, 1.0f, T6SDK::Drawing::WHITECOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
				}
				CurFadeIn++;
				//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "T6SDK", "Fading in notification: %i", CurFadeIn);
				if (CurFadeIn > FadeIn)
					CurFadeIn = FadeIn;
			}
			//Base showing
			if (CurFadeIn == FadeIn)
			{
				if (CurDuration < Duration)
				{
					vec2_t pos = T6SDK::Drawing::GetGridCellCoords(8, 0);
					if (T6SDK::Drawing::DrawRectAbsolute(pos.x, 10.0f, WIDTH, HEIGHT, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopCenter, &BaseRect))
					{
						float textX = (float)BaseRect.left + 5.0f;
						float textY = (float)BaseRect.top + 2.0f;
						T6SDK::Drawing::DrawTextAbsolute(DisplayingText, textX, textY, 1.0f, T6SDK::Drawing::WHITECOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
					}
					//Draw notification
					//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "T6SDK", "Showing notification: %i", CurDuration);
					CurDuration++;
					if (CurDuration > Duration)
					{
						CurDuration = Duration;
						CurFadeOut = 0;
					}
				}
			}
			if (CurFadeIn == FadeIn && CurDuration == Duration)
			{
				//Fade out animation
				if (CurFadeOut < FadeOut)
				{
					//Anim fade out
					vec2_t pos = T6SDK::Drawing::GetGridCellCoords(8, 0);
					float yPos = 10.0f - ((CurFadeOut / (float)FadeOut) * (HEIGHT + 10.0f));
					if (T6SDK::Drawing::DrawRectAbsolute(pos.x, yPos, WIDTH, HEIGHT, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopCenter, &BaseRect))
					{
						float textX = (float)BaseRect.left + 5.0f;
						float textY = (float)BaseRect.top + 2.0f;
						T6SDK::Drawing::DrawTextAbsolute(DisplayingText, textX, textY, 1.0f, T6SDK::Drawing::WHITECOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
					}
					CurFadeOut++;
					//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "T6SDK", "Fading out notification: %i", CurFadeOut);
					if (CurFadeOut >= FadeOut)
					{
						CurFadeOut = FadeOut;
						this->Shown = false;
						//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "T6SDK", "Notification shown: %s", Shown ? "true" : "false");
					}
				}
			}
		}
	};
}