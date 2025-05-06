#include "pch.h"
#include "StdInclude.h"

namespace T6SDK
{
	#pragma region Helpers
	uint64_t bytesToLong(const std::vector<unsigned char>& bytes)
	{
		if (bytes.size() < 8) {
			throw std::runtime_error("Need at least 8 bytes");
		}

		uint64_t result;
		std::memcpy(&result, bytes.data(), sizeof(result)); // Copy bytes directly
		return result;
	}
	int bytesToInt(const std::vector<unsigned char>& bytes)
	{
		if (bytes.size() < sizeof(int))
		{
			throw std::runtime_error("Not enough bytes to convert to long");
		}
		int result;
		std::memcpy(&result, bytes.data(), sizeof(int));
		return result;
	}	
	bool DecodeString(const std::vector<char>& encoded, std::string& decodedString) //ASCII decoder (BO2 has ascii bytes multiplied by 2 in %s.tags file somehow)
	{
		std::string result;
		for (uint8_t byte : encoded) 
		{
			if (byte == 0x00) //Null terminator
				break;
			if (byte == 0xFF) //End of string
				break;
			if(byte % 2 ==  0) //If it can be divided by two
				result += byte/2;
			else if(byte % 2 > 0)
				result += (byte - 1) / 2; //If it can't be divided by two, subtract 1 and divide by 2
			else
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Unreadable byte: 0x%X", byte);
				decodedString = "";
				return false;
			}
		}
		if (result.empty())
		{
			//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Decoded string is empty!");
			return false;
		}
		//else
		//	T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Decoded string: %s", result.c_str());
		decodedString = result;
		return true;
	}
	bool EncodeString(const std::string& inputString, std::vector<char>& encodedString)
	{
		encodedString.clear();
		for (char c : inputString)
		{
			encodedString.push_back(c * 2);
		}
		encodedString.push_back(0x00); //Null terminator
		return true;
	}
	std::vector<char> timeToBytes(time_t timestamp) 
	{
		std::vector<char> bytes(8);

		// Convert to known-size integer type (uint64_t)
		uint64_t timeValue = static_cast<uint64_t>(timestamp);

		// Copy bytes in little-endian order (change if you need big-endian)
		for (int i = 0; i < 8; ++i) {
			bytes[i] = static_cast<char>((timeValue >> (i * 8)) & 0xFF);
		}

		return bytes;
	}
	void cStyleWrite(const char* filename, size_t pos, const void* data, size_t size) 
	{
		FILE* file = fopen(filename, "r+b"); // Read/write binary
		if (!file) {
			file = fopen(filename, "w+b"); // Create if doesn't exist
			if (!file) {
				perror("Failed to open file");
				return;
			}
		}

		fseek(file, pos, SEEK_SET);
		fwrite(data, 1, size, file);
		fclose(file);
	}
	bool DecodeCODUint32(const uint8_t* bytes, uint32_t* output)
	{
		try
		{
			// 1. Read as little-endian 32-bit integer
			uint32_t raw = (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];

			// 2. Apply COD's scaling factor (2048)
			*output = raw / 2048;  // Exact integer division
			return true;
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Error decoding COD uint32: %s", e.what());
			*output = 0; // Set output to 0 in case of error
			return false;
		}
	}
	bool DecodeCODUint64(const uint8_t* bytes, uint64_t* output)
	{
		try
		{
			// 1. Read as little-endian 64-bit integer
			uint64_t raw = ((uint64_t)bytes[7] << 56) |  // Most significant byte
							((uint64_t)bytes[6] << 48) |
							((uint64_t)bytes[5] << 40) |
							((uint64_t)bytes[4] << 32) |
							((uint64_t)bytes[3] << 24) |
							((uint64_t)bytes[2] << 16) |
							((uint64_t)bytes[1] << 8) |
							(uint64_t)bytes[0];         // Least significant byte

			// 2. Apply COD's scaling factor (2048)
			*output = raw / (uint64_t)2048;  // Exact integer division
			return true;
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Error decoding COD uint64: %s", e.what());
			*output = 0; // Set output to 0 in case of error
			return false;
		}
	}
#pragma endregion
	bool T6SDK::DemoHandler::ReadMapName(vector<char> tagsFileData, std::string& mapName, std::string& friendlyName, std::string& uiSelectImage, bool supressConsoleLog)
	{
		char mapByte = 0x00;
		vector<char> tagsData = tagsFileData;
		mapByte = tagsData[0x21];
		switch (T6SDK::CrossVersion::GetGameVersion())
		{
		case T6SDK::CrossVersion::GameVersion::V43:
		case T6SDK::CrossVersion::GameVersion::MP:
		{
			try
			{
				mapName = T6SDK::DemoHandler::MpMaps[(int)mapByte].map;
				friendlyName = T6SDK::DemoHandler::MpMaps[(int)mapByte].friendlyName;
				uiSelectImage = T6SDK::DemoHandler::MpMaps[(int)mapByte].menuSelectImage;
				if(!supressConsoleLog)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo map name: %s -> %s", mapName.c_str(), friendlyName.c_str());
				return true;
			}
			catch (const std::out_of_range& e)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Map name out of range: %s", e.what());
				return false;
			}
		}
		case T6SDK::CrossVersion::GameVersion::V41:
		case T6SDK::CrossVersion::GameVersion::ZM:
			return false;
		default:
			return false;
		}
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo map name!");
		return false;
	}
	bool T6SDK::DemoHandler::ReadDemoGameMode(vector<char> tagsFileData, std::string& gameMode, std::string& friendlyName, bool supressConsoleLog)
	{
		char modeByte = 0x00;
		vector<char> tagsData = tagsFileData;
		modeByte = tagsData[0x33];
		switch (T6SDK::CrossVersion::GetGameVersion())
		{
		case T6SDK::CrossVersion::GameVersion::V43:
		case T6SDK::CrossVersion::GameVersion::MP:
		{
			try
			{
				gameMode = T6SDK::DemoHandler::MpGameModes.find((T6SDK::MP_DemoGameMode)modeByte)->second.mode;
				friendlyName = T6SDK::DemoHandler::MpGameModes.find((T6SDK::MP_DemoGameMode)modeByte)->second.friendlyName;
				if (!supressConsoleLog)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo game mode: %s -> %s", gameMode.c_str(), friendlyName.c_str());
				return true;
			}
			catch (const std::out_of_range& e)
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Game mode out of range: %s", e.what());
				return false;
			}
		}
		case T6SDK::CrossVersion::GameVersion::V41:
		case T6SDK::CrossVersion::GameVersion::ZM:
			return false;
		default:
			return false;
		}
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo game mode!");
		return false;
	}
	bool T6SDK::DemoHandler::DemoTagsHasMetadata(vector<char> tagsFileData, std::string& customMetaData, bool supressConsoleLog)
	{
		try
		{
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "1) Getting metadata footer subarray!");
			std::vector<char> subarray(tagsFileData.end() - 0x12, tagsFileData.end()); //0x12 = 18 in dec
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "2) Got metadata footer subarray!");
			vector<char> defaultTagsFooter = { 0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Comparing metadata footers!");
			if (subarray == defaultTagsFooter)
			{
				if (!supressConsoleLog)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo tags file has no metadata!");
				return false;
			}
			else
			{
				if (!supressConsoleLog)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEMOHANDLER", "Demo tags file has metadata!");
				//Reading metadata length
				std::vector<unsigned char> subarray2(tagsFileData.end() - 12, tagsFileData.end() - 8);
				int customMetaDataSize = bytesToInt(subarray2);
				//Reading actual metadata text
				std::vector<char> MedataDataBytes(tagsFileData.end() - customMetaDataSize, tagsFileData.end() - 12);
				std::string outPut{};
				for (int i = 0; i < MedataDataBytes.size(); i++)
				{
					if (MedataDataBytes[i] != 0x00)
					{
						//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "MTDATA BYTES", "0x%X", MedataDataBytes[i]);
						outPut += MedataDataBytes[i];
					}
				}
				customMetaData = outPut;
				return true;
			}
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo metadata: %s", e.what());
			return false;
		}
	}
	bool T6SDK::DemoHandler::ReadDemoAuthor(vector<char> thumbnailFileData, std::string& author, bool supressConsoleLog)
	{
		std::string authorString;
		std::vector<char> subarray(thumbnailFileData.begin()+0x30, thumbnailFileData.end());
		if (DecodeString(subarray, authorString))
		{
			author = authorString.c_str();
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo author: %s", author.c_str());
			return true;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo author!");
			return false;
		}
	}
	bool T6SDK::DemoHandler::ReadDemoName(vector<char> thumbnailFileData, std::string& demoName, bool supressConsoleLog)
	{
		std::string demonameString;
		std::vector<char> subarray(thumbnailFileData.begin() + 0x60, thumbnailFileData.end());
		if (DecodeString(subarray, demonameString))
		{
			demoName = demonameString.c_str();
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo name: %s", demoName.c_str());
			return true;
		}
		else
		{
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo name!");
			return false;
		}
	}
	bool T6SDK::DemoHandler::ReadDemoDuration(vector<char> thumbnailFileData, uint32_t* duration, bool supressConsoleLog)
	{
		std::vector<char> subarray(thumbnailFileData.begin() + 0xDF, thumbnailFileData.begin() + 0xDF+0x04);
		if (DecodeCODUint32((uint8_t*)subarray.data(), duration))
		{
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo duration: %i -> %02i:%02i", *duration, *duration / 60000, *duration % 60000 / 1000);
			return true;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo duration!");
			return false;
		}
	}
	bool T6SDK::DemoHandler::ReadDemoCreateDate(std::string path, vector<char> thumbnailFileData, int* createDate, bool supressConsoleLog)
	{
		std::vector<char> subarray(thumbnailFileData.begin() + 0xE3, thumbnailFileData.begin() + 0xE3 + 0x08);
		if (DecodeCODUint64((uint8_t*)subarray.data(), (uint64_t*)createDate))
		{
			if (*createDate == 0)
			{
				if (!supressConsoleLog)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Demo create date is 0! Trying to get date from somewhere else...");
				auto ftime = std::filesystem::last_write_time(path);
				// Convert to system_clock time_point
				auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
				// Convert to time_t and format
				std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
				if (tt != -1)
				{
					*createDate = static_cast<int>(tt);
					if (!supressConsoleLog)
						T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Got the date. Writing it to the file...");
					uint64_t encodedTime = (uint64_t)*createDate * (uint64_t)2048;
					std::ofstream file;
					file.open(path, std::ios::binary | std::ios::in | std::ios::out);
					if (file.is_open())
					{
						file.seekp(0xE3, std::ios_base::beg);
						file.write(reinterpret_cast<const char*>(&encodedTime), sizeof(encodedTime));
						file.close();
					}
					if (!supressConsoleLog)
						T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo create date: %i -> %s", *createDate, T6SDK::InternalFunctions::FormatUnixTime(*createDate).c_str());
					return true;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo create date!");
					return false;
				}
			}
			if (!supressConsoleLog)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo create date: %i -> %s", *createDate, T6SDK::InternalFunctions::FormatUnixTime(*createDate).c_str());
			return true;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo create date!");
			return false;
		}
	}

	T6SDK::DemoBriefData T6SDK::DemoHandler::GetDemoBriefData(const char* demoPath)
	{
		bool suppressLogs = true;
		T6SDK::DemoBriefData demoData{};

		//Setting demo path
		demoData.DemoPath = demoPath;

		//Getting map name
		std::string mapName{};
		std::string mapFriendlyName{};
		std::string mapUiSelect{};
		vector<char> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		if (T6SDK::DemoHandler::ReadMapName(tagsData, mapName, mapFriendlyName, mapUiSelect, suppressLogs))
		{
			demoData.Map = mapName.c_str();
			demoData.MapUiSelect = mapUiSelect.c_str();
			demoData.MapFriendlyName = mapFriendlyName.c_str();
		}
		else
		{
			demoData.Map = "mp_raid";
			demoData.MapUiSelect = "^1Unknown";
			demoData.MapFriendlyName = "^1Unknown";
		}
		//Getting game mode
		std::string gameMode{};
		std::string gameModeFriendlyName{};
		if (T6SDK::DemoHandler::ReadDemoGameMode(tagsData, gameMode, gameModeFriendlyName, suppressLogs))
		{
			demoData.GameMode = gameModeFriendlyName.c_str();
		}
		else
		{
			demoData.GameMode = "^1Unknown";
		}
		//Getting metadata info
		std::string customMetaData{};
		if (T6SDK::DemoHandler::DemoTagsHasMetadata(tagsData, customMetaData, suppressLogs))
		{
			demoData.HasMetadata = true;
			demoData.Metadata = customMetaData;
		}
		else
		{
			demoData.HasMetadata = false;
		}
		//Getting data from thumbnail
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
		//Getting author info
		std::string authorString{};
		if (T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData, authorString, suppressLogs))
		{
			demoData.Author = authorString.c_str();
		}
		else
		{
			demoData.Author = "^1Unknown";
		}
		//Getting demo name
		std::string demoNameString{};
		if (T6SDK::DemoHandler::ReadDemoName(thumbnailData, demoNameString, suppressLogs))
		{
			demoData.DemoName = demoNameString.c_str();
		}
		else
		{
			demoData.DemoName = "^1Unknown";
		}
		//Getting duration info
		uint32_t duration{};
		if (T6SDK::DemoHandler::ReadDemoDuration(thumbnailData, &duration, suppressLogs))
		{
			demoData.Duration = duration;
		}
		else
		{
			demoData.Duration = 0;
		}
		//Getting create date info
		int createDate{};
		if (T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData, &createDate, suppressLogs))
		{
			demoData.CreateDate = createDate;
		}
		else
		{
			demoData.CreateDate = 0;
		}
		
		
		return demoData;
	}

	bool T6SDK::DemoHandler::TryGetDemoBriefData(const char* demoPath, T6SDK::DemoBriefData* demoDataOut)
	{
		try
		{
			bool suppressLogs = false;
			//Setting demo path
			demoDataOut->DemoPath = demoPath;

			//Getting map name
			std::string mapName{};
			std::string mapFriendlyName{};
			std::string mapUiSelect{};
			vector<char> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
			if (T6SDK::DemoHandler::ReadMapName(tagsData, mapName, mapFriendlyName, mapUiSelect, suppressLogs))
			{
				demoDataOut->Map = mapName.c_str();
				demoDataOut->MapUiSelect = mapUiSelect.c_str();
				demoDataOut->MapFriendlyName = mapFriendlyName.c_str();
			}
			else
			{
				demoDataOut->Map = "mp_raid";
				demoDataOut->MapUiSelect = "^1Unknown";
				demoDataOut->MapFriendlyName = "^1Unknown";
			}
			//Getting game mode
			std::string gameMode{};
			std::string gameModeFriendlyName{};
			if (T6SDK::DemoHandler::ReadDemoGameMode(tagsData, gameMode, gameModeFriendlyName, suppressLogs))
			{
				demoDataOut->GameMode = gameModeFriendlyName.c_str();
			}
			else
			{
				demoDataOut->GameMode = "^1Unknown";
			}
			//Getting metadata info
			std::string customMetaData{};
			if (T6SDK::DemoHandler::DemoTagsHasMetadata(tagsData, customMetaData, suppressLogs))
			{
				demoDataOut->HasMetadata = true;
				demoDataOut->Metadata = customMetaData;
			}
			//Getting data from thumbnail
			std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
			vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			//Getting author info
			std::string authorString{};
			if (T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData, authorString, suppressLogs))
			{
				demoDataOut->Author = authorString.c_str();
			}
			else
			{
				demoDataOut->Author = "^1Unknown";
			}
			//Getting demo name
			std::string demoNameString{};
			if (T6SDK::DemoHandler::ReadDemoName(thumbnailData, demoNameString, suppressLogs))
			{
				demoDataOut->DemoName = demoNameString.c_str();
			}
			else
			{
				demoDataOut->DemoName = "^1Unknown";
			}
			//Getting duration info
			uint32_t duration{};
			if (T6SDK::DemoHandler::ReadDemoDuration(thumbnailData, &duration, suppressLogs))
			{
				demoDataOut->Duration = duration;
			}
			else
			{
				demoDataOut->Duration = 0;
			}
			//Getting create date info
			int createDate{};
			if (T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData, &createDate, suppressLogs))
			{
				demoDataOut->CreateDate = createDate;
			}
			else
			{
				demoDataOut->CreateDate = 0;
			}

			
			return true;
		}
		catch (std::exception e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Error getting demo brief data: %s", e.what());
			return false;
		}
		return false;
	}

	bool T6SDK::DemoHandler::LoadDemoFromBriefData(T6SDK::DemoBriefData& briefData)
	{
		std::string cmd = std::string("ui_mapname ") + briefData.Map;
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");
		vector<char> demoData = T6SDK::InternalFunctions::readBytesSimple(briefData.DemoPath);
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data read!");
		if (T6SDK::DemoHandler::allocatedMemory)
		{
			free(allocatedMemory);
		}
		allocatedMemory = malloc(demoData.size());
		T6SDK::Memory::MemoryCopySafe(allocatedMemory, demoData.data(), demoData.size());

		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data size: %i.", demoData.size());
		T6SDK::Addresses::DemoAddress1.Value() = (int)allocatedMemory;
		T6SDK::Addresses::DemoAddress2.Value() = (int)allocatedMemory;
		*(int*)(T6SDK::Addresses::DemoAddress1.EndPointerAddress() + 0x04) = demoData.size();
		*(int*)(T6SDK::Addresses::DemoAddress2.EndPointerAddress() + 0x04) = demoData.size();
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo address set: 0x%X", (int)allocatedMemory);

		//Loading thumbnail
		std::string thumbnailPath = std::string(briefData.DemoPath) + ".thumbnail";
		if (std::filesystem::exists(thumbnailPath))
		{
			vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			vector<char>().swap(thumbnailData);
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist!");
			return false;
		}

		//TODO: add summary

		//Bypass errors
		T6SDK::Addresses::DemoLoadPatch.Value() = (BYTE)0xEB;
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo load patch applied!");
		//Start demo
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Attempting to start demo!");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		return true;
	}
	bool T6SDK::DemoHandler::LoadDemoFromFile(const char* demoPath)
	{
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "DEMOHANDLER", "Demo file loaded!");
		vector<char> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		std::string mapName{};
		std::string mapFriendlyName{};
		std::string mapUiSelect{};
		if (!T6SDK::DemoHandler::ReadMapName(tagsData, mapName, mapFriendlyName, mapUiSelect, false))
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Could not read demo map name!");
		else
			mapName = "mp_raid";
		std::string cmd = "ui_mapname " + mapName;
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");
		//Loading demo data

		vector<char> demoData = T6SDK::InternalFunctions::readBytesSimple(demoPath);
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data read!");
		if (T6SDK::DemoHandler::allocatedMemory)
		{
			free(allocatedMemory);
		}
		allocatedMemory = malloc(demoData.size());
		T6SDK::Memory::MemoryCopySafe(allocatedMemory, demoData.data(), demoData.size());

		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data size: %i.", demoData.size());
		T6SDK::Addresses::DemoAddress1.Value() = (int)allocatedMemory;
		T6SDK::Addresses::DemoAddress2.Value() = (int)allocatedMemory;
		*(int*)(T6SDK::Addresses::DemoAddress1.EndPointerAddress() + 0x04) = demoData.size();
		*(int*)(T6SDK::Addresses::DemoAddress2.EndPointerAddress() + 0x04) = demoData.size();
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo address set: 0x%X", (int)allocatedMemory);
		//Loading thumbnail
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail path: %s", thumbnailPath.c_str());
		if (std::filesystem::exists(thumbnailPath))
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail file exists!");
			vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Thumbnail size: %i", thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			std::string authorString{};
			std::string demoNameString{};
			uint32_t duration{};
			int createDate{};
			T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData, authorString, false);
			T6SDK::DemoHandler::ReadDemoName(thumbnailData, demoNameString, false);
			T6SDK::DemoHandler::ReadDemoDuration(thumbnailData, &duration, false);
			T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData, &createDate, false);
			//Getting metadata info
			std::string customMetaData{};
			if(T6SDK::DemoHandler::DemoTagsHasMetadata(tagsData, customMetaData, false))
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Metadata: %s", customMetaData.c_str());
			vector<char>().swap(thumbnailData);
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist!");
			return false;
		}

		//TODO: add summary

		//Bypass errors
		T6SDK::Addresses::DemoLoadPatch.Value() = (BYTE)0xEB;
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo load patch applied!");
		//Start demo
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Attempting to start demo!");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		vector<char>().swap(tagsData);

		return true;
	}
	bool T6SDK::DemoHandler::LoadDemoFromFile(const char* demoPath, bool* hasMetadata, std::string& metadata)
	{
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "DEMOHANDLER", "Demo file loaded!");
		vector<char> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		std::string mapName{};
		std::string mapFriendlyName{};
		std::string mapUiSelect{};
		if (!T6SDK::DemoHandler::ReadMapName(tagsData, mapName, mapFriendlyName, mapUiSelect, false))
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Could not read demo map name!");
		else
			mapName = "mp_raid";
		std::string cmd = "ui_mapname " + mapName;
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");
		//Loading demo data

		vector<char> demoData = T6SDK::InternalFunctions::readBytesSimple(demoPath);
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data read!");
		if (T6SDK::DemoHandler::allocatedMemory)
		{
			free(allocatedMemory);
		}
		allocatedMemory = malloc(demoData.size());
		T6SDK::Memory::MemoryCopySafe(allocatedMemory, demoData.data(), demoData.size());

		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data size: %i.", demoData.size());
		T6SDK::Addresses::DemoAddress1.Value() = (int)allocatedMemory;
		T6SDK::Addresses::DemoAddress2.Value() = (int)allocatedMemory;
		*(int*)(T6SDK::Addresses::DemoAddress1.EndPointerAddress() + 0x04) = demoData.size();
		*(int*)(T6SDK::Addresses::DemoAddress2.EndPointerAddress() + 0x04) = demoData.size();
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo address set: 0x%X", (int)allocatedMemory);
		//Loading thumbnail
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail path: %s", thumbnailPath.c_str());
		if (std::filesystem::exists(thumbnailPath))
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail file exists!");
			vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Thumbnail size: %i", thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			std::string authorString{};
			std::string demoNameString{};
			uint32_t duration{};
			int createDate{};
			T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData, authorString, false);
			T6SDK::DemoHandler::ReadDemoName(thumbnailData, demoNameString, false);
			T6SDK::DemoHandler::ReadDemoDuration(thumbnailData, &duration, false);
			T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData, &createDate, false);
			//Getting metadata info
			std::string customMetaData{};
			if (T6SDK::DemoHandler::DemoTagsHasMetadata(tagsData, customMetaData, false))
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Metadata: %s", customMetaData.c_str());
				*hasMetadata = true;
				metadata = customMetaData;
			}
			vector<char>().swap(thumbnailData);
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist!");
			return false;
		}

		//TODO: add summary

		//Bypass errors
		T6SDK::Addresses::DemoLoadPatch.Value() = (BYTE)0xEB;
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo load patch applied!");
		//Start demo
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Attempting to start demo!");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		vector<char>().swap(tagsData);

		return true;
	}

	bool T6SDK::DemoHandler::LoadDemoFromFile(const char* demoPath, T6SDK::DemoBriefData* demoBriefData)
	{
		demoBriefData->DemoPath = std::string(demoPath);
		std::string filename = T6SDK::InternalFunctions::getFilenameFromPath(std::string(demoPath));
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "filename -> %s", filename.c_str());
		//T6SDK::Addresses::DemoName = filename.c_str();
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "DEMOHANDLER", "Demo file loaded!");
		vector<char> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		std::string mapName{};
		std::string mapFriendlyName{};
		std::string mapUiSelect{};
		if (!T6SDK::DemoHandler::ReadMapName(tagsData, mapName, mapFriendlyName, mapUiSelect, false))
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Could not read demo map name!");
		else
			mapName = "mp_raid";
		std::string cmd = "ui_mapname " + mapName;
		demoBriefData->Map = mapName;
		demoBriefData->MapFriendlyName = mapFriendlyName;
		demoBriefData->MapUiSelect = mapUiSelect;
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");

		//Getting metadata info
		std::string customMetaData{};
		if (T6SDK::DemoHandler::DemoTagsHasMetadata(tagsData, customMetaData, false))
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Metadata: %s", customMetaData.c_str());
			demoBriefData->HasMetadata = true;
			demoBriefData->Metadata = customMetaData;
		}

		//Loading demo data
		vector<char> demoData = T6SDK::InternalFunctions::readBytesSimple(demoPath);
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data read!");
		if (T6SDK::DemoHandler::allocatedMemory)
		{
			free(allocatedMemory);
		}
		allocatedMemory = malloc(demoData.size());
		T6SDK::Memory::MemoryCopySafe(allocatedMemory, demoData.data(), demoData.size());

		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data size: %i.", demoData.size());
		T6SDK::Addresses::DemoAddress1.Value() = (int)allocatedMemory;
		T6SDK::Addresses::DemoAddress2.Value() = (int)allocatedMemory;
		*(int*)(T6SDK::Addresses::DemoAddress1.EndPointerAddress() + 0x04) = demoData.size();
		*(int*)(T6SDK::Addresses::DemoAddress2.EndPointerAddress() + 0x04) = demoData.size();
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo address set: 0x%X", (int)allocatedMemory);
		//Loading thumbnail
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail path: %s", thumbnailPath.c_str());
		if (std::filesystem::exists(thumbnailPath))
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail file exists!");
			vector<char> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Thumbnail size: %i", thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			std::string authorString{};
			std::string demoNameString{};
			uint32_t duration{};
			int createDate{};
			T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData, authorString, false);
			T6SDK::DemoHandler::ReadDemoName(thumbnailData, demoNameString, false);
			T6SDK::DemoHandler::ReadDemoDuration(thumbnailData, &duration, false);
			T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData, &createDate, false);

			demoBriefData->Author = authorString;
			demoBriefData->DemoName = demoNameString;
			demoBriefData->Duration = duration;
			demoBriefData->CreateDate = createDate;
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "demoBriefData almost set!");
			vector<char>().swap(thumbnailData);
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist!");
			return false;
		}

		//TODO: add summary

		//Bypass errors
		T6SDK::Addresses::DemoLoadPatch.Value() = (BYTE)0xEB;
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo load patch applied!");
		//Start demo
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Attempting to start demo!");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		vector<char>().swap(tagsData);
		demoBriefData->Inited = true;
		//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Brief data inited! Author: %s\nMap: %s\nDuration: %i\nCreateDate: %i\nPath: %s\n", demoBriefData->Author.c_str(), demoBriefData->MapFriendlyName.c_str(), demoBriefData->Duration, demoBriefData->CreateDate, demoPath);
		return true;
	}
	
	bool T6SDK::DemoHandler::WriteTagsMetadata(const char* demoPath, std::string& metadata, uint64_t magicNumber)
	{
		std::ofstream file;
		try
		{
			std::string fullPath = std::string(demoPath) + ".tags";

			// Open file in binary append mode
			file.open(fullPath, std::ios::binary | std::ios::app);
			if (!file.is_open())
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DEMOHANDLER", "Failed to open file for writing metadata: %s", fullPath.c_str());
				return false;
			}
			else
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "DEMOHANDLER", "Opened file for writing metadata: %s", fullPath.c_str());
			// Prepare the length prefix (4 bytes)
			uint32_t length = static_cast<uint32_t>(metadata.size())+12;

			// Write data in order: text, length (4 bytes), custom number (8 bytes)
			file.write(metadata.data(), metadata.size());
			file.write(reinterpret_cast<const char*>(&length), sizeof(length));
			file.write(reinterpret_cast<const char*>(&magicNumber), sizeof(magicNumber));

			// Verify all writes succeeded
			if (!file.good())
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DEMOHANDLER", "Failed during file write operation");
				file.close();
				return false;
			}

			file.close();
			return true;
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DEMOHANDLER", "Exception while writing metadata: %s",e.what());
			if (file.is_open())
				file.close();
			return false;
		}
		catch (...)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, true, "DEMOHANDLER", "Unknown exception while writing metadata");
			if (file.is_open())
				file.close();
			return false;
		}
	}
}