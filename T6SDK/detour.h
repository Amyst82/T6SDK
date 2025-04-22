#pragma once
#include <Windows.h>
#include <iostream>
#include <cstdint>
#include "StdInclude.h"
namespace T6SDK
{
	class CDetourHook
	{

	private:
		void* m_original_function = nullptr;
		std::uint8_t* m_original_bytes = nullptr;
		std::uint8_t* m_hook_bytes = nullptr;
		void* hook_func = nullptr;
		const char* m_name{};
	public:
		CDetourHook(const char* name, void* trampoline)
		{
			m_name = name;
			m_original_function = trampoline;
			m_original_bytes = new std::uint8_t[6];
			m_hook_bytes = new std::uint8_t[6];
			if (!trampoline)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "Hooking attempted without trampoline!");
				return;
			}

			T6SDK::Memory::MemoryCopySafe(m_original_bytes, trampoline, 6);

			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "CDetourHook", "Saving old instructions: [0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X]",
				m_original_bytes[0], m_original_bytes[1], m_original_bytes[2], m_original_bytes[3], m_original_bytes[4], m_original_bytes[5]);
		}
		void Hook(void* hook_func)
		{
			const auto rel_address = static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(hook_func) - reinterpret_cast<std::uintptr_t>(m_original_function) - 5);

			m_hook_bytes[0] = 0xE9; //jmp
			*reinterpret_cast<std::uint32_t*>(&m_hook_bytes[1]) = rel_address;
			m_hook_bytes[5] = 0xCC; //int3

			T6SDK::Memory::MemoryCopySafe(m_original_bytes, m_original_function, 6);

			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "CDetourHook", "Writing new instructions: [0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X]",
				m_hook_bytes[0], m_hook_bytes[1], m_hook_bytes[2], m_hook_bytes[3], m_hook_bytes[4], m_hook_bytes[5]);

			T6SDK::Memory::MemoryCopySafe(m_original_function, m_hook_bytes, 6);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "CDetourHook", "%s detoured!", m_name);
		}
		//~CDetourHook()
		//{
		//	unhook();
		//	delete[] m_original_bytes;
		//	delete[] m_hook_bytes;
		//}

		void UnHook()
		{
			if (!m_original_function)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "unhook: original_function is nullptr");
				return;
			}

			if (!m_original_bytes)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "unhook: original_bytes is nullptr");
				return;
			}
			T6SDK::Memory::MemoryCopySafe(m_original_function, m_original_bytes, 6);
			//T6SDK::ConsoleLog::LogSameLineFormatted("[CDetourHook] Restoring %s: [0x%X, 0x%X, 0x%X, 0x%X, 0x%X, 0x%X]", m_name, m_original_bytes[0], m_original_bytes[1], m_original_bytes[2], m_original_bytes[3], m_original_bytes[4], m_original_bytes[5]);
		}
		void Dispose()
		{
			UnHook();
			delete[] m_original_bytes;
			delete[] m_hook_bytes;
		}
		void rehook()
		{
			if (!m_original_function)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "rehook: original_function is nullptr");
				return;
			}
			if (!m_hook_bytes)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "rehook: hook_bytes is nullptr");
				return;
			}
			T6SDK::Memory::MemoryCopySafe(m_original_function, m_hook_bytes, 6);
		}

		template<typename Fn = void*>
		Fn get_original_function()
		{
			return reinterpret_cast<Fn>(m_original_function);
		}

		template<typename ReturnType, typename Fn, typename... Args>
		ReturnType call_original(Args... args)
		{
			auto original = get_original_function<Fn>();
			if (!original)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "call_original: original is nullptr");

			UnHook();
			ReturnType ret = original(args...);
			rehook();

			return ret;
		}

		template<typename Fn, typename... Args>
		void call_original_noreturn(Args... args)
		{
			auto original = get_original_function<Fn>();
			if (!original)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "CDetourHook", "call_original_noreturn: original is nullptr\n");

			UnHook();
			original(args...);
			rehook();
		}

	};
}