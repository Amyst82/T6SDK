#pragma once
#define ILINE __forceinline
#include "StdInclude.h"

#pragma region Dvar structures
union DvarLimits {
	struct
	{
		int stringCount;
		char** strings;
	} enumeration;
	struct
	{
		int min;
		int max;
	} integer;
	struct
	{
		float min;
		float max;
	} decimal;
};

union DvarValue {
	bool enabled;
	int integer;
	unsigned int unsignedInt;
	float value;
	float vector[4];
	const char* string;
	unsigned char color[4];
};

typedef enum DvarType : int
{
	Dvar_Bool = 0x00,
	Dvar_Float = 0x02,
	Dvar_Vec2 = 0x03,
	Dvar_Vec3 = 0x04,
	Dvar_Vec4 = 0x05,
	Dvar_Int = 0x06,
	Dvar_Enum = 0x07,
	Dvar_String = 0x08,
	Dvar_Color = 0x09,
	Dvar_DevTweak = 0x0A,
	Dvar_LinearColorRGB = 0x0B,
	Dvar_ColorXYZ = 0x0C,
	Dvar_Count = 0x0D
} DvarType;

typedef struct dvar_s
{
	char* dvarName;
	char* dvarDesc;
	int hash;
	int flags;
	DvarType type;
	bool modified;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
	DvarValue saved;
	DvarLimits domain;
	dvar_s* next;
} dvar_s;

typedef struct cmd_function_s
{
	cmd_function_s* next;
	char* name;
	void* autoCompleteDir;
	void* autoCompleteExt;
	void* function;
} cmd_function_s;
#pragma endregion

#pragma region Vectors
typedef struct vec2_t
{
public:
	float x{}, y{};
	ILINE vec2_t(float f) : x(f), y(f){};
	ILINE vec2_t() {};
	ILINE vec2_t(float _x, float _y)
	{
		x = _x;
		y = _y;
	};
	ILINE vec2_t& operator = (const vec2_t& source)
	{
		x = source.x;
		y = source.y;
		return *this;
	}
	ILINE vec2_t& operator = (const float value)
	{
		x = value; y = value;
		return *this;
	}
	ILINE float& operator[](int index) { return ((float*)this)[index]; }
	ILINE float operator[](int index) const { return ((float*)this)[index]; }

	void operator += (float f)
	{
		x += f; y += f;
	}
	void operator += (vec2_t d)
	{
		x += d.x; y += d.y;
	}
	void operator -= (vec2_t d)
	{
		x -= d.x; y -= d.y;
	}
	friend bool operator == (const vec2_t d, const vec2_t& v)
	{
		return v.x == d.x && v.y == d.y;
	}
	ILINE vec2_t& operator / (float f)
	{
		x /= f; y /= f;
		return *this;
	}
	ILINE vec2_t& operator *= (float f)
	{
		x *= f; y *= f;
		return *this;
	}
	ILINE vec2_t& operator /= (float f)
	{
		x /= f; y /= f;
		return *this;
	}
	ILINE vec2_t operator*(float f) const
	{
		const vec2_t v = *this;
		return vec2_t(v.x * f, v.y * f);
	}
	ILINE friend vec2_t operator*(float f, vec2_t v) { return v * f; }
	ILINE vec2_t operator*(int k) const { vec2_t v = *this; return vec2_t(v.x * k, v.y * k); return v; }
	ILINE friend vec2_t operator*(int k, const vec2_t v) { return vec2_t(v.x * k, v.y * k); }

	ILINE friend vec2_t operator + (const vec2_t& vec1, const vec2_t& vec2)
	{
		return vec2_t(vec1.x + vec2.x, vec1.y + vec2.y);
	}
	ILINE friend vec2_t operator + (const vec2_t& vec1, const float* vec2)
	{
		return vec1 + vec2_t(*vec2);
	}
	ILINE friend vec2_t operator + (const float* vec1, const vec2_t& vec2)
	{
		return vec2_t(*vec1) + vec2;
	}

	ILINE friend vec2_t operator - (const vec2_t& vec1, const vec2_t& vec2)
	{
		return vec2_t(vec1.x - vec2.x, vec1.y - vec2.y);
	}
	ILINE friend vec2_t operator - (const vec2_t& vec1, const float* vec2)
	{
		return vec1 - vec2_t(*vec2);
	}
	ILINE friend vec2_t operator - (const float* vec1, const vec2_t& vec2)
	{
		return vec2_t(*vec1) - vec2;
	}

	vec2_t Subtract(const vec2_t& src, const vec2_t& dst)
	{
		vec2_t diff;
		diff.x = src.x - dst.x;
		diff.y = src.y - dst.y;
		return diff;
	}

	float Magnitude(const vec2_t& vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y);
	}

	float Distance(const vec2_t& vec1, const vec2_t& vec2)
	{
		vec2_t diff = Subtract(vec1, vec2);
		return Magnitude(diff);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2));
	}
	float LengthSquared()
	{
		return powf(x, 2) + powf(y, 2);
	}
} vec2_t;
typedef struct vec3_t
{
public:
	float x{}, y{}, z{};
	ILINE vec3_t(float f) : x(f), y(f), z(f) {};
	ILINE vec3_t() {};
	ILINE vec3_t(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	};
	ILINE vec3_t& operator = (const vec3_t& source)
	{
		x = source.x;
		y = source.y;
		z = source.z;
		return *this;
	}
	ILINE vec3_t& operator = (const float value)
	{
		x = value; y = value; z = value;
		return *this;
	}
	ILINE float& operator[](int index) { return ((float*)this)[index]; }
	ILINE float operator[](int index) const { return ((float*)this)[index]; }

	void operator += (float f)
	{
		x += f; y += f; z += f;
	}
	void operator += (vec3_t d)
	{
		x += d.x; y += d.y; z += d.z;
	}
	void operator -= (vec3_t d)
	{
		x -= d.x; y -= d.y; z -= d.z;
	}
	friend bool operator == (const vec3_t d, const vec3_t& v)
	{
		return v.x == d.x && v.y == d.y && v.z == d.z;
	}
	ILINE vec3_t& operator / (float f)
	{
		x /= f; y /= f; z /= f;
		return *this;
	}
	ILINE vec3_t& operator *= (float f)
	{
		x *= f; y *= f; z *= f;
		return *this;
	}
	ILINE vec3_t& operator /= (float f)
	{
		x /= f; y /= f; z /= f;
		return *this;
	}
	ILINE vec3_t operator*(float f) const
	{
		const vec3_t v = *this;
		return vec3_t(v.x * f, v.y * f, v.z * f);
	}
	ILINE friend vec3_t operator*(float f, vec3_t v) { return v * f; }
	ILINE vec3_t operator*(int k) const { vec3_t v = *this; return vec3_t(v.x * k, v.y * k, v.z * k); return v; }
	ILINE friend vec3_t operator*(int k, const vec3_t v) { return vec3_t(v.x * k, v.y * k, v.z * k); }

	ILINE friend vec3_t operator + (const vec3_t& vec1, const vec3_t& vec2)
	{
		return vec3_t(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
	}
	ILINE friend vec3_t operator + (const vec3_t& vec1, const float* vec2)
	{
		return vec1 + vec3_t(*vec2);
	}
	ILINE friend vec3_t operator + (const float* vec1, const vec3_t& vec2)
	{
		return vec3_t(*vec1) + vec2;
	}

	ILINE friend vec3_t operator - (const vec3_t& vec1, const vec3_t& vec2)
	{
		return vec3_t(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	}
	ILINE friend vec3_t operator - (const vec3_t& vec1, const float* vec2)
	{
		return vec1 - vec3_t(*vec2);
	}
	ILINE friend vec3_t operator - (const float* vec1, const vec3_t& vec2)
	{
		return vec3_t(*vec1) - vec2;
	}

	vec3_t Subtract(const vec3_t& src, const vec3_t& dst)
	{
		vec3_t diff;
		diff.x = src.x - dst.x;
		diff.y = src.y - dst.y;
		diff.z = src.z - dst.z;
		return diff;
	}

	float Magnitude(const vec3_t& vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	float Distance(const vec3_t& vec1, const vec3_t& vec2)
	{
		vec3_t diff = Subtract(vec1, vec2);
		return Magnitude(diff);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}
	float LengthSquared()
	{
		return powf(x, 2) + powf(y, 2) + powf(z, 2);
	}
} vec3_t;
typedef struct vec4_t
{
public:
	float x{}, y{}, z{}, w{};
	ILINE vec4_t(float f) : x(f), y(f), z(f), w(f) {};
	ILINE vec4_t() {};
	ILINE vec4_t(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	};
	ILINE vec4_t& operator = (const vec4_t& source)
	{
		x = source.x;
		y = source.y;
		z = source.z;
		w = source.w;
		return *this;
	}
	ILINE vec4_t& operator = (const float value)
	{
		x = value; y = value; z = value; w = value;
		return *this;
	}
	ILINE float& operator[](int index) { return ((float*)this)[index]; }
	ILINE float operator[](int index) const { return ((float*)this)[index]; }

	void operator += (float f)
	{
		x += f; y += f; z += f; w += f;
	}
	void operator += (vec4_t d)
	{
		x += d.x; y += d.y; z += d.z; w += d.w;
	}
	void operator -= (vec4_t d)
	{
		x -= d.x; y -= d.y; z -= d.z; w -= d.w;
	}
	friend bool operator == (const vec4_t d, const vec4_t& v)
	{
		return v.x == d.x && v.y == d.y && v.z == d.z && v.w == d.w;
	}
	ILINE vec4_t& operator / (float f)
	{
		x /= f; y /= f; z /= f; w /= f;
		return *this;
	}
	ILINE vec4_t& operator *= (float f)
	{
		x *= f; y *= f; z *= f; w *= f;
		return *this;
	}
	ILINE vec4_t& operator /= (float f)
	{
		x /= f; y /= f; z /= f; w /= f;
		return *this;
	}
	ILINE vec4_t operator*(float f) const
	{
		const vec4_t v = *this;
		return vec4_t(v.x * f, v.y * f, v.z * f, v.w * f);
	}
	ILINE friend vec4_t operator*(float f, vec4_t v) { return v * f; }
	ILINE vec4_t operator*(int k) const { vec4_t v = *this; return vec4_t(v.x * k, v.y * k, v.z * k, v.w * k); return v; }
	ILINE friend vec4_t operator*(int k, const vec4_t v) { return vec4_t(v.x * k, v.y * k, v.z * k, v.w * k); }

	ILINE friend vec4_t operator + (const vec4_t& vec1, const vec4_t& vec2)
	{
		return vec4_t(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
	}
	ILINE friend vec4_t operator + (const vec4_t& vec1, const float* vec2)
	{
		return vec1 + vec4_t(*vec2);
	}
	ILINE friend vec4_t operator + (const float* vec1, const vec4_t& vec2)
	{
		return vec4_t(*vec1) + vec2;
	}

	ILINE friend vec4_t operator - (const vec4_t& vec1, const vec4_t& vec2)
	{
		return vec4_t(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
	}
	ILINE friend vec4_t operator - (const vec4_t& vec1, const float* vec2)
	{
		return vec1 - vec4_t(*vec2);
	}
	ILINE friend vec4_t operator - (const float* vec1, const vec4_t& vec2)
	{
		return vec4_t(*vec1) - vec2;
	}

	vec4_t Subtract(const vec4_t& src, const vec4_t& dst)
	{
		vec4_t diff;
		diff.x = src.x - dst.x;
		diff.y = src.y - dst.y;
		diff.z = src.z - dst.z;
		return diff;
	}

	float Magnitude(const vec4_t& vec)
	{
		return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	}

	float Distance(const vec4_t& vec1, const vec4_t& vec2)
	{
		vec4_t diff = Subtract(vec1, vec2);
		return Magnitude(diff);
	}
	float Length()
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}
	float LengthSquared()
	{
		return powf(x, 2) + powf(y, 2) + powf(z, 2);
	}
} vec4_t;

typedef struct Matrix44_s
{
	vec4_t m[4];
}Matrix44_s;

typedef struct Matrix33_s
{
	vec3_t m[3];
} Matrix33_s;
#pragma endregion

#pragma region Camera structures

typedef struct FreeRoamCamera_s
{
	vec3_t Origin;
	vec3_t Angles;
} FreeRoamCamera_s;

typedef struct CameraWayPoint_s
{
	vec3_t src;
	vec3_t dst;
	float roll, fov;
	ILINE CameraWayPoint_s() : src(0.0f), dst(0.0f), roll(0.0f), fov(0.0f) {}
	explicit ILINE CameraWayPoint_s(float t) : src(t), dst(t), roll(t), fov(t) {}
	ILINE CameraWayPoint_s(float _x, float _y, float _z, float _dirx, float _diry, float _dirz, float _roll, float _fov)
	{
		src.x = _x; src.y = _y; src.z = _z;
		dst.x = _dirx; dst.y = _diry; dst.z = _dirz;
		roll = _roll, fov = _fov;
	}
	ILINE CameraWayPoint_s(vec3_t _src, vec3_t _dst, float _roll, float _fov)
	{
		src = _src;
		dst = _dst;
		roll = _roll, fov = _fov;
	}

	float Length()
	{
		return sqrtf(src.Length() + dst.Length() + powf(roll, 2) + powf(fov, 2));
	}
	float LengthSquared()
	{
		return src.LengthSquared() + dst.LengthSquared() + powf(roll, 2) + powf(fov, 2);
	}

	ILINE CameraWayPoint_s& operator = (const CameraWayPoint_s& source)
	{
		src = source.src;
		dst = source.dst;
		roll = source.roll, fov = source.fov;
		return *this;
	}
	ILINE CameraWayPoint_s& operator = (const float value)
	{
		src = value; dst = value;
		roll = value, fov = value;
		return *this;
	}

	ILINE float& operator[](int index) { return ((float*)this)[index]; }
	ILINE float operator[](int index) const { return ((float*)this)[index]; }

	void operator += (float f)
	{
		src += f; dst += f;
		roll += f, fov += f;
	}
	void operator += (CameraWayPoint_s d)
	{
		src += d.src; dst += d.dst;
		roll += d.roll; fov += d.fov;
	}
	void operator -= (CameraWayPoint_s d)
	{
		src -= d.src; dst -= d.dst;
		roll -= d.roll; fov -= d.fov;
	}

	ILINE CameraWayPoint_s operator / (float f)
	{
		return CameraWayPoint_s(src / f, dst / f, roll / f, fov / f);
	}
	ILINE CameraWayPoint_s& operator *= (float f)
	{
		src *= f; dst *= f;
		roll *= f; fov *= f;
		return *this;
	}
	ILINE CameraWayPoint_s& operator /= (float f)
	{
		src /= f; dst /= f;
		roll /= f; fov /= f;
		return *this;
	}
	ILINE CameraWayPoint_s operator*(float f) const
	{
		const CameraWayPoint_s v = *this;
		return CameraWayPoint_s(v.src * f, v.dst * f, v.roll * f, v.fov * f);
	}
	ILINE friend CameraWayPoint_s operator*(float f, CameraWayPoint_s v) { return v * f; }
	ILINE CameraWayPoint_s operator*(int k) const { CameraWayPoint_s v = *this; return CameraWayPoint_s(v.src * k, v.dst * k, v.roll * k, v.fov * k); return v; }
	ILINE friend CameraWayPoint_s operator*(int k, const CameraWayPoint_s v) { return CameraWayPoint_s(v.src * k, v.dst * k, v.roll * k, v.fov * k); }

	ILINE friend CameraWayPoint_s operator + (const CameraWayPoint_s& vec1, const CameraWayPoint_s& vec2)
	{
		return CameraWayPoint_s(vec1.src + vec2.src, vec1.dst + vec2.dst, vec1.roll + vec2.roll, vec1.fov + vec2.fov);
	}
	ILINE friend CameraWayPoint_s operator + (const CameraWayPoint_s& vec1, const float* vec2)
	{
		return vec1 + CameraWayPoint_s(*vec2);
	}
	ILINE friend CameraWayPoint_s operator + (const float* vec1, const CameraWayPoint_s& vec2)
	{
		return CameraWayPoint_s(*vec1) + vec2;
	}
	ILINE friend CameraWayPoint_s operator + (float k, const CameraWayPoint_s& v)
	{
		return CameraWayPoint_s(v.src + k, v.dst + k, v.roll + k, v.fov + k);
	}

	ILINE friend CameraWayPoint_s operator - (const CameraWayPoint_s& vec1, const CameraWayPoint_s& vec2)
	{
		return CameraWayPoint_s(vec1.src - vec2.src, vec1.dst - vec2.dst, vec1.roll - vec2.roll, vec1.fov - vec2.fov);
	}
	ILINE friend CameraWayPoint_s operator - (const CameraWayPoint_s& vec1, const float* vec2)
	{
		return vec1 - CameraWayPoint_s(*vec2);
	}
	ILINE friend CameraWayPoint_s operator - (const float* vec1, const CameraWayPoint_s& vec2)
	{
		return CameraWayPoint_s(*vec1) - vec2;
	}
} CameraWayPoint_s;

typedef struct CameraMarker_s
{
public:
	int Tick;
private:
	int pad0;
public:
	vec3_t Position;
	vec3_t Direction;
	int Mode;
	float MarkerSpeed;
private:
	int pad1[5];
public:
	float Roll; //Can be used for something else
private:
	int pad2;
private:
	int pad3[6];
public:
	float Fov;
} CameraMarker_s;

typedef struct demoPlayback
{
private:
	int ukn0;//0x00
	float timescale;//0x04
public:
	float fov;//0x08
private:
	char _0x0C[406876]; //length 0x6355C
public:
	bool Completed; //0x63568
	bool GameHudHidden; //0x63569
	bool DemoHudHidden; //0x6356A
private:
	char _0x6356B[464533]; //length of 0x71695
public:
	T6SDK::DemoCameraMode CameraMode; //0xD4C00
	T6SDK::DemoFreeCameraMode FreeCameraMode; //0xD4C04
private:
	char _0xD4C08[0x17068]; //length of 0x17068
public:
	FreeRoamCamera_s FreeRoamCamera; //0xEBC70
private:
	char _0xEBC88[0x44]; //length of 0x44
public:
	vec3_t DollyCamPathVerts[500]; //0xEBCCC
private:
	int _0xED43C;
public:
	CameraMarker_s DollyCameraMarkers[50]; //0xED440
private:
	int _0xEE700[2];
public:
	int DollyCamMarkerCount; //0xEE708
private:
	int _0xEE70C;
public:
	signed int HighlightedDollyCamMarker; //0xEE710
	bool RepositioningDollyCamMarker;//0xEE714
	bool CancelRepositioning;//0xEE715
} demoPlayback;
#pragma endregion

#pragma region cg stuff
class entityState_t
{
public:
	int number; //0x00
private:
	char _0xE0[212];
public:
	BYTE eType;//0xD8
private:
	char _0x0C[11];
public:
	int WeaponID; //0xE4
private:
	char _0xE8[11];
public:
	BYTE clientNum; //0xF3
private:
	char _0xF4[4];
}; //size 0xF8
class cpose_t
{
private:
	WORD lightingHandle; //0x00
public:
	BYTE eType; //0x02
private:
	BYTE eTypeUnion; //0x03
public:
	BYTE localClientNum; //0x04
private:
	bool isRagdoll; //0x05
	bool unk1; //0x06
	bool unk2; //0x07
	int ragdollHandle;//0x08
	int physObjId;//0x0C
public:
	int physUserBody;//0x10
private:
	int killcamRagdollHandle;//0x14
	int physUserBodyProneFeet; //0x18
	bool destructiblePose;//0x1C
	char _0x1D[3];//0x1D
	int startBurnTime; //0x20
	int wetness;//0x24
	int cullIn;//0x28
public:
	vec3_t origin;//0x2C
	vec3_t angles;//0x38
private:
	char _0x11C[284];
}; //size 0x160
class entity_t
{
public:
	cpose_t pose; //0x00
private:
	char _0x7C[124];
public:
	entityState_t nextState; //0x1DC
private:
	char _0xAC[164];
};//size 0x380
class snapshot_t
{
private:
	int snapFlags;
public:
	int ping;
	int serverTime;
	int physicsTime;
private:
	char _0x0010[10760];
public:
	int numEntities; //0x2A18
	int numClients; //0x2A1C
private:
	char _0x2A20[136672];
}; //size 0x24000
class clientinfo_t
{
public:
	char _0x0000[4];
	__int32 IsValid; //0x0004 
	__int32 clientNum; //0x0008 
	char szName[32]; //0x000C 
	__int32 Team; //0x002C 
	__int32 Team2; //0x0030 
	char _0x0034[88];
	__int32 IsDead; //0x008C 
	char _0x0090[4];
	__int32 Score; //0x0094 
	__int32 Kills; //0x0098 
	char _0x009C[4];
	__int32 Deaths; //0x00A0 
	char _0x00A4[20];
	__int32 Assists; //0x00B8 
	char _0x00BC[1032];
	float ViewAngleY; //0x04C4 
	float ViewAngleX; //0x04C8 
	char _0x04CC[192];
	__int32 IsFiring; //0x058C 
	__int32 IsZoomed; //0x0590 
	char _0x0594[48];
	__int32 weaponID; //0x05C4 
	char _0x05C8[576];
};
class refdef_t
{
public:
	__int32 x; //0x0000 
	__int32 y; //0x0004 
	__int32 iWidth; //0x0008 
	__int32 iHeight; //0x000C 
	char _0x0010[16];
	float fovx; //0x0020 
	float fovy; //0x0024 
	float fovz; //0x0028 
	char _0x002C[4];
	float TotalFov; //0x0030 
	vec3_t vOrigin; //0x0034 
	char _0x0040[4];
	Matrix33_s viewAxis; //0x0044 
	char _0x0068[4];
	__int32 iTime; //0x006C 
	char _0x0070[144];

};

class cg_t
{
public:
	int clientnum; //0x0000 
private:
	char _0x0004[20];
public:
	int IsIngame; //0x0018 
private:
	char _0x001C[100];
public:
	snapshot_t activeSnapshots[2];//0x80
private:
	char _0x48080[10];
public:
	int Tick; //0x4808C
private:
	char _0x48090[22528];
public:
	refdef_t RefDef; //0x4D890
private:
	char _0x4D990[0x1709C];
public:
	vec3_t baseGunAngles; //0x64A2C
private:
	char _unknown[0x5028];
public:
	clientinfo_t client[18]; //0x69A60
}; 

#pragma endregion

#pragma region uiDrawing
typedef struct UiContext_t
{
private:
	int contextIndex; //0x00
	float bias; //0x04
public:
	int realTime; //0x08
	int frameTime; //0x0C
	vec2_t cursor; //0x10
	int isCursorVisible; //0x18
	int screenWidth; //0x1C
	int screenHeight; //0x20
	float screenAspect; //0x24
	float FPS; //0x28
private:
	char _0x2C[0x2188];
}UiContext_t;
typedef struct uiInfo_s
{
public:
	UiContext_t uiDC;//0x00
private:
	char _0x21B4[0x1C];
public:
	T6SDK::uiMenuCommand_t currentMenuType;//0x21D0
private:
	char _0x21D4[0x314];
}uiInfo_s; //size 0x24E8
#pragma endregion

union GfxColor {
	int packed;
	BYTE color[4];
};
typedef float tColor[4];

typedef struct Font_s
{
	const char* fontName;
	int pixelHeight;
} Font_s;

struct DemoTimescaleFormat_s
{
	char text[6];
};

typedef struct FxSprite_t
{
	int MaterialOffset;
	vec3_t Position;
	BYTE R;
	BYTE G;
	BYTE B;
	BYTE A;
	float Radius;
	float minScreenRadius;
	int flags;
}FxSprite_t;