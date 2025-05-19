#pragma once
#include "pch.h"
#include "StdInclude.h"
#include "T6SDK.h"

namespace T6SDK
{
	class MemoryPatch
	{
	private:
		DWORD BaseAddress{};
		std::vector<BYTE> Opcodes{};
        std::vector<BYTE> OriginalOpcodes{};
        BYTE* OriginalBytes{};
	public:

		MemoryPatch(DWORD baseAddress, std::vector<BYTE> opcodes)
		{
			BaseAddress = baseAddress;
			Opcodes = opcodes;
            OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Opcodes.size());
            T6SDK::MAIN::PatchList.push_back((int)this);
		}
        MemoryPatch(DWORD v43BaseAddress, DWORD mpBaseAddress, DWORD v41BaseAddress, DWORD zmBaseAddress, std::vector<BYTE> opcodes)
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
            Opcodes = opcodes;
            OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Opcodes.size());
            T6SDK::MAIN::PatchList.push_back((int)this);
        }
        bool IsValid()
        {
            return *(int*)BaseAddress != 0x00;
        }
        void Patch()
        {
            if (!IsValid())
                return;
            size_t size = Opcodes.size();
            BYTE* ptr = new BYTE[size];
            memcpy(ptr, &Opcodes[0], size * sizeof(BYTE));
            //if (OriginalBytes != ptr)
            //    OriginalBytes = T6SDK::Memory::StoreOldBytes(BaseAddress, Opcodes.size());
            T6SDK::Memory::RestoreOldBytes(BaseAddress, ptr, Opcodes.size());

            //T6SDK::ConsoleLog::LogFormatted(14, "[MemoryPatch] Patched %i bytes at address 0x%x", Opcodes.size(), BaseAddress);
        }
        void UnPatch()
        {
			if (!IsValid())
				return;
			T6SDK::Memory::RestoreOldBytes(BaseAddress, OriginalBytes, Opcodes.size());

			//T6SDK::ConsoleLog::LogFormatted(14, "[MemoryPatch] Unpatched %i bytes at address 0x%x", Opcodes.size(), BaseAddress);
        }
        DWORD EndPointerAddress()
        {
            if (BaseAddress != NULL)
            {
                return BaseAddress;
            }
        }
	};
}