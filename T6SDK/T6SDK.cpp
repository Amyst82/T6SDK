#include "pch.h"
#include "StdInclude.h"

namespace T6SDK
{
    inline static T6SDK::Drawing::UI_Notification UINotificationControl{};

	uintptr_t eaxTMP, ecxTMP, edxTMP, esiTMP, ediTMP, espTMP, ebpTMP, eaxTMP2=0x00;
	__declspec(naked) void EndFrameDrawn()
	{
        __asm
        {
            mov[eaxTMP2], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {
                mov eax, [eaxTMP2]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
            }
            T6SDK::Events::Invoke(T6SDK::EventType::OnEndFrameDrawn);
            __asm
            {
                mov eax, [eaxTMP2]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                add dword ptr[eax + 0x18], 0x400
                jmp[T6SDK::Addresses::HookAddresses::h_EndFrameDrawn.JumpBackAddress]
            }
        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP2]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                add dword ptr[eax + 0x18], 0x400
                jmp[T6SDK::Addresses::HookAddresses::h_EndFrameDrawn.JumpBackAddress]
            }
        }
	}
	_declspec(naked) void TheaterControlsDrawn()
	{
		__asm
		{
			mov[eaxTMP], eax
			mov[edxTMP], edx
			mov[ecxTMP], ecx
			mov[esiTMP], esi
			mov[ediTMP], edi
			mov[espTMP], esp
			mov[ebpTMP], ebp
		}
        if(T6SDK::MAIN::ENABLED)
		    T6SDK::Events::Invoke(T6SDK::EventType::OnTheaterControlsDrawn);
		__asm
		{
			mov eax, [eaxTMP]
			mov edx, [edxTMP]
			mov ecx, [ecxTMP]
			mov esi, [esiTMP]
			mov edi, [ediTMP]
			mov esp, [espTMP]
			mov ebp, [ebpTMP]
			mov[esp + 0x000000AC], eax
			jmp[T6SDK::Addresses::HookAddresses::h_TheaterControlsDrawn.JumpBackAddress]
		}
	}

    void HandleIngameKeyPressed(BYTE keyCode)
    {
        if (keyCode == 0xCD) //MouseWheel Up
        {
            T6SDK::Input::MouseWheelDelta = 1.0f;
            T6SDK::Events::Invoke(T6SDK::EventType::OnMouseWheelUp);
        }
        else if (keyCode == 0xCC) //MouseWheel down
        {
            T6SDK::Input::MouseWheelDelta = -1.0f;
            T6SDK::Events::Invoke(T6SDK::EventType::OnMouseWheelDown);
        }
        else
            T6SDK::Input::MouseWheelDelta = 0.0f;

        T6SDK::Events::InvokeByteParam(T6SDK::EventType::OnKeyPressed, keyCode);

        if (keyCode == 0xC7)
            T6SDK::Events::Invoke(T6SDK::EventType::OnMouseLeftButtonClicked);

        if (keyCode == 0xC8)
            T6SDK::Events::Invoke(T6SDK::EventType::OnMouseRightButtonClicked);
    }
    __declspec(naked) void IngameKeyPressed() //Need to determine mousewheel direction
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[ecxTMP], ecx
            mov[edxTMP], edx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                test eax, eax
                je L7
                test edx, edx
                je L7
                dec eax //somehow its 0x01 bigger so we need to decrement
                push eax //pass esi as a parameter
                call HandleIngameKeyPressed
                L7 :
                mov eax, [eaxTMP]
                mov ecx, [ecxTMP]
                mov edx, [edxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push ecx
                push edx
                push eax
                xor edi, edi
                push edi
                jmp[T6SDK::Addresses::HookAddresses::h_Com_EventLoopKeyEvent.JumpBackAddress]
            }

        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov ecx, [ecxTMP]
                mov edx, [edxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push ecx
                push edx
                push eax
                xor edi, edi
                push edi
                jmp[T6SDK::Addresses::HookAddresses::h_Com_EventLoopKeyEvent.JumpBackAddress]
            }
        }     
    }

    __declspec(naked) void CGDrawActiveFrame()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
            }
            T6SDK::Events::Invoke(T6SDK::EventType::OnActiveFrameDrawn);
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push ebx
                mov ebx, [esp + 0x08]
                jmp[T6SDK::Addresses::HookAddresses::h_CG_DrawActiveFrame.JumpBackAddress]
            }
        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push ebx
                mov ebx, [esp+0x08]
                jmp[T6SDK::Addresses::HookAddresses::h_CG_DrawActiveFrame.JumpBackAddress]
            }
        }
    }

    void HandleAddDollyCamMarker(CameraMarker_s* camMarker)
    {
        T6SDK::Events::InvokeCameraMarkerParam(T6SDK::EventType::OnCameraMarkerAdded, camMarker);
    }
    __declspec(naked) void Demo_AddDollyCamMarker()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {        
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push esi
                call HandleAddDollyCamMarker
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                add eax, 0x00ED440
                jmp[T6SDK::Addresses::HookAddresses::h_Demo_AddDollyCamMarker.JumpBackAddress]
            }
        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                add eax, 0x00ED440
                jmp[T6SDK::Addresses::HookAddresses::h_Demo_AddDollyCamMarker.JumpBackAddress]
            }
        }
    }

	void HandleFreeCameraModeChanged(int mode)
	{
		T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnFreeCameraModeChanged, mode);
	}
    __declspec(naked) void FreeCameraModeChanged()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
            mov[eax + 0xD4C04], esi
            push esi
            call HandleFreeCameraModeChanged
            mov eax, [eaxTMP]
            mov edx, [edxTMP]
            mov ecx, [ecxTMP]
            mov esi, [esiTMP]
            mov edi, [ediTMP]
            mov esp, [espTMP]
            mov ebp, [ebpTMP]
            jmp[T6SDK::Addresses::HookAddresses::h_FreeCameraModeChanged.JumpBackAddress]
        }
    }

    void PatchAspectRatio()
    {
        int width = T6SDK::Addresses::ScreenWidth.Value();
        int height = T6SDK::Addresses::ScreenHeight.Value();
        float ratio = (float)width / (float)height;
        T6SDK::Addresses::AspectRatio.SetValueSafe(ratio);
    }
    __declspec(naked) void AspectRatioChanged()
    {
		__asm
		{
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
            call PatchAspectRatio
            mov eax, [eaxTMP]
            mov edx, [edxTMP]
            mov ecx, [ecxTMP]
            mov esi, [esiTMP]
            mov edi, [ediTMP]
            mov esp, [espTMP]
            mov ebp, [ebpTMP]
			jmp[T6SDK::Addresses::HookAddresses::h_AspectRatioChanged.JumpBackAddress]
		}
    }

    void HandleSwitchCameraMode(int newMode)
    {
        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnCameraModeChanged, newMode);
    }
    __declspec(naked) void Demo_CameraModeSwitched()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push esi
                call HandleSwitchCameraMode
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                jmp[T6SDK::Addresses::HookAddresses::h_Demo_SwitchCameraMode.JumpBackAddress]
            }
        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                jmp[T6SDK::Addresses::HookAddresses::h_Demo_SwitchCameraMode.JumpBackAddress]
            }
        }
    }

    float nearClipping = 4.0f;
    __declspec(naked) void NearClippingPatch()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            if (T6SDK::Dvars::DvarList::r_znear)
                nearClipping = T6SDK::Dvars::GetFloat(*T6SDK::Dvars::DvarList::r_znear);
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                mov eax, nearClipping
                mov[esp + 0x08], eax
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                jmp[T6SDK::Addresses::HookAddresses::h_NearClipping.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, nearClipping
                mov[esp + 0x08], eax

                jmp[T6SDK::Addresses::HookAddresses::h_NearClipping.JumpBackAddress]
            }
        }
    }

    void HandleUnlockGunAngles()
    {
        if (!*T6SDK::Dvars::DvarList::cg_gun_rot_p && !*T6SDK::Dvars::DvarList::cg_gun_rot_y && !*T6SDK::Dvars::DvarList::cg_gun_rot_r)
            return;
        T6SDK::Addresses::cg->baseGunAngles.x += T6SDK::Dvars::GetFloat(*T6SDK::Dvars::DvarList::cg_gun_rot_p);
		T6SDK::Addresses::cg->baseGunAngles.y += T6SDK::Dvars::GetFloat(*T6SDK::Dvars::DvarList::cg_gun_rot_y);
		T6SDK::Addresses::cg->baseGunAngles.z += T6SDK::Dvars::GetFloat(*T6SDK::Dvars::DvarList::cg_gun_rot_r);
    }
    __declspec(naked) void UnlockGunAngles()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                call HandleUnlockGunAngles
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                lea ebx, [esi + 0x480A8]
                jmp[T6SDK::Addresses::HookAddresses::h_UnlockGunAngles.JumpBackAddress]
            }
        }
        else
        {
            __asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                lea ebx, [esi + 0x480A8]
                jmp[T6SDK::Addresses::HookAddresses::h_UnlockGunAngles.JumpBackAddress]
            }
        }
    }
    bool allAngles = false;
    uintptr_t demoPlaybackTmp = 0x00;
    __declspec(naked) void UnlockCameraRoll()
    {
        _asm
        {
            cmp T6SDK::Theater::GrabFreeCameraAngles, 1
            je L7
            cmp esi, 0xEBC84
            je L7
            fstp dword ptr[esi + eax]
            L7:
            add esi, 04
            jmp[T6SDK::Addresses::HookAddresses::h_UnlockCameraRollHook.JumpBackAddress]
        }
    }

    void HandlePovCamoWriting(int entitystateEDI)
    {
        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnPovCamoWriting, entitystateEDI);
    }
    __declspec(naked) void PovCamoWriting()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
        }
        if (T6SDK::MAIN::ENABLED)
        {
            _asm
            {
                mov[edi + 0x8C], edx
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                push edi
                call HandlePovCamoWriting
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                jmp[T6SDK::Addresses::HookAddresses::h_PovCamoWritingHook.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov[edi + 0x8C], edx
                jmp[T6SDK::Addresses::HookAddresses::h_PovCamoWritingHook.JumpBackAddress]
            }
        }
    }

    __declspec(naked) void OnAxisToAngles()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {

            T6SDK::Events::Invoke(T6SDK::EventType::OnAxisToAngles);
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                movss[esi + 0x08], xmm0
                jmp[T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                movss[esi + 0x08], xmm0
                jmp[T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.JumpBackAddress]
            }
        }
    }

    static const char* DetouredSafeStringTranslate(const char* string)
    {
        if (T6SDK::MAIN::ENABLED)
        {
            if (T6SDK::Theater::IsPlaybackInited())
            {
                T6SDK::Events::InvokeConstCharParam(T6SDK::EventType::OnSafeStringTranslated, &string);
            }
        }
        return T6SDK::Addresses::DetoursAddresses::DetouredUI_SafeTranslateStringHook.call_original<const char*, T6SDK::Typedefs::UI_SafeTranslateString_t, const char*>(string);
    }
    void T6SDK::MAIN::InitializeDevConsole()
    {
        T6SDK::DevConsole::Initialize();
        //Bind console events
        T6SDK::Events::RegisterListener(T6SDK::EventType::OnEndFrameDrawn, (uintptr_t)&T6SDK::DevConsole::DrawConsole);
        T6SDK::Events::RegisterListener(T6SDK::EventType::OnKeyPressed, (uintptr_t)&T6SDK::DevConsole::OnInputKey);

    }

    void HandleGameModeChanged(int mode)
    {
        if (mode == 32)
        {
            T6SDK::MAIN::ENABLED = true;
            T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "T6SDK", "Entered theater mode!");
        }
		else
        {
            T6SDK::MAIN::ENABLED = false;
            T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "T6SDK", "Exit theater mode. All MVM features will be disabled.");
        }

        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnGameModeChanged, mode);
    }
    __declspec(naked) void Com_GameMode_SetMode()
    {
        _asm
        {
            mov eax, 0x1
            shl eax, cl
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
            push eax
            call HandleGameModeChanged
            mov eax, [eaxTMP]
            mov edx, [edxTMP]
            mov ecx, [ecxTMP]
            mov esi, [esiTMP]
            mov edi, [ediTMP]
            mov esp, [espTMP]
            mov ebp, [ebpTMP]
            jmp[T6SDK::Addresses::HookAddresses::h_Com_GameMode_SetMode.JumpBackAddress]
        }
    }

    __declspec(naked) void OnDemoPlaybackInited()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {

            T6SDK::Events::Invoke(T6SDK::EventType::OnDemoPlaybackInited);
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                movss[eax + 0x63544], xmm0
                jmp[T6SDK::Addresses::HookAddresses::h_InitDemoPlaybackData.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                movss[eax + 0x63544], xmm0
                jmp[T6SDK::Addresses::HookAddresses::h_InitDemoPlaybackData.JumpBackAddress]
            }
        }
    }

    __declspec(naked) void OnSunInited()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {

            T6SDK::Events::Invoke(T6SDK::EventType::OnSunInited);
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                mov eax, [edx + 0x100]
                jmp[T6SDK::Addresses::HookAddresses::h_SunInited.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                mov eax, [edx + 0x100]
                jmp[T6SDK::Addresses::HookAddresses::h_SunInited.JumpBackAddress]
            }
        }
    }

    void HandleOnCgItem(int centity)
    {
        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnCgItemDrawn, centity);
    }
    __declspec(naked) void OnCG_Item()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {
            _asm
            {
                push esi
                call HandleOnCgItem
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                mov eax, [esi + 0x1DC]
                jmp[T6SDK::Addresses::HookAddresses::h_CG_Item.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                mov eax, [esi + 0x1DC]
                jmp[T6SDK::Addresses::HookAddresses::h_CG_Item.JumpBackAddress]
            }
        }
    }

    void HandleOnProcessEntity(int centity)
    {
        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnProcessEntity, centity);
    }
    __declspec(naked) void OnCG_ProcessEntity()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {
            _asm
            {
                push esi
                call HandleOnProcessEntity
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                cmp dword ptr[esi + 0x260], 0x00
                jmp[T6SDK::Addresses::HookAddresses::h_CG_ProcessEntity.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                cmp dword ptr[esi + 0x260], 0x00
                jmp[T6SDK::Addresses::HookAddresses::h_CG_ProcessEntity.JumpBackAddress]
            }
        }
    }
    void HandleOnCGCalcEntityLerpPositions(int centity)
    {
        T6SDK::Events::InvokeIntParam(T6SDK::EventType::OnCGCalcEntityLerpPositions, centity);
    }
    __declspec(naked) void OnCGCalcEntityLerpPositions()
    {
        _asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp

        }
        if (T6SDK::MAIN::ENABLED)
        {
            _asm
            {
                push esi
                call HandleOnCGCalcEntityLerpPositions
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                pop edi
                pop esi
                pop ebp
                pop ebx
                ret
                //jmp[T6SDK::Addresses::HookAddresses::h_CG_CalcEntityLerpPositions.JumpBackAddress]
            }
        }
        else
        {
            _asm
            {
                mov eax, [eaxTMP]
                mov edx, [edxTMP]
                mov ecx, [ecxTMP]
                mov esi, [esiTMP]
                mov edi, [ediTMP]
                mov esp, [espTMP]
                mov ebp, [ebpTMP]
                pop edi
                pop esi
                pop ebp
                pop ebx
                ret
                //jmp[T6SDK::Addresses::HookAddresses::h_CG_CalcEntityLerpPositions.JumpBackAddress]
            }
        }
    }
	void T6SDK::MAIN::Initialize()
	{
        T6SDK::Drawing::normalFont = T6SDK::Typedefs::R_RegisterFont_FastFile("fonts/720/normalFont", 1);
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Normal Font registered: 0x%X->0x%X", T6SDK::Drawing::normalFont, *T6SDK::Drawing::normalFont);
        T6SDK::Drawing::consoleFont = T6SDK::Typedefs::R_RegisterFont_FastFile("fonts/720/consoleFont", 1);
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Console Font registered: 0x%X->0x%X", T6SDK::Drawing::consoleFont, *T6SDK::Drawing::consoleFont);
        T6SDK::Drawing::WhiteMaterial = T6SDK::InternalFunctions::Material_RegisterHandle("white", (int)T6SDK::XAssetType::MATERIAL);
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "White Material registered: 0x%X", T6SDK::Drawing::WhiteMaterial);
        T6SDK::Drawing::headicontalkballoon = T6SDK::InternalFunctions::Material_RegisterHandle("headicontalkballoon", (int)T6SDK::XAssetType::MATERIAL);
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "headicontalkballoon registered: 0x%X", T6SDK::Drawing::headicontalkballoon);
        T6SDK::Drawing::LightDef = T6SDK::InternalFunctions::DB_FindXAssetHeader(T6SDK::XAssetType::LIGHT_DEF, "light_dynamic");
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Light Def: 0x%X", T6SDK::Drawing::LightDef);
        T6SDK::Drawing::FxCameraSelect = T6SDK::InternalFunctions::DB_FindXAssetHeader(T6SDK::XAssetType::FX, "misc/fx_theater_mode_camera_head_select");
       
        T6SDK::Addresses::HookAddresses::h_TheaterControlsDrawn.Hook(TheaterControlsDrawn);
        T6SDK::Addresses::HookAddresses::h_Com_EventLoopKeyEvent.Hook(IngameKeyPressed);
        T6SDK::Addresses::HookAddresses::h_CG_DrawActiveFrame.Hook(CGDrawActiveFrame);
        T6SDK::Addresses::HookAddresses::h_Demo_AddDollyCamMarker.Hook(Demo_AddDollyCamMarker);
        T6SDK::Addresses::HookAddresses::h_FreeCameraModeChanged.Hook(FreeCameraModeChanged);
        T6SDK::Addresses::HookAddresses::h_AspectRatioChanged.Hook(AspectRatioChanged);
        T6SDK::Addresses::HookAddresses::h_Demo_SwitchCameraMode.Hook(Demo_CameraModeSwitched);
        T6SDK::Addresses::HookAddresses::h_NearClipping.Hook(NearClippingPatch);
        T6SDK::Addresses::HookAddresses::h_UnlockGunAngles.Hook(UnlockGunAngles);
        T6SDK::Addresses::HookAddresses::h_UnlockCameraRollHook.Hook(UnlockCameraRoll);
        T6SDK::Addresses::HookAddresses::h_PovCamoWritingHook.Hook(PovCamoWriting);

        T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.SetOutFunc((DWORD)&OnAxisToAngles);
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Hooking: 0x%X", T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.OutFunc);
        T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.Hook(OnAxisToAngles);

        T6SDK::Addresses::HookAddresses::h_InitDemoPlaybackData.Hook(OnDemoPlaybackInited);
        T6SDK::Addresses::HookAddresses::h_SunInited.Hook(OnSunInited);
        T6SDK::Addresses::HookAddresses::h_CG_Item.Hook(OnCG_Item);
        T6SDK::Addresses::HookAddresses::h_CG_ProcessEntity.Hook(OnCG_ProcessEntity);
        T6SDK::Addresses::HookAddresses::h_CG_CalcEntityLerpPositions.Hook(OnCGCalcEntityLerpPositions);

        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "T6SDK", "Hooks set!");
        //Detours
        T6SDK::Addresses::DetoursAddresses::DetouredSwitchCameraHook.Hook(T6SDK::Theater::DetouredSwitchCamera);
        T6SDK::Addresses::DetoursAddresses::DetouredUI_SafeTranslateStringHook.Hook(DetouredSafeStringTranslate);

        T6SDK::Events::RegisterListener(T6SDK::EventType::OnSafeStringTranslated, (uintptr_t)&T6SDK::Theater::HandleTheaterSafeStringTranslate);

        T6SDK::Addresses::DetoursAddresses::DetouredGetNextFreeCameraModeHook.Hook(T6SDK::Theater::DetouredGetNextFreeCameraMode);
        T6SDK::Addresses::DetoursAddresses::DetouredGetFreeCamModeNameHook.Hook(T6SDK::Theater::DetouredGetFreeCamModeName);

        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "T6SDK", "Detours set!");
        //Patches

        T6SDK::Addresses::Patches::AllowRollPatch.Patch();
        T6SDK::Addresses::Patches::Demo_IsAnyMoveCameraPatch.Patch();
        T6SDK::Addresses::Patches::Demo_IsAnyMoveCameraPatch2.Patch();

        T6SDK::Addresses::HookAddresses::h_EndFrameDrawn.Hook(EndFrameDrawn);
        T6SDK::Addresses::HookAddresses::h_Com_GameMode_SetMode.Hook(Com_GameMode_SetMode);
        T6SDK::Addresses::Patches::DisableDvarsLimitsPatch.Patch();
        T6SDK::Addresses::Patches::DisableDvarProtectionPatch.Patch();
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "T6SDK", "Dvars limits disabled");
        T6SDK::Addresses::Patches::FogPatch.Patch();
        T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "T6SDK", "FOG patched!");
        UINotificationControl = T6SDK::Drawing::UI_Notification();
	}
	void T6SDK::MAIN::DeInitialize()
	{
        T6SDK::Addresses::HookAddresses::h_TheaterControlsDrawn.UnHook();
        T6SDK::Addresses::HookAddresses::h_Com_EventLoopKeyEvent.UnHook();
        T6SDK::Addresses::HookAddresses::h_CG_DrawActiveFrame.UnHook();
        T6SDK::Addresses::HookAddresses::h_Demo_AddDollyCamMarker.UnHook();
        T6SDK::Addresses::HookAddresses::h_FreeCameraModeChanged.UnHook();
        T6SDK::Addresses::HookAddresses::h_AspectRatioChanged.UnHook();
        T6SDK::Addresses::HookAddresses::h_Demo_SwitchCameraMode.UnHook();
        T6SDK::Addresses::HookAddresses::h_NearClipping.UnHook();
        T6SDK::Addresses::HookAddresses::h_UnlockGunAngles.UnHook();
        T6SDK::Addresses::HookAddresses::h_UnlockCameraRollHook.UnHook();
        T6SDK::Addresses::HookAddresses::h_PovCamoWritingHook.UnHook();
        T6SDK::Addresses::HookAddresses::h_AxisToAnglesHook.UnHook();
        //Removing detours
        T6SDK::Addresses::DetoursAddresses::DetouredSwitchCameraHook.UnHook();
        T6SDK::Addresses::DetoursAddresses::DetouredUI_SafeTranslateStringHook.UnHook();
        T6SDK::Addresses::DetoursAddresses::DetouredGetNextFreeCameraModeHook.UnHook();
        T6SDK::Addresses::DetoursAddresses::DetouredGetFreeCamModeNameHook.UnHook();
        //Un-patches
        T6SDK::Addresses::Patches::Demo_IsAnyMoveCameraPatch.UnPatch();
        T6SDK::Addresses::Patches::Demo_IsAnyMoveCameraPatch2.UnPatch();
        T6SDK::Addresses::Patches::AllowRollPatch.UnPatch();

        T6SDK::Addresses::HookAddresses::h_EndFrameDrawn.UnHook();
		
        T6SDK::Addresses::Patches::DisableDvarsLimitsPatch.UnPatch();
		T6SDK::Addresses::Patches::DisableDvarProtectionPatch.UnPatch();
        T6SDK::Addresses::HookAddresses::h_Com_GameMode_SetMode.UnHook();

        if (T6SDK::MAIN::DEBUG)
            T6SDK::ConsoleLog::DeInitialize();
	}

    void HandleGameLoaded()
    {
        if (T6SDK::MAIN::GameLoaded == false)
        {
            T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "T6SDK", "Game loaded!");
            //Sleep(1000);
			T6SDK::MAIN::Initialize();
            T6SDK::Events::Invoke(T6SDK::EventType::OnGameLoaded);
            T6SDK::MAIN::GameLoaded = true;
			T6SDK::Addresses::HookAddresses::h_GameLoaded.UnHook();
        }
    }
    __declspec(naked) void hGameLoaded()
    {
        __asm
        {
            mov[eaxTMP], eax
            mov[edxTMP], edx
            mov[ecxTMP], ecx
            mov[esiTMP], esi
            mov[ediTMP], edi
            mov[espTMP], esp
            mov[ebpTMP], ebp
            call HandleGameLoaded
            mov eax, [eaxTMP]
            mov edx, [edxTMP]
            mov ecx, [ecxTMP]
            mov esi, [esiTMP]
            mov edi, [ediTMP]
            mov esp, [espTMP]
            mov ebp, [ebpTMP]
            push 0x0000D6D8
            jmp[T6SDK::Addresses::HookAddresses::h_GameLoaded.JumpBackAddress]
        }
    }
    void T6SDK::MAIN::PreInit()
    {
        if (T6SDK::MAIN::DEBUG)
            T6SDK::ConsoleLog::Initialize();
        T6SDK::Addresses::HookAddresses::h_GameLoaded.Hook(hGameLoaded);
    }
    void T6SDK::MAIN::UI_ShowNotification(const char* title, const char* text, int duration)
    {
        UINotificationControl = T6SDK::Drawing::UI_Notification(title, text, duration);
        UINotificationControl.Show();
    }
	int T6SDK::MAIN::GetNotificationControl()
	{
        return (int) &UINotificationControl;
	}
}
