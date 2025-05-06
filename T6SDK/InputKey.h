#pragma once
#include "pch.h"
#include "StdInclude.h"
#include "T6SDK.h"
namespace T6SDK::Input
{

    class InputKey
    {

    private:
        bool ReturnedTrue = false;
        DWORD BaseAddress{};
    public:
        BYTE KeyCode = 0x00;
        char KeyChar = '\0';
		char UpperCasedKeyChar = '\0';
		bool Printable = false;
        InputKey(DWORD baseAddress, BYTE keycode, char keyChar, char upperCasedKeyChar, bool printable)
        {
            BaseAddress = baseAddress;
            KeyCode = keycode;
			KeyChar = keyChar;
            UpperCasedKeyChar = upperCasedKeyChar;
            Printable = printable;
            T6SDK::MAIN::CharKeys.emplace(keycode, (int)this);
        }
#pragma region CrossVersion 
        InputKey(DWORD v43BaseAddress, DWORD mpBaseAddress, DWORD v41BaseAddress, DWORD zmBaseAddress, BYTE keycode, char keyChar, char upperCasedKeyChar, bool printable)
        {
            switch (T6SDK::CrossVersion::GetGameVersion())
            {
            case T6SDK::CrossVersion::GameVersion::V43:
                BaseAddress = v43BaseAddress;
                break;
            case T6SDK::CrossVersion::GameVersion::MP:
                BaseAddress = mpBaseAddress;
                break;
            case T6SDK::CrossVersion::GameVersion::V41:
                BaseAddress = v41BaseAddress;
                break;
            case T6SDK::CrossVersion::GameVersion::ZM:
                BaseAddress = zmBaseAddress;
                break;
            }
            KeyCode = keycode;
			KeyChar = keyChar;
			UpperCasedKeyChar = upperCasedKeyChar;
			Printable = printable;
            T6SDK::MAIN::CharKeys.emplace(keycode, (int)this);
        }
#pragma endregion
        bool IsValid()
        {
            return *(int*)BaseAddress != 0x00;
        }
        bool Pressed()
        {
            if (BaseAddress != NULL)
            {
                return *(bool*)BaseAddress == 1 && *(int*)(BaseAddress + 0x04) == 1;
                if (*(bool*)BaseAddress == 1 && *(int*)(BaseAddress + 0x04) == 1 && ReturnedTrue == false)
                {
                    ReturnedTrue = true;
                    return true;
                }
                else if (*(bool*)BaseAddress == 1 && *(int*)(BaseAddress + 0x04) == 1 && ReturnedTrue == true)
                {
                    return false;
                }
                else
                {
                    ReturnedTrue = false;
                    return false;
                }
            }
        }
        bool Hold()
        {
            if (BaseAddress != NULL)
            {
                return *(bool*)BaseAddress == 1 && *(int*)(BaseAddress + 0x04) >= 1;
            }
        }
        bool HoldWithInterval(int interval)
        {
            if (BaseAddress != NULL)
            {
                bool pressed = *(bool*)BaseAddress == 1;
                bool intervalStep = *(int*)(BaseAddress + 0x04) % interval == 0;
                return pressed && intervalStep;
            }
        }
        bool HoldFor(int time)
        {
            if (BaseAddress != NULL)
            {
                if (*(int*)(BaseAddress + 0x04) == time && ReturnedTrue == false)
                {
                    ReturnedTrue = true;
                    return true;
                }
                else if (*(int*)(BaseAddress + 0x04) == time && ReturnedTrue == true)
                {
                    return false;
                }
                else
                {
                    ReturnedTrue = false;
                    return false;
                }
            }
        }
        bool IsAnyPressState()
        {
            return (Pressed() || Hold());
        }
    };
}