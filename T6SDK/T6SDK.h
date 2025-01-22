#pragma once
#include <vector>
#pragma warning(disable:4996)

namespace T6SDK
{
	class MAIN
	{
	private:

	public:
		static void PreInit();
		inline static bool GameLoaded = false;
		inline static bool DEBUG = false;
		static void Initialize();
		static void DeInitialize();
		inline static std::vector<int> RegisteredCameraModes{};
		inline static std::vector<int> RegisteredRadioButtons{};
		inline static std::map<BYTE, int> CharKeys{};
	};
}