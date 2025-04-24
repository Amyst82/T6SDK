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
		inline static int SelectedLine = 0;

		inline static int KeyChatcherMask = 0x00;
		inline static bool IsConsoleOpened = false;
		inline static float CaretBlink = 1.0f;
		inline static bool CaretBlinkDirectionTowards = false;
		inline static int CaretIndex = 0;
		inline static float charWidth = 8.0f;

		static std::vector<dvar_s*> FoundDvars{};
		static float ContentXOffset = 105.0f;
		static float bgHeight = 25.0f;
		static float bgY = 10.0f;
		static void OpenConsole()
		{
			inputBuffer.clear();
			KeyChatcherMask = T6SDK::Addresses::CurrentKeyCatcher.Value();
			T6SDK::InternalFunctions::Key_SetCatcher(17);
			T6SDK::MAIN::DevConsoleOpened = true;
			T6SDK::Input::SetInputLocked(true);
			CaretIndex = 0;
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEVCONSOLE", "Console opened!");
		}
		static void CloseConsole()
		{
			T6SDK::InternalFunctions::Key_SetCatcher(KeyChatcherMask);
			T6SDK::MAIN::DevConsoleOpened = false;
			T6SDK::Input::SetInputLocked(false);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEVCONSOLE", "Console closed!");
		}

		static void SwtichConsoleVisibileMode()
		{
			T6SDK::MAIN::DevConsoleOpened == false ? OpenConsole() : CloseConsole();
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
			if (!T6SDK::MAIN::ENABLED)
				return;
			//Getting InputKey by key
			T6SDK::Input::InputKey* keyPointer = 0x00;
			try
			{
				keyPointer = (T6SDK::Input::InputKey*)T6SDK::MAIN::CharKeys[key];
			}
			catch(const char* errorMessage)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DEVCONSOLE", errorMessage);
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
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEVCONSOLE", "Tilda pressed!");
			}
			
			
			//Handling input if console is opened
			if (T6SDK::MAIN::DevConsoleOpened)
			{
				if (key == T6SDK::Input::Keys::LEFT.KeyCode) // Left
				{
					if (CaretIndex > 0)
						CaretIndex--;
				}
				if (key == T6SDK::Input::Keys::RIGHT.KeyCode) // Right
				{
					if (CaretIndex < inputBuffer.length())
						CaretIndex++;
				}
				if (key == T6SDK::Input::Keys::UP.KeyCode) // Up
				{
					if (FoundDvars.empty())
					{
						if (!consoleBuffer.empty())
						{
							inputBuffer = consoleBuffer.back();
							consoleBuffer.pop_back();
							CaretIndex = inputBuffer.length();
						}
					}
					else
					{
						if (SelectedLine > 0)
							SelectedLine--;
						else
						{
							if(FoundDvars.size() < maxLines)
								SelectedLine = FoundDvars.size() - 1;
							else
								SelectedLine = maxLines - 1;
						}
					}
				}
				if (key == T6SDK::Input::Keys::DOWN.KeyCode) // Down
				{
					if (SelectedLine < maxLines - 1)
						SelectedLine++;
					else
						SelectedLine = 0;
				}
				if (key == T6SDK::Input::Keys::TAB.KeyCode) // Tab
				{
					if (FoundDvars.size() > 0)
					{
						inputBuffer = std::string(FoundDvars[SelectedLine]->dvarName) + std::string(" ");
						SelectedLine = 0;
						CaretIndex = inputBuffer.length();
					}
				}
				if (key == T6SDK::Input::Keys::ESCAPE.KeyCode) // Escape
				{
					CloseConsole();
				}
				if (keyPointer->KeyChar == '\b' && !inputBuffer.empty()) // Backspace
				{
					if(CaretIndex > 0)
					{
						inputBuffer.erase(CaretIndex - 1, 1);
						CaretIndex--;
					}
				}
				if (key == T6SDK::Input::Keys::DELETE_KEY.KeyCode && !inputBuffer.empty()) // Delete
				{
					if (CaretIndex < inputBuffer.length())
					{
						inputBuffer.erase(CaretIndex, 1);
					}
				}
				else if (keyPointer->KeyChar == '\r') // Enter
				{
					AddConsoleMessage(inputBuffer);
					ExecuteCommand(inputBuffer);
					inputBuffer.clear();
					SelectedLine = 0;
					CaretIndex = 0;
					CloseConsole();
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
					CaretIndex = inputBuffer.length();
				}
			}
		}


		static void DrawConsole()
		{
			if (!T6SDK::MAIN::ENABLED)
				return;
			if (!T6SDK::MAIN::DevConsoleOpened)
				return;
			if (!T6SDK::Drawing::CheckResources())
				return;
			T6SDK::InternalFunctions::Key_SetCatcher(17);
			T6SDK::MAIN::DevConsoleOpened = true;
			T6SDK::Input::SetInputLocked(true);
			RECT bgRect{};

			//Drawing background outline
			if (!T6SDK::Drawing::DrawRectAbsolute(10.0f, bgY, T6SDK::Addresses::ScreenWidth.Value() - 20.0f, bgHeight, tColor{ 0.31f, 0.31f, 0.35f, 1.0f}, T6SDK::AnchorPoint::TopLeft, &bgRect))
				return;
			//Drawing background
			T6SDK::Drawing::DrawRectAbsolute(11.0f, bgY+1.0f, T6SDK::Addresses::ScreenWidth.Value() - 22.0f, bgHeight - 2.0f, tColor{ 0.09f, 0.11f, 0.16f, 1.0f}, T6SDK::AnchorPoint::TopLeft, 0x00);
			//Drawing text (test)
			float height = (float)T6SDK::Drawing::consoleFont->pixelHeight;
			const char* DEVCONSOLETITLE = "^5AIRYZ ^7>  ";
			ContentXOffset = T6SDK::InternalFunctions::R_TextWidth(DEVCONSOLETITLE, strlen(DEVCONSOLETITLE), T6SDK::Drawing::consoleFont);
			T6SDK::Typedefs::R_AddCmdDrawTextInternal(DEVCONSOLETITLE, 256, T6SDK::Drawing::consoleFont, bgRect.left + 5.0f, bgRect.top + height + 5.0f, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);
			//MAIN CONTENT
			T6SDK::Typedefs::R_AddCmdDrawTextInternal(inputBuffer.c_str(), 256, T6SDK::Drawing::consoleFont, bgRect.left + ContentXOffset, bgRect.top + height + 5.0f, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);

			//Drawing caret
			float blinkDuration = 50.0f;

			if (CaretBlinkDirectionTowards)//increase opacity
			{
				CaretBlink += (1.0f / blinkDuration);
				if(CaretBlink >= 1.0f)
				{
					CaretBlink = 1.0f;
					CaretBlinkDirectionTowards = false;
				}
			}
			else //decrease opacity
			{
				CaretBlink -= (1.0f / blinkDuration);
				if (CaretBlink <= 0.0f)
				{
					CaretBlink = 0.0f;
					CaretBlinkDirectionTowards = true;
				}
			}
			float x = bgRect.left + ContentXOffset + CaretIndex * charWidth;
			float y = bgRect.top + 5.0f;
			T6SDK::Drawing::DrawRectAbsolute(x, y, 2.0f, 15.0f, tColor{ 1.0f, 1.0f, 1.0f, CaretBlink}, T6SDK::AnchorPoint::TopLeft, 0x00);

			//Drawing results
			if(!inputBuffer.empty())
			{
				//lowercase that
				std::string word = inputBuffer;
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				FoundDvars = T6SDK::Dvars::_DvarTrie.searchByPrefix(word);
			}
			else
				FoundDvars.clear();
			if(FoundDvars.size() == 0)
				bgHeight = 25.0f;
			else if(FoundDvars.size() <= maxLines)
			{
				bgHeight = (float)(FoundDvars.size() + 1) * 25.0f;
				if(SelectedLine >= FoundDvars.size())
					SelectedLine = 0;
			}
			else
			{
				bgHeight = (float)(maxLines + 1) * 25.0f;
				if(SelectedLine >= maxLines)
					SelectedLine = 0;
			}

			float foundDvarsY = bgRect.top + (height * 2.0f) + 15.0f;
			for (int i = 0; i < maxLines; i++)
			{
				if(i<FoundDvars.size())
				{

					char nameBuffer[256];
					if(SelectedLine == i)
					{
						sprintf(nameBuffer, "^5%s", FoundDvars[i]->dvarName);
						T6SDK::Drawing::DrawRectAbsolute(bgRect.left + 1.0f, foundDvarsY - 20.0f, bgRect.right - bgRect.left - 2.0f, 25.0f, tColor{ 0.19f, 0.21f, 0.26f, 0.7f }, T6SDK::AnchorPoint::TopLeft, 0x00);
					}
					else
						sprintf(nameBuffer, "^7%s", FoundDvars[i]->dvarName);
					char buffer[256];
					sprintf(buffer, "%s\t\t\t\t^9Type: ^3%s\t\t\t\t^9Current: ^3%s\t\t\t\t^9%s", nameBuffer, T6SDK::Dvars::GetTypeAsString(FoundDvars[i]), T6SDK::Dvars::GetCurrentValueAsString(FoundDvars[i]).c_str(), FoundDvars[i]->dvarDesc);

					RECT selectedLineRect{};
					if (T6SDK::Drawing::DrawRectAbsolute(bgRect.left+1.0f, foundDvarsY - 20.0f, bgRect.right - bgRect.left-2.0f, 25.0f, tColor{ 0.09f, 0.11f, 0.16f, 0.0f }, T6SDK::AnchorPoint::TopLeft, &selectedLineRect))
					{
						if (T6SDK::Input::MousePosX() > selectedLineRect.left && T6SDK::Input::MousePosX() < selectedLineRect.right && T6SDK::Input::MousePosY() > selectedLineRect.top && T6SDK::Input::MousePosY() < selectedLineRect.bottom)
						{
							if(SelectedLine != i)
								T6SDK::Drawing::DrawRectAbsolute(bgRect.left + 1.0f, foundDvarsY - 20.0f, bgRect.right - bgRect.left - 2.0f, 25.0f, tColor{ 0.19f, 0.21f, 0.26f, 0.7f }, T6SDK::AnchorPoint::TopLeft, 0x00);
							if (T6SDK::Input::Keys::LMB.Pressed())
								SelectedLine = i;
							else if (T6SDK::Input::Keys::RMB.Pressed())
							{
								SelectedLine = i;
								inputBuffer = std::string(FoundDvars[i]->dvarName) + std::string(" ");
								CaretIndex = inputBuffer.length();
							}
						}
					}
					T6SDK::Typedefs::R_AddCmdDrawTextInternal(buffer, 256, T6SDK::Drawing::consoleFont, bgRect.left + ContentXOffset, foundDvarsY, 1.0f, 1.0f, 0, T6SDK::Drawing::WHITECOLOR, 0);
					foundDvarsY += 25.0f;
				}
			}
		
		}

		static void Initialize()
		{
			//Remove redacted's console
			if (T6SDK::CrossVersion::GetGameVersion() == T6SDK::CrossVersion::GameVersion::V43 || T6SDK::CrossVersion::GetGameVersion() == T6SDK::CrossVersion::GameVersion::V41)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEVCONSOLE", "Removing Redacted's console...");
				DWORD redactedConsole = T6SDK::Memory::IdaSigScan("FF D0 47 8D 76 ? 3B FB 75 ? A1", "ExtendedConsole.Red32n");
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEVCONSOLE", "Redacted's console address: %p", redactedConsole);
				T6SDK::Addresses::Patches::DisableRedactedConsole = T6SDK::MemoryPatch(redactedConsole, { 0x90, 0x90 });
				T6SDK::Addresses::Patches::DisableRedactedConsole.Patch();
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, true, "DEVCONSOLE", "Redacted's console removed!");
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