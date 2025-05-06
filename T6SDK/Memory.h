#pragma once
#include "pch.h"
#include "StdInclude.h"
namespace T6SDK
{
	namespace Memory
	{

		inline static MODULEINFO GetModuleInfo(LPCSTR szModule)
		{
			{
				MODULEINFO modinfo = { 0 };
				HMODULE hModule = GetModuleHandleA(szModule);
				if (hModule == 0)
					return modinfo;
				GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
				return modinfo;
			}
		}
		inline static BOOL MatchPattern(const BYTE* pData, const BYTE* bMask, const char* szMask)
		{
			for (; *szMask; ++szMask, ++pData, ++bMask)
				if (*szMask == 'x' && *pData != *bMask)
					return false;
			return (*szMask) == NULL;
		}
		inline static uintptr_t ReadPointer(uintptr_t ptr, std::vector<unsigned int> ofssets)
		{
			uintptr_t addr = ptr;
			for (unsigned int i = 0; i < ofssets.size(); ++i)
			{
				addr = *(uintptr_t*)addr;
				if (addr == 0x00)
				{
					return NULL;
				}
				addr += ofssets[i];
			}
			return addr;
		}
		inline static void SetFloatValueProtected(DWORD address, float value)
		{
			DWORD dwOldProtect, dwNewProtect;
			VirtualProtect((LPVOID)(address), sizeof(float), PAGE_EXECUTE_READWRITE, &dwOldProtect);
			*(float*)address = value;
			VirtualProtect((LPVOID)(address), sizeof(float), dwOldProtect, &dwNewProtect);
		}
		inline static bool Hook(void* toHook, void* ourFunc, int len)
		{
			if (len < 5)
			{
				return false;
			}
			DWORD curProtection;
			VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
			memset(toHook, 0x90, len);

			DWORD relativeAddress = ((DWORD)ourFunc - (DWORD)toHook) - 5;

			*(BYTE*)toHook = 0xE9;
			*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

			DWORD temp;
			VirtualProtect(toHook, len, curProtection, &temp);

			return true;
		}
		inline static BYTE* StoreOldBytes(DWORD dwAddress, int size)
		{
			DWORD dwOldProtect, dwNewProtect;
			BYTE* OldBytes;
			VirtualProtect((LPVOID)(dwAddress), size, PAGE_READWRITE, &dwOldProtect);
			OldBytes = new BYTE[size];
			memcpy(OldBytes, (LPVOID)(dwAddress), size);
			VirtualProtect((LPVOID)(dwAddress), size, dwOldProtect, &dwNewProtect);

			return OldBytes;
		}
		inline static BYTE* Hook_o(void* toHook, void* ourFunc, int len)
		{
			if (len < 5)
			{
				return nullptr;
			}
			BYTE* OriginalBytes = StoreOldBytes((DWORD)toHook, len);
			DWORD curProtection;
			VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
			memset(toHook, 0x90, len);

			DWORD relativeAddress = ((DWORD)ourFunc - (DWORD)toHook) - 5;

			*(BYTE*)toHook = 0xE9;
			*(DWORD*)((DWORD)toHook + 1) = relativeAddress;

			DWORD temp;
			VirtualProtect(toHook, len, curProtection, &temp);

			return OriginalBytes;
		}

		inline static void RestoreOldBytes(DWORD dwAddress, BYTE* OldBytes, int size)
		{
			DWORD dwOldProtect, dwNewProtect;
			VirtualProtect((LPVOID)(dwAddress), size, PAGE_READWRITE, &dwOldProtect);
			memcpy((LPVOID)(dwAddress), OldBytes, size);
			VirtualProtect((LPVOID)(dwAddress), size, dwOldProtect, &dwNewProtect);

			//delete[] OldBytes;
			//OldBytes = 0;
		}
		inline static void NOP(DWORD dwAddress, int size)
		{
			DWORD dwOldProtect, dwNewProtect;
			VirtualProtect((LPVOID)(dwAddress), size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			memset((LPVOID)(dwAddress), 0x90, size);
			VirtualProtect((LPVOID)(dwAddress), size, dwOldProtect, &dwNewProtect);
		}
		inline static void MemoryCopySafe(void* dst, const void* src, size_t size)
		{
			DWORD dwOldProtect, dwNewProtect;
			VirtualProtect((LPVOID)(dst), size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
			memcpy((LPVOID)(dst), src, size);
			VirtualProtect((LPVOID)(dst), size, dwOldProtect, &dwNewProtect);
		}
		inline static void UnprotectModule(std::uintptr_t module)
		{
			if (module == NULL)
				module = (std::uintptr_t)GetModuleHandle(NULL);

			PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)module;
			PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)module + header->e_lfanew);

			SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
			DWORD oldProtect;
			VirtualProtect((LPVOID)module, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		}
		inline static DWORD SignatureScan(const char* szSig, const char* szMask)
		{
			DWORD dwAddress = (DWORD)GetModuleHandleA(NULL);
			DWORD dwLen = GetModuleInfo(NULL).SizeOfImage;

			for (DWORD i = 0; i < dwLen; i++)
				if (MatchPattern((BYTE*)(dwAddress + i), (BYTE*)szSig, szMask))
					return (DWORD)(dwAddress + i);

			return 0;
		}
		inline static DWORD IdaSigScan(const char* signature, LPCSTR moduleName)
		{
			static auto pattern_to_byte = [](const char* pattern)
				{
					auto bytes = std::vector<char>{};
					auto start = const_cast<char*>(pattern);
					auto end = const_cast<char*>(pattern) + strlen(pattern);

					for (auto current = start; current < end; ++current)
					{
						if (*current == '?')
						{
							++current;
							if (*current == '?')
								++current;
							bytes.push_back('\?');
						}
						else
						{
							bytes.push_back(strtoul(current, &current, 16));
						}
					}
					return bytes;
				};

			DWORD base = (DWORD)GetModuleHandleA(moduleName);
			if (base == NULL)
				return 0x00;
			DWORD sizeOfImage = GetModuleInfo(moduleName).SizeOfImage;
			auto patternBytes = pattern_to_byte(signature);

			DWORD patternLength = patternBytes.size();
			auto data = patternBytes.data();

			for (DWORD i = 0; i < sizeOfImage - patternLength; i++)
			{
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++)
				{
					char a = '\?';
					char b = *(char*)(base + i + j);
					found &= data[j] == a || data[j] == b;
				}
				if (found)
				{
					return base + i;
				}
			}
			return NULL;
		}
		inline static std::vector<DWORD> IdaSigScanM(const char* signature, LPCSTR moduleName)
		{
			static auto pattern_to_byte = [](const char* pattern)
			{
				auto bytes = std::vector<char>{};
				auto start = const_cast<char*>(pattern);
				auto end = const_cast<char*>(pattern) + strlen(pattern);
			
				for (auto current = start; current < end; ++current)
				{
					if (*current == '?')
					{
						++current;
						if (*current == '?')
							++current;
						bytes.push_back('\?');
					}
					else
					{
						bytes.push_back(strtoul(current, &current, 16));
					}
				}
				return bytes;
			};
			std::vector<DWORD> FoundAddreses{};
			DWORD base = (DWORD)GetModuleHandleA(moduleName);
			if (base == NULL)
				return FoundAddreses;
			DWORD sizeOfImage = GetModuleInfo(moduleName).SizeOfImage;
			auto patternBytes = pattern_to_byte(signature);

			DWORD patternLength = patternBytes.size();
			auto data = patternBytes.data();

			for (DWORD i = 0; i < sizeOfImage - patternLength; i++)
			{
				bool found = true;
				for (DWORD j = 0; j < patternLength; j++)
				{
					char a = '\?';
					char b = *(char*)(base + i + j);
					found &= data[j] == a || data[j] == b;
				}
				if (found)
				{
					FoundAddreses.push_back(base + i);
				}
			}
			return FoundAddreses;
		}
		inline static DWORD IdaSigScan(const char* signature)
		{
			return IdaSigScan(signature, NULL);
		}
	}
}