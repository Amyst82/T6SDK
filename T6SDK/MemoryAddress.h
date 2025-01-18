#pragma once
#include "pch.h"
#include "StdInclude.h"

namespace T6SDK
{
    template <typename T>
    class MemoryAddress
    {
    private:
        DWORD BaseAddress{};
        std::vector<unsigned int> Offset{};
    public:

        MemoryAddress(DWORD baseAddress, std::vector<unsigned int> offsets)
        {
            BaseAddress = baseAddress;
            Offset = offsets;
        }
        MemoryAddress(DWORD baseAddress)
        {
            BaseAddress = baseAddress;
        }
        #pragma region CrossVersion 
        MemoryAddress(DWORD v43BaseAddress, DWORD mpBaseAddress, DWORD v41BaseAddress, DWORD zmBaseAddress, std::vector<unsigned int> offsets)
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
            Offset = offsets;
        }
        MemoryAddress(DWORD v43BaseAddress, DWORD mpBaseAddress, DWORD v41BaseAddress, DWORD zmBaseAddress)
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
        }
#pragma endregion
        bool IsValid()
        {
            if (BaseAddress == NULL)
                return false;
            if (Offset.size() > 0)
                return *(int*)BaseAddress != 0x00;
            else
                return true;
        }
        T& Value()
        {
            if (Offset.empty() && BaseAddress != NULL)
            {
                return *(T*)BaseAddress;
            }
            else if (BaseAddress != NULL && !Offset.empty())
            {
                uintptr_t addr = T6SDK::Memory::ReadPointer(BaseAddress, Offset);
                return *(T*)addr;
            }
        }
        DWORD EndPointerAddress()
        {
            if (Offset.empty() && BaseAddress != NULL)
            {
                return BaseAddress;
            }
            else if (BaseAddress != NULL && !Offset.empty())
            {
                uintptr_t addr = T6SDK::Memory::ReadPointer(BaseAddress, Offset);
                return addr;
            }
        }
        void SetValueSafe(const T& value)
        {
            if (IsValid() == false)
            {
                char buffer[256];
				sprintf_s(buffer, 256, "Unable to set value of base address 0x%x", BaseAddress);
                T6SDK::ConsoleLog::Log(buffer);
                return;
            }
            if (Offset.empty() && BaseAddress != NULL)
            {
                DWORD curProtection;
                VirtualProtect((void*)BaseAddress, sizeof(T), PAGE_EXECUTE_READWRITE, &curProtection);
                *(T*)BaseAddress = value; // writing
                DWORD temp;
                VirtualProtect((void*)BaseAddress, sizeof(T), curProtection, &temp);
            }
            else if (BaseAddress != NULL && !Offset.empty())
            {
                uintptr_t addr = T6SDK::Memory::ReadPointer(BaseAddress, Offset);
                DWORD curProtection;
                VirtualProtect((void*)addr, sizeof(T), PAGE_EXECUTE_READWRITE, &curProtection);
                *(T*)addr = value; // writing
                DWORD temp;
                VirtualProtect((void*)addr, sizeof(T), curProtection, &temp);
            }

        }

    };
}