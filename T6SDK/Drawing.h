#pragma once
#include "pch.h"
#include "StdInclude.h"
namespace T6SDK
{
	namespace Drawing
	{
		#pragma region Definitions
		static Font_s* normalFont;
		static Font_s* consoleFont;
		static void* WhiteMaterial;
		static void* headicontalkballoon;
		static void* LightDef;
		static void* FxCameraSelect;

		static tColor T_WHITECOLOR = { 1.0f, 1.0f, 1.0f, 0.5f };
		static tColor WHITECOLOR = { 1.0f, 1.0f, 1.0f, 1.0f };
		static tColor BLACKCOLOR = { 0.0f, 0.0f, 0.0f, 1.0f };
		static tColor REDCOLOR = { 0.6f, 0.0f, 0.2f, 1.0f };
		static tColor GREENCOLOR = { 0.4f, 1.0f, 0.4f, 1.0f };
		static tColor BLUECOLOR = { 0.33f, 0.57f, 1.0f, 1.0f };
		static tColor YELLOWCOLOR = { 1.0f, 1.0f, 0.0f, 1.0f };
		static tColor CYANCOLOR = { 0.0f, 1.0f, 1.0f, 1.0f };
		static tColor MAGENTACOLOR = { 1.0f, 0.0f, 1.0f, 1.0f };
		static tColor GRAYCOLOR = { 0.5f, 0.5f, 0.5f, 1.0f };
		static tColor ORANGECOLOR = { 1.0f, 0.6f, 0.2f, 1.0f };
		static tColor T_BLACKCOLOR = { 0.0f, 0.0f, 0.0f, 0.5f };
		static tColor TRANSPARENTCOLOR = { 0.0f, 0.0f, 0.0f, 0.0f };

#pragma endregion
		#pragma region Helpers
		static bool CheckResources()
		{
			if (!normalFont)
			{
				normalFont = T6SDK::Typedefs::R_RegisterFont_FastFile("fonts/720/normalFont", 1);
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DRAWING", "normalFont restored: 0x%X", *normalFont);
				return false;
			}
			if (!consoleFont)
			{
				consoleFont = T6SDK::Typedefs::R_RegisterFont_FastFile("fonts/720/consoleFont", 1);
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DRAWING", "consoleFont restored: 0x%X", *consoleFont);
				return false;
			}
			if(!WhiteMaterial)
			{
				WhiteMaterial = T6SDK::InternalFunctions::Material_RegisterHandle("white", (int)T6SDK::XAssetType::MATERIAL);
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DRAWING", "WhiteMaterial restored: 0x%X", WhiteMaterial);
				return false;
			}
			if (!headicontalkballoon)
			{
				headicontalkballoon = T6SDK::InternalFunctions::Material_RegisterHandle("headicontalkballoon", (int)T6SDK::XAssetType::MATERIAL);
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DRAWING", "headicontalkballoon restored: 0x%X", headicontalkballoon);
				return false;
			}
			if(!normalFont || !WhiteMaterial || !headicontalkballoon)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DRAWING", "Missing some drawing resources");
				return false;
			}
			if (!LightDef)
			{
				LightDef = T6SDK::InternalFunctions::DB_FindXAssetHeader(T6SDK::XAssetType::LIGHT_DEF, "light_dynamic");
			}
			if (!FxCameraSelect)
			{
				FxCameraSelect = T6SDK::InternalFunctions::DB_FindXAssetHeader(T6SDK::XAssetType::FX, "misc/fx_theater_mode_camera_head_select");
			}
			if (normalFont && consoleFont && WhiteMaterial && headicontalkballoon)
			{
				//T6SDK::ConsoleLog::LogFormatted(12, "Drawing resources are alright!");
				return true;
			}
			return false;
		}

		static vec2_t GetAbsoluteCoords(float x, float y)
		{
			float X = x * static_cast<float>(T6SDK::Addresses::ScreenWidth.Value());
			float Y = y * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value());
			return { X, Y };
		}
		static vec2_t EvaluateAnchorPoint(AnchorPoint anchorPoint, float X, float Y, float width, float height)
		{
			float x = X;
			float y = Y;

			switch (anchorPoint)
			{
			case AnchorPoint::TopLeft:
				x = X;
				y = Y;
				break;
			case AnchorPoint::TopCenter:
				x = X - width / 2.0f;
				y = Y;
				break;
			case AnchorPoint::TopRight:
				x = X - width;
				y = Y;
				break;
			case AnchorPoint::CenterLeft:
				x = X;
				y = Y - height / 2.0f;
				break;
			case AnchorPoint::Center:
				x = X - width / 2.0f;
				y = Y - height / 2.0f;
				break;
			case AnchorPoint::CenterRight:
				x = X - width;
				y = Y - height / 2.0f;
				break;
			case AnchorPoint::BottomLeft:
				x = X;
				y = Y - height;
				break;
			case AnchorPoint::BottomCenter:
				x = X - width / 2.0f;
				y = Y - height;
				break;
			case AnchorPoint::BottomRight:
				x = X - width;
				y = Y - height;
				break;
			}

			return { x, y };
		}
		static vec2_t GetGridCellCoords(int column, int row)
		{
			float X = (float)(column * (T6SDK::Addresses::ScreenWidth.Value() / 16)); //Eight columns
			float Y = (float)(row * (T6SDK::Addresses::ScreenHeight.Value() / 40)); //Twenty one rows
			return { X, Y };
		}
		
#pragma endregion
		#pragma region Text absolute
		/// <summary>
		/// Draw text with absolute screen position.
		/// </summary>
		/// <param name="Text"></param>
		/// <param name="X">Horizontal position in pixels.</param>
		/// <param name="Y">Vertical position in pixels.</param>
		/// <param name="Scale">Text scale.</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values.</param>
		/// <param name="anchorPoint">Anchor point.</param>
		/// <param name="TextRect">Output text bounds.</param>
		/// <returns></returns>
		static bool DrawTextAbsolute(const char* Text, float X, float Y, float Scale, tColor Color, AnchorPoint anchorPoint, RECT* TextRect)
		{
			if (!CheckResources())
				return false;
			float scale = Scale / 1080.0f * static_cast<float>(T6SDK::Addresses::ScreenHeight.Value()); //Assuming that initial size is in 1920x1080			
			int MaxLength = strlen(Text);

			float width = (float)T6SDK::Typedefs::R_TextWidth(0, Text, MaxLength, normalFont) * scale;
			float height = (float)normalFont->pixelHeight * scale;
			vec2_t coords = EvaluateAnchorPoint(anchorPoint, X, Y, width, height);
			T6SDK::Typedefs::R_AddCmdDrawTextInternal(Text, MaxLength, normalFont, coords.x, coords.y + height, scale, scale, 0, Color, 0);
			if(TextRect)
			{
				TextRect->left = coords.x;
				TextRect->top = coords.y;
				TextRect->right = coords.x + width;
				TextRect->bottom = coords.y + height;
			}
			return true;
		}
#pragma endregion
		#pragma region Text relative
		/// <summary>
		/// Draw text relative to the screen size
		/// </summary>
		/// <param name="Text"></param>
		/// <param name="X">Position in size from 0.0f to 1.0f</param>
		/// <param name="Y">Position in size from 0.0f to 1.0f</param>
		/// <param name="Scale">Text scale</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values</param>
		/// <param name="anchorPoint">Anchor point</param>
		/// <param name="TextRect">Output text bounds</param>
		static bool DrawTextRelative(const char* Text, float X, float Y, float Scale, tColor Color, AnchorPoint anchorPoint, RECT* TextRect)
		{
			if (!CheckResources())
				return false;
			vec2_t coords = GetAbsoluteCoords(X, Y);
			return DrawTextAbsolute(Text, coords.x, coords.y, Scale, Color, anchorPoint, TextRect);
		}

#pragma endregion
		#pragma region Rect absolute
		/// <summary>
		/// Draw rect on screen with absolute position and size.
		/// </summary>
		/// <param name="X">Horizontal position in pixels.</param>
		/// <param name="Y">Vertical position in pixels.</param>
		/// <param name="width">Width in pixels.</param>
		/// <param name="height">Height in pixels.</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values.</param>
		/// <param name="anchorPoint">Anchor point.</param>
		/// <param name="OutRect">Output rect bounds.</param>
		static bool DrawRectAbsolute(float x, float y, float width, float height, tColor Color, AnchorPoint anchorPoint, RECT* OutRect)
		{
			if (!CheckResources())
				return false;
			vec2_t coords = EvaluateAnchorPoint(anchorPoint, x, y, width, height);
			T6SDK::Typedefs::R_AddCmdDrawStretchPicRotateXYInternal(coords.x, coords.y, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, Color, WhiteMaterial);
			if (OutRect)
			{
				OutRect->left = coords.x;
				OutRect->top = coords.y;
				OutRect->right = coords.x + width;
				OutRect->bottom = coords.y + height;
			}
			return true;
		}
		/// <summary>
		/// Draw rect on screen snapped to grid.
		/// </summary>
		/// <param name="GridColumn0">Number of column.</param>
		/// <param name="GridRow0">Number of row.</param>
		/// <param name="GridColumn1">End number of column.</param>
		/// <param name="GridRow1">End number of row.</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values.</param>
		/// <param name="anchorPoint"></param>
		/// <param name="OutRect">Out rect bounds.</param>
		/// <returns></returns>
		static bool DrawRectAbsolute(int GridColumn0, int GridRow0, int GridColumn1, int GridRow1, vec4_t margin, tColor Color, AnchorPoint anchorPoint, RECT* OutRect)
		{
			if (!CheckResources())
				return false;
			vec2_t coords = T6SDK::Drawing::GetGridCellCoords(GridColumn0, GridRow0);
			vec2_t coords2 = T6SDK::Drawing::GetGridCellCoords(GridColumn1, GridRow1);
			return DrawRectAbsolute(coords.x+margin.x, coords.y+margin.y, coords2.x - coords.x+margin.z, coords2.y - coords.y+margin.w, Color, anchorPoint, OutRect);
		}
#pragma endregion
		#pragma region Rect coords relative
		/// <summary>
		/// Draw rect on screen with position relative to the screen size and absolute size.
		/// </summary>
		/// <param name="X">Horizontal position [0.0f - 1.0].</param>
		/// <param name="Y"> Vertical position [0.0f - 1.0].</param>
		/// <param name="width">Absolute width in pixels.</param>
		/// <param name="height">Absolute height in pixels.</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values.</param>
		/// <param name="anchorPoint">Anchor point enum.</param>
		/// <param name="OutRect">Output rect bounds.</param>
		/// <returns></returns>
		static bool DrawRectCoordsRelative(float X, float Y, float width, float height, tColor Color, AnchorPoint anchorPoint, RECT* OutRect)
		{
			vec2_t coords = GetAbsoluteCoords(X, Y);
			return DrawRectAbsolute(coords.x, coords.y, width, height, Color, anchorPoint, OutRect);
		}
#pragma endregion
		#pragma region Rect size relative
		/// <summary>
		/// Draw rect on screen with absolute position and size Relative to the screen size.
		/// </summary>
		/// <param name="X">Horizontal position in pixels.</param>
		/// <param name="Y">Vertical position in pixels.</param>
		/// <param name="width">Relative width [0.0f - 1.0].</param>
		/// <param name="height">Relative height [0.0f - 1.0].</param>
		/// <param name="Color"></param>
		/// <param name="anchorPoint"></param>
		/// <param name="OutRect"></param>
		/// <returns></returns>
		static bool DrawRectSizeRelative(float X, float Y, float width, float height, tColor Color, AnchorPoint anchorPoint, RECT* OutRect)
		{
			vec2_t size = GetAbsoluteCoords(width, height);
			return DrawRectAbsolute(X, X, size.x, size.y, Color, anchorPoint, OutRect);
		}
#pragma endregion
		#pragma region Rect fully relative
		/// <summary>
		/// Draw rect on screen with position relative to the screen size and size relative to the screen size.
		/// </summary>
		/// <param name="X">Horizontal position [0.0f - 1.0].</param>
		/// <param name="Y">Vertical position [0.0f - 1.0].</param>
		/// <param name="width">Relative width [0.0f - 1.0].</param>
		/// <param name="height">Relative height [0.0f - 1.0].</param>
		/// <param name="Color">tColor struct with four [0.0 - 1.0] values.</param>
		/// <param name="anchorPoint">Anchor point enum.</param>
		/// <param name="OutRect">Output rect bounds.</param>
		/// <returns></returns>
		static bool DrawRectRelative(float X, float Y, float width, float height, tColor Color, AnchorPoint anchorPoint, RECT* OutRect)
		{
			vec2_t coords = GetAbsoluteCoords(X, Y);
			vec2_t size = GetAbsoluteCoords(width, height);
			return DrawRectAbsolute(coords.x, coords.y, size.x, size.y, Color, anchorPoint, OutRect);
		}
#pragma endregion

		static void DrawMaterial(float x, float y, float size, AnchorPoint anchorPoint, tColor Color, void* material)
		{
			if (!CheckResources())
				return;
			vec2_t coords = EvaluateAnchorPoint(anchorPoint, x, y, size, size);
			T6SDK::Typedefs::R_AddCmdDrawStretchPicRotateXYInternal(coords.x, coords.y, size, size, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, Color, material);
		}
		static void ShowToolTip(const char* Text)
		{
			vec2_t coords = GetGridCellCoords(8, 39);
			char buffer[256];
			sprintf(buffer, "^5> ^7%s", Text);
			T6SDK::Drawing::DrawTextAbsolute(buffer, coords.x, coords.y, 1.0f, T6SDK::Drawing::T_WHITECOLOR, AnchorPoint::Center, 0x00);
		}
	}
}