#pragma once
#include "StdInclude.h"
#define FILLIN 0x00
namespace T6SDK::Addresses
{
    inline static uintptr_t t6mpv43 = (uintptr_t)GetModuleHandle("t6mpv43.exe");
    inline static uintptr_t t6mp = (uintptr_t)GetModuleHandle("t6mp.exe");
    inline static uintptr_t t6zmv41 = (uintptr_t)GetModuleHandle("t6zmv41.exe");
    inline static uintptr_t t6zm = (uintptr_t)GetModuleHandle("t6zm.exe");
    namespace HookAddresses
    {
        //89 AE 8C 80 04 00 A1
        inline static T6SDK::MemoryHook h_TickChanged(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x11D663, T6SDK::Addresses::t6mp + 0x15CAA3,
            T6SDK::Addresses::t6zmv41 + 0x19BB91, T6SDK::Addresses::t6zm + 0x141AD1).GetValue(), 6);

        //81 40 18 ? ? ? ? E8 ? ? ? ? A1 ? ? ? ? 81 40 ? ? ? ? ? 53
        inline static T6SDK::MemoryHook h_EndFrameDrawn(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3EF9C3, T6SDK::Addresses::t6mp + 0x3EEE13,
            T6SDK::Addresses::t6zmv41 + 0x3EF1B3, T6SDK::Addresses::t6zm + 0x3EDFE3).GetValue(), 7);

        //68 ? ? ? ? 52 E8 ? ? ? ? 8B 74 24 54
        inline static T6SDK::MemoryHook h_DisplayMarkerInfo(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x2DFF0E, T6SDK::Addresses::t6mp + 0x17BADE,
            T6SDK::Addresses::t6zmv41 + 0x13509E, T6SDK::Addresses::t6zm + 0x116C6E).GetValue(), 6);

        //89 84 24 AC 00 00 00 E8 ? ? ? ? F3 0F 10 05
        inline static T6SDK::MemoryHook h_TheaterControlsDrawn(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x58EE55, T6SDK::Addresses::t6mp + 0x58EE45,
            T6SDK::Addresses::t6zmv41 + 0x58B715, T6SDK::Addresses::t6zm + 0x58BD15).GetValue(), 7);

        //8B 74 24 ? 55 57 8B C6 - what is this?
        //51 52 50 33 FF
        inline static T6SDK::MemoryHook h_Com_EventLoopKeyEvent(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x21E8AB, T6SDK::Addresses::t6mp + 0x1F376B,
            T6SDK::Addresses::t6zmv41 + 0x3801B, T6SDK::Addresses::t6zm + 0x173BFB).GetValue(), 6);

        //53 8B 5C 24 ? 56 8B 74 24 ? 83 BE ? ? ? ? ? 74
        inline static T6SDK::MemoryHook h_CG_DrawActiveFrame(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x067DE0, T6SDK::Addresses::t6mp + 0x15D0C0, // T6SDK::Addresses::t6mpv43 + 0x11DC80,
            T6SDK::Addresses::t6zmv41 + 0x1211B0, T6SDK::Addresses::t6zm + 0x1420F9).GetValue(), 5);

        //05 ? ? ? ? 50 E8 ? ? ? ? 6A ? E8 ? ? ? ? 6A 00
        inline static T6SDK::MemoryHook h_Demo_AddDollyCamMarker(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x52903B, T6SDK::Addresses::t6mp + 0x5291EB,
            T6SDK::Addresses::t6zmv41 + 0x5260AB, T6SDK::Addresses::t6zm + 0x5262DB).GetValue(), 5);

        //89 B0 ? ? ? ? E8 ? ? ? ? 83 C4 ? 5F 5E 5D
        inline static T6SDK::MemoryHook h_FreeCameraModeChanged(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x01C4FA, T6SDK::Addresses::t6mp + 0x0B3EDA,
            T6SDK::Addresses::t6zmv41 + 0x121D8C, T6SDK::Addresses::t6zm + 0x29140C).GetValue(), 6);

        //83 F8 0A 75 ? F3 0F 10 05 ? ? ? ? F3 0F 11 05
        inline static T6SDK::MemoryHook h_AspectRatioChanged(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3352A6, T6SDK::Addresses::t6mp + 0x3345E6,
            T6SDK::Addresses::t6zmv41 + 0x3339A6, T6SDK::Addresses::t6zm + 0x3321F6).GetValue(), 70);

        // I know we have a detour for that but i cant Invoke event from detoured func somehow
        //A1 ? ? ? ? 53 55 8B 6C 24 ? 33 DB + 0x1C
        inline static T6SDK::MemoryHook h_Demo_SwitchCameraMode(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x005DE0+0x1C, T6SDK::Addresses::t6mp + 0x105DE0 + 0x1C,
            T6SDK::Addresses::t6zmv41 + 0x19E9F0+0x1C, T6SDK::Addresses::t6zm + 0x300AC0 + 0x1C).GetValue(), 6);

        //F3 0F 11 44 24 ? F3 0F 11 87 ? ? ? ? F3 0F 10 46
        inline static T6SDK::MemoryHook h_NearClipping(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x330D50, T6SDK::Addresses::t6mp + 0x330090,
            T6SDK::Addresses::t6zmv41 + 0x32F430, T6SDK::Addresses::t6zm + 0x32DCA0).GetValue(), 6);

        //8D 9E ? ? ? ? E8 ? ? ? ? 8D 4C 24 ? 51 57
        inline static T6SDK::MemoryHook h_UnlockGunAngles(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3E1487, T6SDK::Addresses::t6mp + 0x3E0BF7,
            T6SDK::Addresses::t6zmv41 + 0x3E1847, T6SDK::Addresses::t6zm + 0x3E0707).GetValue(), 6);

        //68 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 83 C4 ? 03 C3 A3 ? ? ? ? EB
        inline static T6SDK::MemoryHook h_GameLoaded(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x104BCA, T6SDK::Addresses::t6mp + 0x185F3A,
			T6SDK::Addresses::t6zmv41 + 0x11AEAA, T6SDK::Addresses::t6zm + 0x5147A).GetValue(), 5);

        inline static T6SDK::MemoryHook h_UnlockCameraRollHook(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x143276, T6SDK::Addresses::t6mp + 0x1246C6,
			T6SDK::Addresses::t6zmv41 + 0x18B5C6, T6SDK::Addresses::t6zm + 0x10A1A6).GetValue(), 6);

        //89 8F 8C ? ? ? 8B 86 ? ? ? ? 50
        inline static T6SDK::MemoryHook h_PovCamoWritingHook(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x5406DD, T6SDK::Addresses::t6mp + 0x54089D,
			T6SDK::Addresses::t6zmv41 + 0x53D66D, T6SDK::Addresses::t6zm + 0x53D8DD).GetValue(), 6);

        //B9 3E 00 00 00 F3 A5 E8 ? ? ? ? 83 8D
        inline static T6SDK::MemoryHook h_CamoChangingCinePatch(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3075C3, T6SDK::Addresses::t6mp + 0x249733,
            T6SDK::Addresses::t6zmv41 + 0x142733, T6SDK::Addresses::t6zm + 0x3E443).GetValue(), 5);

        //F3 0F 11 44 24 ? F3 0F 10 47 ? F3 0F 11 44 24 ? F3 0F 10 47 ? F3 0F 11 44 24 ? F3 0F 10 46 ? 0F 57 C3 -> movss dword ptr [esi+ ^HERE^ 8], xmm0
        inline static T6SDK::MemoryHook h_AxisToAnglesHook(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x1A5FC9, T6SDK::Addresses::t6mp + 0x1F4719,
			T6SDK::Addresses::t6zmv41 + 0x2943E9, T6SDK::Addresses::t6zm + 0x187459).GetValue(), 5);

        //E8 ? ? ? ? 83 C4 ? A1 ? ? ? ? 50 E8 ? ? ? ? 83 C4 ? 85 C0 75 ? 84 DB the follwing call func
        inline static T6SDK::MemoryHook h_Com_GameMode_SetMode(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x1B9C73, T6SDK::Addresses::t6mp + 0x2A53,
            T6SDK::Addresses::t6zmv41 + 0x2D9DB3, T6SDK::Addresses::t6zm + 0x1940A3).GetValue(), 7);

        //F3 0F 11 80 ? ? ? ? E8 ? ? ? ? C6 05
        inline static T6SDK::MemoryHook h_InitDemoPlaybackData(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x1AE42A, T6SDK::Addresses::t6mp + 0x239C1A,
            T6SDK::Addresses::t6zmv41 + 0x243C4A, T6SDK::Addresses::t6zm + 0x1E80A).GetValue(), 8);

        //8B 82 ? ? ? ? 6A ? A3 ? ? ? ? E8 ? ? ? ? 83 C4 ? EB ? 50
        inline static T6SDK::MemoryHook h_SunInited(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x19D1DF, T6SDK::Addresses::t6mp + 0x296BDF,
            T6SDK::Addresses::t6zmv41 + 0x27686F, T6SDK::Addresses::t6zm + 0x31B2F).GetValue(), 6);

        //8B 86 ? ? ? ? 8D 4C 24 ? 51 8D 54 24 ? 52 57
        inline static T6SDK::MemoryHook h_CG_Item(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3A20B0, T6SDK::Addresses::t6mp + 0x3A1420,
            T6SDK::Addresses::t6zmv41 + 0x3A0AF0, T6SDK::Addresses::t6zm + 0x39F700).GetValue(), 6);

        //83 BE ? ? ? ? ? 74 ? 56 53 E8 ? ? ? ? 83 C4 ? 8D 86 //TODO REDO t6mp, t6zm
        inline static T6SDK::MemoryHook h_CG_ProcessEntity(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x67DEA, T6SDK::Addresses::t6mp + 0x18779A,
            T6SDK::Addresses::t6zmv41 + 0x1211BA, T6SDK::Addresses::t6zm + 0xCD4EA).GetValue(), 7);

        //E8 ? ? ? ? 57 E8 ? ? ? ? 83 C4 ? 84 C0 74 ? 53 -> following [pop esi]
        inline static T6SDK::MemoryHook h_CG_CalcEntityLerpPositions(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x2B9B58, T6SDK::Addresses::t6mp + 0x69AF8,
            T6SDK::Addresses::t6zmv41 + 0x2A37D8, T6SDK::Addresses::t6zm + 0x143C28).GetValue(), 5);
    }
    namespace DetoursAddresses
    {
        //E8 ? ? ? ? 84 C0 75 ? E8 ? ? ? ? 84 C0 75 ? A1 ? ? ? ? 8B 88
        inline static T6SDK::CDetourHook DetouredSwitchCameraHook("Demo_SwitchCamera", (void*)T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x08E770, T6SDK::Addresses::t6mp + 0x206460,
            T6SDK::Addresses::t6zmv41 + 0x2107D0, T6SDK::Addresses::t6zm + 0x067C00).GetValue());

        //8B 0D ? ? ? ? 83 EC 08 53 8B 5C 24 18 B8 ? ? ? ? 66 39 04 59 0F 85 ? ? ? ? 55 56 57 8B 7C 24 1C 57 E8 ? ? ? ? 83 C4 04 33 F6 89 44 24 14
        inline static T6SDK::CDetourHook DetouredAddDObjToScene("R_AddDObjToScene", (void*)T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3269C0, T6SDK::Addresses::t6mp + 0x325D00,
            T6SDK::Addresses::t6zmv41 + 0x324CC0, T6SDK::Addresses::t6zm + 0x323530).GetValue());

        //56 8B 74 24 ? 80 3E ? 75 ? 46
        inline static T6SDK::CDetourHook DetouredUI_SafeTranslateStringHook("UI_SafeTranslateString", (void*)T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x05A8E0, T6SDK::Addresses::t6mp + 0x1E8830,
            T6SDK::Addresses::t6zmv41 + 0x1E3CA0, T6SDK::Addresses::t6zm + 0x00D010).GetValue());

        //E8 ? ? ? ? 84 C0 75 ? 33 C0 C3 80 7C 24
        inline static T6SDK::CDetourHook DetouredGetNextFreeCameraModeHook("Demo_GetNextFreeCameraMode", (void*)T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x525FB0, T6SDK::Addresses::t6mp + 0x526160,
            T6SDK::Addresses::t6zmv41 + 0x523020, T6SDK::Addresses::t6zm + 0x523250).GetValue());

        //E8 ? ? ? ? 83 E8 ? 74 ? 48 74 ? 48 74
        inline static T6SDK::CDetourHook DetouredGetFreeCamModeNameHook("Demo_GetFreeCamModeName", (void*)T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x28E680, T6SDK::Addresses::t6mp + 0x0C5E30,
            T6SDK::Addresses::t6zmv41 + 0x181C50, T6SDK::Addresses::t6zm + 0x0D6770).GetValue());
    }
    namespace Patches
    {
        //8B 0D ? ? ? ? 85 C9 74 ? 33 C0 39 41 ? 0F 95 C0 84 C0 74 ? 56 8B 74 24 ? 56 E8 ? ? ? ? 83 C4 ? 84 C0 75 ? 83 3D ? ? ? ? ? 75 ? A1
        inline static T6SDK::MemoryPatch PreventDemoScoreboardOpen(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x194CC0, T6SDK::Addresses::t6mp + 0x137F80,
            T6SDK::Addresses::t6zmv41 + 0x2B3C20, T6SDK::Addresses::t6zm + 0x29B5C0).GetValue() + 0x4E, { 0x6A, 0x00 });
        
        //8B 54 24 ? 8B 44 24 ? 52 50 56 E8 ? ? ? ? 83 C4 ? 5D
        inline static T6SDK::MemoryPatch PreventDemoNavigation(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x1F4505, T6SDK::Addresses::t6mp + 0x23BB15,
            T6SDK::Addresses::t6zmv41 + 0x1B39D5, T6SDK::Addresses::t6zm + 0x2D6065).GetValue() + 0x0B, { 0x90, 0x90, 0x90, 0x90, 0x90 }); //NOP for 5 bytes

        //8B 44 24 0C F3 0F 58 D0 F3 0F 10 44 24 08 F3 0F 11 10 F3 0F 11 40 04 F3 0F 11 48 08
        inline static T6SDK::MemoryPatch PreventDollyCamAnglesWriting(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x03EF2E, T6SDK::Addresses::t6mp + 0x1CD39E,
            T6SDK::Addresses::t6zmv41 + 0x09E5FE, T6SDK::Addresses::t6zm + 0x2D9D5E).GetValue() + 0x0E, { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); //NOP for 14 bytes

        //F3 0F 11 7D 00 F3 0F 11 6D 04 F3 0F 11 75 08 F3 0F 11 7C 24 20 F3 0F 11 6C 24 24 F3 0F 11 74 24 28
        inline static T6SDK::MemoryPatch PreventDollyCamPositonWriting(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x526286, T6SDK::Addresses::t6mp + 0x526436,
            T6SDK::Addresses::t6zmv41 + 0x5232F6, T6SDK::Addresses::t6zm + 0x523526).GetValue(),
            { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 }); //NOP for 33 bytes

        //E8 ? ? ? ? 8B 15 ? ? ? ? 52 E8 ? ? ? ? 83 C4 ? 84 C0 74 ? 8D 44 24 ? EB
        inline static T6SDK::MemoryPatch PreventFreeRoamCameraWriting(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x143425, T6SDK::Addresses::t6mp + 0x124875,
            T6SDK::Addresses::t6zmv41 + 0x18B775, T6SDK::Addresses::t6zm + 0x10A355).GetValue(), { 0x90, 0x90, 0x90, 0x90, 0x90 });

        //8B 15 ? ? ? ? 51 F3 0F 11 44 24
        inline static T6SDK::MemoryPatch RemoveSkyBoxPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x32F596, T6SDK::Addresses::t6mp + 0x32E8D6,
            T6SDK::Addresses::t6zmv41 + 0x32DC76, T6SDK::Addresses::t6zm + 0x32C4E6).GetValue(), { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x51, 0xF3, 0x0F, 0x11, 0x44, 0x24 });

        //E8 ? ? ? ? 53 E8 ? ? ? ? 83 C4 0C 83 BE A0 80 04 00 01
        inline static T6SDK::MemoryPatch GrabRefDefViewAxisMatrix1(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3D75A8, T6SDK::Addresses::t6mp + 0x3D6CB8,
            T6SDK::Addresses::t6zmv41 + 0x3D780E, T6SDK::Addresses::t6zm + 0x3D656E).GetValue(), {0x90, 0x90, 0x90, 0x90, 0x90}); //Second call of AnglesToAxis in CG_CalcViewValues

        //56 51 F3 0F 11 44 24 ? E8 ? ? ? ? 83 C4 ? 5F
        inline static T6SDK::MemoryPatch GrabRefDefViewAxisMatrix2(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x3D6012, T6SDK::Addresses::t6mp + 0x3D5722,
            T6SDK::Addresses::t6zmv41 + 0x3D6252, T6SDK::Addresses::t6zm + 0x3D4FB2).GetValue() + 0x08, { 0x90, 0x90, 0x90, 0x90, 0x90 }); //AnglesToAxis in CG_OffsetThirdPersonView

        //81 C1 ? ? ? ? 51 E8 ? ? ? ? A1 ? ? ? ? D9 80
        inline static T6SDK::MemoryPatch GrabRefDefViewAxisMatrix3(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x030C11, T6SDK::Addresses::t6mp + 0x2B00C1,
            T6SDK::Addresses::t6zmv41 + 0x1FB261, T6SDK::Addresses::t6zm + 0x225271).GetValue() + 0x07, { 0x90, 0x90, 0x90, 0x90, 0x90 }); //AnglesToAxis in Demo_FreeCameraCalcView

        //E8 ? ? ? ? 84 C0 75 01 C3 E8 ? ? ? ? 84 C0 75 0B 33 C0 33 C9 83 F8 02 0F 94 C0 C3 A1 ? ? ? ? 8B 80 ? ? ? ?
        inline static T6SDK::MemoryPatch Demo_IsAnyMoveCameraPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x2D7B20, T6SDK::Addresses::t6mp + 0x2E2CC0,
            T6SDK::Addresses::t6zmv41 + 0x10C500, T6SDK::Addresses::t6zm + 0x24F470).GetValue() + 0x2E, { 0x0F, 0x9D, 0xC0 });
        
        //83 F8 ? 0F 94 C0 84 C0 0F 84 ? ? ? ? E8 ? ? ? ? 84
        inline static T6SDK::MemoryPatch Demo_IsAnyMoveCameraPatch2(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x01C3A6, T6SDK::Addresses::t6mp + 0x0B3D86,
            T6SDK::Addresses::t6zmv41 + 0x121BC6, T6SDK::Addresses::t6zm + 0x291246).GetValue() +0x03, { 0x0F, 0x9D, 0xC0 });

        //E8 ? ? ? ? 83 C4 ? 84 C0 75 ? 83 FA
        inline static T6SDK::MemoryPatch DisableDvarsLimitsPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x4C93AF, T6SDK::Addresses::t6mp + 0x4C924F,
            T6SDK::Addresses::t6zmv41 + 0x4C7FEF, T6SDK::Addresses::t6zm + 0x4C77FF).GetValue(), {0xB0, 0x01, 0x90, 0x90, 0x90}); //mov al, 0x01

        inline static T6SDK::MemoryPatch DisableDvarProtectionPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x4C923A, T6SDK::Addresses::t6mp + 0x4C90DA,
			T6SDK::Addresses::t6zmv41 + 0x4C7E7A, T6SDK::Addresses::t6zm + 0x4C768A).GetValue(), { 0x90, 0x90});

        //75 ? A1 ? ? ? ? 0F 57 C0 F3 0F 11 80 84 BC 0E 00 8B 54 24 08 51
        inline static T6SDK::MemoryPatch AllowRollPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x030BD7, T6SDK::Addresses::t6mp + 0x2B0087,
            T6SDK::Addresses::t6zmv41 + 0x1FB227, T6SDK::Addresses::t6zm + 0x225237).GetValue(), { 0xEB /*jmp instruction instead of jne*/});

        //E8 ? ? ? ? 83 C4 ? 5F 5E 83 C4 ? C3 53 55 56
        inline static T6SDK::MemoryPatch DisableClipRecordingPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x1F3F93, T6SDK::Addresses::t6mp + 0x23B5A3,
			T6SDK::Addresses::t6zmv41 + 0x1B3463, T6SDK::Addresses::t6zm + 0x2D5AF3).GetValue(), { 0x90, 0x90, 0x90, 0x90, 0x90});

        //0F 84 ? ? ? ? E8 ? ? ? ? 84 C0 0F 85 ? ? ? ? E8 ? ? ? ? 84 C0 75 ? 53
        inline static T6SDK::MemoryPatch JumpToDollyCamMarkerPatch(T6SDK::CrossVersion::CrossValue<DWORD>(
			T6SDK::Addresses::t6mpv43 + 0x16A42D, T6SDK::Addresses::t6mp + 0x1F05CD,
			T6SDK::Addresses::t6zmv41 + 0x22939D, T6SDK::Addresses::t6zm + 0x14D91D).GetValue(), { 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 });

        inline static T6SDK::MemoryPatch InitialTickSTOP(T6SDK::CrossVersion::CrossValue<DWORD>(
            T6SDK::Addresses::t6mpv43 + 0x16C2D1, T6SDK::Addresses::t6mp + 0x14F521, 
            T6SDK::Addresses::t6zmv41 + 0x1614B1, T6SDK::Addresses::t6zm + 0x170801).GetValue(), { 0x8B });//What writes to inital tick; Replace with 0xB8

        //FF D0 47 8D 76 ? 3B FB 75 ? A1
        inline static T6SDK::MemoryPatch DisableRedactedConsole((uintptr_t)GetModuleHandle("ExtendedConsole.Red32n") + 0x420A, { 0x90, 0x90});

        static std::vector<BYTE> fogPatchBytes()
        {
            switch (T6SDK::CrossVersion::GetGameVersion())
            {
            case T6SDK::CrossVersion::V43:
                return { 0xB8, 0xB8, 0x24, 0x62, 0x03, 0x90 };
            case T6SDK::CrossVersion::MP:
                return { 0xB8, 0xB8, 0x34, 0x64, 0x03, 0x90 };
            case T6SDK::CrossVersion::V41:
                return { 0xB8, 0xB8, 0x22, 0x5F, 0x03, 0x90 };
            case T6SDK::CrossVersion::ZM:
                return { 0xB8, 0x38, 0x8B, 0x61, 0x03, 0x90 };
            }
        }
		inline static T6SDK::MemoryPatch FogPatch(T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x3275D7, T6SDK::Addresses::t6mp + 0x326917, T6SDK::Addresses::t6zmv41 + 0x325cb7, T6SDK::Addresses::t6zm + 0x324527).GetValue(), fogPatchBytes());
    }
#pragma region Addresses
    inline static cg_t* cg = (cg_t*)T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2E048C80, T6SDK::Addresses::t6mp + 0x2E048C80, T6SDK::Addresses::t6zmv41 + 0x2E048C80, T6SDK::Addresses::t6zm + 0x2E048C80).GetValue();
    //05 ? ? ? ? 50 56 E8 ? ? ? ? 83 C4 ? 5E 5B
    inline static DWORD PlayerStates = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2CFE400, T6SDK::Addresses::t6mp + 0x2D1F400, T6SDK::Addresses::t6zmv41 + 0x2CCE480, T6SDK::Addresses::t6zm + 0x2CF4B00).GetValue();
    //Sig is too fucking long. Find with "Can't create dvar '%s': %i dvars already exist" in IDA.
    inline static DWORD dvarPool = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x261FC48, T6SDK::Addresses::t6mp + 0x261FC48, T6SDK::Addresses::t6zmv41 + 0x25EFF48, T6SDK::Addresses::t6zm + 0x25F5548).GetValue();
    inline static DWORD cmdFunctionsPool = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2138B54, T6SDK::Addresses::t6mp + FILLIN, T6SDK::Addresses::t6zmv41 + FILLIN, T6SDK::Addresses::t6zm + FILLIN).GetValue();
    inline static int* g_dvarCount = (int*)T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x0267FC4C, T6SDK::Addresses::t6mp + 0x2267FC4C, T6SDK::Addresses::t6zmv41 + 0x264FF4C, T6SDK::Addresses::t6zm + 0x265554C).GetValue();
    
    inline static T6SDK::MemoryAddress<demoPlayback*> DemoPlayback(T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2D83A00, T6SDK::Addresses::t6mp + 0x2DA4A00,
        T6SDK::Addresses::t6zmv41 + 0x2D53A80, T6SDK::Addresses::t6zm + 0x2D7A100).GetValue());

    inline static T6SDK::MemoryAddress<GfxDrawMethod_t> GfxDrawMethod(T6SDK::Addresses::t6mpv43 + 0x363EAB0, T6SDK::Addresses::t6mp + 0x365FAB0, T6SDK::Addresses::t6zmv41 + 0x360E8B0, T6SDK::Addresses::t6zm + 0x3635130);

    inline static T6SDK::MemoryAddress<bool> IsDemoPaused(T6SDK::Addresses::t6mpv43 + 0x264C960, T6SDK::Addresses::t6mp + 0x264C960, T6SDK::Addresses::t6zmv41 + 0x261D140, T6SDK::Addresses::t6zm + 0x2622740);
    inline static T6SDK::MemoryAddress<UiContext_t> UiContext(T6SDK::Addresses::t6mpv43 + 0x2556228, T6SDK::Addresses::t6mp + 0x2556228, T6SDK::Addresses::t6zmv41 + 0x2526558, T6SDK::Addresses::t6zm + 0x252BB58);
    //2B 15 ? ? ? ? 33 F6
    inline static T6SDK::MemoryAddress<int> Tick(T6SDK::Addresses::t6mpv43 + 0xDC7EE0, T6SDK::Addresses::t6mp + 0xDC7EE0, T6SDK::Addresses::t6zmv41 + 0xD9CCF0, T6SDK::Addresses::t6zm + 0xD9DD70);
    
    static MemoryAddress<int> InitialTick(t6mpv43 + 0xDC7D74, t6mp + 0xDC7D74, t6zmv41 + 0xD9CB84, t6zm + 0xD9DC04, { 0x2AA4 }); //Use for go to first marker feature //8B 87 A4 2A 00 00 2B 87 B0 2A 00 00 5F 5E 83 E8 05 5D

    inline static T6SDK::MemoryAddress<BYTE> IsInputLocked(T6SDK::Addresses::t6mpv43 + 0x30053B8, T6SDK::Addresses::t6mp + 0x30263B8, T6SDK::Addresses::t6zmv41 + 0x2FD5228, T6SDK::Addresses::t6zm + 0x2FFBAA8);

    inline static T6SDK::MemoryAddress<float> AspectRatio(t6mpv43 + 0x31A9348, t6mp + 0x31CA348, t6zmv41 + 0x3179148, t6zm + 0x319F9C8);
    inline static T6SDK::MemoryAddress<int> ScreenWidth(T6SDK::Addresses::t6mpv43 + 0x31A9328, T6SDK::Addresses::t6mp + 0x31CA328, T6SDK::Addresses::t6zmv41 + 0x3179128, T6SDK::Addresses::t6zm + 0x319F9A8);
    inline static T6SDK::MemoryAddress<int> ScreenHeight(T6SDK::Addresses::t6mpv43 + 0x31A932C, T6SDK::Addresses::t6mp + 0x31CA32C, T6SDK::Addresses::t6zmv41 + 0x317912C, T6SDK::Addresses::t6zm + 0x319F9AC);
    inline static DWORD KeyboardKeysBase = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0xDBF0D4, T6SDK::Addresses::t6mp + 0xDBF0D4,
        T6SDK::Addresses::t6zmv41 + 0xD93EE4, T6SDK::Addresses::t6zm + 0xD94F64).GetValue();

    inline static T6SDK::MemoryAddress<float> FreeRoamSpeed(t6mpv43 + 0x7E4724, t6mp + 0x82E108, t6zmv41 + 0x8260D8, t6zm + 0x7D01C0); // Camera free roam mode speed. //0.01666999981

    //Values in these addresses point to demo internal timescale step (default value of step is 0.2 and default address of step is t6mpv43.exe+0x85E7C8). 
    //We will change the pointer to our custom step. IDK why bo2 uses 4 addresses for it lmao
    inline static T6SDK::MemoryAddress<int> DemoTimescaleStepBasePointer0(t6mpv43 + 0x1F44B7, t6mp + 0x23BA3D, t6zmv41 + 0x1B3987, t6zm + 0x2D5F8D);
    inline static T6SDK::MemoryAddress<int> DemoTimescaleStepBasePointer1(t6mpv43 + 0x1F442D, t6mp + 0x23BA4E, t6zmv41 + 0x1B3998, t6zm + 0x2D5F9E);
    inline static T6SDK::MemoryAddress<int> DemoTimescaleStepBasePointer2(t6mpv43 + 0x1F443E, t6mp + 0x23BAC7, t6zmv41 + 0x1B38FD, t6zm + 0x2D6017);
    inline static T6SDK::MemoryAddress<int> DemoTimescaleStepBasePointer3(t6mpv43 + 0x1F44C8, t6mp + 0x23BAD8, t6zmv41 + 0x1B390E, t6zm + 0x2D6028);

    inline static T6SDK::MemoryAddress<vec3_t> CameraForwardVector(t6mpv43 + 0x301D550, t6mp + 0x3041690, t6zmv41 + 0x2FED350, t6zm + 0x3016D10); //F3 0F 10 55 14 F3 0F 10 80 10 01 00 00 F3 0F 10 88 14 01 00 00 F3 0F 10 B0 18 01 00 00 F3 0F 10 5B 04 F3 0F 10 63 08; See what it acess at secons movss
    inline static T6SDK::MemoryAddress<vec3_t> CameraRightVector(t6mpv43 + 0x301D55C, t6mp + 0x304169C, t6zmv41 + 0x2FED35C, t6zm + 0x3016D1C);
    inline static T6SDK::MemoryAddress<vec3_t> CameraUpVector(t6mpv43 + 0x301D568, t6mp + 0x30416A8, t6zmv41 + 0x2FED368, t6zm + 0x3016D28);

    inline static T6SDK::MemoryAddress<bool> IsGameInFocus(t6mpv43 + 0x2556240, t6mp + 0x2556240, t6zmv41 + 0x2526570, t6zm + 0x252BB70); //B8 01 00 00 00 33 C9 85 C0 0F 94 C1 first mov func

    inline static T6SDK::MemoryAddress<DemoTimescaleFormat_s> DemoTimescaleFormat(t6mpv43 + 0x861F48, t6mp + 0x86C53C, t6zmv41 + 0x825BF8, t6zm + 0x83AFDC); //that 0.1x string format in demo
    inline static T6SDK::MemoryAddress<float> Demo_timescale(t6mpv43 + 0x2162B04, t6mp + 0x2162B04, t6zmv41 + 0x2134684, t6zm + 0x2138A04); //float value of demo timescale
    inline static T6SDK::MemoryAddress<float> Demo_timescale_step(t6mpv43 + 0x85E7C8, t6mp + 0x85D35C, t6zmv41 + 0x8348E4, t6zm + 0x7EA744); //float value of demo timescale step //0.200000003
    inline static T6SDK::MemoryAddress<bool> PlaybackInitedFlag(T6SDK::Addresses::t6mpv43 + 0x2D83A04, T6SDK::Addresses::t6mp + 0x2DA4A04, T6SDK::Addresses::t6zmv41 + 0x2D53A84, T6SDK::Addresses::t6zm + 0x2D7A104);
    //F6 05 ? ? ? ? ? 74 ? 56
    inline static T6SDK::MemoryAddress<int> CurrentKeyCatcher(t6mpv43 + 0xDC7844, t6mp + 0xDC7844, t6zmv41 + 0xD9C654, t6zm + 0xD9D6D4);

    inline static T6SDK::MemoryAddress<vec3_t> SunPosition(t6mpv43 + 0x00EE7A0C, t6mp + 0x00EE7A0C, t6zmv41 + 0xEBC88C, t6zm + 0x00EBD90C, { 0x14 }); //Check BO2 Console v4 source
    inline static T6SDK::MemoryAddress<vec3_t> SunColor(t6mpv43 + 0x00EE7A0C, t6mp + 0x00EE7A0C, t6zmv41 + 0xEBC88C, t6zm + 0x00EBD90C, { 0x58 });
    //3D ? ? ? ? 7C ? B8 ? ? ? ? C3 8D 04 49
    inline static T6SDK::MemoryAddress<int> GameMode(T6SDK::Addresses::t6mpv43 + 0x2160890, T6SDK::Addresses::t6mp + 0x2160890, T6SDK::Addresses::t6zmv41 + 0x2132410, T6SDK::Addresses::t6zm + 0x2136790);
    //8B 3D ? ? ? ? 2B FB
    inline static T6SDK::MemoryAddress<int> DemoEndTick(T6SDK::Addresses::t6mpv43 + 0x2CF3470, T6SDK::Addresses::t6mp + 0x2D14470, T6SDK::Addresses::t6zmv41 + 0x2CC34F0, T6SDK::Addresses::t6zm + 0x2CE9B70);
    //A3 ? ? ? ? 85 C0 0F 8E ? ? ? ? BE
    inline static T6SDK::MemoryAddress<int> NumDefaultBookmarks(T6SDK::Addresses::t6mpv43+0x2CF42E8, T6SDK::Addresses::t6mp + 0x2D152E8, T6SDK::Addresses::t6zmv41 + 0x2CC4368, T6SDK::Addresses::t6zm + 0x2CEA9E8);
    //E8 ? ? ? ? 89 06 E8 -> following func call
    inline static T6SDK::MemoryAddress<int> DemoSummary(t6mpv43 + 0x2B63B40, T6SDK::Addresses::t6mp + 0x2B64B40, T6SDK::Addresses::t6zmv41 + 0x2B33E08, T6SDK::Addresses::t6zm + 0x2B3A440);
    //68 ? ? ? ? E8 ? ? ? ? 8B 84 24 ? ? ? ? 8B 8C 24 ? ? ? ? 83 C4
    inline static T6SDK::MemoryAddress<int> DemoAddress1(T6SDK::Addresses::t6mpv43 + 0x2E046D0, T6SDK::Addresses::t6mp + 0x2E256D0, T6SDK::Addresses::t6zmv41 + 0x2DD4750, T6SDK::Addresses::t6zm + 0x2DFADD0);
    //A3 ? ? ? ? E8 ? ? ? ? 84 C0 74 ? E8 ? ? ? ? 50 -> 2nd function in brackets
    inline static T6SDK::MemoryAddress<int> DemoAddress2(T6SDK::Addresses::t6mpv43 + 0x2E05678, T6SDK::Addresses::t6mp + 0x2E26678, T6SDK::Addresses::t6zmv41 + 0x2DD56F8, T6SDK::Addresses::t6zm + 0x2DFBD78);
    //Search for 00 00 00 00 00 00 00 07 01 00 00 02 BE EF 00
    inline static DWORD DemoThumbnailAddress = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2B17A38, T6SDK::Addresses::t6mp + 0x2BDAAB8, T6SDK::Addresses::t6zmv41 + 0x2AE7D30, T6SDK::Addresses::t6zm + 0x2AED338).GetValue();
    inline static DWORD DemoThumbnailAddress2 = T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2BB9AB8, FILLIN /*NOT NEEDED*/, T6SDK::Addresses::t6zmv41 + 0x2B89D80, T6SDK::Addresses::t6zm + 0x2BB03B8).GetValue();
    //75 ? 68 ? ? ? ? 6A ? E8 ? ? ? ? 83 C4 ? 57 E8
    inline static T6SDK::MemoryAddress<BYTE> DemoLoadPatch(T6SDK::Addresses::t6mpv43 + 0x1C79E6, T6SDK::Addresses::t6mp + 0x10C3F6, T6SDK::Addresses::t6zmv41 + 0x14B786, T6SDK::Addresses::t6zm + 0x10A886);
    inline static const char* DemoName = (const char*)T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x2BB98B2, T6SDK::Addresses::t6mp + 0x2BDA8B2, T6SDK::Addresses::t6zmv41 + 0x2B89C19, T6SDK::Addresses::t6zm + 0x2BB01B2).GetValue();
    inline static Fog_s* fog = (Fog_s*)T6SDK::CrossVersion::CrossValue<DWORD>(T6SDK::Addresses::t6mpv43 + 0x032224B8, T6SDK::Addresses::t6mp + 0x032434B8, T6SDK::Addresses::t6zmv41 + 0x031F22B8, T6SDK::Addresses::t6zm + 0x03218B38).GetValue();

#pragma endregion

}