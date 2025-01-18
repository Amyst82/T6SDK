#pragma once
#include "StdInclude.h"
namespace T6SDK::CrossVersion
{
    static enum GameVersion
    {
        V43 = 0,
        MP = 1,
        V41 = 2,
        ZM = 3
    };
    static GameVersion GAMEVERSION = MP;
    static GameVersion GetGameVersion()
    {
        HANDLE proc = GetCurrentProcess;
        DWORD ID = GetCurrentProcessId();
        TCHAR szProcessName[12] = TEXT("<unknown>");
        TCHAR RedactedMPName[12] = TEXT("t6mpv43.exe");
        TCHAR SteamMPName[12] = TEXT("t6mp.exe");
        TCHAR RedactedZMName[12] = TEXT("t6zmv41.exe");
        TCHAR SteamZMName[12] = TEXT("t6zm.exe");
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ID);
        if (NULL != hProcess)
        {
            HMODULE hMod;
            DWORD cbNeeded;
            if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
            {
                GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
            }
        }
        if (lstrcmp(szProcessName, RedactedMPName) == 0)
        {
            GAMEVERSION = V43;
            return V43;
        }
        else if (lstrcmp(szProcessName, SteamMPName) == 0)
        {
            GAMEVERSION = MP;
            return MP;
        }
        else if (lstrcmp(szProcessName, RedactedZMName) == 0)
        {
            GAMEVERSION = V41;
            return V41;
        }
        else if (lstrcmp(szProcessName, SteamZMName) == 0)
        {
            GAMEVERSION = ZM;
            return ZM;
        }
        else
        {
            return V43;
        }
        return V43;
    }

    template <typename T>
    class CrossValue
    {
    private:
        T _v43Value{};
        T _mpValue{};
        T _v41Value{};
        T _zmValue{};

    public:
        CrossValue(const T& V43Value, const T& MPValue, const T& V41Value, const T& ZMValue)
        {
            _v43Value = V43Value;
            _mpValue = MPValue;
            _v41Value = V41Value;
            _zmValue = ZMValue;
        }

        T& GetValue()
        {
            switch (GetGameVersion())
            {
            case V43:
                return _v43Value;
            case MP:
                return _mpValue;
            case V41:
                return _v41Value;
            case ZM:
                return _zmValue;
            }
        }

    };
}