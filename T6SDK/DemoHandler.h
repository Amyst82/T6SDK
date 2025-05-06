#pragma once
#include "StdInclude.h"
#pragma warning(disable:4996)
namespace T6SDK
{
    class DemoBriefData
    {
    public:
        bool Inited = false;
        std::string DemoPath{};
        std::string Map{};
        std::string MapUiSelect{};
        std::string MapFriendlyName{};
        std::string GameMode{};
        int Duration{};
        int CreateDate{};
        std::string Author{};
        std::string DemoName{};
        bool HasMetadata{};
        std::string Metadata{};
        DemoBriefData()
        {

        }
        //// Regular copy constructor
        DemoBriefData(const DemoBriefData&) = default;

        // Copy assignment
        DemoBriefData& operator=(const DemoBriefData&) = default;
        /*DemoBriefData(DemoBriefData& data)
        {
            this->Author = data.Author;
			this->CreateDate = data.CreateDate;
			this->DemoName = data.DemoName;
			this->DemoPath = data.DemoPath;
			this->Duration = data.Duration;
			this->GameMode = data.GameMode;
			this->HasMetadata = data.HasMetadata;
			this->Map = data.Map;
			this->MapFriendlyName = data.MapFriendlyName;
			this->MapUiSelect = data.MapUiSelect;
			this->Metadata = data.Metadata;
			Inited = true;
        }*/
        DemoBriefData(std::string& demoPath, std::string& mapName, std::string& mapUiSelect, std::string& mapFriendlyName, std::string& gameMode, int duration, int createDate, std::string& author, std::string& demoName, bool hasMetadata, std::string metadata)
        {
            this->DemoPath = demoPath;
			this->Map = mapName;
			this->MapUiSelect = mapUiSelect;
			this->MapFriendlyName = mapFriendlyName;
			this->GameMode = gameMode;
			this->Duration = duration;
			this->CreateDate = createDate;
			this->Author = author;
			this->DemoName = demoName;
			this->HasMetadata = hasMetadata;
			this->Metadata = metadata;
            Inited = true;
        }
        void Clear()
        {
			DemoPath = std::string("");
			Map = std::string("");
			MapUiSelect = std::string("");
			MapFriendlyName = std::string("");
			GameMode = std::string("");
			Duration = 0;
			CreateDate = 0;
			Author = std::string("");
			DemoName = std::string("");
			HasMetadata = false;
			Metadata = std::string("");
            Inited = false;
        }
    };
	class DemoHandler
	{
	private:
        class GameModeStrings
        {
        public:
            const char* mode{};
			const char* friendlyName{};
            GameModeStrings(const char* modeName, const char* _friendlyName)
            {
				mode = modeName;
				friendlyName = _friendlyName;
            }
		};
        class MpMapsStrngs
        {
        public:
			const char* map{};
			const char* friendlyName{};
            const char* menuSelectImage{};
            MpMapsStrngs(const char* mapName, const char* _friendlyName, const char* menuImage)
            {
				map = mapName;
				friendlyName = _friendlyName;
				menuSelectImage = menuImage;
            }
        };
        

		inline static void* allocatedMemory = 0;
	public:
        inline static const std::vector<MpMapsStrngs> MpMaps = {
            MpMapsStrngs("mp_la", "Aftermath", "loadscreen_mp_la"),
            MpMapsStrngs("mp_dockside", "Cargo", "loadscreen_mp_dockside"),
            MpMapsStrngs("mp_carrier", "Carrier", "loadscreen_mp_carrier"),
            MpMapsStrngs("mp_drone", "Drone", "loadscreen_mp_drone"),
            MpMapsStrngs("mp_express", "Express", "loadscreen_mp_express"),
            MpMapsStrngs("mp_hijacked", "Hijacked", "loadscreen_mp_hijacked"),
            MpMapsStrngs("mp_meltdown", "Meltdown", "loadscreen_mp_meltdown"),
            MpMapsStrngs("mp_overflow", "Overflow", "loadscreen_mp_overflow"),
            MpMapsStrngs("mp_nightclub", "Plaza", "loadscreen_mp_nightclub"),
            MpMapsStrngs("mp_raid", "Everyone's favourite map :)", "loadscreen_mp_raid"),
            MpMapsStrngs("mp_slums", "Slums", "loadscreen_mp_slums"),
            MpMapsStrngs("mp_village", "Standoff", "loadscreen_mp_village"),
            MpMapsStrngs("mp_turbine", "Turbine", "loadscreen_mp_turbine"),
            MpMapsStrngs("mp_socotra", "Yemen", "loadscreen_mp_socotra"),
            MpMapsStrngs("mp_nuketown_2020", "Nuketown 2025", "loadscreen_mp_nuketown_2020"),
            MpMapsStrngs("mp_downhill", "Downhill", "loadscreen_mp_downhill"),
            MpMapsStrngs("mp_mirage", "Mirage", "loadscreen_mp_mirage"),
            MpMapsStrngs("mp_hydro", "Hydro", "loadscreen_mp_hydro"),
            MpMapsStrngs("mp_skate", "Grind", "loadscreen_mp_skate"),
            MpMapsStrngs("mp_concert", "Encore", "loadscreen_mp_concert"),
            MpMapsStrngs("mp_magma", "Magma", "loadscreen_mp_magma"),
            MpMapsStrngs("mp_vertigo", "Vertigo", "loadscreen_mp_vertigo"),
            MpMapsStrngs("mp_studio", "Studio", "loadscreen_mp_studio"),
            MpMapsStrngs("mp_uplink", "Uplink", "loadscreen_mp_uplink"),
            MpMapsStrngs("mp_bridge", "Detour", "loadscreen_mp_bridge"),
            MpMapsStrngs("mp_castaway", "Cove", "loadscreen_mp_castaway"),
            MpMapsStrngs("mp_paintball", "Rush", "loadscreen_mp_paintball"),
            MpMapsStrngs("mp_dig", "Dig", "loadscreen_mp_dig"),
            MpMapsStrngs("mp_frostbite", "Frost", "loadscreen_mp_frostbite"),
            MpMapsStrngs("mp_pod", "Pod", "loadscreen_mp_pod"),
            MpMapsStrngs("mp_takeoff", "Takeoff", "loadscreen_mp_takeoff"),
        };
        inline static const std::map<MP_DemoGameMode, GameModeStrings> MpGameModes = { 
            {MP_DemoGameMode::tdm, GameModeStrings("tdm", "Team Deathmatch")}, 
            {MP_DemoGameMode::dm, GameModeStrings("dm", "Free For All")},
			{MP_DemoGameMode::dom, GameModeStrings("dom", "Domination")},
			{MP_DemoGameMode::dem, GameModeStrings("dem", "Demolition")},
			{MP_DemoGameMode::conf, GameModeStrings("conf", "Kill Confirmed")},
			{MP_DemoGameMode::koth, GameModeStrings("koth", "Hardpoint")},
			{MP_DemoGameMode::hq, GameModeStrings("hq", "Headquarters")},
			{MP_DemoGameMode::ctf, GameModeStrings("ctf", "Capture the flag")},
			{MP_DemoGameMode::sd, GameModeStrings("sd", "Search and Destroy")},
			{MP_DemoGameMode::oneflag, GameModeStrings("oneflag", "One Flag CTF")},
			{MP_DemoGameMode::gun, GameModeStrings("gun", "Gun Game")},
			{MP_DemoGameMode::oic, GameModeStrings("oic", "One in the Chamber")},
			{MP_DemoGameMode::shrp, GameModeStrings("shrp", "Sharpshooter")},
			{MP_DemoGameMode::sas, GameModeStrings("sas", "Sticks and Stones")}
        };
		static bool ReadMapName(vector<char> tagsFileData, std::string& mapName, std::string& friendlyName, std::string& uiSelectImage, bool supressConsoleLog);
		static bool ReadDemoGameMode(vector<char> tagsFileData, std::string& gameMode, std::string& friendlyName, bool supressConsoleLog);
		static bool DemoTagsHasMetadata(vector<char> tagsFileData, std::string& customMetaData, bool supressConsoleLog);
		static bool ReadDemoAuthor(vector<char> thumbnailFileData, std::string& author, bool supressConsoleLog);
		static bool ReadDemoName(vector<char> thumbnailFileData, std::string& demoName, bool supressConsoleLog);
		static bool ReadDemoDuration(vector<char> thumbnailFileData, uint32_t* duration, bool supressConsoleLog);
		static bool ReadDemoCreateDate(std::string path, vector<char> thumbnailFileData, int* createDate, bool supressConsoleLog);
        static DemoBriefData GetDemoBriefData(const char* demoPath);
        static bool TryGetDemoBriefData(const char* demoPath, DemoBriefData* briefData);
        static bool LoadDemoFromBriefData(T6SDK::DemoBriefData& briefData);
        static bool LoadDemoFromFile(const char* demoPath);
        static bool LoadDemoFromFile(const char* demoPath, T6SDK::DemoBriefData* briefData);
        static bool LoadDemoFromFile(const char* demoPath, bool* hasMetadata, std::string& metadata);
        static bool WriteTagsMetadata(const char* demoPath, std::string& metadata, uint64_t magicNumber);
	};
}