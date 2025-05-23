#pragma once
#include "StdInclude.h"
#pragma warning(disable:4996)
namespace T6SDK
{
    class DemoBriefData
    {
    public:
        bool Inited = false;
        std::string DemoPath = std::string("");
        std::string Map = std::string("");
        std::string MapUiSelect = std::string("");
        std::string MapFriendlyName = std::string("");
        std::string GameMode = std::string("");
        int Duration = 0;
        int CreateDate = 0;
        std::string Author = std::string("");
        std::string DemoName = std::string("");
        std::string Description = std::string("");
        bool HasMetadata = false;
        std::string Metadata = std::string("");

        DemoBriefData() = default;
        DemoBriefData(const DemoBriefData&) = default;
        DemoBriefData(DemoBriefData&&) = default;
        DemoBriefData& operator=(const DemoBriefData&) = default;
        DemoBriefData& operator=(DemoBriefData&&) = default;
        DemoBriefData(std::string& demoPath, std::string& mapName, std::string& mapUiSelect, std::string& mapFriendlyName, std::string& gameMode, int duration, int createDate, std::string& author, std::string& demoName, std::string& description, bool hasMetadata, std::string metadata)
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
            this->Description = description;
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
			Description = std::string("");
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
        inline static const std::vector<GameModeStrings> MpGameModes = { 
            GameModeStrings("tdm", "Team Deathmatch"), 
            GameModeStrings("dm", "Free For All"),
			GameModeStrings("dom", "Domination"),
			GameModeStrings("dem", "Demolition"),
			GameModeStrings("conf", "Kill Confirmed"),
			GameModeStrings("koth", "Hardpoint"),
			GameModeStrings("hq", "Headquarters"),
			GameModeStrings("ctf", "Capture the flag"),
			GameModeStrings("sd", "Search and Destroy"),
			GameModeStrings("oneflag", "One Flag CTF"),
			GameModeStrings("gun", "Gun Game"),
			GameModeStrings("oic", "One in the Chamber"),
			GameModeStrings("shrp", "Sharpshooter"),
			GameModeStrings("sas", "Sticks and Stones")
        };

        inline static const std::vector<MpMapsStrngs> ZmMaps = {
            MpMapsStrngs("zm_transit", "Tranzit", "menu_zm_transit_zsurvival_transit"),
            MpMapsStrngs("zm_transit_dr", "Diner", "menu_zm_transit_zsurvival_diner"),
            MpMapsStrngs("zm_highrise", "Die Rise", "menu_zm_highrise_zclassic_rooftop"),
            MpMapsStrngs("zm_nuked", "Nuketown", "menu_zm_nuketown_select"),
            MpMapsStrngs("zm_prison", "Mob of the Dead", "menu_zm_prison_zclassic_prison"),
            MpMapsStrngs("zm_buried", "Buried", "menu_zm_buried_zclassic_processing"),
            MpMapsStrngs("zm_tomb", "Origins", "menu_zm_tomb_zclassic_tomb"),
        };
        inline static const std::vector<GameModeStrings> ZmGameModes = {
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode"),
			 GameModeStrings("Unknown", "^1Unknown mode")
        };

        //map
		static std::string ReadMapName(vector<uint8_t>& tagsFileData);
		static std::string ReadMapFriendlyName(vector<uint8_t>& tagsFileData);
		static std::string ReadMapMenuSelectMaterial(vector<uint8_t>& tagsFileData);
        //game mode
		static std::string ReadDemoGameMode(vector<uint8_t>& tagsFileData);
        //duration
        static uint32_t ReadDemoDuration(vector<uint8_t>& thumbnailFileData);
        //metadata
        static std::string ReadDemoMetadata(vector<uint8_t>& tagsFileData);
        //author
		static std::string ReadDemoAuthor(vector<uint8_t>& thumbnailFileData);
        //description
        static std::string ReadDemoDescription(vector<uint8_t >& thumbnailFileData);
        //demo name
		static std::string ReadDemoName(vector<uint8_t >& thumbnailFileData);
        static bool SetDemoName(std::string& demoPath, std::string& name);
		//create date
		static int ReadDemoCreateDate(std::string& path, vector<uint8_t>& thumbnailFileData);

        
        static DemoBriefData GetDemoBriefData(const char* demoPath);
        static bool TryGetDemoBriefData(const char* demoPath, DemoBriefData* briefData);
        static bool LoadDemoFromBriefData(T6SDK::DemoBriefData& briefData);
        static bool LoadDemoFromFile(const char* demoPath);
        static bool LoadDemoFromFile(const char* demoPath, T6SDK::DemoBriefData* briefData);
        static bool WriteTagsMetadata(const char* demoPath, std::string& metadata, uint64_t magicNumber);
	};
}