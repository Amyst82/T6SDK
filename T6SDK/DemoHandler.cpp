#include "pch.h"
#include "StdInclude.h"

namespace T6SDK
{
	bool suppressLogs = true;
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
	bool DecodeString(const std::vector<uint8_t >& encoded, int startindex, std::string& decodedString) //ASCII decoder (BO2 has ascii bytes multiplied by 2 in %s.tags file somehow)
	{
		std::string result{};
		for (int i = startindex; i < encoded.size(); i++)
		{
			if (encoded[i] == 0x00) //Null terminator
				break;
			if (encoded[i] == 0xFF) //End of string
				break;
			if(encoded[i] % 2 ==  0) //If it can be divided by two
				result += encoded[i] / 2;
			else if(encoded[i] % 2 > 0)
				result += (encoded[i] - 1) / 2; //If it can't be divided by two, subtract 1 and divide by 2
			else
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Unreadable byte: 0x%X", encoded[i]);
				decodedString = "";
				return false;
			}
		}
		if (result.empty())
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Decoded string is empty!");
			return false;
		}
		else
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "T6SDK", "Decoded string: %s", result.c_str());
		}
		decodedString = result;
		return true;
	}
	bool EncodeString(const std::string& inputString, std::vector<uint8_t>& encodedString)
	{
		encodedString.clear();
		for (char c : inputString)
		{
			encodedString.push_back(c * 2);
		}
		encodedString.push_back(0x00); //Null terminator
		return true;
	}
	std::vector<uint8_t> timeToBytes(time_t timestamp) 
	{
		std::vector<uint8_t> bytes(8);

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

	#pragma region Map stuff
	std::string T6SDK::DemoHandler::ReadMapName(vector<uint8_t>& tagsFileData)
	{
		char mapByte = 0x00;
		vector<uint8_t> tagsData = tagsFileData;
		mapByte = tagsData[0x01] == 0x14 ? tagsData[0x45] : tagsData[0x21];
		try
		{
			std::string mapName{};
			if(T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::MP|| T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V43)
				mapName = T6SDK::DemoHandler::MpMaps[(int)mapByte].map;
			else if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V41 || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::ZM)
				mapName = T6SDK::DemoHandler::ZmMaps[(int)mapByte].map;
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo map name: %s ", mapName.c_str());
			return mapName;
		}
		catch (const std::out_of_range& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Unable to read demo map name: %s", e.what());
			return std::string("^1Unknown^7");
		}
	}
	std::string T6SDK::DemoHandler::ReadMapFriendlyName(vector<uint8_t>& tagsFileData)
	{
		char mapByte = 0x00;
		vector<uint8_t> tagsData = tagsFileData;
		mapByte = tagsData[0x01] == 0x14 ? tagsData[0x45] : tagsData[0x21];
		try
		{
			std::string mapName{};
			if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::MP || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V43)
				mapName = T6SDK::DemoHandler::MpMaps[(int)mapByte].friendlyName;
			else if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V41 || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::ZM)
				mapName = T6SDK::DemoHandler::ZmMaps[(int)mapByte].friendlyName;
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo map friendly name: %s ", mapName.c_str());
			return mapName;
		}
		catch (const std::out_of_range& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Unable to read demo map friendly name: %s", e.what());
			return std::string("^1Unknown^7");
		}
	}
	std::string T6SDK::DemoHandler::ReadMapMenuSelectMaterial(vector<uint8_t>& tagsFileData)
	{
		char mapByte = 0x00;
		vector<uint8_t> tagsData = tagsFileData;
		mapByte = tagsData[0x01] == 0x14 ? tagsData[0x45] : tagsData[0x21];
		try
		{
			std::string mapName{};
			if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::MP || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V43)
				mapName = T6SDK::DemoHandler::MpMaps[(int)mapByte].menuSelectImage;
			else if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V41 || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::ZM)
				mapName = T6SDK::DemoHandler::ZmMaps[(int)mapByte].menuSelectImage;
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo map friendly name: %s ", mapName.c_str());
			return mapName;
		}
		catch (const std::out_of_range& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Unable to read demo map friendly name: %s", e.what());
			return std::string("^1Unknown^7");
		}
	}
#pragma endregion
	#pragma region GameMode
	std::string T6SDK::DemoHandler::ReadDemoGameMode(vector<uint8_t>& tagsFileData)
	{
		char modeByte = 0x00;
		vector<uint8_t> tagsData = tagsFileData;
		modeByte = tagsData[0x01] == 0x14 ? tagsData[0x57] : tagsData[0x33]; //if its from redacted public match
		std::string gameMode{}, friendlyName{};
		try
		{
			if(T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::MP || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V43)
			{
				gameMode = T6SDK::DemoHandler::MpGameModes[(int)modeByte - 1].mode;
				friendlyName = T6SDK::DemoHandler::MpGameModes[(int)modeByte - 1].friendlyName;
			}
			else if (T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::V41 || T6SDK::CrossVersion::GAMEVERSION == T6SDK::CrossVersion::GameVersion::ZM)
			{
				gameMode = T6SDK::DemoHandler::ZmGameModes[(int)modeByte - 1].mode;
				friendlyName = T6SDK::DemoHandler::ZmGameModes[(int)modeByte - 1].friendlyName;
				
			}
			return friendlyName;
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo game mode: %s -> %s", gameMode.c_str(), friendlyName.c_str());
		}
		catch (const std::out_of_range& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Game mode out of range: %s", e.what());
			return std::string("^1Unknown^7");
		}
	}
#pragma endregion
	#pragma region Duration
	uint32_t T6SDK::DemoHandler::ReadDemoDuration(vector<uint8_t>& thumbnailFileData)
	{
		std::vector<uint8_t> subarray(thumbnailFileData.begin() + 0xDF, thumbnailFileData.begin() + 0xDF + 0x04);
		uint32_t duration = 0;
		if (DecodeCODUint32((uint8_t*)subarray.data(), &duration))
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo duration: %i -> %02i:%02i", duration, duration / 60000, duration % 60000 / 1000);
			return duration;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo duration!");
			return 0;
		}
	}
#pragma endregion
	#pragma region Metadata
	static int GetMetadataLength(vector<uint8_t>& tagsFileData)
	{
		try
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "1) Getting metadata footer subarray!");
			std::vector<uint8_t> subarray(tagsFileData.end() - 0x12, tagsFileData.end()); //0x12 = 18 in dec
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "2) Got metadata footer subarray!");
			vector<uint8_t> defaultTagsFooter = { 0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			vector<uint8_t> defaultTagsFooter2 = { 0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Comparing metadata footers!");
			if (subarray == defaultTagsFooter || subarray == defaultTagsFooter2)
			{
				if (!suppressLogs)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo tags file has no metadata!");
				return 0;
			}
			else
			{
				if (!suppressLogs)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEMOHANDLER", "Demo tags file has metadata!");
				//Reading metadata length
				std::vector<unsigned char> subarray2(tagsFileData.end() - 12, tagsFileData.end() - 8);
				int customMetaDataSize = bytesToInt(subarray2);
				return customMetaDataSize;
			}
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo metadata: %s", e.what());
			return 0;
		}
	}
	std::string T6SDK::DemoHandler::ReadDemoMetadata(vector<uint8_t>& tagsFileData)
	{
		try
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "1) Getting metadata footer subarray!");
			std::vector<uint8_t> subarray(tagsFileData.end() - 0x12, tagsFileData.end()); //0x12 = 18 in dec
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "2) Got metadata footer subarray!");
			vector<uint8_t> defaultTagsFooter = { 0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			vector<uint8_t> defaultTagsFooter2 = { 0x0A, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Comparing metadata footers!");
			if (subarray == defaultTagsFooter || subarray == defaultTagsFooter2)
			{
				if (!suppressLogs)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo tags file has no metadata!");
				return std::string("");
			}
			else
			{
				if (!suppressLogs)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEMOHANDLER", "Demo tags file has metadata!");
				//Reading metadata length
				std::vector<unsigned char> subarray2(tagsFileData.end() - 12, tagsFileData.end() - 8);
				int customMetaDataSize = bytesToInt(subarray2);
				//Reading actual metadata text
				std::vector<uint8_t> MedataDataBytes(tagsFileData.end() - customMetaDataSize, tagsFileData.end() - 12);
				std::string outPut{};
				for (int i = 0; i < MedataDataBytes.size(); i++)
				{
					if (MedataDataBytes[i] != 0x00)
					{
						//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, true, "MTDATA BYTES", "0x%X", MedataDataBytes[i]);
						outPut += MedataDataBytes[i];
					}
				}
				return outPut;
			}
		}
		catch (const std::exception& e)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo metadata: %s", e.what());
			return std::string("");
		}
	}
	#pragma endregion
	#pragma region Author
	std::string T6SDK::DemoHandler::ReadDemoAuthor(vector<uint8_t>& thumbnailFileData)
	{
		std::string authorString;
		if (DecodeString(thumbnailFileData, 0x30, authorString))
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo author: %s", authorString.c_str());
			return authorString;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo author!");
			return std::string("^1Unknown^7");
		}
	}
	#pragma endregion
	#pragma region Description
	std::string T6SDK::DemoHandler::ReadDemoDescription(vector<uint8_t >& thumbnailFileData)
	{
		// Check if there's enough data for 0xA0 offset
		if (thumbnailFileData.size() < 0xA0)
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Thumbnail data too small for demo description!");
			return std::string("^9Description not provided^7");
		}

		// Verify the subarray won't cause overflow
		size_t remainingSize = thumbnailFileData.size() - 0xA0;
		if (remainingSize > 0x5F)
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Suspiciously large description data");
		}

		std::string demodescriptionString{};
		if (DecodeString(thumbnailFileData, 0xA0, demodescriptionString))
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo description: %s", demodescriptionString.c_str());
			return demodescriptionString;
		}
		else
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo description!");
			return std::string("^9Description not provided^7");
		}
	}
	#pragma endregion
	#pragma region DemoName
	std::string T6SDK::DemoHandler::ReadDemoName(vector<uint8_t >& thumbnailFileData)
	{
		std::string demonameString;
		if (DecodeString(thumbnailFileData, 0x60, demonameString))
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo name: %s", demonameString.c_str());
			return demonameString;
		}
		else
		{
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo name!");
			return std::string("^1Unknown^7");
		}
	}
	bool T6SDK::DemoHandler::SetDemoName(std::string& demoPath, std::string& name)
	{
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		if (std::filesystem::exists(thumbnailPath))
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnail file exists! Setting it's name...");
			vector<uint8_t> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			std::ofstream file;
			file.open(thumbnailPath, std::ios::binary | std::ios::in | std::ios::out);
			if (file.is_open())
			{
				file.seekp(0x60, std::ios_base::beg);
				vector<uint8_t> encodedString{};
				if (EncodeString(name, encodedString))
				{
					file.write(reinterpret_cast<const char*>(encodedString.data()), name.length());
					file.close();
					return true;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not encode demo name!");
					file.close();
					return false;
				}
				return false;
			}
			else
			{
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not open demo thumbnail file!");
				return false;
			}
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist! Couln't set name!");
			return false;
		}
	}
	#pragma endregion
	#pragma region CreateDate
	int T6SDK::DemoHandler::ReadDemoCreateDate(std::string& path, vector<uint8_t>& thumbnailFileData)
	{
		std::vector<uint8_t> subarray(thumbnailFileData.begin() + 0xE3, thumbnailFileData.begin() + 0xE3 + 0x08);
		int createDate = 0;
		if (DecodeCODUint64((uint8_t*)subarray.data(), (uint64_t*)&createDate))
		{
			if (createDate == 0)
			{
				if (!suppressLogs)
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Demo create date is 0! Trying to get date from somewhere else...");
				auto ftime = std::filesystem::last_write_time(path);
				// Convert to system_clock time_point
				auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - std::filesystem::file_time_type::clock::now() + std::chrono::system_clock::now());
				// Convert to time_t and format
				std::time_t tt = std::chrono::system_clock::to_time_t(sctp);
				if (tt != -1)
				{
					createDate = static_cast<int>(tt);
					if (!suppressLogs)
						T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_WARNING, false, "DEMOHANDLER", "Got the date. Writing it to the file...");
					uint64_t encodedTime = (uint64_t)createDate * (uint64_t)2048;
					std::ofstream file;
					file.open(path, std::ios::binary | std::ios::in | std::ios::out);
					if (file.is_open())
					{
						file.seekp(0xE3, std::ios_base::beg);
						file.write(reinterpret_cast<const char*>(&encodedTime), sizeof(encodedTime));
						file.close();
					}
					if (!suppressLogs)
						T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo create date: %i -> %s", createDate, T6SDK::InternalFunctions::FormatUnixTime(createDate).c_str());
					return createDate;
				}
				else
				{
					T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not get demo create date!");
					return 0;
				}
			}
			if (!suppressLogs)
				T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo create date: %i -> %s", createDate, T6SDK::InternalFunctions::FormatUnixTime(createDate).c_str());
			return createDate;
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Could not read demo create date!");
			return 0;
		}
	}
	#pragma endregion

	T6SDK::DemoBriefData T6SDK::DemoHandler::GetDemoBriefData(const char* demoPath)
	{
		if (!suppressLogs)
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Getting demo brief data of %s", demoPath);
		vector<uint8_t> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		std::string thumbnailPath = std::string(demoPath) + ".thumbnail";
		vector<uint8_t> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".thumbnail");
		if (thumbnailData.size() == 0)
		{
			return T6SDK::DemoBriefData();
		}
		std::string path(demoPath);

		int duration = T6SDK::DemoHandler::ReadDemoDuration(thumbnailData);
		int createDate = T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData);
		std::string mapName = T6SDK::DemoHandler::ReadMapName(tagsData);
		std::string mapUiSelect = T6SDK::DemoHandler::ReadMapMenuSelectMaterial(tagsData);
		std::string mapFriendlyName = T6SDK::DemoHandler::ReadMapFriendlyName(tagsData);
		std::string gameModeFriendlyName = T6SDK::DemoHandler::ReadDemoGameMode(tagsData);
		std::string authorString = T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData);
		std::string demoNameString = T6SDK::DemoHandler::ReadDemoName(thumbnailData);
		std::string desc = T6SDK::DemoHandler::ReadDemoDescription(thumbnailData);
		std::string customMetaData = T6SDK::DemoHandler::ReadDemoMetadata(tagsData);
		bool hasMetadata = !customMetaData.empty();
		if(!suppressLogs)
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Got demo brief data");
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_INFO, false, "DEMOHANDLER", "BRIEF:\n%s\n%s\n%s\n%s\n%s\n%i\n%i\n%s\n%s\n%s\n%s\n%s",
				path.c_str(), mapName.c_str(), mapUiSelect.c_str(), mapFriendlyName.c_str(), gameModeFriendlyName.c_str(),
				duration, createDate,
				authorString.c_str(), demoNameString.c_str(), desc.c_str(), hasMetadata ? "METADATA FOUND" : "NO METADATA", customMetaData.c_str());
		}
		return DemoBriefData(path, mapName, mapUiSelect, mapFriendlyName, gameModeFriendlyName, duration, createDate, authorString, demoNameString, desc, hasMetadata, customMetaData);
	}
	bool T6SDK::DemoHandler::TryGetDemoBriefData(const char* demoPath, T6SDK::DemoBriefData* demoDataOut)
	{
		try
		{
			*demoDataOut = GetDemoBriefData(demoPath);
			return true;
		}
		catch (std::exception e)
		{
			return false;
		}
		return false;
	}
	bool T6SDK::DemoHandler::LoadDemoFromBriefData(T6SDK::DemoBriefData& briefData)
	{
		std::string cmd = std::string("ui_mapname ") + briefData.Map;
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");
		vector<uint8_t> demoData = T6SDK::InternalFunctions::readBytesSimple(briefData.DemoPath);
		if (!suppressLogs)
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data read!");
		if (T6SDK::DemoHandler::allocatedMemory)
		{
			free(allocatedMemory);
		}
		allocatedMemory = malloc(demoData.size());
		T6SDK::Memory::MemoryCopySafe(allocatedMemory, demoData.data(), demoData.size());
		if (!suppressLogs)
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo data size: %i.", demoData.size());
		T6SDK::Addresses::DemoAddress1.Value() = (int)allocatedMemory;
		T6SDK::Addresses::DemoAddress2.Value() = (int)allocatedMemory;
		*(int*)(T6SDK::Addresses::DemoAddress1.EndPointerAddress() + 0x04) = demoData.size();
		*(int*)(T6SDK::Addresses::DemoAddress2.EndPointerAddress() + 0x04) = demoData.size();
		if (!suppressLogs)
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo address set: 0x%X", (int)allocatedMemory);

		//Loading thumbnail
		std::string thumbnailPath = std::string(briefData.DemoPath) + ".thumbnail";
		if (std::filesystem::exists(thumbnailPath))
		{
			vector<uint8_t> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			if (T6SDK::Addresses::DemoThumbnailAddress2 != 0)
				T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			vector<uint8_t>().swap(thumbnailData);
		}
		else
		{
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_ERROR, false, "DEMOHANDLER", "Demo thumbnail file does not exist!");
			return false;
		}

		//TODO: add summary

		//Bypass errors
		T6SDK::Addresses::DemoLoadPatch.Value() = (BYTE)0xEB;
		if (!suppressLogs)
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo load patch applied!");
		//Start demo
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Attempting to start demo!");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		T6SDK::Dvars::cbuf_AddText("demo_play demo;");
		return true;
	}
	bool T6SDK::DemoHandler::LoadDemoFromFile(const char* demoPath)
	{
		std::string filename = T6SDK::InternalFunctions::getFilenameFromPath(std::string(demoPath));
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "filename -> %s", filename.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "DEMOHANDLER", "Demo file loaded!");
		vector<uint8_t> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		std::string cmd = "ui_mapname " + T6SDK::DemoHandler::ReadMapName(tagsData);
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");
		//Loading demo data
		vector<uint8_t> demoData = T6SDK::InternalFunctions::readBytesSimple(demoPath);
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
			vector<uint8_t> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Thumbnail size: %i", thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			if (T6SDK::Addresses::DemoThumbnailAddress2 != 0)
				T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "demoBriefData almost set!");
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
	bool T6SDK::DemoHandler::LoadDemoFromFile(const char* demoPath, T6SDK::DemoBriefData* demoBriefData)
	{
		demoBriefData->DemoPath = std::string(demoPath);
		std::string filename = T6SDK::InternalFunctions::getFilenameFromPath(std::string(demoPath));
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "filename -> %s", filename.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_SUCCESS, false, "DEMOHANDLER", "Demo file loaded!");
		vector<uint8_t> tagsData = T6SDK::InternalFunctions::readBytesSimple(std::string(demoPath) + ".tags");
		
		demoBriefData->Map = T6SDK::DemoHandler::ReadMapName(tagsData);
		demoBriefData->MapFriendlyName = T6SDK::DemoHandler::ReadMapFriendlyName(tagsData);
		demoBriefData->MapUiSelect = T6SDK::DemoHandler::ReadMapMenuSelectMaterial(tagsData);
		std::string cmd = "ui_mapname " + T6SDK::DemoHandler::ReadMapName(tagsData);
		T6SDK::Dvars::cbuf_AddText(cmd.c_str());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "ui_mapname command sent!");

		//Getting metadata info
		demoBriefData->Metadata = T6SDK::DemoHandler::ReadDemoMetadata(tagsData);
		demoBriefData->HasMetadata = !demoBriefData->Metadata.empty();

		//Loading demo data
		vector<uint8_t> demoData = T6SDK::InternalFunctions::readBytesSimple(demoPath);
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
			vector<uint8_t> thumbnailData = T6SDK::InternalFunctions::readBytesSimple(thumbnailPath);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Thumbnail size: %i", thumbnailData.size());
			T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress, thumbnailData.data(), thumbnailData.size());
			if (T6SDK::Addresses::DemoThumbnailAddress2 != 0)
				T6SDK::Memory::MemoryCopySafe((void*)T6SDK::Addresses::DemoThumbnailAddress2, thumbnailData.data(), thumbnailData.size());
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "Demo thumbnails set!");

			demoBriefData->Author = T6SDK::DemoHandler::ReadDemoAuthor(thumbnailData);
			demoBriefData->DemoName = T6SDK::DemoHandler::ReadDemoName(thumbnailData);
			demoBriefData->Duration = T6SDK::DemoHandler::ReadDemoDuration(thumbnailData);
			demoBriefData->CreateDate = T6SDK::DemoHandler::ReadDemoCreateDate(thumbnailPath, thumbnailData);
			T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "DEMOHANDLER", "demoBriefData almost set!");
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
		demoBriefData->Inited = true;
		return true;
	}
	bool T6SDK::DemoHandler::WriteTagsMetadata(const char* demoPath, std::string& metadata, uint64_t magicNumber)
	{
		std::ofstream file;
		try
		{
			//Remove old metadata
			std::string fullPath = std::string(demoPath) + ".tags";
			vector<uint8_t> tagsData = T6SDK::InternalFunctions::readBytesSimple(fullPath);
			int oldMetadataSize = GetMetadataLength(tagsData);
			if (oldMetadataSize > 0)
			{
				// Get current file size
				uintmax_t size = std::filesystem::file_size(fullPath);
				if (size <= 5)
				{
					// Handle case where file is too small
					std::filesystem::resize_file(fullPath, 0);
				}
				// Truncate file
				std::filesystem::resize_file(fullPath, size - oldMetadataSize);
			}
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