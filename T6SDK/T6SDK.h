#pragma once
#pragma warning(disable:4996)

namespace T6SDK
{
	class MAIN
	{
	public:
		static void PreInit();
		inline static bool GameLoaded = false;
		inline static bool DEBUG = false;
		static void Initialize();
		static void DeInitialize();
		inline static std::vector<int> RegisteredCameraModes{};
		inline static std::vector<int> RegisteredRadioButtons{};
	};
}