#pragma once
#include "StdInclude.h"
#define FREEROAM_DEFAULTSPEED 0.016999f
namespace T6SDK
{
	namespace Theater::FreeRoamCamera
	{
		inline static T6SDK::CustomDvar c_FreeRoamSpeed(T6SDK::Dvars::RegisterFloat("c_freeRoamSpeed", 1.0f, 0.0f, 10.0f, "Speed of free roam camera."));
		inline static T6SDK::CustomDvar c_AccelerationFactor(T6SDK::Dvars::RegisterFloat("c_accelerationFactor", 2.0f, 0.0f, 10.0f, "Speed multiplier that free camera will accelerate to while pressing shift."));
		inline static T6SDK::CustomDvar c_SlowingFactor(T6SDK::Dvars::RegisterFloat("c_slowingFactor", 0.25f, 0.0f, 10.0f,"Speed multiplier that free camera will slow down to while pressing ctrl."));
		static void SetFreeRoamCameraSpeed(float speed)
		{
			T6SDK::Addresses::FreeRoamSpeed.SetValueSafe(FREEROAM_DEFAULTSPEED * speed);
		}
		static void CheckFreeRoamCameraDvarsModified()
		{
			if (c_FreeRoamSpeed.Modified())
			{
				SetFreeRoamCameraSpeed(c_FreeRoamSpeed.GetFloat());
				T6SDK::ConsoleLog::LogFormatted("FreeRoamSpeed changed to %.3f", c_FreeRoamSpeed.GetFloat());
				c_FreeRoamSpeed.ClearModified();
			}
			if (c_AccelerationFactor.Modified())
			{
				T6SDK::ConsoleLog::LogFormatted("AccelerationFactor changed to %.3f", c_AccelerationFactor.GetFloat());
				c_AccelerationFactor.ClearModified();
			}
			if (c_SlowingFactor.Modified())
			{
				T6SDK::ConsoleLog::LogFormatted("SlowingFactor changed to %.3f", c_SlowingFactor.GetFloat());
				c_SlowingFactor.ClearModified();
			}
		}
		static void HandleInput()
		{
			if (T6SDK::Input::Keys::MINUS.Hold()) //Minus pressed
			{
				if (c_FreeRoamSpeed.GetFloat() > 0.0f)
				{
					c_FreeRoamSpeed._dvar->current.value -= 0.005f;
					c_FreeRoamSpeed._dvar->modified = true;
				}
				else
					c_FreeRoamSpeed._dvar->current.value = 0.000f;
			}
			else if (T6SDK::Input::Keys::PLUS.Hold()) //Plus pressed
			{
				if (c_FreeRoamSpeed.GetFloat() < 10.0f)
				{
					c_FreeRoamSpeed._dvar->current.value += 0.005f;
					c_FreeRoamSpeed._dvar->modified = true;
				}
				else
					c_FreeRoamSpeed._dvar->current.value = 10.0f;
			}

			if (T6SDK::Input::Keys::SHIFT.Hold())
				SetFreeRoamCameraSpeed(c_AccelerationFactor.GetFloat());
			else if (T6SDK::Input::Keys::CTRL.Hold())
				SetFreeRoamCameraSpeed(c_SlowingFactor.GetFloat());
			else
				SetFreeRoamCameraSpeed(c_FreeRoamSpeed.GetFloat());
		}
		static void Update()
		{
			CheckFreeRoamCameraDvarsModified();
			HandleInput();
		}
	}
}