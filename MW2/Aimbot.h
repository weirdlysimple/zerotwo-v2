
#define XM_PI               3.141592654f
bool targeting_player;
int NearestPlayer;
int nearestClient;
bool Required;
bool DoAngles;

bool ti_is_targeting = false;
char* ti_name;
int ti_distance;
bool ti_visible;
float ti_bullet_damage;
const char* ti_bone;
char* ti_weapon;

bool should_target;
int target_client = 0;
void VectoAngles(Vector3* vec, Vector3* angles)
{
	Invoke<void>(0x2590A8, vec, angles);
}

structures::opd_s glt = { 0x096178, TOC };
void(*CG_LocationalTracee)(trace_t* trace, float* start, float* end, int passEntityNum, int contentmask) = (void(*)(trace_t*, float*, float*, int, int)) & glt;
bool Trace(int clientNum, Vector3 start, Vector3 end) {
	trace_t trace;
	CG_LocationalTracee(&trace, (float*)&start, (float*)&end, clientNum, 0x2803001);
	return (trace.fraction >= 0.95f);
}



Vector3 GetPos(int playerIndex, const char* tagName)
{
	c_entity_t cent = c_entity[playerIndex];
	Vector3 out;
	int obj = pointers::Com_GetClientDObj(playerIndex, 0);
	if (!obj)
		return;

	if (pointers::CG_DObjGetWorldTagPos(&c_entity[playerIndex], obj, pointers::SL_GetString(tagName, 0), &out))
		return out;
}
int cstrcmp(const char* s1, const char* s2) { //Please note if its equal to zero the strings are equal 
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}
bool isSameTeam(int cl1, int cl2)
{
	if (cstrcmp(pointers::Dvar_GetString("ui_gametype"), "dm") == 0)
	{
		return false;
	}
	else
	{
		int cg_s = *(int*)(0x915254);
		int ent2 = *(char*)(cg_s + 0xF6E80 + ((cl2) * 0x544) + 0x2F);
		int ent1 = *(char*)(cg_s + 0xF6E80 + ((cl1) * 0x544) + 0x2F);
		if ((ent1) == (ent2))
		{
			return true;
		}
		return false;
	}
}


bool IsUsingRiot(int i)
{
	if (c_entity[i].WeaponID != 2 && c_entity[i].WeaponID != 3)
		return false;

	return true;
}
int clwpAddr = 0x000A1A88;
structures::opd_s clwp = { clwpAddr, TOC };
int(*CL_WritePacket)(int localClientNum) = (int(*)(int)) & clwp;

int hkCL(int r3);

int wp_redo(int r3, int howManyTimes = 0) {
	char bytes[16] = { 0x7D, 0x80, 0x00, 0x26, 0xF8, 0x21, 0xF6, 0xA1, 0xFA, 0xA1, 0x09, 0x08, 0x3A, 0xA1, 0x00, 0x70 };
	mainFuncs::writeProcMem(clwpAddr, bytes, 16, true);
	int j = 0;
	for (int i = 0; i < howManyTimes; i++)
		j = CL_WritePacket(r3);
	PatchInJump(clwpAddr, (int)hkCL);
	return j;
}
Vector3 GetPlayerViewOrigin() {
	Vector3 Pos;
	pointers::CG_GetPlayerViewOrigin(0, cg, Pos);
	return Pos;
}

bool VisiblyBool = false;
bool start_shooting = false;

float* getMyRefDef() {
	return (float*)&(cg->RefDef.viewOrigin);
}
void SinCos(float num, float* sin, float* cos) {
	*sin = myMath::sin(num);
	*cos = myMath::cos(num);
}
void AngleVectors(Vector3 angles, Vector3 forward, bool right_up, Vector3 right, Vector3 up)
{
	float sr, sp, sy, cr, cp, cy;
	SinCos(angles.y, &sy, &cy);
	SinCos(angles.x, &sp, &cp);
	SinCos(angles.z, &sr, &cr);
	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
	if (right_up) {
		right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right.y = (-1 * sr * sp * sy + -1 * cr * cy);
		right.z = -1 * sr * cp;
		up.x = (cr * sp * cy + -sr * -sy);
		up.y = (cr * sp * sy + -sr * cy);
		up.z = cr * cp;
	}

}


char* Bones[] = {
	/*Head*/		  "j_helmet"     , "j_head"			, "j_neck"
	/*Arms*/		, "j_shoulder_le", "j_shoulder_ri"  , "j_elbow_le"	 , "j_elbow_ri", "j_wrist_le", "j_wrist_ri", "j_gun"
	/*Back*/		, "j_mainroot"   , "j_spineupper"   , "j_spinelower" , "j_spine4"
	/*Legs*/		, "j_hip_ri"     , "j_hip_le"       , "j_knee_le"    , "j_knee_ri" , "j_ankle_ri", "j_ankle_le" };
char* AimbottagList(int index)
{
	if (index == 0)
		return "j_head";
	if (index == 1)
		return "j_helmet";
	if (index == 2)
		return "j_neck";
	if (index == 3)
		return "pelvis";
	if (index == 4)
		return "j_spineupper";
	if (index == 5)
		return "j_knee_le";
	if (index == 6)
		return "j_knee_ri";
	if (index == 7)
		return "j_ankle_le";
	if (index == 8)
		return "j_ankle_ri";
	if (index == 9)
		return "j_hip_ri";
	if (index == 10)
		return "j_hip_le";
	if (index == 11)
		return "j_mainroot";
	if (index == 12)
		return "j_spineupper";
	if (index == 13)
		return "j_spinelower";
	if (index == 14)
		return "j_gun";
	if (index == 15)
		return "j_shoulder_le";
	if (index == 16)
		return "j_shoulder_ri";
}


const char* previewTagList(int index)
{
	if (index == 0)
		return "head";
	if (index == 1)
		return "helmet";
	if (index == 2)
		return "neck";
	if (index == 3)
		return "pelvis";
	if (index == 4)
		return "upper spine";
	if (index == 5)
		return "left knee";
	if (index == 6)
		return "right knee";
	if (index == 7)
		return "left ankle";
	if (index == 8)
		return "right ankle";
	if (index == 9)
		return "right hip";
	if (index == 10)
		return "left hip";
	if (index == 11)
		return "main";
	if (index == 12)
		return "upper spine";
	if (index == 13)
		return "lower spine";
	if (index == 14)
		return "end of gun";
	if (index == 15)
		return "left shoulder";
	if (index == 16)
		return "right shoulder";
}
float min(float x, float y) {
	return x > y ? y : x;
}
float BG_GetSurfacePenetrationDepth(int pt, int surfaceType)
{
	if (surfaceType >= 0x20)
	{
		return 0;
	}
	return pointers::BG_GetSurfacePenetrationDepthF(pt, surfaceType);
}

bool BulletTrace(BulletFireParams* bulletFireParams, BulletTraceResults* bulletTraceResults, int localClientNum, c_entity_t* entity, int surfaceType)
{
	int wepid = c_entity[cg->ClientNumber].WeaponID;
	int weaponDefPtr = pointers::GetWeaponDef(wepid);
	return pointers::bulletTrace(0, bulletFireParams, weaponDefPtr, entity, bulletTraceResults, surfaceType);
}

void SetupBulletTrace(BulletFireParams* btr, Vector3 start, Vector3 end, int skipNum) {
	btr->worldEntNum = 2046;
	btr->ignoreEntIndex = skipNum;
	btr->damageMultiplier = 1;
	btr->methodOfDeath = 1;
	btr->origStart = start;
	btr->start = start;
	btr->end = end;

	Vector3 delta = end - start;

	Vector3 angles;
	VectorAngles(delta, angles);
	btr->dir = delta;
}

bool can_autowall(int ent, char* ent_tag)
{
	BulletFireParams params;
	BulletTraceResults result;

	Vector3 target_position = GetPos(ent, ent_tag);

	if (target_position.x == 0 || target_position.y == 0 || target_position.z == 0)
		return false;

	SetupBulletTrace(&params, cg->RefDef.viewOrigin, target_position, cg->ClientNumber);
	Bools::has_hit_trace = false;
	if (!BulletTrace(&params, &result, cg->ClientNumber, &c_entity[cg->ClientNumber], 0))
		return false;

	Bools::has_hit_trace = true;
	Bools::trace_fraction = result.fraction;

	if (result.fraction > (Bools::autoWallStrength == 0 ? 0.85f : 0.75f))
		return true;

	return false;
}

float traceWall(int Client, const char* tag) {
	Vector3 eye = cg->RefDef.viewOrigin;
	Vector3 bonePos = GetPos(Client, tag);
	BulletTraceResults bulletTrRes;
	BulletFireParams bulletTrace;

	bulletTrace.worldEntNum = 2046;
	bulletTrace.ignoreEntIndex = cg->ClientNumber;
	bulletTrace.damageMultiplier = 1.f;
	bulletTrace.methodOfDeath = 1.0f;

	SetupBulletTrace(&bulletTrace, cg->RefDef.viewOrigin, bonePos, cg->ClientNumber);
	//Bullet_FirePenetrate((WeaponDef*)pointers::GetWeaponDefWD(c_entity[cg->ClientNumber].WeaponID), c_entity[cg->ClientNumber].WeaponID, &bulletTrace, &bulletTrRes);

	if (bulletTrRes.fraction >= 0.97f)
		return 1.f;

	if (bulletTrace.ignoreEntIndex == Client)
		return bulletTrace.damageMultiplier;


	return 0.f;
}

Vector3 calculateRelativeAngle(const Vector3& source, const Vector3& destination, const Vector3& viewAngles) noexcept
{
	float one = destination.x - source.x;
	float two = destination.y - source.y;
	float three = destination.z - source.z;
	Vector3 angle = Vector3(one, two, three);


	return angle.toAngle().normalize();

	//return ((destination - source).toAngle() - viewAngles).normalize();
}
int max_bone_iteration = 8;
int target_bone = 0;

int GetNearestPlayer(int Client)
{
	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
	{
		float nearestDistance = 1E+08f;
		float nearest_bone = 1E+08f;
		for (int i = 0; i < 18; i++)
		{
			if (i != Client)
			{
				if (c_entity[i].Alive)
				{
					if (c_entity[i].Type == 1)
					{
						if (!isSameTeam(cg->ClientNumber, i))
						{
							bool can_see_head_bone = Trace(0, cg->RefDef.viewOrigin, GetPos(i, AimbottagList(0)));
							bool can_see_helmet_bone = Trace(0, cg->RefDef.viewOrigin, GetPos(i, AimbottagList(1)));
							bool can_see_pelvis_bone = Trace(0, cg->RefDef.viewOrigin, GetPos(i, AimbottagList(3)));
							if (Bools::AutoBone) {
								max_bone_iteration = Bools::autoBoneStrength == 0 ? 8 : 16;
								if (IsUsingRiot(i)) {
									target_bone = 7; // j_ankle_le
									nearest_bone = Distance3D(c_entity[Client].Origin, GetPos(i, AimbottagList(7)));
								}
								else {
									for (int bone_iteration = 0; bone_iteration < max_bone_iteration + 1; bone_iteration++) {
										Vector3 current_bone_position = GetPos(i, AimbottagList(bone_iteration));
										float bone_distance = Distance3D(c_entity[Client].Origin, current_bone_position);

										if (Bools::antiHeadGlitch && can_see_helmet_bone && !can_see_head_bone) {
											target_bone = 1;
											nearest_bone = Distance3D(c_entity[Client].Origin, GetPos(i, AimbottagList(1)));
											break;
										}
										else if (can_see_head_bone) {
											target_bone = 0;
											nearest_bone = Distance3D(c_entity[Client].Origin, GetPos(i, AimbottagList(0)));
											break;
										}
										else if (can_see_pelvis_bone && !can_see_head_bone) {
											target_bone = 3;
											nearest_bone = Distance3D(c_entity[Client].Origin, GetPos(i, AimbottagList(3)));
											break;
										}

										if (bone_distance < nearest_bone) {
											nearest_bone = bone_distance;
											target_bone = bone_iteration;
											break;

										}
									}
								}
							}
							else
								target_bone = Bools::targetBone;
							

							bool bone_visible = Trace(0, cg->RefDef.viewOrigin, GetPos(i, AimbottagList(target_bone)));
							if (bone_visible || (Bools::autoWall && can_autowall(i, AimbottagList(target_bone)))) //PlayerVisible(i, AimbottagList(target_bone)) ///traceWall(i, AimbottagList(target_bone)) > 0.f
							{
								float distance_to_bone = Distance3D(c_entity[Client].Origin, GetPos(i, AimbottagList(target_bone)));

								if (distance_to_bone < nearestDistance)
								{
									nearestDistance = distance_to_bone;
									NearestPlayer = i;
									targeting_player = true;


									ti_is_targeting = true;
									ti_name = cg->ClientInfo[i].Name;
									ti_distance = distance_to_bone;
									ti_visible = bone_visible;
									ti_bullet_damage = traceWall(i, AimbottagList(target_bone));
									ti_bone = previewTagList(target_bone);
									ti_weapon = cg->ClientInfo[i].WeaponModel;
								}
							}
						}
					}

				}
			}

		}
	}
	return NearestPlayer;
}

float FinalAngles[2];
bool setCheck = false;

void AimbotHook()
{
	if (!cg || !c_entity || !active_client)
		return;

	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
	{
		if (Bools::Aimbot && cg->Health > 0)
		{
			int me = cg->ClientNumber;
			NearestPlayer = GetNearestPlayer(me);


			if (targeting_player)
			{

				Vector3 Position = GetPos(NearestPlayer, AimbottagList(target_bone)); //AimbottagList(Bools::targetBone)
				Vector3 Angles = Difference(Position, cg->RefDef.viewOrigin);

				should_target = true;

				if (should_target)
				{
					Vector3 anglesOut;
					VectoAngles(&Angles, &anglesOut);

					FinalAngles[0] = anglesOut.x - active_client->baseAngle.x;
					FinalAngles[1] = anglesOut.y - active_client->baseAngle.y;
					FinalAngles[2] = 0.0f;

					if (!Bools::silentAimbot)
					{
						active_client->viewAngle.x = FinalAngles[0];
						active_client->viewAngle.y = FinalAngles[1];
						active_client->viewAngle.z = 0.0f;
					}
					start_shooting = true;

					targeting_player = false;
				}

				should_target = false;
			}
			else
				ti_is_targeting = false;
		}


	}
}