
#define spreadMultiplier 0.00392156862f


double radians(float degrees)
{
	return 0.01745329238474369 * degrees;
}

signed char ClampChar(int i)
{
	if (i < -128)
		return -128;

	if (i > 127)
		return 127;

	return i;
}
void FixMovement(Usercmd_t* cmd, float angleY)
{
	float differenceY = (angleY - active_client->viewAngle.y);
	int forward = cosf(radians(differenceY)) * cmd->fDir + cosf(radians(differenceY + 90.0f)) * cmd->rDir;
	int right = sinf(radians(differenceY)) * cmd->fDir + sinf(radians(differenceY + 90.0f)) * cmd->rDir;

	cmd->fDir = ClampChar(forward);
	cmd->rDir = ClampChar(right);
}

int Centity(int ent)
{
	int cent = *(int*)0x91527C;
	if (cent == 0)
		return -1;
	return cent + (ent * 0x1F8);
};
bool isAlive(int cl)
{
	if (*(char*)(Centity(cl) + 0x02) == 0x01)
	{
		return true;
	}
	return false;
}
float CG_GoodRandomFloat(int* pHoldrand)
{
	unsigned int r11 = 214013 * *pHoldrand + 2531011;
	*pHoldrand = r11;
	return (r11 >> 17) * 0.000030517578;
}
void RandomBulletDir(int randSeed, float* x, float* y)
{
	float f26 = (CG_GoodRandomFloat(&randSeed) * 360.0f) * 0.01745329998474369f;
	float f28 = CG_GoodRandomFloat(&randSeed);
	*x = f28 * cosf(f26); // sin
	*y = f28 * sinf(f26); // cos
}


int transformSeed(int* seed) {
	return (0x343FD * (0x343FD * (0x343FD * (0x343FD * *seed + 0x269EC3) + 0x269EC3) + 0x269EC3) + 0x269EC3);
}
void noSpread(Usercmd_t* old)
{
	if (!((structures::ButtonPressed(structures::R1) / 30) > 0))
	{
		int def = pointers::GetWeaponDef(c_entity[cg->ClientNumber].WeaponID);
		float min, max, rndX, rndY;
		pointers::BG_GetSpreadForWeapon(cg, def, &min, &max);
		float spread = (cg->SpreadMultiplier * spreadMultiplier);
		int mSeed = transformSeed(&old->time);
		spread = min + ((max - min) * spread);
		RandomBulletDir(mSeed, &rndX, &rndY);
		rndX *= spread; rndY *= spread;
		old->viewAngles[0] -= ANGLE2SHORT(-rndY);
		old->viewAngles[1] -= ANGLE2SHORT(-rndX);
	}
}


void CL_SendCmdStub(...)
{
	__asm("li %r3, 0x4;");
}
enum player_stance {
	e_stand,
	e_crouch,
	e_prone
};
int spinSpeed = 10, spinAngle;
bool should_flip;
int CL_SendCmd(int r3)
{
	if (!c_entity || !active_client || !cg) {
		CL_SendCmdStub(r3);
		return;
	}

	Usercmd_t* newcmd = &active_client->Usercmd[(active_client->CurrentCmdNumber + 1) & 0x7F];
	Usercmd_t* currcmd = &active_client->Usercmd[active_client->CurrentCmdNumber & 0x7F];
	*newcmd = *currcmd;

	if (!newcmd || !currcmd)
		return;

	++active_client->CurrentCmdNumber;
	currcmd->time--;
	
	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game() && isAlive(cg->ClientNumber))
	{
		if (Bools::enableAntiAim) {
			if (c_entity[cg->ClientNumber].Alive && cg->Health > 0)
			{
				// pitch
				switch (Bools::aa_pitch) {
				case 1: // up
					newcmd->viewAngles[0] = ANGLE2SHORT(-69.99999f - active_client->baseAngle.x);
					break;
				case 2: // down
					newcmd->viewAngles[0] = ANGLE2SHORT(69.99999f - active_client->baseAngle.x);
					break;
				case 3: // emotion
					newcmd->viewAngles[0] = ANGLE2SHORT((!(newcmd->time % 3) ? 69.99999f : -69.99999f) - active_client->baseAngle.x);
					break;
				case 4: // fake
					if (start_shooting)
						newcmd->viewAngles[0] = ANGLE2SHORT((!(newcmd->time % 3) ? 69.99999f : -69.99999f) - active_client->baseAngle.x);
					break;
				}

				switch (Bools::aa_yaw) {
				case 1: // jitter
					newcmd->viewAngles[1] -= ANGLE2SHORT(!(newcmd->time % 2) ? 180.0f : 0.0f);
					break;
				case 2: // spin
					if (spinAngle < -360)
						spinAngle = 0;

					spinAngle -= spinSpeed;

					newcmd->viewAngles[1] = ANGLE2SHORT(spinAngle);
					break;
				case 3: // reverse spin random
					if (spinAngle < -360) {
						spinAngle = 0;
						should_flip = true;
					}
					else
						should_flip = false;

					if (should_flip)
						spinAngle += spinSpeed;
					else
						spinAngle -= spinSpeed;

					newcmd->viewAngles[1] = ANGLE2SHORT(spinAngle);
					break;
				case 4: // shielding
					newcmd->viewAngles[1] -= ANGLE2SHORT(180.0f);
					break;
				case 5: // emotion
					newcmd->viewAngles[1] = ANGLE2SHORT((!(newcmd->time % 3) ? 180.0f : -0.0f) - active_client->baseAngle.y);
					break;
				}
			}
		}

	}
	CL_SendCmdStub(r3);
}
int hkCL(int r3)
{
	if (!cg || !c_entity || !active_client)
		return 0;

	bool doWpRedo = true;

	Usercmd_t* cur = &active_client->Usercmd[(active_client->CurrentCmdNumber) & 0x7F];
	Usercmd_t* old = &active_client->Usercmd[(active_client->CurrentCmdNumber - 1) & 0x7F];
	Usercmd_t* newCmd = &active_client->Usercmd[(active_client->CurrentCmdNumber + 2) & 0x7F];


	if (!cur || !old || !newCmd)
		return;

	if (start_shooting)
	{
		if (Bools::silentAimbot)
		{
			old->viewAngles[0] = ANGLE2SHORT(FinalAngles[0]);
			old->viewAngles[1] = ANGLE2SHORT(FinalAngles[1]);
			FixMovement(old, FinalAngles[1]);
		}

		if (Bools::NoSpread)
			noSpread(old);

		if (Bools::autoShoot && Bools::Aimbot)
		{
			old->buttons |= 1;
		}


		start_shooting = false;
	}

	if (Bools::aimLock) {
		if (start_shooting)
			*(float*)(0x1D17918 + 0xC) = 0.00f;
		else
			*(float*)(0x1D17918 + 0xC) = 0.022f;
	}

	if (doWpRedo)
		return wp_redo(r3, 1);

	return 0;
}