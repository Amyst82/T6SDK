#pragma once
#include "StdInclude.h"
#include <shobjidl.h> // For IFileDialog
#include <commdlg.h>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>
#pragma comment(lib, "ole32.lib") // Link against Ole32 library
#define FILLIN 0x00
namespace T6SDK::Typedefs
{
	//I used to use IDA to find the function signatures and it worked well. However it has poor performance and causes bugs when you make a plugin for Redacted for example.
	//Since it's being loaded on the game startup some code blocks of a game are not loaded yet and signature scanner can't find the functions what causes some bugs.
	
	//56 8B 74 24 ? 57 56 E8 ? ? ? ? 8B F8 A1 ? ? ? ? 83 C4 ? 50 68 ? ? ? ? 57 E8 ? ? ? ? 83 C4 ? 50 E8 ? ? ? ? 83 C4 ? 84 C0 74 ? 8B 0D ? ? ? ? 8B 54 24
	typedef void(__cdecl* Demo_Error_t)(int localClientNum, const char* TitleText, const char* MessageText);
	inline extern Demo_Error_t Demo_Error = (Demo_Error_t)T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0F5CD0, T6SDK::Addresses::t6mp + 0x246260,
		T6SDK::Addresses::t6zmv41 + 0x261AC10, T6SDK::Addresses::t6zm + 0x073210).GetValue();
	
	typedef void(__cdecl* Demo_Back_t)();
	inline extern Demo_Back_t Demo_Back = (Demo_Back_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x528110, T6SDK::Addresses::t6mp + 0x5282C0, 
		T6SDK::Addresses::t6zmv41 + 0x525180, T6SDK::Addresses::t6zm + 0x5253B0).GetValue());

	//8B 44 24 ? 8B 4C 24 ? 8B 54 24 ? 50 8B 44 24 ? 51 8B 4C 24 ? 52 50 51 E8 ? ? ? ? 83 C4 ? 50
	typedef void(__cdecl* UI_OpenToastPopup_t)(int a1, const char* a2, const char* a3, const char* a4, int a5);
	inline extern UI_OpenToastPopup_t UI_OpenToastPopup = (UI_OpenToastPopup_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x059520, T6SDK::Addresses::t6mp + 0x2A8310,
		T6SDK::Addresses::t6zmv41 + 0x05B660, T6SDK::Addresses::t6zm + 0x2136E0).GetValue());

	//8B 4C 24 10 F3 0F 10 11 F3 0F 5C 96 C4 D8 04 00 F3 0F 10 61 04 F3 0F 5C A6 C8 D8 04 00 F3 0F 10 9E D8 D8 04 00 F3 0F 10 86 D4 D8 04 00 F3 0F 10 69 08 F3 0F 5C AE CC D8 04 00 F3 0F 10 8E E0 D8 04 00
	typedef bool(__cdecl* WorldPosToScreenPos_t)(int localClientNum, vec3_t* worldPos, vec2_t* outScreenPos);
	inline extern WorldPosToScreenPos_t WorldPosToScreenPos = (WorldPosToScreenPos_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x029A80, T6SDK::Addresses::t6mp + 0x195690,
		T6SDK::Addresses::t6zmv41 + 0x0D53C0, T6SDK::Addresses::t6zm + 0x07C3D0).GetValue());

	//56 8B 74 24 ? 81 FE ? ? ? ? 7D ? A1 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 85 C0 74 ? 68 ? ? ? ? 6A ? E8 ? ? ? ? 83 C4 ? 8B 4C 24 ? 8B C6
	typedef entity_t*(__cdecl* CG_GetEntity_t)(int localClientIndex, int index);
	inline extern CG_GetEntity_t CG_GetEntity = (CG_GetEntity_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x157170, T6SDK::Addresses::t6mp + 0x1077A0,
		T6SDK::Addresses::t6zmv41 + 0x0C6E40, T6SDK::Addresses::t6zm + 0x182000).GetValue());

	//56 8B 74 24 ? 56 E8 ? ? ? ? 83 C4 ? 83 F8 ? 74 ? 56
	typedef bool(__cdecl* CG_IsScoreboardDisplayed_t)(int localClientIndex);
	inline extern CG_IsScoreboardDisplayed_t CG_IsScoreboardDisplayed = (CG_IsScoreboardDisplayed_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x2712E0, T6SDK::Addresses::t6mp + 0x27A720,
		T6SDK::Addresses::t6zmv41 + 0x17FAC0, T6SDK::Addresses::t6zm + 0x160A70).GetValue());

	//8B 44 24 ? 50 E8 ? ? ? ? A1 ? ? ? ? 83 C4 ? C3
	typedef uiMenuCommand_t(__cdecl* UI_GetActiveMenu_t)(int localClientIndex);
	inline extern UI_GetActiveMenu_t UI_GetActiveMenu = (UI_GetActiveMenu_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x21CD30, T6SDK::Addresses::t6mp + 0x189BA0,
		T6SDK::Addresses::t6zmv41 + 0x0A8A90, T6SDK::Addresses::t6zm + 0x2993C0).GetValue());

	typedef void(__cdecl* Key_SetCatcher_t)(int localClientIndex, int mask);
	//56 8B 74 24 ? 83 FE ? 74 ? E8
	inline extern Key_SetCatcher_t Key_SetCatcher = (Key_SetCatcher_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x114950, T6SDK::Addresses::t6mp + 0x23FD30,
		T6SDK::Addresses::t6zmv41 + 0x21AD70, T6SDK::Addresses::t6zm + 0x05E090).GetValue());

	//8B 44 24 ? 83 F8 ? 74 ? 8B 0D ? ? ? ? 23 4C 24
	inline extern Key_SetCatcher_t Key_SetCatcher2 = (Key_SetCatcher_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x2F6380, T6SDK::Addresses::t6mp + 0x099410,
		T6SDK::Addresses::t6zmv41 + 0x139C00, T6SDK::Addresses::t6zm + 0x17A240).GetValue());

	//81 EC ? ? ? ? 53 55 56 8B B4 24 ? ? ? ? 57 6A
	typedef void*(__cdecl* DB_FindXAssetHeader_t)(BYTE type, const char* name, bool errorIfMissing, int waitTime);
	inline extern DB_FindXAssetHeader_t DB_FindXAssetHeader = (DB_FindXAssetHeader_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x2F9030, T6SDK::Addresses::t6mp + 0x20B610,
		T6SDK::Addresses::t6zmv41 + 0x03F460, T6SDK::Addresses::t6zm + 0x2CBF50).GetValue());

	//8B 44 24 04 80 38 ? 75 06 A1 ? ? ? ? C3 89 44 24 04 E9 ? ? ? ?
	typedef void* (__cdecl* Material_RegisterHandle_t)(const char* name, int imageTrack, bool errorIfMissing, int waitTime);
	inline extern Material_RegisterHandle_t Material_RegisterHandle = (Material_RegisterHandle_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x334CC0, T6SDK::Addresses::t6mp + 0x334000,
		T6SDK::Addresses::t6zmv41 + 0x3333C0, T6SDK::Addresses::t6zm + 0x331C10).GetValue());

	//A1 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 84 C0 0F 84 ? ? ? ? E8 ? ? ? ? 84 C0 0F 84 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? E8 ? ? ? ? 84 C0 75
	typedef void (__cdecl* Demo_JumpToDollyCamMarkerTime_t)(int localClientIndex, int markerNum);
	inline extern Demo_JumpToDollyCamMarkerTime_t Demo_JumpToDollyCamMarkerTime = (Demo_JumpToDollyCamMarkerTime_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x16A410, T6SDK::Addresses::t6mp + 0x1F05B0,
		T6SDK::Addresses::t6zmv41 + 0x229380, T6SDK::Addresses::t6zm + 0x14D900).GetValue());

	//56 57 BF ? ? ? ? 8D 57 ? E8 ? ? ? ? 8B F0 85 F6 0F 84 ? ? ? ? 8B 44 24 ? 85 C0 75 ? A1 ? ? ? ? F3 0F 10 44 24 ? 8B 4C 24 ? F3 0F 11 46 ? F3 0F 10 44 24 ? F3 0F 11 46 ? F3 0F 10 05
	typedef void (__cdecl* R_AddCmdDrawStretchPicRotateXYInternal_t)(float x, float y, float w, float h, float s0, float t0, float s1, float t1, float angle, tColor color, void* material);
	inline extern R_AddCmdDrawStretchPicRotateXYInternal_t R_AddCmdDrawStretchPicRotateXYInternal = (R_AddCmdDrawStretchPicRotateXYInternal_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x310DF0, T6SDK::Addresses::t6mp + 0x310110,
		T6SDK::Addresses::t6zmv41 + 0x30F0E0, T6SDK::Addresses::t6zm + 0x30D930).GetValue());

	//8B 44 24 04 80 38 00 55 56 57 0F 84 03 01 00 00
	typedef void* (__cdecl* R_AddCmdDrawTextInternal_t)(const char* Text, int NumOfChars, Font_s* Font, float X, float Y, float ScaleX, float ScaleY, float unk1, tColor Color, int unk2);
	inline extern R_AddCmdDrawTextInternal_t R_AddCmdDrawTextInternal = (R_AddCmdDrawTextInternal_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x311150, T6SDK::Addresses::t6mp + 0x310470,
		T6SDK::Addresses::t6zmv41 + 0x30F440, T6SDK::Addresses::t6zm + 0x30DC90).GetValue());

	//8B 44 24 04 6A FF 6A 01 50 6A 14 E8
	typedef Font_s* (__cdecl* R_RegisterFont_FastFile_t)(const char* FontName, int unk);
	inline extern R_RegisterFont_FastFile_t R_RegisterFont_FastFile = (R_RegisterFont_FastFile_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x333F50, T6SDK::Addresses::t6mp + 0x333290,
		T6SDK::Addresses::t6zmv41 + 0x332640, T6SDK::Addresses::t6zm + 0x330EA0).GetValue());

	//51 F3 0F 10 44 24 ? 56 8B 74 24 ? 51 F3 0F 11 04 24 56 E8 ? ? ? ? D9 5C 24 ? 8B 44 24 ? 8B 4C 24 ? 8B 54 24
	typedef int(__cdecl* UI_TextWidth_t)(int localCLientNum, const char* text, int iMaxLen, Font_s* pFont, float Scale);
	inline extern UI_TextWidth_t UI_TextWidth = (UI_TextWidth_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x01F490, T6SDK::Addresses::t6mp + 0x034570,
		T6SDK::Addresses::t6zmv41 + 0x0A7E20, T6SDK::Addresses::t6zm + 0x01D650).GetValue());

	//83 EC 0C 55 57 33 ED 33 FF 39 6C 24 20
	typedef int(__cdecl* R_TextWidth_t)(int localCLientNum, const char* text, int iMaxLen, Font_s* pFont);
	inline extern R_TextWidth_t R_TextWidth = (R_TextWidth_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x334020, T6SDK::Addresses::t6mp + 0x333360,
		T6SDK::Addresses::t6zmv41 + 0x332710, T6SDK::Addresses::t6zm + 0x330F70).GetValue());
	//A1 ? ? ? ? 3D ? ? ? ? 74 ? 8B 4C 24
	typedef void(__cdecl* FxSpriteAdd_t)(FxSprite_t* sprite);
	inline extern FxSpriteAdd_t FxSpriteAdd = (FxSpriteAdd_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x10AD60, T6SDK::Addresses::t6mp + 0x013B20,
		T6SDK::Addresses::t6zmv41 + 0x0DA9D0, T6SDK::Addresses::t6zm + 0x197820).GetValue());

	typedef int(__cdecl* FX_PlayOrientedEffect_t)(int localClientNum, void* def, int startMsec,vec3_t* origin,	Matrix33_s* axis);
	inline extern FX_PlayOrientedEffect_t FX_PlayOrientedEffect = (FX_PlayOrientedEffect_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x1CD600, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//55 8B EC 83 E4 ? 83 EC 0C 80 3D ? ? ? ? ? 56 0F 84
	typedef void(__cdecl* R_AddOmniLightToScene_t)(vec3_t* org, float radius, float r, float g, float b, float a);
	inline extern R_AddOmniLightToScene_t R_AddOmniLightToScene = (R_AddOmniLightToScene_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x326F00, T6SDK::Addresses::t6mp + 0x326240,
		T6SDK::Addresses::t6zmv41 + 0x325200, T6SDK::Addresses::t6zm + 0x323A70).GetValue());

	//55 8B EC 83 E4 ? 83 EC ? 80 3D ? ? ? ? ? 56 8B 75
	typedef void(__cdecl* R_AddSpotLightToScene_t)(vec3_t* org, Matrix33_s* axis, float radius, float fovInnerFraction, float startRadius, float endRadius, float r, float g, float b, float a, int lightDef);
	inline extern R_AddSpotLightToScene_t R_AddSpotLightToScene = (R_AddSpotLightToScene_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x327110, T6SDK::Addresses::t6mp + 0x326450,
		T6SDK::Addresses::t6zmv41 + 0x325410, T6SDK::Addresses::t6zm + 0x323C80).GetValue());

	//8B 4C 24 ? 8B 44 24 ? 69 C9 ? ? ? ? 03 C1
	typedef PVOID(__cdecl* Com_GetClientDObj_t)(UINT EntityClientNum, UINT localClientNum);
	inline extern Com_GetClientDObj_t Com_GetClientDObj = (Com_GetClientDObj_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0DA190, T6SDK::Addresses::t6mp + 0x1D2590,
		T6SDK::Addresses::t6zmv41 + 0x260CA0, T6SDK::Addresses::t6zm + 0x212DD0).GetValue());

	//8B 44 24 ? 8B 4C 24 ? F3 0F 10 09
	typedef void(__cdecl* MatrixSet44_t)(vec4_t* out, vec3_t* origin, Matrix33_s* axis, float scale);
	inline extern MatrixSet44_t MatrixSet44 = (MatrixSet44_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x055870, T6SDK::Addresses::t6mp + 0x2F2BE0,
		T6SDK::Addresses::t6zmv41 + 0x289F40, T6SDK::Addresses::t6zm + 0x09ED40).GetValue());

	//55 8B EC 83 E4 ? 81 EC ? ? ? ? 8B 45 ? 0F 10 00
	typedef void(__cdecl* MatrixInverse44_t)(vec4_t* mat, vec4_t* dst);
	inline extern MatrixInverse44_t MatrixInverse44 = (MatrixInverse44_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x04CB40, T6SDK::Addresses::t6mp + 0x205B20,
		T6SDK::Addresses::t6zmv41 + 0x2C04C0, T6SDK::Addresses::t6zm + 0x2FBEF0).GetValue());

	//8B 44 24 ? 0F 10 00
	typedef void(__cdecl* MatrixMultiply44_t)(vec4_t* in1, vec4_t* in2, vec4_t* out);
	inline extern MatrixMultiply44_t MatrixMultiply44 = (MatrixMultiply44_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x1866B0, T6SDK::Addresses::t6mp + 0x2B8250,
		T6SDK::Addresses::t6zmv41 + 0x085170, T6SDK::Addresses::t6zm + 0x0BCC60).GetValue());

	//83 EC ? F3 0F 10 0D ? ? ? ? 56 8B 74 24 ? F3 0F 10 46
	typedef void(__cdecl* AnglesToAxis_t)(vec3_t* angles, Matrix33_s* axis);
	inline extern AnglesToAxis_t AnglesToAxis = (AnglesToAxis_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x171A10, T6SDK::Addresses::t6mp + 0x0D01F0,
		T6SDK::Addresses::t6zmv41 + 0x0AC740, T6SDK::Addresses::t6zm + 0x029360).GetValue());

	//83 EC ? 56 8B 74 24 ? 57 8B 7C 24 ? 56 57 E8 ? ? ? ? F3 0F 10 47
	typedef void(__cdecl* AxisToAngles_t)(Matrix33_s* axis, vec3_t* angles);
	inline extern AxisToAngles_t AxisToAngles = (AxisToAngles_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x1A5E40, T6SDK::Addresses::t6mp + 0x1F4590,
		T6SDK::Addresses::t6zmv41 + 0x294260, T6SDK::Addresses::t6zm + 0x1872D0).GetValue());

	//83 EC ? 8B 4C 24 ? 56 57 8B 7C 24 ? 6A
	typedef int(__cdecl* CG_DObjGetWorldTagMatrix_t)(cpose_t* pose, PVOID obj, unsigned int tagName, Matrix33_s* tagMat, vec3_t* origin);
	inline extern CG_DObjGetWorldTagMatrix_t CG_DObjGetWorldTagMatrix = (CG_DObjGetWorldTagMatrix_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0FC740, T6SDK::Addresses::t6mp + 0x07AC00,
		T6SDK::Addresses::t6zmv41 + 0x29D500, T6SDK::Addresses::t6zm + 0x0EC3A0).GetValue());

	//51 8B 4C 24 10 56 57 8B 7C 24 14 6A FF 8D 44 24
	typedef bool(__cdecl* CG_DObjGetWorldTagPos_t)(cpose_t* pose, PVOID objEA, unsigned int tagName, vec3_t* pos);
	inline extern CG_DObjGetWorldTagPos_t CG_DObjGetWorldTagPos = (CG_DObjGetWorldTagPos_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0A1210, T6SDK::Addresses::t6mp + 0x264930,
		T6SDK::Addresses::t6zmv41 + 0x0A0EF0, T6SDK::Addresses::t6zm + 0x05E5E0).GetValue());

	//83 EC ? 8B 54 24 ? 53 8B 5C 24 ? 55 56 57 8B C3 E8 ? ? ? ? 8B E8
	typedef unsigned int(__cdecl* SL_GetStringOfSize_t)(const char* str, EntityType type, unsigned int len, int unk);
	inline extern SL_GetStringOfSize_t SL_GetStringOfSize = (SL_GetStringOfSize_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x227FE0, T6SDK::Addresses::t6mp + 0x208260,
		T6SDK::Addresses::t6zmv41 + 0x256D70, T6SDK::Addresses::t6zm + 0x018B40).GetValue());

	//* (DWORD*)(T6SDK::Memory::IdaSigScan("E8 ? ? ? ? 83 C4 ? 5F 5E 84 C0 74") + 1); //We find it in Demo_InitPlaybackData function
	typedef bool(__cdecl* Com_GameMode_IsMode_t)(eGameModes mode);
	inline extern Com_GameMode_IsMode_t Com_GameMode_IsMode = (Com_GameMode_IsMode_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x2F7570, T6SDK::Addresses::t6mp + 0x1B44C0,
		T6SDK::Addresses::t6zmv41 + 0x1B0BA0, T6SDK::Addresses::t6zm + 0x29BA80).GetValue());

	//E8 ? ? ? ? 84 C0 75 ? E8 ? ? ? ? 84 C0 75 ? A1 ? ? ? ? 8B 88
	typedef void(__cdecl* Demo_SwitchCamera_t)(int localClientNum);
	inline extern Demo_SwitchCamera_t Demo_SwitchCamera = (Demo_SwitchCamera_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x08E770, T6SDK::Addresses::t6mp + 0x206460,
		T6SDK::Addresses::t6zmv41 + 0x2107D0, T6SDK::Addresses::t6zm + 0x067C00).GetValue());

	//E8 ? ? ? ? F6 D8
	typedef bool(__cdecl* Demo_IsClipPlaying_t)();
	inline extern Demo_IsClipPlaying_t Demo_IsClipPlaying = (Demo_IsClipPlaying_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0B1130, T6SDK::Addresses::t6mp + 0x2C89A0,
		T6SDK::Addresses::t6zmv41 + 0x176DC0, T6SDK::Addresses::t6zm + 0x0A84B0).GetValue());

	//E8 ? ? ? ? 84 C0 75 ? 32 C0 C3 80 3D ? ? ? ? ? 74 ? A1 ? ? ? ? 8B 80
	typedef bool(__cdecl* Demo_IsClipPreviewRunning_t)();
	inline extern Demo_IsClipPreviewRunning_t Demo_IsClipPreviewRunning = (Demo_IsClipPreviewRunning_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x1FE170, T6SDK::Addresses::t6mp + 0x1D0E70,
		T6SDK::Addresses::t6zmv41 + 0x229350, T6SDK::Addresses::t6zm + 0x02D290).GetValue());

	//A1 ? ? ? ? 53 55 8B 6C 24 ? 33 DB
	typedef void(__cdecl* Demo_SwitchCameraMode_t)(int localClientNum, int newCamMode);
	inline extern Demo_SwitchCameraMode_t Demo_SwitchCameraMode = (Demo_SwitchCameraMode_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x005DE0, T6SDK::Addresses::t6mp + 0x1C4CB0,
		T6SDK::Addresses::t6zmv41 + 0x19E9F0, T6SDK::Addresses::t6zm + 0x300AC0).GetValue());

	//8B 0D ? ? ? ? 83 EC 08 53 8B 5C 24 18 B8 ? ? ? ? 66 39 04 59 0F 85 ? ? ? ? 55 56 57 8B 7C 24 1C 57 E8 ? ? ? ? 83 C4 04 33 F6 89 44 24 14
	typedef void(__cdecl* R_AddDObjToScene_t)(void* obj, entity_t* pose, unsigned int entnum, unsigned int renderFxFlags, 
		vec3_t* lightingOrigin, float* materialTime, float* burnFraction, char altXModel, int textureOverrideIndex, void* dobjConstantSet, float lightingOriginToleranceSq, float scale, bool isMarkableViewmodel);
	inline extern R_AddDObjToScene_t R_AddDObjToScene = (R_AddDObjToScene_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x3269C0, T6SDK::Addresses::t6mp + 0x325D00,
		T6SDK::Addresses::t6zmv41 + 0x324CC0, T6SDK::Addresses::t6zm + 0x323530).GetValue());

	//56 8B 74 24 ? 80 3E ? 75 ? 46
	typedef const char*(__cdecl* UI_SafeTranslateString_t)(const char* reference);
	inline extern UI_SafeTranslateString_t UI_SafeTranslateString = (UI_SafeTranslateString_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x05A8E0, T6SDK::Addresses::t6mp + 0x1E8830,
		T6SDK::Addresses::t6zmv41 + 0x1E3CA0, T6SDK::Addresses::t6zm + 0x00D010).GetValue());

	//E8 ? ? ? ? 84 C0 75 ? 33 C0 C3 80 7C 24
	typedef int(__cdecl* Demo_GetNextFreeCameraMode_t)(bool direction);
	inline extern Demo_GetNextFreeCameraMode_t Demo_GetNextFreeCameraMode = (Demo_GetNextFreeCameraMode_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x525FB0, T6SDK::Addresses::t6mp + 0x526160,
		T6SDK::Addresses::t6zmv41 + 0x523020, T6SDK::Addresses::t6zm + 0x523250).GetValue());

	//E8 ? ? ? ? 83 E8 ? 74 ? 48 74 ? 48 74
	typedef const char*(__cdecl* Demo_GetFreeCamModeName_t)();
	inline extern Demo_GetFreeCamModeName_t Demo_GetFreeCamModeName = (Demo_GetFreeCamModeName_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x28E680, T6SDK::Addresses::t6mp + 0x0C5E30,
		T6SDK::Addresses::t6zmv41 + 0x281C50, T6SDK::Addresses::t6zm + 0x0D6770).GetValue());
	
	//56 8B 74 24 ? 56 E8 ? ? ? ? 68 ? ? ? ? 56 E8 ? ? ? ? 6A
	typedef void (__cdecl* UI_CloseAll_t)(int localClientNum);
	inline extern UI_CloseAll_t UI_CloseAll = (UI_CloseAll_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x0529C0, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//83 EC ? F3 0F 10 05 ? ? ? ? 56 8B 74 24 ? F3 0F 10 4E
	typedef void (__cdecl* AngleVectors_t)(vec3_t* angles, vec3_t* forward, vec3_t* right, vec3_t* up);
	inline extern AngleVectors_t AngleVectors = (AngleVectors_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x05DC40, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//A1 ? ? ? ? 80 B8 ? ? ? ? ? 56
	typedef void (__cdecl* FX_ThroughWithEffect_t)(int localClientNum, unsigned int hEffect, bool forcekill);
	inline extern FX_ThroughWithEffect_t FX_ThroughWithEffect = (FX_ThroughWithEffect_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x1FBD70, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//80 3D ? ? ? ? ? 0F 85 ? ? ? ? 56 8B 35
	typedef void(__cdecl* SCR_UpdateScreen_t)();
	inline extern SCR_UpdateScreen_t SCR_UpdateScreen = (SCR_UpdateScreen_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x086E40, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//51 8B 44 24 ? 53 55 56 C6 00
	typedef int(__cdecl* Demo_GetNextDefaultBookmarkForPlayer_t)(int localClientNum, int index, int* type, int* time, vec4_t* color, bool* useBottomHalfColor, vec4_t* bottomHalfColor);
	inline extern Demo_GetNextDefaultBookmarkForPlayer_t Demo_GetNextDefaultBookmarkForPlayer = (Demo_GetNextDefaultBookmarkForPlayer_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x18D590, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

	//E8 ? ? ? ? F3 0F 10 05 ? ? ? ? 6A ? 83 E0
	typedef void(__cdecl* PlaySound_t)(const char* soundName);
	inline extern PlaySound_t PlaySound = (PlaySound_t)(T6SDK::CrossVersion::CrossValue<DWORD>(
		T6SDK::Addresses::t6mpv43 + 0x3F1580, T6SDK::Addresses::t6mp + FILLIN,
		T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue());

}
namespace T6SDK
{
	namespace InternalFunctions
	{	static float PI = 3.14159265f;
		static void AngleVectors(vec3_t* angles, vec3_t* forward, vec3_t* right, vec3_t* up)
		{
			T6SDK::Typedefs::AngleVectors(angles, forward, right, up);
		}
		static void UI_CloseAll()
		{
			T6SDK::Typedefs::UI_CloseAll(0);
		}
		static int R_TextWidth(const char* text, int iMaxLen, Font_s* pFont)
		{
			return T6SDK::Typedefs::R_TextWidth(0, text, iMaxLen, pFont);
		}
		static void R_AddCmdDrawTextInternal(const char* Text, int NumOfChars, Font_s* Font, float X, float Y, float ScaleX, float ScaleY, float unk1, tColor Color, int unk2)
		{
			T6SDK::Typedefs::R_AddCmdDrawTextInternal(Text, NumOfChars, Font, X, Y, ScaleX, ScaleY, unk1, Color, unk2);
		}
		static void UI_OpenToastPopup(const char* toastPopupIconName, const char* toastPopupTitle, const char* toastPopupDesc, int toastPopupDuration)
		{
			T6SDK::Typedefs::UI_OpenToastPopup(0, toastPopupIconName, toastPopupTitle, toastPopupDesc, toastPopupDuration);
		}
		static void UI_OpenToastPopup(const char* toastPopupTitle, const char* toastPopupDesc, int toastPopupDuration)
		{
			T6SDK::Typedefs::UI_OpenToastPopup(0, "menu_lobby_icon_blackops", toastPopupTitle, toastPopupDesc, toastPopupDuration);
		}
		static bool WorldPosToScreenPos(vec3_t* worldPos, vec2_t* outScreenPos)
		{
			return T6SDK::Typedefs::WorldPosToScreenPos(0, worldPos, outScreenPos);
		}
		static entity_t* CG_GetEntity(int index)
		{
			return T6SDK::Typedefs::CG_GetEntity(0, index);
		}
		static bool CG_IsScoreboardDisplayed()
		{
			return T6SDK::Typedefs::CG_IsScoreboardDisplayed(0);
		}
		static uiMenuCommand_t UI_GetActiveMenu()
		{
			return T6SDK::Typedefs::UI_GetActiveMenu(0);
		}
		static void Key_SetCatcher(int mask)
		{
			T6SDK::Typedefs::Key_SetCatcher(0, mask);
			T6SDK::Typedefs::Key_SetCatcher2(0, mask);
		}
		static void* DB_FindXAssetHeader(XAssetType type, const char* name)
		{
			return T6SDK::Typedefs::DB_FindXAssetHeader((BYTE)type, name, 0, -1);
		}
		static void* DB_FindXAssetHeader(BYTE type, const char* name)
		{
			return T6SDK::Typedefs::DB_FindXAssetHeader(type, name, 0, -1);
		}
		static void* Material_RegisterHandle(const char* name, int imageTrack)
		{
			return T6SDK::Typedefs::Material_RegisterHandle(name, imageTrack, true, -1);
		}
		static void FxSpriteAdd(FxSprite_t* sprite)
		{
			T6SDK::Typedefs::FxSpriteAdd(sprite);
		}
		static int FX_PlayOrientedEffect(void* def, int tick, vec3_t* origin, Matrix33_s* axis)
		{
			if(!def) return 0;
			return T6SDK::Typedefs::FX_PlayOrientedEffect(0, def, tick, origin, axis);
		}
		static void FX_ThroughWithEffect(unsigned int hEffect, bool forcekill)
		{
			T6SDK::Typedefs::FX_ThroughWithEffect(0, hEffect, forcekill);
		}
		static void R_AddOmniLightToScene(vec3_t org, float radius, float r, float g, float b, float a)
		{
			T6SDK::Typedefs::R_AddOmniLightToScene(&org, radius, r, g, b, a);
		}
		static void R_AddSpotLightToScene(vec3_t org, Matrix33_s axis, float radius, float fovInnerFraction, float startRadius, float endRadius, float r, float g, float b, float a, int lightDef)
		{
			T6SDK::Typedefs::R_AddSpotLightToScene(&org, &axis, radius, fovInnerFraction, startRadius, endRadius, r, g, b, a, lightDef);
		}
		static PVOID Com_GetClientDObj(entity_t* Entity)
		{
			return T6SDK::Typedefs::Com_GetClientDObj(Entity->nextState.number, Entity->pose.localClientNum);
		}
		static PVOID Com_GetClientDObj(int EntityClientNum, int localClientNum)
		{
			return T6SDK::Typedefs::Com_GetClientDObj(EntityClientNum, localClientNum);
		}

		static void MatrixSet44(vec4_t* out, vec3_t* origin, Matrix33_s* axis, float scale)
		{
			T6SDK::Typedefs::MatrixSet44(out, origin, axis, scale);
		}
		static void MatrixSet44(Matrix44_s* out, vec3_t* origin, Matrix33_s* axis, float scale)
		{
			T6SDK::Typedefs::MatrixSet44(out->m, origin, axis, scale);
		}
		static void MatrixMultiply44(vec4_t* in1, vec4_t* in2, vec4_t* out)
		{
			T6SDK::Typedefs::MatrixMultiply44(in1, in2, out);
		}
		static void MatrixMultiply44(Matrix44_s* in1, Matrix44_s* in2, Matrix44_s* out) //In-game multiply function sucks so fuck yeah i did it myself
		{
			//T6SDK::Typedefs::MatrixMultiply44(in1->m, in2->m, out->m);

			float a00 = in1->m[0][0];
			float a01 = in1->m[0][1];
			float a02 = in1->m[0][2];
			float a03 = in1->m[0][3];

			float a10 = in1->m[1][0];
			float a11 = in1->m[1][1];
			float a12 = in1->m[1][2];
			float a13 = in1->m[1][3];

			float a20 = in1->m[2][0];
			float a21 = in1->m[2][1];
			float a22 = in1->m[2][2];
			float a23 = in1->m[2][3];

			float a30 = in1->m[3][0];
			float a31 = in1->m[3][1];
			float a32 = in1->m[3][2];
			float a33 = in1->m[3][3];

			float b00 = in2->m[0][0];
			float b01 = in2->m[0][1];
			float b02 = in2->m[0][2];
			float b03 = in2->m[0][3];

			float b10 = in2->m[1][0];
			float b11 = in2->m[1][1];
			float b12 = in2->m[1][2];
			float b13 = in2->m[1][3];

			float b20 = in2->m[2][0];
			float b21 = in2->m[2][1];
			float b22 = in2->m[2][2];
			float b23 = in2->m[2][3];

			float b30 = in2->m[3][0];
			float b31 = in2->m[3][1];
			float b32 = in2->m[3][2];
			float b33 = in2->m[3][3];

			out->m[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
			out->m[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
			out->m[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
			out->m[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;

			out->m[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
			out->m[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
			out->m[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
			out->m[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;

			out->m[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
			out->m[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
			out->m[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
			out->m[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;

			out->m[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
			out->m[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
			out->m[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
			out->m[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
		}
		static void MatrixInverse44(vec4_t* mat, vec4_t* dst)
		{
			T6SDK::Typedefs::MatrixInverse44(mat, dst);
		}
		static void TransposeMatrix33(Matrix33_s* mat, Matrix33_s* dst)
		{
			int i, j;
			for (i = 0; i < 3; i++)
			{
				for (j = 0; j < 3; j++)
				{
					dst->m[i][j] = mat->m[j][i];
				}
			}
		}		
		static bool MatrixInverse44(Matrix44_s* mat, Matrix44_s* dst) //In-game inverse function sucks so fuck yeah i did it myself
		{
			//T6SDK::Typedefs::MatrixInverse44(mat->m, dst->m);
			float det;
			Matrix44_s tempMat{};
			Matrix44_s result{};
			tempMat.m[0][0] = mat->m[1][1] * mat->m[2][2] * mat->m[3][3] -
				mat->m[1][1] * mat->m[2][3] * mat->m[3][2] -
				mat->m[2][1] * mat->m[1][2] * mat->m[3][3] +
				mat->m[2][1] * mat->m[1][3] * mat->m[3][2] +
				mat->m[3][1] * mat->m[1][2] * mat->m[2][3] -
				mat->m[3][1] * mat->m[1][3] * mat->m[2][2];

			tempMat.m[1][0] = -mat->m[1][0] * mat->m[2][2] * mat->m[3][3] +
				mat->m[1][0] * mat->m[2][3] * mat->m[3][2] +
				mat->m[2][0] * mat->m[1][2] * mat->m[3][3] -
				mat->m[2][0] * mat->m[1][3] * mat->m[3][2] -
				mat->m[3][0] * mat->m[1][2] * mat->m[2][3] +
				mat->m[3][0] * mat->m[1][3] * mat->m[2][2];

			tempMat.m[2][0] = mat->m[1][0] * mat->m[2][1] * mat->m[3][3] -
				mat->m[1][0] * mat->m[2][3] * mat->m[3][1] -
				mat->m[2][0] * mat->m[1][1] * mat->m[3][3] +
				mat->m[2][0] * mat->m[1][3] * mat->m[3][1] +
				mat->m[3][0] * mat->m[1][1] * mat->m[2][3] -
				mat->m[3][0] * mat->m[1][3] * mat->m[2][1];

			tempMat.m[3][0] = -mat->m[1][0] * mat->m[2][1] * mat->m[3][2] +
				mat->m[1][0] * mat->m[2][2] * mat->m[3][1] +
				mat->m[2][0] * mat->m[1][1] * mat->m[3][2] -
				mat->m[2][0] * mat->m[1][2] * mat->m[3][1] -
				mat->m[3][0] * mat->m[1][1] * mat->m[2][2] +
				mat->m[3][0] * mat->m[1][2] * mat->m[2][1];

			tempMat.m[0][1] = -mat->m[0][1] * mat->m[2][2] * mat->m[3][3] +
				mat->m[0][1] * mat->m[2][3] * mat->m[3][2] +
				mat->m[2][1] * mat->m[0][2] * mat->m[3][3] -
				mat->m[2][1] * mat->m[0][3] * mat->m[3][2] -
				mat->m[3][1] * mat->m[0][2] * mat->m[2][3] +
				mat->m[3][1] * mat->m[0][3] * mat->m[2][2];

			tempMat.m[1][1] = mat->m[0][0] * mat->m[2][2] * mat->m[3][3] -
				mat->m[0][0] * mat->m[2][3] * mat->m[3][2] -
				mat->m[2][0] * mat->m[0][2] * mat->m[3][3] +
				mat->m[2][0] * mat->m[0][3] * mat->m[3][2] +
				mat->m[3][0] * mat->m[0][2] * mat->m[2][3] -
				mat->m[3][0] * mat->m[0][3] * mat->m[2][2];

			tempMat.m[2][1] = -mat->m[0][0] * mat->m[2][1] * mat->m[3][3] +
				mat->m[0][0] * mat->m[2][3] * mat->m[3][1] +
				mat->m[2][0] * mat->m[0][1] * mat->m[3][3] -
				mat->m[2][0] * mat->m[0][3] * mat->m[3][1] -
				mat->m[3][0] * mat->m[0][1] * mat->m[2][3] +
				mat->m[3][0] * mat->m[0][3] * mat->m[2][1];

			tempMat.m[3][1] = mat->m[0][0] * mat->m[2][1] * mat->m[3][2] -
				mat->m[0][0] * mat->m[2][2] * mat->m[3][1] -
				mat->m[2][0] * mat->m[0][1] * mat->m[3][2] +
				mat->m[2][0] * mat->m[0][2] * mat->m[3][1] +
				mat->m[3][0] * mat->m[0][1] * mat->m[2][2] -
				mat->m[3][0] * mat->m[0][2] * mat->m[2][1];

			tempMat.m[0][2] = mat->m[0][1] * mat->m[1][2] * mat->m[3][3] -
				mat->m[0][1] * mat->m[1][3] * mat->m[3][2] -
				mat->m[1][1] * mat->m[0][2] * mat->m[3][3] +
				mat->m[1][1] * mat->m[0][3] * mat->m[3][2] +
				mat->m[3][1] * mat->m[0][2] * mat->m[1][3] -
				mat->m[3][1] * mat->m[0][3] * mat->m[1][2];

			tempMat.m[1][2] = -mat->m[0][0] * mat->m[1][2] * mat->m[3][3] +
				mat->m[0][0] * mat->m[1][3] * mat->m[3][2] +
				mat->m[1][0] * mat->m[0][2] * mat->m[3][3] -
				mat->m[1][0] * mat->m[0][3] * mat->m[3][2] -
				mat->m[3][0] * mat->m[0][2] * mat->m[1][3] +
				mat->m[3][0] * mat->m[0][3] * mat->m[1][2];

			tempMat.m[2][2] = mat->m[0][0] * mat->m[1][1] * mat->m[3][3] -
				mat->m[0][0] * mat->m[1][3] * mat->m[3][1] -
				mat->m[1][0] * mat->m[0][1] * mat->m[3][3] +
				mat->m[1][0] * mat->m[0][3] * mat->m[3][1] +
				mat->m[3][0] * mat->m[0][1] * mat->m[1][3] -
				mat->m[3][0] * mat->m[0][3] * mat->m[1][1];

			tempMat.m[3][2] = -mat->m[0][0] * mat->m[1][1] * mat->m[3][2] +
				mat->m[0][0] * mat->m[1][2] * mat->m[3][1] +
				mat->m[1][0] * mat->m[0][1] * mat->m[3][2] -
				mat->m[1][0] * mat->m[0][2] * mat->m[3][1] -
				mat->m[3][0] * mat->m[0][1] * mat->m[1][2] +
				mat->m[3][0] * mat->m[0][2] * mat->m[1][1];

			tempMat.m[0][3] = -mat->m[0][1] * mat->m[1][2] * mat->m[2][3] +
				mat->m[0][1] * mat->m[1][3] * mat->m[2][2] +
				mat->m[1][1] * mat->m[0][2] * mat->m[2][3] -
				mat->m[1][1] * mat->m[0][3] * mat->m[2][2] -
				mat->m[2][1] * mat->m[0][2] * mat->m[1][3] +
				mat->m[2][1] * mat->m[0][3] * mat->m[1][2];

			tempMat.m[1][3] = mat->m[0][0] * mat->m[1][2] * mat->m[2][3] -
				mat->m[0][0] * mat->m[1][3] * mat->m[2][2] -
				mat->m[1][0] * mat->m[0][2] * mat->m[2][3] +
				mat->m[1][0] * mat->m[0][3] * mat->m[2][2] +
				mat->m[2][0] * mat->m[0][2] * mat->m[1][3] -
				mat->m[2][0] * mat->m[0][3] * mat->m[1][2];

			tempMat.m[2][3] = -mat->m[0][0] * mat->m[1][1] * mat->m[2][3] +
				mat->m[0][0] * mat->m[1][3] * mat->m[2][1] +
				mat->m[1][0] * mat->m[0][1] * mat->m[2][3] -
				mat->m[1][0] * mat->m[0][3] * mat->m[2][1] -
				mat->m[2][0] * mat->m[0][1] * mat->m[1][3] +
				mat->m[2][0] * mat->m[0][3] * mat->m[1][1];

			tempMat.m[3][3] = mat->m[0][0] * mat->m[1][1] * mat->m[2][2] -
				mat->m[0][0] * mat->m[1][2] * mat->m[2][1] -
				mat->m[1][0] * mat->m[0][1] * mat->m[2][2] +
				mat->m[1][0] * mat->m[0][2] * mat->m[2][1] +
				mat->m[2][0] * mat->m[0][1] * mat->m[1][2] -
				mat->m[2][0] * mat->m[0][2] * mat->m[1][1];

			det = mat->m[0][0] * tempMat.m[0][0] + mat->m[0][1] * tempMat.m[1][0] + mat->m[0][2] * tempMat.m[2][0] + mat->m[0][3] * tempMat.m[3][0];

			if (det == 0.0f)
				return false;

			det = 1.0f / det;

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					result.m[i][j] = tempMat.m[i][j] * det;
				}
			}
			*dst = result;
			return true;
		}
		static void AnglesToAxis(vec3_t* angles, Matrix33_s* axis)
		{
			T6SDK::Typedefs::AnglesToAxis(angles, axis);
		}
		
		static void AxisToAngles(Matrix33_s* axis, vec3_t* angles)
		{
			//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "INTERNAL FUNC", "UnHooking AxisToAngles... OutFunc: 0x%X", T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.OutFunc);
			T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.UnHook();
			T6SDK::Typedefs::AxisToAngles(axis, angles);
			T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.ReHook();
		}
		static Matrix33_s GetRotation33FromMatrix44(Matrix44_s* tagMat)
		{
			Matrix33_s rotation = {vec3_t{tagMat->m[0][0], tagMat->m[0][1], tagMat->m[0][2]}, vec3_t{tagMat->m[1][0], tagMat->m[1][1], tagMat->m[1][2]}, vec3_t{tagMat->m[2][0], tagMat->m[2][1], tagMat->m[2][2]}};	
			return rotation;
		}
		static vec3_t GetAnglesFromMatrix44(Matrix44_s* tagMat)
		{
			vec3_t angles{};
			Matrix33_s mat = GetRotation33FromMatrix44(tagMat);
			AxisToAngles(&mat, &angles);
			return angles;
		}
		static vec3_t GetOriginFromMatrix44(Matrix44_s* tagMat)
		{
			vec3_t origin = {tagMat->m[3][0], tagMat->m[3][1], tagMat->m[3][2]};
			return origin;
		}
		static float Distance(vec3_t vec1, vec3_t vec2)
		{
			vec3_t vec{};
			return vec.Distance(vec1, vec2);
		}
		static vec3_t VectorToAngles(vec3_t src, vec3_t dst)
		{
			float pitch = -atan2f(src.x - dst.x, src.y - dst.y) / PI * 180.0f + 270.0f;
			if (pitch > 360.0f)
				pitch -= 360.0f;
			if (pitch < 0.0f)
				pitch += 360.0f;
			float yaw = -asinf((src.z - dst.z) / Distance(src, dst)) / PI * 180.0f;
			if (yaw > 360.0f)
				yaw -= 360.0f;
			if (yaw < 0.0f)
				yaw += 360.0f;
			return vec3_t(yaw, pitch, 0.0f);
		}

		static bool CG_DObjGetWorldTagMatrix(cpose_t* pose, PVOID obj, unsigned int tagName, Matrix33_s* tagMat, vec3_t* origin)
		{
			return T6SDK::Typedefs::CG_DObjGetWorldTagMatrix(pose, obj, tagName, tagMat, origin);
		}
		static bool CG_DObjGetWorldTagMatrix(entity_t* entity, unsigned int tagName, Matrix33_s* tagMat, vec3_t* origin)
		{
			PVOID DObj = Com_GetClientDObj(entity);

			if (!DObj)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "INTERNAL FUNC", "CG_DObjGetWorldTagMatrix failed on DObj");
				return FALSE;
			}
			return T6SDK::Typedefs::CG_DObjGetWorldTagMatrix(&entity->pose, DObj, tagName, tagMat, origin) != 0x00;
		}
		static bool CG_DObjGetWorldTagPos(cpose_t* pose, PVOID obj, unsigned int tagName, vec3_t* pos)
		{
			return T6SDK::Typedefs::CG_DObjGetWorldTagPos(pose, obj, tagName, pos);
		}
		static bool CG_DObjGetWorldTagPos(entity_t* entity, unsigned int tagName, vec3_t* pos)
		{
			PVOID DObj = Com_GetClientDObj(entity);

			if (!DObj)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "INTERNAL FUNC", "CG_DObjGetWorldTagMatrix failed on DObj");
				return FALSE;
			}
			return T6SDK::Typedefs::CG_DObjGetWorldTagPos(&entity->pose, DObj, tagName, pos);
		}

		static unsigned int SL_GetStringOfSize(const char* str, EntityType type)
		{
			return T6SDK::Typedefs::SL_GetStringOfSize(str, type, strlen(str)+1, 6);
		}

		static bool Com_GameMode_IsMode(eGameModes mode)
		{
			return T6SDK::Typedefs::Com_GameMode_IsMode(mode);
		}

		static void GrabRefDefViewAxisMatrix(bool state)
		{
			if (state)
			{
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix1.Patch();
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix2.Patch();
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix3.Patch();
			}
			else
			{
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix1.UnPatch();
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix2.UnPatch();
				T6SDK::Addresses::Patches::GrabRefDefViewAxisMatrix3.UnPatch();
			}
		}

		static const char* UI_SafeTranslateString(const char* referense)
		{
			return T6SDK::Typedefs::UI_SafeTranslateString(referense);
		}

		static void SCR_UpdateScreen(int count)
		{
			for(int i = 0; i < count; i++)
			{
				T6SDK::Typedefs::SCR_UpdateScreen();
			}
		}
		static int Demo_GetNextDefaultBookmarkForPlayer(int index, int* type, int* time, vec4_t* color)
		{
			bool useBottomHalfColor = false;
			vec4_t bottomHalfColor{};
			return T6SDK::Typedefs::Demo_GetNextDefaultBookmarkForPlayer(0, index, type, time, color, &useBottomHalfColor, &bottomHalfColor);
		}
		static void PlaySound(const char* soundName)
		{
			__asm
			{
				mov eax, 0x69AA70
				call eax
			}
			T6SDK::Typedefs::PlaySound(soundName);
		}

		#pragma region Misc (not part of engine)
		static OPENFILENAME ofn;
		
		static bool OpenFileDialog(TCHAR szFileName[], bool saveDialog = false, const TCHAR* filter = NULL, const TCHAR* title = NULL)
		{
			const TCHAR* FilterSpec;
			const TCHAR* Title;
			FilterSpec = (const TCHAR*)filter;
			Title = (const TCHAR*)title;

			TCHAR szFileTitle[MAX_PATH] = { '\0' };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			*szFileName = 0;

			/* fill in non-variant fields of OPENFILENAME struct. */
			ofn.lStructSize = sizeof(OPENFILENAME);

			ofn.hwndOwner = GetFocus();
			ofn.lpstrFilter = FilterSpec;
			ofn.lpstrCustomFilter = NULL;
			ofn.nMaxCustFilter = 0;
			ofn.nFilterIndex = 1;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrFile[0] = '\0';
			//ofn.lpstrInitialDir = myDir; // Initial directory.
			ofn.lpstrFileTitle = szFileTitle;
			ofn.nMaxFileTitle = MAX_PATH;
			ofn.lpstrTitle = Title;
			//ofn.lpstrDefExt = 0; // I've set to null for demonstration
			ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
			ShowCursor(true);
			if (saveDialog)
			{
				if (GetSaveFileName(&ofn) == 1)
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "SAVE FILE DIALOG", "SaveFileDialog succeeded!");
					return 1;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "SAVE FILE DIALOG", "SaveFileDialog failed or user cancelled the operation!");
					return 0;
				}
			}
			else
			{
				if (GetOpenFileName(&ofn) == 1)
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "OPEN FILE DIALOG", "OpenFileDialog succeeded!");
					return 1;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "OPEN FILE DIALOG", "OpenFileDialog failed or user cancelled the operation!");
					return 0;
				}
			}
		}
		static bool StringEndsWith(std::string const& fullString, std::string const& ending) {
			if (fullString.length() >= ending.length()) {
				return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
			}
			else {
				return false;
			}
		}
		static void CreateDirectoryForFile(std::string filename)
		{
			std::wstring wide_string(filename.begin(), filename.end());

			wchar_t* path = (wchar_t*)wide_string.c_str();

			wchar_t folder[MAX_PATH];
			wchar_t* end;
			ZeroMemory(folder, MAX_PATH * sizeof(wchar_t));

			end = wcschr(path, L'\\');

			while (end != NULL)
			{
				wcsncpy(folder, path, end - path + 1);
				if (!CreateDirectory((LPTSTR)folder, NULL))
				{
					DWORD err = GetLastError();

					if (err != ERROR_ALREADY_EXISTS)
					{
						// do whatever handling you'd like
					}
				}
				end = wcschr(++end, L'\\');
			}
		}

		static bool CreateNewDirectory(const char* fullPath)
		{
			// Call CreateDirectoryA to create the directory
			if (CreateDirectory(fullPath, NULL)) 
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "DIRECTORY", "Directory %s created successfully.", fullPath);
				return true;
			}
			else 
			{
				// Get the error code if the function fails
				DWORD error = GetLastError();
				if (error == ERROR_ALREADY_EXISTS)
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, true, "DIRECTORY", "Directory %s already exists.", fullPath);
					return true;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DIRECTORY", "Failed to create directory %s. Error code: .", fullPath, error);
				}
				return false;
			}
		}
		static std::string getCurrentDateTimeString() 
		{
			// Get the current time
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			// Format the time as a string (e.g., "2023-10-05_14-30-45")
			std::stringstream ss{};
			ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");
			return ss.str();
		}

		// Function to open a folder dialog and return the selected folder path
		static bool OpenFolderDialog(std::string& folderPath) 
		{
			ShowCursor(true);
			// Initialize the COM library
			HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
			if (FAILED(hr)) {
				std::cerr << "Failed to initialize COM library." << std::endl;
				return false;
			}

			// Create the File Open Dialog object
			IFileOpenDialog* pFileOpen = nullptr;
			hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));
			if (FAILED(hr)) {
				std::cerr << "Failed to create File Open Dialog." << std::endl;
				CoUninitialize();
				return false;
			}

			// Set options to select folders instead of files
			DWORD dwOptions;
			pFileOpen->GetOptions(&dwOptions);
			pFileOpen->SetOptions(dwOptions | FOS_PICKFOLDERS);

			// Show the dialog
			hr = pFileOpen->Show(NULL);
			if (FAILED(hr)) {
				std::cerr << "User canceled the dialog or an error occurred." << std::endl;
				pFileOpen->Release();
				CoUninitialize();
				return false;
			}

			// Get the selected folder
			IShellItem* pItem = nullptr;
			hr = pFileOpen->GetResult(&pItem);
			if (FAILED(hr)) {
				std::cerr << "Failed to get selected folder." << std::endl;
				pFileOpen->Release();
				CoUninitialize();
				return false;
			}

			// Get the folder path
			PWSTR pszFilePath = nullptr;
			hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
			if (SUCCEEDED(hr)) {
				// Convert the wide string to a std::string
				char buffer[MAX_PATH];
				WideCharToMultiByte(CP_UTF8, 0, pszFilePath, -1, buffer, MAX_PATH, NULL, NULL);
				folderPath = buffer;

				// Free the memory allocated for the path
				CoTaskMemFree(pszFilePath);
			}
			else {
				std::cerr << "Failed to get folder path." << std::endl;
				pItem->Release();
				pFileOpen->Release();
				CoUninitialize();
				return false;
			}

			// Release COM objects
			pItem->Release();
			pFileOpen->Release();

			// Uninitialize the COM library
			CoUninitialize();

			return true;
		}

		static bool SetClipboardText(const std::string& text)
		{
			// Open the clipboard
			if (!OpenClipboard(nullptr)) {
				// Handle error
				return false;
			}
			// Empty the clipboard
			if (!EmptyClipboard()) {
				// Handle error
				CloseClipboard();
				return false;
			}
			// Allocate global memory for the text
			HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
			if (!hGlobal) 
			{
				// Handle error
				CloseClipboard();
				return false;
			}
			// Copy the text to the global memory
			char* pGlobal = static_cast<char*>(GlobalLock(hGlobal));
			if (pGlobal) 
			{
				memcpy(pGlobal, text.c_str(), text.size() + 1);
				GlobalUnlock(hGlobal);
			}
			else 
			{
				// Handle error
				GlobalFree(hGlobal);
				CloseClipboard();
				return false;
			}

			// Set the clipboard data
			if (!SetClipboardData(CF_TEXT, hGlobal)) 
			{
				// Handle error
				GlobalFree(hGlobal);
				CloseClipboard();
				return false;
			}

			// Close the clipboard
			CloseClipboard();

			return true;
		}
		static std::vector<char> readBytesSimple(const std::string& filename) 
		{
			// Open file in binary mode
			std::ifstream file(filename, std::ios::binary);

			if (!file) 
			{
				throw std::runtime_error("Cannot open file: " + filename);
			}

			// Get file size
			file.seekg(0, std::ios::end);
			std::streampos fileSize = file.tellg();
			file.seekg(0, std::ios::beg);

			// Read file contents into vector
			std::vector<char> fileData(fileSize);
			file.read(fileData.data(), fileSize);

			return fileData;
		}
		static std::string removeExtension(std::filesystem::path filepath) 
		{
			// Replace extension with empty string
			return filepath.replace_extension().string();
		}
		static std::vector<std::string> splitString(const std::string& str, char delimiter, bool keepEmpty = false) 
		{
			std::vector<std::string> tokens;
			size_t start = 0;
			size_t end = str.find(delimiter);

			while (end != std::string::npos) {
				if (keepEmpty || (end - start) > 0) {
					tokens.push_back(str.substr(start, end - start));
				}
				start = end + 1;
				end = str.find(delimiter, start);
			}

			if (keepEmpty || (str.size() - start) > 0) {
				tokens.push_back(str.substr(start));
			}

			return tokens;
		}
		static std::string FormatUnixTime(time_t unixTime) 
		{
			std::stringstream oss{};
			oss << std::put_time(std::localtime(&unixTime), "%A %d %B %Y %H:%M");
			return oss.str();
		}
		static std::vector<std::filesystem::path> find_files_by_extension(const std::filesystem::path& root, const std::string& ext)
		{
			std::vector<std::filesystem::path> results;
			try
			{
				for (const auto& entry : std::filesystem::recursive_directory_iterator(root))
				{
					if (entry.is_regular_file() && entry.path().extension() == ext)
					{
						results.push_back(entry.path());
					}
				}
			}
			catch (const std::filesystem::filesystem_error& e)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "T6SDK", "Error accessing path: %s -> %s", root.c_str(), e.what());
			}
			return results;
		}

		static std::string getFilenameFromPath(const std::string& path) 
		{
			return std::filesystem::path(path).filename().string();
		}
#pragma endregion
	}
}