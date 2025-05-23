#include "pch.h"
#include "StdInclude.h"
namespace T6SDK
{
	FILE* fDummy;
	void ConsoleLog::Initialize()
	{
		if (!T6SDK::MAIN::DEBUG)
			return;
		try
		{
			AllocConsole();

			freopen_s(&fDummy, "CONOUT$", "w", stdout);
			EnableVTMode();
			switch (T6SDK::CrossVersion::GetGameVersion())
			{
			case T6SDK::CrossVersion::GameVersion::V43:
				LogTagged(C_SUCCESS, false, "DEVCONSOLE", "Loaded console Redacted MP");
				SetConsoleTitleA("T6SDK Redacted MP");
				break;
			case T6SDK::CrossVersion::GameVersion::MP:
				LogTagged(C_SUCCESS, false, "DEVCONSOLE", "Loaded console Steam MP");
				SetConsoleTitleA("T6SDK Steam MP");
				break;
			case T6SDK::CrossVersion::GameVersion::V41:
				LogTagged(C_SUCCESS, false, "DEVCONSOLE", "Loaded console Redacted ZM");
				SetConsoleTitleA("T6SDK Redacted ZM");
				break;
			case T6SDK::CrossVersion::GameVersion::ZM:
				LogTagged(C_SUCCESS, false, "DEVCONSOLE", "Loaded console Steam ZM");
				SetConsoleTitleA("T6SDK Steam ZM");
				break;
			}
			LogTagged(C_DEBUG, false, "DEVCONSOLE", "Console initialized!");
			return;
		}
		catch (const char* errorMessage)
		{
			MessageBoxA(NULL, errorMessage, "Error", MB_OK);
			return;
		}
		return;
	}
	void ConsoleLog::DeInitialize()
	{
		if (!T6SDK::MAIN::DEBUG)
			return;
		try
		{
			fclose(fDummy);
			FreeConsole();
			return;
		}
		catch (const char* errorMessage)
		{
			return;
		}
		return;
	}


}