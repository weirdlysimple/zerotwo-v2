#pragma once
#define TOC 0x00724C38 


extern "C" {
	int	_sys_printf(const char* format, ...);
	int	_sys_sprintf(char* s, const char* format, ...);
	int	_sys_vsprintf(char* s, const char* format, va_list arg);
	int _sys_vsnprintf(char*, size_t, const char*, va_list);
	int _sys_snprintf(char*, size_t, const char*, ...);
	void* _sys_malloc(size_t n);
	void _sys_free(void* ptr);
	size_t _sys_wcstombs(char*, const wchar_t*, size_t);
}

#define array_size(a) (sizeof(a) / sizeof(*(a)))
#define nullptr 0
#define zero_memory(a, b) memset(a, 0, b) 

#define printf			_sys_printf
#define sprintf			_sys_sprintf
#define vsprintf		_sys_vsprintf
#define vsnprintf		_sys_vsnprintf
#define snprintf		_sys_snprintf

namespace structures
{
	struct opd_s
	{
		int sub;
		int toc;
	};

	enum Buttons
	{
		L1 = 0x41,
		R1 = 0x4D,
		Square = 0x29,
		R3 = 0xD1,
		DpadUp = 0xF5,
		DpadDown = 0x105,
		Cross = 0x11,
		Triangle = 0x34,
		Circle = 0x1D,
		L2 = 0xDC,
		R2 = 0xE8,
		L3 = 0xC4,
		Left = 0x10D,
		Right = 0x119,
		Select = 0xB8,
		Start = 0xAC

	};
	bool ButtonPressed(Buttons Button)
	{
		return (*(char*)(0x0095C08A + Button) != 0);
	}
	struct UiContext
	{
		int localClientNum;
		float bias;
		int realTime;
		int frameTime;
		int cursorx;
		int cursory;
		int debug[2];
		int screenWidth;
		int screenHeight;
		float screenAspect;
		float FPS;
		float blurRadiusOut;
		void* Menus[512];
		int menuCount;
		void* menuStack[16];
		int openMenuCount;
		void* localVars;
	};
	UiContext ui_context;

	int time;
}
static void color_convert_hsv_to_rgb(float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	if (s == 0.0f) {
		// gray
		out_r = out_g = out_b = v;
		return;
	}

	h = fmodf(h, 1.0f) / (60.0f / 360.0f);
	int i = (int)h;
	float f = h - (float)i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - s * f);
	float t = v * (1.0f - s * (1.0f - f));

	switch (i) {
	case 0:
		out_r = v;
		out_g = t;
		out_b = p;
		break;
	case 1:
		out_r = q;
		out_g = v;
		out_b = p;
		break;
	case 2:
		out_r = p;
		out_g = v;
		out_b = t;
		break;
	case 3:
		out_r = p;
		out_g = q;
		out_b = v;
		break;
	case 4:
		out_r = t;
		out_g = p;
		out_b = v;
		break;
	case 5:
	default:
		out_r = v;
		out_g = p;
		out_b = q;
		break;
	}
}
namespace menuMiscFunctions
{
	void sleep(usecond_t time) { sys_timer_usleep(time * 1000); }
	bool getStructs() {
		structures::ui_context = *(structures::UiContext*)0x01C1DF20;
		return true;
	}
}
bool InGame()
{
	if (*(char*)0x01D17A8C == 1)
		return true;
	else
		return false;
}
struct Material {
	const char* szMaterialName;
};
struct Font_s {
	const char* fontName;
	int pixelHeight;
	int isScalingAllowed;
	int glyphCount;
	int kerningPairsCount;
	Material* material;
	Material* glowMaterial;
	struct Glyph* glyphs;
	struct KerningPairs* kerningPairs;
};
class hsv_value {
public:
	float h, s, v;
	hsv_value() {
		h = 1;
		s = 1;
		v = 1;
	}

};

namespace espColors {
	float enemy_col_r = 1;
	float enemy_col_g = 0.5;
	float enemy_col_b = 0.5;
	
	float team_col_r = 0.5;
	float team_col_g = 0.5;
	float team_col_b = 1;

	float crosshair_col_r = 1;
	float crosshair_col_g = 0.5;
	float crosshair_col_b = 1;

	float camo_col_r = 1;
	float camo_col_g = 0.5;
	float camo_col_b = 1;
}
namespace menuColors
{


	typedef struct  {
		float r, g, b, a;
		
	} Color;

	Color hsvToColor(float value) {

		static float temp_r, temp_g, temp_b;
		color_convert_hsv_to_rgb(value, 1, 1, temp_r, temp_g, temp_b);

		Color output = { temp_r, temp_g, temp_b, 1 };

		return output;
	}

	float clamp(float var, float min, float max) {

		if (var < min)
			var = min;
		if (var > max)
			var = max;

		return var;
	}
	Color blend(const Color& a, const Color& b, const float multiplier)
	{
		return
		{

			a.a + static_cast<int>(clamp(multiplier, 0.f, 1.f) * (b.r - a.r)),
			a.g + static_cast<int>(clamp(multiplier, 0.f, 1.f) * (b.g - a.g)),
			a.b + static_cast<int>(clamp(multiplier, 0.f, 1.f) * (b.b - a.b)),
			a.a + static_cast<int>(clamp(multiplier, 0.f, 1.f) * (b.a - a.a))
		};
	}

	Color MainColor = { 1, 1, 0, 1 };
	Color White = { 1, 1, 1, 1 };
	Color menuWhite = { 1, 1, 1, 1 };
	//Color dimWhite = { 170 / 255.f, 170 / 255.f, 170 / 255.f, 1 };

	Color menuDimmedWhite = { 170 / 255.f, 170 / 255.f, 170 / 255.f, 1 };
	Color Gray = { 0.4, 0.4, 0.4, 1 };
	Color Green = { 0, 1, 0, 1 };
	Color Red = { 1, 0, 0, 1 };
	//	Color BlackShader = { 0, 0, 0, .7 };
	Color menuDimmedBlack = { 0, 0, 0, .7 };
	Color dimmedBlack = { 0, 0, 0, .7 };
	//Color black = { 0, 0, 0, 1 };
	Color menuBlack = { 0, 0, 0, 1 };
	Color MainColor2 = { 0, 0, 1, 1 };
	Color OptionColor[99];
	Color dflash;
	Color dflash2;
	Color ESPColor;
	Color ESPEnemy = { 1, 0, 0, 1 };
	Color ESPFriendly = { 0.1, 1, 0.1, 1 };

	//Color Grey = { 0.359f, 0.359f, 0.359f, 0.862f };
	Color menuGrey = { 0.359f, 0.359f, 0.359f, 0.862f };
	Color Main = { 1, .5, 1, 1.000f }; //this is a sexy looking pink
	Color menuMain = { 1, .5, 1, 1.000f }; //this is a sexy looking pink
	Color FadedPink = { 25 / 255.f, 25 / 255.f, 25 / 255.f, 1.000f }; //this is for false bools

	Color inputtedColor = { 1, .5, 1, 1.000f };

	Color Grey15 = { 15 / 255.f, 15 / 255.f, 15 / 255.f, 1.f };
	Color Blue = { 0.5, 0.5, 1, 1 };
}

namespace myMath {
#define PI (3.1415926535897931)
	float abs(float a) {
		if (a < 0)
			return a * -1;
		return a;
	}
	float DegreesToRadians(float Degrees)
	{
		return Degrees * PI / 180.0f;
	}

	float RadiansToDegrees(float Radians)
	{
		return Radians * 180.0f / PI;
	}

	float pow(float num, int power) {
		float ret = 1;
		for (int i = 0; i < power; i++)
			ret = ret * num;
		return ret;
	}

	float root(float num, int nroot) {
		int iterations = 15 * (nroot - 1);
		float x = iterations * 100;
		for (int i = 1; i < iterations; i++) {
			x = (float)(((float)1 / nroot) * (((nroot - 1) * x) + (num / powf(x, nroot - 1))));
		}
		return x;
	}

	float sin(float deg) {
		bool neg = false;
		while (deg >= 360) deg = deg - 360;
		while (deg < 0) deg = deg + 360;
		if (deg > 180) {
			deg = deg - 180;
			neg = true;
		}
		float ret = (float)(4 * deg * (180 - deg)) / (40500 - (deg * (180 - deg)));
		if (neg)return ret * -1;
		return ret;
	}

	float cos(float AnglesDeg)
	{
		float AnglesRad = DegreesToRadians(AnglesDeg);
		float Rad = (float)(PI / 2.0f) - AnglesRad;
		float ang = RadiansToDegrees(Rad);
		return sinf(ang);
	}

	float tan(float AnglesDeg)
	{
		float sinus = sinf(AnglesDeg);
		float cosinus = cosf(AnglesDeg);
		return sinus / cosinus;
	}

	double atan(double x, int n)
	{
		double a = 0.0;// 1st term
		double sum = 0.0;

		// special cases
		if (x == 1.0) return PI / 4.0;
		if (x == -1.0) return -PI / 4.0;

		if (n > 0)
		{
			if ((x < -1.0) || (x > 1.0))
			{
				// constant term
				if (x > 1.0)
					sum = PI / 2.0;
				else
					sum = -PI / 2.0;
				// initial value of a
				a = -1.0 / x;
				for (int j = 1; j <= n; j++)
				{
					sum += a;
					a *= -1.0 * (2.0 * j - 1) / ((2.0 * j + 1) * x * x);// next term from last
				}
			}
			else// -1 < x < 1
			{
				// constant term
				sum = 0.0;
				// initial value of a
				a = x;
				for (int j = 1; j <= n; j++)
				{
					sum += a;
					a *= -1.0 * (2.0 * j - 1) * x * x / (2.0 * j + 1);// next term from last
				}
			}
			//r_err = a;// max. error = 1st term not taken for alternating series
		}

		return sum;
	}

	double atan2(double y, double x)
	{
		double u = atan2f(y / x, 24);
		if (x < 0.0)// 2nd, 3rd quadrant
		{
			if (u > 0.0)// will go to 3rd quadrant
				u -= PI;
			else
				u += PI;
		}
		return u;
	}

}


struct vec3
{
	float x;
	float y;
	float z;
};

typedef struct Vector2
{
	float x, y;
	Vector2()
	{
		x = y = 0;
	}
	Vector2(float x, float y)
	{
		this->x = x; this->y = y;
	}

}Vector2, * PVector2;
float rad2deg(float angle) {
	return angle / 180 / PI;
}
float remainder_f(float v1, float v2) {

	return (fmodf(v1, (v1 / v2)));
}
typedef struct Vector3
{
	float x, y, z;
	Vector3()
	{
		x = y = z = 0;
	}
	Vector3(float x, float y, float z)
	{
		this->x = x; this->y = y; this->z = z;
	}
	const bool operator== (Vector3 const& Vector)
	{
		return (this->x == Vector.x && this->y == Vector.y && this->z == Vector.z);
	}
	const Vector3& operator+ (Vector3 const& Vector)
	{
		return Vector3(this->x + Vector.x, this->y + Vector.y, this->z + Vector.z);
	}
	const Vector3& operator- (Vector3 const& Vector)
	{
		return Vector3(this->x - Vector.x, this->y - Vector.y, this->z - Vector.z);
	}
	Vector3 toAngle() const
	{
		return Vector3{ rad2deg(atan2f(-z, hypotf(x, y))),
					   rad2deg(atan2f(y, x)),
					   0.0f };
	}
	Vector3& normalize() noexcept
	{
		
		x = isfinite(x) ? remainder_f(x, 360.0f) : 0.0f;
		y = isfinite(y) ? remainder_f(y, 360.0f) : 0.0f;
		z = 0.0f;
		return *this;
	}
	float Distance(Vector3 const& Vector)
	{
		return sqrtf(DistanceEx(Vector));
	}
	float DistanceEx(Vector3 const& Vector)
	{
		float _x = this->x - Vector.x, _y = this->y - Vector.y, _z = this->z - Vector.z;
		return ((_x * _x) + (_y * _y) + (_z * _z));
	}
	float DotProduct(Vector3& Vector)
	{
		return (this->x * Vector.x) + (this->y * Vector.y) + (this->z * Vector.z);
	}
	const Vector3& RoundHalfUp()
	{
		return Vector3(floorf(this->x + 0.5), floorf(this->y + 0.5), floorf(this->z + 0.5));
	}\
		const Vector3& RoundHalfDown()
	{
		return Vector3(floorf(this->x + 0.5), floorf(this->y + 0.5), floorf(this->z + 0.5));
	}

	float Vector3::getLength() const {
		return sqrtf((x * x) + (y * y) + (z * z));
	}
} Vector3, * PVector3;

Vector3 AnglesToFoward(Vector3 Origin, Vector3 Angles, float diff) {
	float angle, sr, sp, sy, cr, cp, cy, PiDiv;
	PiDiv = ((float)M_PI / 180);
	angle = Angles.y * PiDiv;
	sy = (float)sinf(angle);
	cy = (float)cosf(angle);
	angle = Angles.x * PiDiv;
	sp = sinf(angle);
	cp = (float)cosf(angle);
	angle = Angles.y * PiDiv;
	sr = (float)sinf(angle);
	cr = (float)cosf(angle);
	Vector3 Final((cp * cy * diff) + Origin.x, (cp * sy * diff) + Origin.y, (-sp * diff) + Origin.z);
	return Final;
}
float dx, dy, dz;
float Distance3D(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;

	return sqrtf((float)((dx * dx) + (dy * dy) + (dz * dz)));
}
typedef struct Vector4
{
	float x, y, z, a;


} Vector4, * PVector4;

Vector3 vectoangles(Vector3 Angles)
{
	float forward;
	float yaw, pitch;
	//float PI = 3.1415926535897931;
	if (Angles.x == 0 && Angles.y == 0)
	{
		yaw = 0;
		if (Angles.z > 0) pitch = 90.00;
		else pitch = 270.00;
	}
	else
	{
		if (Angles.x != -1) yaw = (float)(atan2f((double)Angles.y, (double)Angles.x) * 180.00 / PI);
		else if (Angles.y > 0) yaw = 90.00;
		else yaw = 270;
		if (yaw < 0) yaw += 360.00;

		forward = (float)sqrtf((double)(Angles.x * Angles.x + Angles.y * Angles.y));
		pitch = (float)(atan2f((double)Angles.z, (double)forward) * 180.00 / PI);
		if (pitch < 0) pitch += 360.00;
	}
	Vector3 AnglesVector(-pitch, yaw, 0);
	return AnglesVector;
}
void vector_angles(const Vector3& forward, Vector3& angles) {
	float	tmp, yaw, pitch;

	if (forward.y == 0 && forward.x == 0) {
		yaw = 0;
		if (forward.z > 0)
			pitch = 270;
		else
			pitch = 90;
	}
	else {
		yaw = (atan2f(forward.y, forward.x) * 180 / PI);
		if (yaw < 0)
			yaw += 360;

		tmp = sqrtf(forward.x * forward.x + forward.y * forward.y);
		pitch = (atan2f(-forward.z, tmp) * 180 / PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles.x = pitch;
	angles.y = yaw;
	angles.z = 0;
}
Vector3 calculate_angle(Vector3& src, Vector3& dst) {
	Vector3 angle;

	vector_angles(dst - src, angle);
	return angle;
}
Vector3 Difference(Vector3 Target, Vector3 Entity)
{
	Vector3 Return = Target - Entity;
	return Return;
}

typedef struct vec4_t
{
	float x, y, z, w;

};

void VectorCopy(Vector3* orig, Vector3* final) {
	final->x = orig->x;
	final->y = orig->y;
	final->z = orig->z;
}
enum entityType_t
{
	ET_General = 0,
	ET_Player = 1,
	ET_Corpse = 2,
	ET_Item = 3,
	ET_Missile = 4,
	ET_Invisible_entity = 5,
	ET_Scriptmover = 6,
	ET_Sound_blend = 7,
	ET_Fx = 8,
	ET_Loop_FX = 9,
	ET_Primary_Light = 10,
	ET_Turret = 11,
	ET_Helicopter = 12,
	ET_Plane = 13,
	ET_Vehicle = 14,
	ET_Vehicle_corpse = 15,
	ET_Actor = 16,
	ET_Actor_spawner = 17,
	ET_Actor_corpse = 18,
	ET_Streamer_Hint = 19,
};

#define INT16 int16_t
#define INT32 int32_t
#define INT64 int64_t
#define UINT16 uint16_t
#define UINT32 uint32_t
#define UINT64 uint64_t


/*INT16 lightingHandle; //0x0000
	unsigned char eType; //0x0002
	unsigned char localClientNum; //0x0003
	char _0x0004[40];
	Vector3 Origin; //0x002C
	char _0x0038[284];
	INT32 Flags; //0x0154
	INT32 eFlags2; //0x0158
	unsigned char trType; //0x015C
	char _0x015D[3];
	INT32 trTime; //0x0160
	INT32 trDuration; //0x0164
	Vector3 NewOrigin; //0x0168
	Vector3 trDelta; //0x0174
	char _0x0180[36];
	float leanf; //0x01A4
	INT32 movementDir; //0x01A8
	INT32 movementType; //0x01AC
	INT32 WeaponID; //0x01B0
	INT32 OldWeapon; //0x01B4
	INT32 offHandWeaponModel; //0x01B8
	INT32 meleeWeapon; //0x01BC
	unsigned char offhandeWeaponModel; //0x01C0
	unsigned char meleeWeaponModel; //0x01C1
	unsigned char vehicleType; //0x01C2
	unsigned char vehicleAnimBoneIndex; //0x01C3
	unsigned char vehicleSeat; //0x01C4
	unsigned char stowedweaponCamo; //0x01C5
	char _0x01C6[10];
	INT32 ClientNumber; //0x01D0
	INT32 nextLerpeFlags; //0x01D4
	INT32 nextLerpeFlags1; //0x01D8
	unsigned char nextLerptrType; //0x01DC
	char _0x01DD[3];
	INT32 nextlerptrtime; //0x01E0
	INT32 nextlerptrduration; //0x01E4
	Vector3 OldOrigin; //0x01E8
	Vector3 nextLerptrdelta; //0x01F4
	char _0x0200[90];
	bool Alive; //0x25A
	char _0x025B[77];
	INT16 Type; //0x02A8
	char _0x02AA[202];*/


typedef struct c_entity_t
{
	char _0x0000[0x2];
	char Alive;
	char _0x0003[0x15];
	Vector3 Origin;
	char _0x0024[0x3C];
	int Flags;
	char _0x0064[0x14];
	Vector3 NewOrigin;
	char _0x0084[0x4C];
	int Handle;
	int Type;
	char _0x00D8[0x1C];
	Vector3 OldOrigin;
	char _0x0100[0x58];
	int PickupID;
	char _0x015C[0x40];
	short WeaponID;
	char _0x019E[8];
	short OldWeapon;
	char _0x01B0[0x50];
};

typedef struct
{
	int X;							//0x00
	int Y;							//0x04
	int Width;						//0x08
	int Height;						//0x0C
	Vector2 Fov;					//0x10
	Vector3 viewOrigin;				//0x18
	Vector3 viewAxis[3];			//0x24
	char _0x0048[0x18];
	float flZoomProgress;//0x60
						 //0x64
}refdef_t;


typedef struct
{
	int Valid;						//0x00
	char padding00[0x8];			//0x04
	char Name[32];					//0x0C
	int Team;						//0x2C
	char padding01[0x4];			//0x30
	int Rank;						//0x34
	int Prestige;					//0x38
	char padding02[0xC];			//0x3C
	unsigned int Perk[2];			//0x48
	char padding03[0x4];			//0x4C
	int Score;						//0x54
	char Model[0x40];				//0x58
	char HeadModel[0x40];			//0x98
	char WeaponModel[0x40];			//0xD8
	char WeaponModel2[0x40];		//0x117
	char padding04[0x2C0];			//0x158
	Vector3 viewAngle;				//0x418
	char _0x0424[0x90];				//0x424
	int Attacking;					//0x4B4
	char padding05[0x4];			//0x4B8
	int Zooming;					//0x4BC	
	char padding06[0x58];			//0x4C0
	int Weapon;						//0x518
	char padding07[0x28];			//0x51C

}clientinfo_t;

typedef struct
{
	int Client; //0x0
	int Score; //0x4
	int Ping; //0x8
	int Deaths; //0xC
	int Assists; //0x10
	int team; //0x14
	char _0x0018[0x10];
}score_t;// size 0x28
typedef struct // size 0x34
{
	int width;    //0x00
	int Height;    //0x04
	char padding00[0x10]; //0x08
	char gamemode[0x10]; //0x18
	char padding01[0x10]; //0x28
	char hostName[0x32]; //0x38
	char paddin02[0xDA]; //0x6A
	char mapName[0x32];  //0x144


}cgs;
enum weapType_t
{
	TYPE_BULLET,
	TYPE_GRENADE,
	TYPE_PROJECTILE,
	TYPE_BINOCULARS
};

enum weapClass_t
{
	WEAPCLASS_RIFLE,
	WEAPCLASS_SNIPER,
	WEAPCLASS_MG,
	WEAPCLASS_SMG,
	WEAPCLASS_SPREAD,
	WEAPCLASS_PISTOL,
	WEAPCLASS_GRENADE,
	WEAPCLASS_ROCKETLAUNCHER,
	WEAPCLASS_TURRET,
	WEAPCLASS_THROWINGKNIFE,
	WEAPONCLASS_NON_PLAYER,
	WEAPCLASS_ITEM
};

enum ammoCounterClipType_t
{
	AMMO_COUNTER_CLIP_NONE,
	AMMO_COUNTER_CLIP_MAGAZINE,
	AMMO_COUNTER_CLIP_SHORTMAGAZINE,
	AMMO_COUNTER_CLIP_SHOTGUN,
	AMMO_COUNTER_CLIP_ROCKET,
	AMMO_COUNTER_CLIP_BELTFED,
	AMMO_COUNTER_CLIP_ALTWEAPON,
	AMMO_COUNTER_CLIP_COUNT,
};

enum weaponIconRatioType_t
{
	WEAPON_ICON_RATIO_1TO1,
	WEAPON_ICON_RATIO_2TO1,
	WEAPON_ICON_RATIO_4TO1,
	WEAPON_ICON_RATIO_COUNT,
};
struct rectDef_s
{
	float x;
	float y;
	float w;
	float h;
	int horzAlign;
	int vertAlign;
};
enum CompassType
{
	COMPASS_TYPE_PARTIAL = 0x0,
	COMPASS_TYPE_FULL = 0x1,
};
struct WeaponDef
{
	char padding[0x2C]; //0x0
	weapType_t weapType; //0x30
	weapClass_t weapClass; //0x34
	int penetrateType; //0x38
	int inventoryType; //0x38
	char padding2[0x1CC - 8];
	weaponIconRatioType_t ammoCounterIconRatio; //0x200
	ammoCounterClipType_t ammoCounterClip; //0x204
	int startAmmoCount; //0x208
	char* ammoName; //0x20C
	int iAmmoIndex; //0x210
	char padding3[0x2F0]; //0x2F4
	float maxDamageRange; //0x504
	float minDamageRange; //0x508
};
enum TraceHitType
{
	TRACE_HITTYPE_NONE = 0,
	TRACE_HITTYPE_ENTITY = 1,
	TRACE_HITTYPE_DYNENT_MODEL = 2,
	TRACE_HITTYPE_DYNENT_BRUSH = 3,
	TRACE_HITTYPE_DYNENT_UNKNOWN = 4
};
struct trace_t
{
	float fraction;					//0x0000
	Vector3 normal;					//0x0004
	int surfaceFlags;				//0x0010
	int contents;					//0x0014
	const char* material;			//0x0018
	//int hitType;					//0x001C
	TraceHitType hitType;
	unsigned short hitId;			//0x0020
	unsigned short modelIndex;		//0x0022
	unsigned short partName;		//0x0024
	unsigned short partGroup;		//0x0026
	bool allsolid;					//0x0028 allsolid
	bool startsolid;				//0x0029 startsolid
	char _0x002B[0x02];				//0x002B
}; // 0x002C
struct BulletTraceResults {
	float fraction;
	Vector3 surfaceDirection;
	int surfaceFlags;
	int contents;
	const char* material;
	int hitType;
	unsigned short entityNum;
	unsigned short modelIndex;
	unsigned short partyName;
	unsigned short partyGroup;
	bool allSolid;
	bool startSolid;
	bool walkable;
	char _0x002B[5];
	Vector3 endPos;
	char didHitEnt;
	char skippp[0x3];
	int materialType;
};

typedef struct {
	int	worldEntNum;	         // 00 
	int	ignoreEntIndex;	         // 04 
	float damageMultiplier;	     // 08 
	int	methodOfDeath;	         // 12 

	Vector3	origStart;		// 16
	Vector3	start;			// 28
	Vector3	end;			// 40
	Vector3	dir;	        // 52    
}BulletFireParams;//size= 68 or 0x44

typedef struct
{
	int Servertime;					//0x00
	char padding00[0x100];			//0x04
	int ClientNumber;				//0x104
	char padding01[0x4];			//0x108
	Vector3 ViewAngle;				//0x10C
	char padding03[0x38];			//0x118
	int Health;						//0x150
	char padding04[0x170];			//0x154
	float SpreadMultiplier;			//0x2C4
	char padding05[0xB0];			//0x2C8
	int MaxEntities;				//0x378
	char padding06[0x6A8AC];		//0x37C
	refdef_t RefDef;				//0x6AC28
	char _0x6AC8C[0x84E4];
	score_t Score[18];				//0x73170
	char _0x73440[0x90];
	int Weapon;						//0x734D0  
	char padding08[0x839AC];		//0x734D4
	clientinfo_t ClientInfo[18];	//0xF6E80
	char padding09[0x10C0];			//0xFCD48
	cgs pCgs;
} cgArray_t;

typedef struct
{
	int time;						// 0x00-0x04
	int buttons;					// 0x04-0x08
	int viewAngles[3];				// 0x08-0x14
	short weapon;					// 0x14-0x16
	short offHandIndex;				// 0x16-0x18
	char Buf[0x02];					// 0x18-0x1A
	char fDir;						// 0x1A-0x1B
	char rDir;						// 0x1B-0x1C
	char Buf2[0x0C];				// 0x1C-0x28
}Usercmd_t;

typedef struct
{
	bool ADS;						//0x0000
	char padding00[0xDF];			//0x0001
	Vector3 baseAngle;				//0x00E0
	char padding01[0x31B7];			//0x00EC
	char MapName[0x40];				//0x32A3
	char padding02[0x21];			//0x32E3
	int Stance;						//0x3304
	char padding03[0x28];			//0x3308
	Vector3 Origin;					//0x3330
	char padding04[0x1C];			//0x333C
	Vector3 viewAngle;				//0x3358
	Usercmd_t Usercmd[128];			//0x3364
	int CurrentCmdNumber;			//0x4764
}active_client_t;

void Unfreeze(int client)
{
	*(char*)(0x014E5623 + 0x3700) = 0x00;
}

int GClient(int client)
{
	return (0x14E2200 + (0x3700));
}

int GetIndex()
{
	int cg_s = *(int*)(0x915254);
	if (cg_s == 0)
		return -1;
	return *(int*)(cg_s + 0x3250);
}

int getHostIndex()
{
	int hostIndex = *(int*)(0x50F5E4);
	return hostIndex;
}
#define ScrWidth dc.width
#define ScrHeight dc.height
#define dc (*(UiContext*)(0x186B778))
#define cg (*(cgArray_t**)(0x915254))
#define c_entity (*(c_entity_t**)(0x91527C))
#define active_client (*(active_client_t**)(0x9FD590))
#define FLAG_CROUCHED 0x04
#define FLAG_PRONE 0x08
bool isHost()
{
	if (0x00711720 == 0x16B4)
		return true;
}

struct tocdata_s
{
	int toc;
	tocdata_s() { this->toc = 0; }
	tocdata_s(int toc) { this->toc = toc; }
};

#define SetRToc(toc) (*(tocdata_s*)(0x10005000) = tocdata_s(toc))

struct opd_z
{
	int Sub;
	int Toc;
	opd_z() { this->Sub = this->Toc = (*(tocdata_s*)(0x10005000)).toc; }
	opd_z(int sub) { this->Sub = sub, this->Toc = (*(tocdata_s*)(0x10005000)).toc; }
	opd_z(int sub, int toc) {
		this->Sub = sub,
			this->Toc = toc;
	}
};

template<typename R>
R Invoke(int Address) { return ((R(*)()) & opd_z(Address))(); }
template<typename R, typename A1>
R Invoke(int Address, A1 a1) { return ((R(*)(A1 a1)) & opd_z(Address))(a1); }
template<typename R, typename A1, typename A2>
R Invoke(int Address, A1 a1, A2 a2) { return ((R(*)(A1 a1, A2 a2)) & opd_z(Address))(a1, a2); }
template<typename R, typename A1, typename A2, typename A3>
R Invoke(int Address, A1 a1, A2 a2, A3 a3) { return ((R(*)(A1 a1, A2 a2, A3 a3)) & opd_z(Address))(a1, a2, a3); }
template<typename R, typename A1, typename A2, typename A3, typename A4>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4)) & opd_z(Address))(a1, a2, a3, a4); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)) & opd_z(Address))(a1, a2, a3, a4, a5); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)) & opd_z(Address))(a1, a2, a3, a4, a5, a6); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18); }
template<typename R, typename A1, typename A2, typename A3, typename A4, typename A5, typename A6, typename A7, typename A8, typename A9, typename A10, typename A11, typename A12, typename A13, typename A14, typename A15, typename A16, typename A17, typename A18, typename A19>
R Invoke(int Address, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19) { return ((R(*)(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9, A10 a10, A11 a11, A12 a12, A13 a13, A14 a14, A15 a15, A16 a16, A17 a17, A18 a18, A19 a19)) & opd_z(Address))(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19); }

void VectorAngles(Vector3& forward, Vector3& angles) {
	float tmp, yaw, pitch;
	if (forward.z == 0 && forward.x == 0) {
		yaw = 0;
		if (forward.z > 0) pitch = 90;
		else pitch = 270;
	}
	else {
		yaw = (atan2(forward.z, -forward.x) * 180 / PI) - 90;
		if (yaw < 0) yaw += 360;
		tmp = sqrtf(forward.x * forward.x + forward.z * forward.z);
		pitch = (atan2(forward.y, tmp) * 180 / PI);
		if (pitch < 0) pitch += 360;
	}
	angles.x = -pitch;
	angles.y = yaw;
	angles.z = 0;
}

#define SHORT2ANGLE(x)  ((x)*(360.0/65536))
#define ANGLE2SHORT(x)   ((int)((x)*65536/360) & 65535)

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// libpsutil :D
uint32_t rand_next = 1;
uint32_t rand_r(uint32_t* ctx)
{
	return ((*ctx = *ctx * 0x41C64E6D + 0x3039) % ((uint32_t)0x7FFFFFFF + 1));
}

void ps_srand(uint32_t seed)
{
	rand_next = seed;
}

uint32_t ps_rand()
{
	return rand_r(&rand_next);
}

union DvarValue
{
	char enabled;
	int integer;
	unsigned int unsignedInt;
	std::int64_t integer64;
	std::uint64_t unsignedInt64;
	float value;
	const char* string;
	char color[4];
};

struct dvar_t {
	char* name;
	char* desc;
	DvarValue current;
	DvarValue latched;
	DvarValue reset;
};

int find_image_offset(char* imgName)
{
	int buf = 0x0;
	for (int i = 0; i != 4000; i++)
	{
		buf = 0x00C67D2C + (i * 0x50);
		if (!strcmp((char*)(*(int*)(buf + 0x4C)), imgName))
			return *(int*)(buf + 0x28);
	}
	return 0x0;
}

void set_shader_tint(int offset, int len, char r, char g, char b)
{
	int colorConv = (((r & 0xF8) << 8) + ((g & 0xFC) << 3) + (b >> 3));
	for (int i = 0; i < (len / 8); i++)
	{
		*(int*)(offset + (i * 0x08)) = 0x000000FF;
		*(int*)((offset + 0x04) + (i * 0x08)) = 0x00000000;
		*(char*)(offset + (i * 0x08)) = (colorConv & 0xFF);
		*(char*)((offset + 0x01) + (i * 0x08)) = ((colorConv >> 8) & 0xFF);
	}
}

struct ContentPackList
{
	int contentPack;
	char unk0[0x88];
	char dlcName1[0x5];
	char unk1[0x83];
	char dlcName2[0x5];
};

ContentPackList* contentPack = (ContentPackList*)0x1F96708;

