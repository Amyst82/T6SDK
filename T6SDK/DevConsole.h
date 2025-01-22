#pragma once
#include "StdInclude.h"
#include <string>
#include <deque>

namespace T6SDK
{
	namespace DevConsole
	{
		inline static std::string inputBuffer{};
		inline static std::deque<std::string> consoleBuffer;
		inline static const size_t maxLines = 20; // Maximum number of lines to display


		inline static int KeyChatcherMask = 0x00;
		inline static bool IsConsoleOpened = false;
		static void OpenConsole()
		{
			inputBuffer.clear();
			KeyChatcherMask = T6SDK::Addresses::CurrentKeyCatcher.Value();
			T6SDK::InternalFunctions::Key_SetCatcher(17);
			IsConsoleOpened = true;
			T6SDK::ConsoleLog::Log("Console opened!");
		}
		static void CloseConsole()
		{
			T6SDK::InternalFunctions::Key_SetCatcher(KeyChatcherMask);
			IsConsoleOpened = false;
			T6SDK::ConsoleLog::Log("Console closed!");
		}

		static void SwtichConsoleVisibileMode()
		{
			IsConsoleOpened == false ? OpenConsole() : CloseConsole();
		}
		static void AddConsoleMessage(const std::string& message)
		{
			consoleBuffer.push_back(message);
			if (consoleBuffer.size() > maxLines)
			{
				consoleBuffer.pop_front();
			}
		}
		static void ExecuteCommand(const std::string& command)
		{
			//TODO handle 'exec' command to open OpenFileDialog to select cfg
			T6SDK::Dvars::cbuf_AddText(command.c_str()); // Handle the command
		}
		static void OnInputKey(BYTE key)
		{
			//Getting InputKey by key
			T6SDK::Input::InputKey* keyPointer = 0x00;
			try
			{
				keyPointer = (T6SDK::Input::InputKey*)T6SDK::MAIN::CharKeys[key];
			}
			catch(const char* errorMessage)
			{
				T6SDK::ConsoleLog::LogError(errorMessage);
				keyPointer = 0x00;
			}
			//T6SDK::ConsoleLog::LogFormatted(CONSOLETEXTGREEN, "DevConsole Key pressed: 0x%X", keyPointer);
			if (!keyPointer)
				return;
			//T6SDK::ConsoleLog::LogFormatted(CONSOLETEXTGREEN, "DevConsole Key pressed: %c", keyPointer->KeyChar);
			//Detect opening console key
			if (key == T6SDK::Input::Keys::TILDA.KeyCode)
			{
				SwtichConsoleVisibileMode();
				T6SDK::ConsoleLog::Log("Tilda pressed!");
			}
			//Handling input if console is opened
			if (IsConsoleOpened)
			{
				if (keyPointer->KeyChar == '\b' && !inputBuffer.empty()) // Backspace
				{
					inputBuffer.pop_back();
				}
				else if (keyPointer->KeyChar == '\r') // Enter
				{
					AddConsoleMessage(inputBuffer);
					ExecuteCommand(inputBuffer);
					inputBuffer.clear();
				}
				else if (keyPointer->KeyChar >= 32 && keyPointer->KeyChar <= 126) // Printable ASCII characters
				{
					if(keyPointer->KeyChar == '~')
						return;
					if(inputBuffer.length() >= 150)
						return;
					if(keyPointer->KeyChar == '-' && T6SDK::Input::Keys::SHIFT.IsAnyPressState())
						inputBuffer += '_';
					else
					{
						if (T6SDK::Input::Keys::SHIFT.IsAnyPressState())
							inputBuffer += std::toupper(keyPointer->KeyChar);
						else
							inputBuffer += keyPointer->KeyChar;
					}
				}
			}
		}

		static std::vector<dvar_s*> FoundDvars{};
		static float bgHeight = 25.0f;
		static float bgY = 35.0f;
		static void DrawConsole()
		{
			if (!IsConsoleOpened)
				return;
			if (!T6SDK::Drawing::CheckResources())
				return;
			RECT bgRect{};

			//Drawing background outline
			if (!T6SDK::Drawing::DrawRectAbsolute(10.0f, bgY, T6SDK::Addresses::ScreenWidth.Value() - 20.0f, bgHeight, T6SDK::Drawing::WHITECOLOR, T6SDK::AnchorPoint::TopLeft, &bgRect))
				return;
			//Drawing background
			T6SDK::Drawing::DrawRectAbsolute(11.0f, bgY+1.0f, T6SDK::Addresses::ScreenWidth.Value() - 22.0f, bgHeight - 2.0f, T6SDK::Drawing::T_BLACKCOLOR, T6SDK::AnchorPoint::TopLeft, 0x00);
			//Drawing text (test)
			float height = (float)T6SDK::Drawing::consoleFont->pixelHeight;
			T6SDK::Typedefs::R_AddCmdDrawTextInternal("^5t6sdk^7> ", 256, T6SDK::Drawing::consoleFont, bgRect.left + 5.0f, bgRect.top + height + 5.0f, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);
			T6SDK::Typedefs::R_AddCmdDrawTextInternal(inputBuffer.c_str(), 256, T6SDK::Drawing::consoleFont, bgRect.left+70.0f, bgRect.top + height + 5.0f, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);

			//Drawing results
			if(!inputBuffer.empty())
				FoundDvars = T6SDK::Dvars::_DvarTrie.searchByPrefix(inputBuffer);
			else
				FoundDvars.clear();
			if(FoundDvars.size() == 0)
				bgHeight = 25.0f;
			else if(FoundDvars.size() <= maxLines)
				bgHeight = (float)(FoundDvars.size()+1) * 25.0f;
			else
				bgHeight = (float)(maxLines + 1) * 25.0f;

			float foundDvarsY = bgRect.top + (height * 2.0f) + 10.0f;
			for (int i = 0; i < maxLines; i++)
			{
				if(i<FoundDvars.size())
				{
					T6SDK::Typedefs::R_AddCmdDrawTextInternal(FoundDvars[i]->dvarName, 256, T6SDK::Drawing::consoleFont, bgRect.left + 70.0f, foundDvarsY, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);
					foundDvarsY += 25.0f;
				}
			}
		
		}

		static void Initialize()
		{
			//Remove redacted's console
			if (T6SDK::CrossVersion::GetGameVersion() == T6SDK::CrossVersion::GameVersion::V43 || T6SDK::CrossVersion::GetGameVersion() == T6SDK::CrossVersion::GameVersion::V41)
			{
				T6SDK::ConsoleLog::Log("Removing Redacted's console...");
				T6SDK::Addresses::Patches::DisableRedactedConsole.Patch();
				T6SDK::ConsoleLog::Log("Redacted's console removed!");
			}
			//Add dvars to dvar trie
			for (int i = 0; i < *T6SDK::Addresses::g_dvarCount; i++)
			{
				if (*(int*)(T6SDK::Addresses::dvarPool + (i * 0x60)))
				{
					T6SDK::Dvars::_DvarTrie.insert((dvar_s*)(T6SDK::Addresses::dvarPool + (i * 0x60)));
					//T6SDK::ConsoleLog::LogFormatted(CONSOLETEXTGREEN, "Dvar inserted!");
				}
			}
			
		}
		
	}
}