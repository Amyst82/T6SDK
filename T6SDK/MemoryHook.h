#pragma once
#include "ConsoleLog.h"
#include "StdInclude.h"

namespace T6SDK 
{
    class MemoryHook
    {

    private:
        uintptr_t BaseAddress{};
        int Length{};
        BYTE* OriginalBytes{};
    public:
        DWORD JumpBackAddress{};
        MemoryHook()
        {

        }
        /// <summary>
        /// Initialize a new memory hook instance.
        /// </summary>
        /// <param name="_baseAddress">Adress of a function (or just a region in memory) to hook at.</param>
        /// <param name="_length">Length of bytes being involved in hooking.</param>
        MemoryHook(uintptr_t _baseAddress, int _length)
        {
            BaseAddress = _baseAddress;
            Length = _length;
            JumpBackAddress = BaseAddress + Length;
            OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Length);
        }

        void Init(uintptr_t _baseAddress, int _length)
        {
			BaseAddress = _baseAddress;
			Length = _length;
			JumpBackAddress = BaseAddress + Length;
			OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Length);
        }

#pragma region CrossVersion 

        MemoryHook(DWORD v43BaseAddress, DWORD mpBaseAddress, DWORD v41BaseAddress, DWORD zmBaseAddress, int _length)
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
            Length = _length;
            JumpBackAddress = BaseAddress + Length;
            OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Length);
        }
#pragma endregion

        /// <summary>
        /// Hooks the needed address.
        /// </summary>
        /// <param name="outFunc">Your function that will be called after hook injecteing.</param>
        /// <returns>True if hooked sucñessfully and false otherwise.</returns>
        bool Hook(void* outFunc)
        {
            try
            {
                OriginalBytes = T6SDK::Memory::Hook_o((void*)BaseAddress, outFunc, Length);
                return true;
            }
            catch (const char* errorMessage)
            {
                T6SDK::ConsoleLog::LogError(errorMessage);
                return false;
            }
        }
        /// <summary>
        /// "Unhooks" your created hook. Besically it just restores the original bytes that were stored before hooking;
        /// </summary>
        /// <returns>True if unhooked sucñessfully and false otherwise.</returns>
        bool UnHook()
        {
            try
            {
                T6SDK::ConsoleLog::LogErrorFormatted("Original bytes were: 0%X long", *OriginalBytes);
                if (!OriginalBytes)
                    return false;
                T6SDK::Memory::RestoreOldBytes(BaseAddress, OriginalBytes, Length);
                
                return true;
            }
            catch (const char* errorMessage)
            {
                T6SDK::ConsoleLog::LogError(errorMessage);
                return false;
            }
        }
    };
}