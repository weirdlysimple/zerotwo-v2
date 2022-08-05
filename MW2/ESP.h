#pragma once
#pragma once
bool ESP;
int LocalPlayer;

Vector3 SubstractVector(Vector3 v1, Vector3 v2) {
	Vector3 r;
	r.x = v1.x - v2.x;
	r.y = v1.y - v2.y;
	r.z = v1.z - v2.z;
	return r;
}

float DotProduct(Vector3& a, Vector3& b) {
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

bool WorldToScreen(Vector3 World, float* ScreenX, float* ScreenY)
{
	Vector3 Position = SubstractVector(World, cg->RefDef.viewOrigin);
	Vector3 Transform;

	Transform.x = DotProduct(Position, cg->RefDef.viewAxis[1]);
	Transform.y = DotProduct(Position, cg->RefDef.viewAxis[2]);
	Transform.z = DotProduct(Position, cg->RefDef.viewAxis[0]);

	if (Transform.z < 0.1f)
		return false;

	Vector2 Center = Vector2(cg->RefDef.Width / 2.0f, cg->RefDef.Height / 2.0f);

	*ScreenX = Center.x * (1 - (Transform.x / cg->RefDef.Fov.x / Transform.z));
	*ScreenY = Center.y * (1 - (Transform.y / cg->RefDef.Fov.y / Transform.z));

	return true;
}



void drawLine(float x1, float y1, float x2, float y2, float size, menuColors::Color col)
{
	float x, y, angle, l1, l2, h1;
	h1 = (y2 - y1);
	l1 = (x2 - x1);
	l2 = sqrtf(l1 * l1 + h1 * h1);
	x = (x1 + ((l1 - l2) / 2));
	y = (y1 + (h1 / 2));
	angle = pointers::Atan(h1, l1) * (180 / 3.14159265358979323846);
	pointers::R_AddCmdDrawStretchPicRotateXY(x, y, l2, size, 0.0f, 0.0f, 0.0f, 0.0f, angle, (float*)&col, pointers::MaterialRegisterHandle("white", 0));
}

void DrawBone(int ent, const char* tagname1, const char* tagname2, menuColors::Color col)
{
	Vector3 Origin1 = GetPos(ent, tagname1), Origin2 = GetPos(ent, tagname2);

	Vector2 Loc1, Loc2;
	if (WorldToScreen(Origin1, &Loc1.x, &Loc1.y) && WorldToScreen(Origin2, &Loc2.x, &Loc2.y)) {
		drawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, 1, col);
	}
}

void DoAllBones(int i, menuColors::Color ESPColor)
{
	DrawBone(i, "j_knee_le", "pelvis", ESPColor);
	DrawBone(i, "j_elbow_ri", "j_wrist_ri", ESPColor);
	DrawBone(i, "j_neck", "j_elbow_ri", ESPColor);
	DrawBone(i, "j_ankle_ri", "j_knee_ri", ESPColor);
	DrawBone(i, "j_elbow_le", "j_wrist_le", ESPColor);
	DrawBone(i, "j_ankle_le", "j_knee_le", ESPColor);
	DrawBone(i, "j_knee_ri", "pelvis", ESPColor);
	DrawBone(i, "pelvis", "j_neck", ESPColor);
	DrawBone(i, "j_neck", "j_elbow_le", ESPColor);
	DrawBone(i, "j_neck", "j_head", ESPColor);
}

Vector3 GetPlayerOrigin(int c) {
	return c_entity[c].Origin;
}

bool isFFA()
{
	int serverinfo = *(int*)(0x915258);
	char ffa = *(char*)(serverinfo + 0x21);
	if (ffa == 0x6D)
	{
		return true;
	}
	return false;
}

void outlined_box(int x, int y, int w, int h, menuColors::Color col) {
	menuFunctions::DrawShader(x - 1, y - 1, w, 1, col, "white");
	menuFunctions::DrawShader(x - 1, y  + h - 1, w, 1, col, "white");

	menuFunctions::DrawShader(x - 1, y, 1, h - 1, col, "white");
	menuFunctions::DrawShader(x + w - 1 , y - 1, 1, h + 1, col, "white");
}
void box(int x, int y, int w, int h, menuColors::Color col, menuColors::Color outer_col) {
	outlined_box(x, y, w, h, col);

	outlined_box(x - 1, y - 1, w + 2, h + 2, outer_col);
	outlined_box(x + 1, y + 1, w - 2, h - 2, outer_col);
}

float GetBoxWidth(c_entity_t ent) {
	if (ent.Flags & FLAG_PRONE)
		return 35;
	else return 17;
}

float GetBoxHeight(c_entity_t ent) {
	if (ent.Flags & FLAG_PRONE)
		return 25;
	else if (ent.Flags & FLAG_CROUCHED)
		return 55;
	else return 70;
}
void MakeLines(Vector3 Origin, float X1, float Y1, float Z1, float X2, float Y2, float Z2, menuColors::Color Color1)
{
	Vector2 Screen1, Screen2;
	Vector3 Origin1(Origin.x + X1, Origin.y + Y1, (Origin.z + Z1) - 5);
	Vector3 Origin2(Origin.x + X2, Origin.y + Y2, (Origin.z + Z2) - 5);
	if (WorldToScreen(Origin1, &Screen1.x, &Screen1.y) && WorldToScreen(Origin2, &Screen2.x, &Screen2.y)) {
		drawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, 1, Color1);
	}
}

void Draw3DBox(int client, menuColors::Color sColor)
{
	Vector3 Center = c_entity[client].Origin;
	float W = GetBoxWidth(c_entity[client]), H = GetBoxHeight(c_entity[client]);

	MakeLines(Center, -W, -W, 0, -W + (W / 2), -W, 0, sColor);
	MakeLines(Center, W / 2, -W, 0, W, -W, 0, sColor);
	MakeLines(Center, -W, -W, 0, -W, -W + (W / 2), 0, sColor);
	MakeLines(Center, -W, W - (W / 2), 0, -W, W, 0, sColor);
	MakeLines(Center, W, -W + (W / 2), 0, W, -W, 0, sColor);
	MakeLines(Center, W, W - (W / 2), 0, W, W, 0, sColor);
	MakeLines(Center, -W + (W / 2), W, 0, -W, W, 0, sColor);
	MakeLines(Center, W, W, 0, W - (W / 2), W, 0, sColor);
	MakeLines(Center, -W, -W, 0, -W, -W, H / 6, sColor);
	MakeLines(Center, -W, -W, H, -W, -W, H - (H / 6), sColor);
	MakeLines(Center, -W, W, 0, -W, W, H / 6, sColor);
	MakeLines(Center, -W, W, H, -W, W, H - (H / 6), sColor);
	MakeLines(Center, W, -W, 0, W, -W, H / 6, sColor);
	MakeLines(Center, W, -W, H, W, -W, H - (H / 6), sColor);
	MakeLines(Center, W, W, 0, W, W, H / 6, sColor);
	MakeLines(Center, W, W, H, W, W, H - (H / 6), sColor);
	MakeLines(Center, -W, -W, H, -W + (W / 2), -W, H, sColor);
	MakeLines(Center, W / 2, -W, H, W, -W, H, sColor);
	MakeLines(Center, -W, -W, H, -W, -W + (W / 2), H, sColor);
	MakeLines(Center, -W, W - (W / 2), H, -W, W, H, sColor);
	MakeLines(Center, W, -W + (W / 2), H, W, -W, H, sColor);
	MakeLines(Center, W, W - (W / 2), H, W, W, H, sColor);
	MakeLines(Center, -W + (W / 2), W, H, -W, W, H, sColor);
	MakeLines(Center, W, W, H, W - (W / 2), W, H, sColor);

}
void DrawTriBox(int client, menuColors::Color sColor)
{
	Vector3 Center = c_entity[client].Origin;
	float W = GetBoxWidth(c_entity[client]), H = GetBoxHeight(c_entity[client]);
	W *= 1.5;
	H *= 1.25;
	MakeLines(Center, -W, -W, 0, W, -W, 0, sColor);
	MakeLines(Center, -W, -W, 0, -W, W, 0, sColor);
	MakeLines(Center, W, W, 0, W, -W, 0, sColor);
	MakeLines(Center, W, W, 0, -W, W, 0, sColor);
	MakeLines(Center, -W, -W, 0, 0, 0, H, sColor);
	MakeLines(Center, -W, W, 0, 0, 0, H, sColor);
	MakeLines(Center, W, -W, 0, 0, 0, H, sColor);
	MakeLines(Center, W, W, 0, 0, 0, H, sColor);
}
void renderESP(int local) {

	if (cg->Health > 0)
	{
		for (int i = 0; i < 18; i++)
		{
			if (c_entity[i].Handle != GetIndex())
			{
				if (c_entity[i].Alive)
				{
					Vector2 Screen, Origin, Screen2;
					Vector3 helmet = GetPos(i, "j_head");
					Vector3 foot = GetPos(i, "j_ankle_le");
					Vector3 NeckOrigin = GetPos(i, "j_neck");
					Vector2 FootPos;
					Vector2 HeadPos;
					Vector2 FeetLocation;
					Vector3 FootOrigin = c_entity[i].Origin;
					Vector2 HeadLocation;
					Vector2 NeckLocation;
					FootOrigin.z -= 5;
					helmet.z += 10;
					clientinfo_t client = cg->ClientInfo[i];
					c_entity_t cent = c_entity[i];


					float correctY = HeadPos.y - 36000 / Distance3D(c_entity[local].Origin, c_entity[i].Origin);
					WorldToScreen(c_entity[i].Origin, &Origin.x, &Origin.y);
					if (WorldToScreen(c_entity[i].Origin, &Screen.x, &Screen.y) && WorldToScreen(helmet, &Screen2.x, &Screen2.y)
						&& WorldToScreen(helmet, &HeadPos.x, &HeadPos.y) && WorldToScreen(helmet, &HeadPos.x, &HeadPos.y)
						&& WorldToScreen(FootOrigin, &FeetLocation.x, &FeetLocation.y) && WorldToScreen(helmet, &HeadLocation.x, &HeadLocation.y)
						&& WorldToScreen(NeckOrigin, &NeckLocation.x, &NeckLocation.y))
					{

						float fHeight = FeetLocation.y - HeadLocation.y;
						float fWidth;
						if (c_entity[i].Flags & 0x08) //prone lol
							fWidth = fHeight / 0.9;
						else
							fWidth = fHeight / 1.95;

						float calculateHeight = helmet.z - c_entity[i].Origin.z;
						int BoxHeight = abs(FootPos.y - HeadPos.y);

						if (Bools::EnableESP)
						{
							menuColors::Color esp_col = { espColors::enemy_col_r, espColors::enemy_col_g , espColors::enemy_col_b, 1 };
							isSameTeam(cg->ClientNumber, i) ? esp_col = { espColors::team_col_r, espColors::team_col_g , espColors::team_col_b, 1 } : esp_col = { espColors::enemy_col_r, espColors::enemy_col_g , espColors::enemy_col_b, 1 };
							if ((!isSameTeam(cg->ClientNumber, i) || isFFA()) && Bools::enemyESP)
							{
								Bools::should_draw_esp = true;
							}
							else if (isSameTeam(cg->ClientNumber, i) && Bools::teamESP)
								Bools::should_draw_esp = true;

							if (Bools::should_draw_esp)
							{

								int box_x = (FeetLocation.x - (fWidth / 2)) - 1;
								int box_y = (FeetLocation.y - fHeight) - 1;
								int box_w = fWidth;
								int box_h = fHeight;

								if (Bools::bone_esp)
								{
									DoAllBones(i, esp_col);
								}
								//int health = cg->ClientInfo[i].health
								if (Bools::name_esp) {
									Vector2 player_name_size = menuFunctions::TextSize(client.Name, 0.5);
									menuFunctions::DrawText(client.Name, box_x + (box_w / 2) - (player_name_size.x / 2), box_y, FONT_NORMAL, 0.5, esp_col);
								}
								if (Bools::snap_lines > 0)
									drawLine(1280 / 2, Bools::snap_lines == 1 ? 0 : Bools::snap_lines == 2 ? structures::ui_context.screenHeight / 2 : structures::ui_context.screenHeight, box_x + (box_w / 2), box_y + box_h, 1, esp_col);


								if (Bools::health_esp) {

								}

								switch (Bools::box_esp) {
								case 0:
									break;
								case 1:
									//left
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, fWidth, 1, esp_col, "white");
									//bottom
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, FeetLocation.y - 1, fWidth, 1, esp_col, "white");
									//top
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight), 1, fHeight - 1, esp_col, "white");
									//right
									menuFunctions::DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 1, fHeight + 1, esp_col, "white");
									break;

								case 2:
									box((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, fWidth, fHeight, esp_col, menuColors::dimmedBlack);
									


									break;
								case 3:
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, (fWidth / 4) + 2, 1, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, FeetLocation.y - 1, (fWidth / 4) + 2, 1, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 1, (fWidth / 4) + 2, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x - (fWidth / 2)) - 1, (FeetLocation.y - (fWidth / 4)) - 2, 1, (fWidth / 4) + 2, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - fHeight) - 1, 1, (fWidth / 4) + 2, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))) - 2, (FeetLocation.y - fHeight) - 1, (fWidth / 4) + 2, 1, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x + ((fWidth / 2) - (fWidth / 4))) - 2, FeetLocation.y - 1, (fWidth / 4) + 2, 1, esp_col, "white");
									menuFunctions::DrawShader((FeetLocation.x + (fWidth / 2)) - 1, (FeetLocation.y - (fWidth / 4)) - 2, 1, (fWidth / 4) + 2, esp_col, "white");
									break;
								case 4:
									Draw3DBox(i, esp_col);
									break;
								case 5:
									DrawTriBox(i, esp_col);
									break;
								}

								if (Bools::vangles) {
									Vector2 Screen1, Screen2;
									float Scale = 150;
									Vector3 from = GetPos(i, "j_neck");
									Vector3 to = AnglesToFoward(from, cg[i].ViewAngle, Scale);

									if (WorldToScreen(from, &Screen1.x, &Screen1.y)) {

										if (WorldToScreen(to, &Screen2.x, &Screen2.y)) {

											drawLine(Screen1.x, Screen1.y, Screen2.x, Screen2.y, 1.f, esp_col);
										}
									}

								}
							}

							Bools::should_draw_esp = false;
						}

					}

				}
			}

		}
	}
}

int Widths = 0;
int Heights = 0;
bool is1080 = false;
bool is720 = false;
void Radar(int Client)
{

	if (Bools::Radar)
	{
		if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
		{
			float scaling[4] = { 0.5f, 1.f, 1.5f, 2.f };

			float white[4] = { 1, 1, 1, 1 };
			Vector2 RadarXY, RadarCenter, Center;
			float radar_width = 200 * scaling[Bools::RadarScaling];
			float radar_height = 200 * scaling[Bools::RadarScaling];
			Center.x = cg->RefDef.Width / 2;
			Center.y = cg->RefDef.Height / 2;
			RadarCenter.x = (Center.x * 2) - radar_width - 30;
			RadarCenter.y = 10 + (radar_height / 2);

			data::radar_height = radar_height;
			menuFunctions::DrawShaderWithOutline(cg->RefDef.Width - 10 - radar_width, 10, radar_width, radar_height, menuColors::Main, menuColors::dimmedBlack, 1);

			rectDef_s info = { RadarCenter.x - (radar_width / 2) + 1, 11, radar_width - 2, radar_height - 2, 0, 0 };
			//pointers::CG_CompassDrawPlayerMap(0, COMPASS_TYPE_PARTIAL, &info, &info, pointers::Material_RegisterHandle("white", 0), white);


			for (int i = 0; i < 18; i++)
			{
				int Type = c_entity[i].Type;
				int RadarX, RadarY;

				RadarX = GetPlayerOrigin(cg->ClientNumber).x - GetPlayerOrigin(i).x;
				RadarY = GetPlayerOrigin(cg->ClientNumber).y - GetPlayerOrigin(i).y;

				float Angle = cg->ViewAngle.y / 180 * 3.141;

				float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
				float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);


				float FinalX = RadarCenter.x + RotateX / 8.1232;//9.0686;
				float FinalY = RadarCenter.y + RotateY / 10.4686; //12.5977;


				if (FinalX < RadarCenter.x - radar_width / 2) FinalX = (RadarCenter.x - radar_width / 2) - 8;
				if (FinalY < RadarCenter.y - radar_height / 2) FinalY = (RadarCenter.y - radar_height / 2) - 8;

				if (FinalX > RadarCenter.x + radar_width / 2) FinalX = (RadarCenter.x + radar_width / 2) - 12;
				if (FinalY > RadarCenter.y + radar_height / 2) FinalY = (RadarCenter.y + radar_height / 2) - 12;


				if (i != Client)
				{
					if (Type == 1) { // 1 = ET_PLAYER

						if (c_entity[i].Alive)
						{

							if (!isSameTeam(cg->ClientNumber, i) || isFFA())
							{
								Bools::should_draw_radar = true;
							}

							if (Bools::should_draw_radar)
							{
								menuColors::Color esp_col = { espColors::enemy_col_r, espColors::enemy_col_g , espColors::enemy_col_b, 1 };
								menuFunctions::UiDrawShader(FinalX + (radar_width / 2) + 20, FinalY, 20, 20, (cg->ViewAngle.y - cg->ClientInfo[i].viewAngle.y), isSameTeam(cg->ClientNumber, i) ? menuColors::Blue : esp_col, "compassping_player");

								menuFunctions::UiDrawShader(cg->RefDef.Width - 10 - (radar_width / 2) - 10, 10 + (radar_height / 2) - 10, 20, 20, 0, menuColors::White, "compassping_player");
							}

						}
					}
				}

			}
		}
		Bools::should_draw_radar = false;
	}
}
double atan_lol(double x, int n)
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
double atan2_lol(double y, double x)
{
	double u = atan_lol(y / x, 24);
	if (x < 0.0)// 2nd, 3rd quadrant
	{
		if (u > 0.0)// will go to 3rd quadrant
			u -= PI;
		else
			u += PI;
	}
	return u;
}
void OutofFOVArrows(int Client)
{
	if (Bools::compassArrows)
	{
		if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
		{
			Vector2 cCenter;
			int fCompassSize = 175;
			cCenter.x = cg->RefDef.Width / 2;
			cCenter.y = cg->RefDef.Height / 2;
			int dwWidth = 20; int dwHeight = 20;

			for (int i = 0; i < 18; i++)
			{
				int Type = c_entity[i].Type;
				int RadarX, RadarY;

				RadarX = GetPlayerOrigin(cg->ClientNumber).x - GetPlayerOrigin(i).x;
				RadarY = GetPlayerOrigin(cg->ClientNumber).y - GetPlayerOrigin(i).y;

				float Angle = cg->ViewAngle.y / 180 * 3.141;

				float RotateX = RadarY * cosf(Angle) - RadarX * sinf(Angle);
				float RotateY = RadarX * cosf(Angle) + RadarY * sinf(Angle);

				float FinalX = cCenter.x + RotateX;
				float FinalY = cCenter.y + RotateY;

				float angle = atan2_lol(RotateX, RotateY) * (360 / M_PI);
				float FinalA = (FinalY > cCenter.y ? -angle - 180.0f : -angle);

				if (FinalA < 0)
					FinalA += 360.0f;

				double radians = (M_PI / 180) * (FinalA - 90.0f);
				float CircleX = cCenter.x + (cosf(radians) * fCompassSize);
				float CircleY = cCenter.y + (sinf(radians) * fCompassSize);


				if (i != Client)
				{
					if (Type == 1) { // 1 = ET_PLAYER

						if (c_entity[i].Alive)
						{
							if (!isSameTeam(cg->ClientNumber, i) || isFFA())
							{
								menuColors::Color enemy_col = { espColors::enemy_col_r, espColors::enemy_col_g , espColors::enemy_col_b, 1 };
								menuColors::Color team_col = { espColors::team_col_r, espColors::team_col_g , espColors::team_col_b, 1 };
								menuFunctions::UiDrawShader(CircleX - dwWidth, CircleY - dwHeight, dwWidth, dwHeight, FinalA, (!isSameTeam(cg->ClientNumber, i) || isFFA()) ? enemy_col : team_col, "hud_grenadepointer");
							}
						}
					}
				}

			}
		}
	}

}


void ESPHook()
{
	if (!cg || !c_entity || !active_client)
		return;


	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game() && cg->Health > 0)
	{
		
		LocalPlayer = cg->ClientNumber;
		renderESP(LocalPlayer);
		Radar(LocalPlayer);
		OutofFOVArrows(LocalPlayer);
	}
}