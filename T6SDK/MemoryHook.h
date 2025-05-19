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
        inline static DWORD OutFunc = 0x00;
        MemoryHook()
        {

        }
        /// <summary>
        /// Initialize a new MEMORYHOOK instance.
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
        void SetOutFunc(DWORD _outFunc)
        {
            OutFunc = _outFunc; 
            T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "OutFunc set: 0x%X", OutFunc);
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
                auto bytes = T6SDK::Memory::Hook_o((void*)BaseAddress, outFunc, Length);
                return true;
            }
            catch (const char* errorMessage)
            {
                T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", errorMessage);
                return false;
            }
        }
        bool Hook()
        {
            try
            {
                //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "Rehook func address: 0x%X", OutFunc);
                if (OutFunc == 0x00)
                {
                    T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", "Rehook failed! OutFunc was not set");
                    return false;
                }
                bool res = Hook((void*)OutFunc);
                //if (res)
                    //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "Rehooked!");
                if (!res)
                    T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", "Rehook failed!");
                return res;
            }
            catch (const char* errorMessage)
            {
                T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", errorMessage);
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
               //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "Unhooking at 0x0%X", BaseAddress);
               //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "OutFunc before unhooking: 0x%X", OutFunc);
                if (!OriginalBytes)
                    return false;
                T6SDK::Memory::RestoreOldBytes(BaseAddress, OriginalBytes, Length);
                //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "OutFunc after unhooking: 0x%X", OutFunc);
                return true;
            }
            catch (const char* errorMessage)
            {
                T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", errorMessage);
                return false;
            }
        }
        bool ReHook()
        {
			try
			{
                //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "Rehook func address: 0x%X", OutFunc);
                if(OutFunc == 0x00)
                {
                    T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", "Rehook failed! OutFunc was not set");
                    return false;
                }
                bool res = Hook((void*)OutFunc);
                //if (res)
                    //T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "MEMORYHOOK", "Rehooked!");
                if(!res)
                    T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", "Rehook failed!");
                return res;
			}
			catch (const char* errorMessage)
			{
                T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "MEMORYHOOK", errorMessage);
				return false;
			}
        }
    };
}