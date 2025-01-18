#pragma once
#include "StdInclude.h"
namespace T6SDK
{
    namespace Typedefs
    {
        typedef void func(void);
        typedef void funcByteParam(BYTE);
        typedef void funtKeyPressed(BYTE, bool released);
        typedef void funcIntParam(int);
        typedef void funcConstCharParam(const char**);
        typedef void funcCameraMarkerParam(CameraMarker_s*);
    }
    class Events
    {
    private:
        inline static std::map<EventType, std::vector<uintptr_t>> listeners{};
    public:
        static void Invoke(EventType eventType);
        static void InvokeByteParam(EventType eventType, BYTE value);
		static void InvokeKeyPressed(EventType eventType, BYTE value, bool released);
		static void InvokeIntParam(EventType eventType, int value);
		static void InvokeCameraMarkerParam(EventType eventType, CameraMarker_s* value);
        static void InvokeConstCharParam(EventType eventType, const char** value);
        static void RegisterListener(EventType eventType, uintptr_t function);
    };


}

