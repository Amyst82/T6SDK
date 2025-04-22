#pragma once

#include "StdInclude.h"
#include <stdarg.h>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define CONSOLETEXTGRAY 8
#define CONSOLETEXTGREEN 10
#define CONSOLETEXTCYAN 11
#define CONSOLETEXTRED 12
#define CONSOLETEXTMAGENTA 13
#define CONSOLETEXTYELLOW 14
#define CONSOLETEXTWHITE 15

namespace T6SDK
{
	class ConsoleLog
	{
	public:
		enum LogTag
		{
			C_DEBUG,
			C_INFO,
			C_SUCCESS,
			C_WARNING,
			C_ERROR
		};
		static void Initialize();
		static void DeInitialize();
		inline static void EraseLines(int count) {
			if (count > 0) {
				std::cout << "\x1b[2K"; // Delete current line
				// i=1 because we included the first line
				for (int i = 1; i < count; i++) {
					std::cout
						<< "\x1b[1A" // Move cursor up one
						<< "\x1b[2K"; // Delete the entire line
				}
				std::cout << "\r"; // Resume the cursor at beginning of line
			}
		}
		inline static bool EnableVTMode()
		{
			// Set output mode to handle virtual terminal sequences
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			if (hOut == INVALID_HANDLE_VALUE)
			{
				return false;
			}

			DWORD dwMode = 0;
			if (!GetConsoleMode(hOut, &dwMode))
			{
				return false;
			}

			dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			if (!SetConsoleMode(hOut, dwMode))
			{
				return false;
			}
			return true;
		}

		static std::string formatTimestamp(const std::string& format) 
		{
			auto now = std::chrono::system_clock::now();
			auto in_time_t = std::chrono::system_clock::to_time_t(now);

			std::tm tm_buf;
			localtime_s(&tm_buf, &in_time_t); // Use localtime_s on Windows

			std::stringstream ss;
			ss << std::put_time(&tm_buf, format.c_str());
			return ss.str();
		}
		inline static void LogSuccess(const char* text)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTGREEN);
			auto currentTime = std::chrono::system_clock::now(); // get the time
			auto formattedTime = std::chrono::system_clock::to_time_t(currentTime); // convert it to time_t type (loses some precision)
			std::cout << std::ctime(&formattedTime) << " " << text << std::endl; // print it formatted
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void LogError(const char* text)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTRED);
			auto currentTime = std::chrono::system_clock::now(); // get the time
			auto formattedTime = std::chrono::system_clock::to_time_t(currentTime); // convert it to time_t type (loses some precision)
			std::cout << std::ctime(&formattedTime) << " " << text << std::endl; // print it formatted
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void LogTimeStamp(const char* text)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
			auto currentTime = std::chrono::system_clock::now(); // get the time
			auto formattedTime = std::chrono::system_clock::to_time_t(currentTime); // convert it to time_t type (loses some precision)
			std::cout << std::ctime(&formattedTime) << " " << text << std::endl; // print it formatted
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void Log(const char* text)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
			cout << "\r" << text << endl;
		}
		inline static void LogFormatted(const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			cout << "\r" << buffer << endl;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void LogFormatted(WORD colorIndex, const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, colorIndex);
			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			cout << "\r" << buffer << endl;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void LogSuccessFormatted(const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			LogSuccess(buffer);
		}
		inline static void LogErrorFormatted(const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			LogError(buffer);
		}
		inline static void LogSameLine(const char* text)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
			EraseLines(1);
			cout << text << "\r" << flush;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		inline static void LogSameLineFormatted(const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			LogSameLine(buffer);
		}

		inline static void LogTagged(LogTag tag, bool TimeStamp, const char* caller, const char* format, ...)
		{
			if (!T6SDK::MAIN::DEBUG)
				return;
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			std::string tagString = "DEBUG: ";
			TimeStamp = true;
			switch (tag)
			{
				case C_DEBUG:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTGRAY);
					tagString = "DEBUG: ";
					break;
				case C_INFO:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTCYAN);
					tagString = "INFO: ";
					break;
				case C_SUCCESS:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTGREEN);
					tagString = "SUCCESS: ";
					break;
				case C_WARNING:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTYELLOW);
					tagString = "WARNING: ";
					break;
				case C_ERROR:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTRED);
					tagString = "ERROR: ";
					break;
				default:
					SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
					tagString = "DEBUG: ";
					break;
			}

			char buffer[1024];
			va_list args;
			va_start(args, format);
			vsprintf_s(buffer, format, args);
			va_end(args);
			if (TimeStamp)
			{
				//cout << "\r" << "[" << caller << "] " << tagString << buffer << endl;
				cout << "\r" << "[" << formatTimestamp("%a, %d %b %Y %T") << "] " << "[" << caller << "] " << tagString << buffer << endl;
			}
			else
				cout << "\r" << "[" << caller << "] " << tagString << buffer << endl;
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, CONSOLETEXTWHITE);
		}
		
	};
}
