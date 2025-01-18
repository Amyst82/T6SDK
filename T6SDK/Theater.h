#pragma once
#include "StdInclude.h"

#define FREEROAM_DEFAULTSPEED 0.016999f
namespace T6SDK
{
	namespace Theater
	{
		inline static bool GrabFreeCameraAngles = false;
		class CustomCameraMode
		{
		public:
			const char* Name{};
			vector<const char*> FreeCameraModes{};
			int lastFreeCameraMode = 0;
			CustomCameraMode(const char* name)
			{
				this->Name = name;
				this->FreeCameraModes = {name};
			}
			CustomCameraMode(const char* name, vector<const char*> freeCameraModes)
			{
				this->Name = name;
				this->FreeCameraModes = freeCameraModes;
			}
		};
		static bool IsPlaybackInited()
		{
			if (!T6SDK::Addresses::DemoPlayback.IsValid())
				return false;
			if(!T6SDK::Addresses::PlaybackInitedFlag.IsValid())
				return false;
			return T6SDK::Addresses::PlaybackInitedFlag.Value();
		}
		static bool IsInTheater()
		{
			//T6SDK::ConsoleLog::LogFormatted("Com_GameMode_IsMode address: 0x%X", T6SDK::Typedefs::Com_GameMode_IsMode);
			return IsPlaybackInited() && T6SDK::InternalFunctions::Com_GameMode_IsMode(T6SDK::eGameModes::THEATER);
		}
		static void Demo_Error(const char* TitleText, const char* MessageText)
		{
			T6SDK::Typedefs::Demo_Error(0, TitleText, MessageText);
		}
		static void Demo_Back()
		{
			T6SDK::Typedefs::Demo_Back();
		}
		static void Demo_JumpToDollyCamMarkerTime(int markerNum)
		{
			T6SDK::Typedefs::Demo_JumpToDollyCamMarkerTime(0, markerNum);
		}
		static int	GetSelectedMarkerNum()
		{
			if (IsInTheater() == false) return -1;
			return T6SDK::Addresses::DemoPlayback.Value()->HighlightedDollyCamMarker;
		}
		static int	MarkersCount()
		{
			if(IsInTheater() == false) return -1;
			return T6SDK::Addresses::DemoPlayback.Value()->DollyCamMarkerCount;
		}
		static void SetDemoTimescaleCustomStep(bool state, float* step)
		{
			//Set/unset our custom internal demo timescale step 
			T6SDK::Addresses::DemoTimescaleStepBasePointer0.SetValueSafe(state ? (int)step : T6SDK::Addresses::Demo_timescale_step.EndPointerAddress());
			T6SDK::Addresses::DemoTimescaleStepBasePointer1.SetValueSafe(state ? (int)step : T6SDK::Addresses::Demo_timescale_step.EndPointerAddress());
			T6SDK::Addresses::DemoTimescaleStepBasePointer2.SetValueSafe(state ? (int)step : T6SDK::Addresses::Demo_timescale_step.EndPointerAddress());
			T6SDK::Addresses::DemoTimescaleStepBasePointer3.SetValueSafe(state ? (int)step : T6SDK::Addresses::Demo_timescale_step.EndPointerAddress());
			struct DemoTimescaleFormat_s myTScaleFormat = { "%.3fx" };
			struct DemoTimescaleFormat_s defaultTScaleFormat = { "%.1fx" };
			T6SDK::Addresses::DemoTimescaleFormat.SetValueSafe(state ? myTScaleFormat : defaultTScaleFormat);
		}
		static void SetFreeRoamCameraSpeed(float speed)
		{
			T6SDK::Addresses::FreeRoamSpeed.SetValueSafe(FREEROAM_DEFAULTSPEED * speed);
			//T6SDK::ConsoleLog::LogFormatted("FreeRoamSpeed changed to %.3f", speed);
		}
		static bool Demo_IsClipPlaying()
		{
			return T6SDK::Typedefs::Demo_IsClipPlaying();
		}
		static bool Demo_IsClipPreviewRunning()
		{
			return T6SDK::Typedefs::Demo_IsClipPreviewRunning();
		}
		static void Demo_SwitchCameraMode(int newCamMode)
		{
			T6SDK::Typedefs::Demo_SwitchCameraMode(0, newCamMode);
		}
		static int Demo_GetNextFreeCameraMode(bool anticlockwise)
		{
			return T6SDK::Typedefs::Demo_GetNextFreeCameraMode(anticlockwise);
		}
#pragma region Custom Camera Modes
		static void RegisterCameraMode(T6SDK::Theater::CustomCameraMode mode)
		{
			T6SDK::MAIN::RegisteredCameraModes.push_back((int)&mode);
			T6SDK::ConsoleLog::LogSuccessFormatted("Registered new custom camera mode %s; Total custom modes registered: %i; Free camera modes: %i", mode.Name, T6SDK::MAIN::RegisteredCameraModes.size(), mode.FreeCameraModes.size());
		}
		static void RegisterCameraMode(T6SDK::Theater::CustomCameraMode* mode)
		{
			T6SDK::MAIN::RegisteredCameraModes.push_back((int)mode);
			T6SDK::ConsoleLog::LogSuccessFormatted("Registered new custom camera mode %s; Total custom modes registered: %i; Free camera modes: %i", mode->Name, T6SDK::MAIN::RegisteredCameraModes.size(), mode->FreeCameraModes.size());
		}
		static void RemoveCameraMode(T6SDK::Theater::CustomCameraMode mode)
		{
			for(int i = 0; i < T6SDK::MAIN::RegisteredCameraModes.size(); i++)
			{
				if(T6SDK::MAIN::RegisteredCameraModes[i] == (int)&mode)
				{
					T6SDK::ConsoleLog::LogSuccessFormatted("Removed custom camera mode %s; Total custom modes registered: %i", mode.Name, T6SDK::MAIN::RegisteredCameraModes.size()-1);
					T6SDK::MAIN::RegisteredCameraModes.erase(T6SDK::MAIN::RegisteredCameraModes.begin() + i);
					return;
				}
			}
		}
		static void RemoveCameraMode(T6SDK::Theater::CustomCameraMode* mode)
		{
			for (int i = 0; i < T6SDK::MAIN::RegisteredCameraModes.size(); i++)
			{
				if (T6SDK::MAIN::RegisteredCameraModes[i] == (int)mode)
				{
					T6SDK::ConsoleLog::LogSuccessFormatted("Removed custom camera mode %s; Total custom modes registered: %i", mode->Name, T6SDK::MAIN::RegisteredCameraModes.size() - 1);
					T6SDK::MAIN::RegisteredCameraModes.erase(T6SDK::MAIN::RegisteredCameraModes.begin() + i);
					return;
				}
			}
		}
		static void RemoveCameraMode(const char* name)
		{
			for(int i = 0; i < T6SDK::MAIN::RegisteredCameraModes.size(); i++)
			{
				if(((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[i])->Name == name)
				{
					T6SDK::ConsoleLog::LogSuccessFormatted("Removed custom camera mode %s; Total custom modes registered: %i", name, T6SDK::MAIN::RegisteredCameraModes.size()-1);
					T6SDK::MAIN::RegisteredCameraModes.erase(T6SDK::MAIN::RegisteredCameraModes.begin() + i);
					return;
				}
			}
		}
		static void RemoveCameraMode(int index)
		{
			if(index < 3) return;
			T6SDK::ConsoleLog::LogSuccessFormatted("Removed custom camera mode by index %i; Total custom modes registered: %i", index, T6SDK::MAIN::RegisteredCameraModes.size() - 1);
			T6SDK::MAIN::RegisteredCameraModes.erase(T6SDK::MAIN::RegisteredCameraModes.begin() + index);
		}
#pragma endregion

#pragma region Detours
		static void DetouredSwitchCamera(int localClientNum)
		{
			if (!Demo_IsClipPlaying())
			{
				if (Demo_IsClipPreviewRunning())
					T6SDK::ConsoleLog::LogError("We cannot switch camera in a demo that is being previewed");
				else
				{
					if (!T6SDK::Addresses::DemoPlayback.Value())
					{
						T6SDK::ConsoleLog::LogError("DemoPlayback was null. Return to original func.");
						T6SDK::Addresses::DetoursAddresses::DetouredSwitchCameraHook.call_original_noreturn<T6SDK::Typedefs::Demo_SwitchCamera_t, int>(localClientNum);
						return;
					}
					/*2 is DOLLY CAM*/
					Demo_SwitchCameraMode((int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode != 2  + T6SDK::MAIN::RegisteredCameraModes.size() ? (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode + 1 : 0);
					T6SDK::ConsoleLog::LogFormatted("Switched to %i\n", (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode);
					if(T6SDK::Addresses::DemoPlayback.Value()->CameraMode == T6SDK::DemoCameraMode::NONE)
						T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode = (T6SDK::DemoFreeCameraMode)0x00;
					else if(T6SDK::Addresses::DemoPlayback.Value()->CameraMode == T6SDK::DemoCameraMode::FREECAM)
						T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode = T6SDK::DemoFreeCameraMode::EDIT;
					else if (T6SDK::Addresses::DemoPlayback.Value()->CameraMode > T6SDK::DemoCameraMode::FREECAM)
					{
						int lastCustomFreeMode = ((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[(int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode - 3])->lastFreeCameraMode;
						if (lastCustomFreeMode == 0)
							T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode = (T6SDK::DemoFreeCameraMode)T6SDK::Addresses::DemoPlayback.Value()->CameraMode;
						else
							T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode = (T6SDK::DemoFreeCameraMode)lastCustomFreeMode;
					}	
				}
			}
			T6SDK::ConsoleLog::LogSuccessFormatted("DetouredSwitchCamera fired! Current mode: %i; Total modes count: %i", (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode, T6SDK::MAIN::RegisteredCameraModes.size());
			
		}
		
		static void HandleTheaterSafeStringTranslate(const char** string)
		{
			if (strcmp(*string, "MENU_DEMO_DVR_FREE_CAMERA") == 0) // if passed parameter is "MENU_DEMO_DVR_FREE_CAMERA"
			{
				if (T6SDK::Addresses::DemoPlayback.Value()->CameraMode == T6SDK::DemoCameraMode::FREECAM) // if we currently in real free camera we pass the default string to translate "MENU_DEMO_DVR_FREE_CAMERA"
					*string = "MENU_DEMO_DVR_FREE_CAMERA";
				else if (T6SDK::Addresses::DemoPlayback.Value()->CameraMode > T6SDK::DemoCameraMode::FREECAM) // if we currently in one of custom modes
				{
					*string = ((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[(int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode - 3])->Name;
					//T6SDK::ConsoleLog::LogSameLineFormatted("Displaying custom mode: %s", string);
				}
			}
		}
		static int DetouredGetNextFreeCameraMode(bool anticlockwise)
		{
			if(!T6SDK::Theater::IsPlaybackInited()) return 0;
			int CurrentFreeCameraMode = (int)T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode;
			if(T6SDK::Addresses::DemoPlayback.Value()->CameraMode == T6SDK::DemoCameraMode::FREECAM) // if we are currently in real free camera
			{
				if (anticlockwise) //right mouse button
				{
					if (CurrentFreeCameraMode == 0)
						return 2;
					else
						return CurrentFreeCameraMode - 1;
				}
				else
				{
					if (CurrentFreeCameraMode == 2) //Reached "Dolly Cam"
						return 0;
					return CurrentFreeCameraMode + 1;
				}
			}
			else if(T6SDK::Addresses::DemoPlayback.Value()->CameraMode > T6SDK::DemoCameraMode::FREECAM) // if we are currently in one of custom modes
			{
				int max = (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode + ((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[(int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode - 3])->FreeCameraModes.size() - 1;
				int min = (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode;
				int result = 0;
				if (max <= min)
					max = min;
				if (anticlockwise)
				{
					if (CurrentFreeCameraMode == min)
						result = max;
					else
						result = CurrentFreeCameraMode - 1;
				}
				else
				{
					//if we reached current camera mode index + count of its free camera modes count - 1
					if (CurrentFreeCameraMode == max)
						result = min; //return current camera mode index as a default free camera mode value for a custom camera mode
					else
						result = CurrentFreeCameraMode + 1;
				}
				((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[(int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode - 3])->lastFreeCameraMode = result;
				return result;
			}
		}
		static const char* DetouredGetFreeCamModeName()
		{
			int CurrentFreeCameraMode = (int)T6SDK::Addresses::DemoPlayback.Value()->FreeCameraMode;
			if(CurrentFreeCameraMode == 0)
				return T6SDK::InternalFunctions::UI_SafeTranslateString("MENU_DEMO_FREE_ROAM_MODE");
			else if(CurrentFreeCameraMode == 1)
				return T6SDK::InternalFunctions::UI_SafeTranslateString("MENU_DEMO_EDIT_CAMERA_MODE");
			else if(CurrentFreeCameraMode == 2)
				return T6SDK::InternalFunctions::UI_SafeTranslateString("MENU_DEMO_DOLLY_CAMERA_MODE");
			else if (CurrentFreeCameraMode > 2 && CurrentFreeCameraMode <= 3 + T6SDK::MAIN::RegisteredCameraModes.size()) //if we are currently in one of custom modes
			{
				try
				{
					int currentCameraModeIndex = (int)T6SDK::Addresses::DemoPlayback.Value()->CameraMode;
					return ((T6SDK::Theater::CustomCameraMode*)T6SDK::MAIN::RegisteredCameraModes[currentCameraModeIndex - 3])->FreeCameraModes[CurrentFreeCameraMode - currentCameraModeIndex];
				}
				catch (const char* errorMessage)
				{
					return "";
				}
			}
			return "";
		}
#pragma endregion

	}
	
}