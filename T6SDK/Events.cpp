#include "pch.h"
#include "Events.h"
namespace T6SDK
{
	void T6SDK::Events::Invoke(EventType eventType) 
	{
		for(int i = 0; i < listeners[eventType].size(); i++) 
		{
			T6SDK::Typedefs::func* f =  (T6SDK::Typedefs::func*)listeners[eventType][i];
			if(f)
				f();
		}
	}
	void T6SDK::Events::InvokeByteParam(EventType eventType, BYTE value)
	{
		for (int i = 0; i < listeners[eventType].size(); i++)
		{
			T6SDK::Typedefs::funcByteParam* f = (T6SDK::Typedefs::funcByteParam*)listeners[eventType][i];
			if (f)
				f(value);
		}
	}

	void T6SDK::Events::InvokeKeyPressed(EventType eventType, BYTE value, bool released)
	{
		for (int i = 0; i < listeners[eventType].size(); i++)
		{
			T6SDK::Typedefs::funtKeyPressed* f = (T6SDK::Typedefs::funtKeyPressed*)listeners[eventType][i];
			if (f)
				f(value, released);
		}
	}

	void T6SDK::Events::InvokeIntParam(EventType eventType, int value)
	{
		for (int i = 0; i < listeners[eventType].size(); i++)
		{
			T6SDK::Typedefs::funcIntParam* f = (T6SDK::Typedefs::funcIntParam*)listeners[eventType][i];
			if (f)
				f(value);
		}
	}
	void T6SDK::Events::InvokeCameraMarkerParam(EventType eventType, CameraMarker_s* value)
	{
		for (int i = 0; i < listeners[eventType].size(); i++)
		{
			T6SDK::Typedefs::funcCameraMarkerParam* f = (T6SDK::Typedefs::funcCameraMarkerParam*)listeners[eventType][i];
			if (f)
				f(value);
		}
	}
	void T6SDK::Events::InvokeConstCharParam(EventType eventType, const char** value)
	{
		for (int i = 0; i < listeners[eventType].size(); i++)
		{
			T6SDK::Typedefs::funcConstCharParam* f = (T6SDK::Typedefs::funcConstCharParam*)listeners[eventType][i];
			if (f)
				f(value);
		}
	}
	void T6SDK::Events::RegisterListener(EventType eventType, uintptr_t function) 
	{
		listeners[eventType].push_back(function);
		std::string eventNameString = "OnGameLoaded";
		switch (eventType)
		{
			case EventType::OnGameLoaded:
				eventNameString = "OnGameLoaded";
				break;
			case EventType::OnGameModeChanged:
				eventNameString = "OnGameModeChanged";
				break;
			case EventType::OnTheaterControlsDrawn:
				eventNameString = "OnTheaterControlsDrawn";
				break;
			case EventType::OnActiveFrameDrawn:
				eventNameString = "OnActiveFrameDrawn";
				break;
			case EventType::OnViewMatrixWritten:
				eventNameString = "OnViewMatrixWritten";
				break;
			case EventType::OnEndFrameDrawn:
				eventNameString = "OnEndFrameDrawn";
				break;
			case EventType::OnTickChanged:
				eventNameString = "OnTickChanged";
				break;
			case EventType::OnAspectRatioChanged:
				eventNameString = "OnAspectRatioChanged";
				break;
			case EventType::OnCameraMarkerAdded:
				eventNameString = "OnCameraMarkerAdded";
				break;
			case EventType::OnFreeCameraModeChanged:
				eventNameString = "OnFreeCameraModeChanged";
				break;
			case EventType::OnCameraModeChanged:
				eventNameString = "OnCameraModeChanged";
				break;
			case EventType::OnKeyPressed:
				eventNameString = "OnKeyPressed";
				break;
			case EventType::OnMouseLeftButtonClicked:
				eventNameString = "OnMouseLeftButtonClicked";
				break;
			case EventType::OnMouseRightButtonClicked:
				eventNameString = "OnMouseRightButtonClicked";
				break;
			case EventType::OnMouseWheelUp:
				eventNameString = "OnMouseWheelUp";
				break;
			case EventType::OnMouseWheelDown:
				eventNameString = "OnMouseWheelDown";
				break;
			case EventType::OnSafeStringTranslated:
				eventNameString = "OnSafeStringTranslated";
				break;
			case EventType::OnPovCamoWriting:
				eventNameString = "OnPovCamoWriting";
				break;
			case EventType::OnAxisToAngles:
				eventNameString = "OnAxisToAngles";
				break;
			case EventType::OnDemoPlaybackInited:
				eventNameString = "OnDemoPlaybackInited";
				break;
			case EventType::OnSunInited:
				eventNameString = "OnSunInited";
				break;
			case EventType::OnCgItemDrawn:
				eventNameString = "OnCgItemDrawn";
				break;
			case EventType::OnProcessEntity:
				eventNameString = "OnProcessEntity";
				break;
			case EventType::OnDemoRecordingEnded:
				eventNameString = "OnDemoRecordingEnded";
				break;
			case EventType::OnCGCalcEntityLerpPositions:
				eventNameString = "OnCGCalcEntityLerpPositions";
				break;
			default:
				eventNameString = "";
				break;
		}
		//T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "EVENTS", "Added a new function: 0x%X; Events count: %i", listeners[eventType][0], listeners[eventType].size());
		T6SDK::ConsoleLog::LogTagged(T6SDK::ConsoleLog::C_DEBUG, false, "EVENTS", "Listener added on [%s]. Listeners count: %i.", eventNameString.c_str(), listeners[eventType].size());
	}
}