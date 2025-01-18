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
		T6SDK::ConsoleLog::LogFormatted("Added a new function: 0x%X; Events count: %i", listeners[eventType][0], listeners[eventType].size());
	}
}