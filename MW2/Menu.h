
void men::RenderMenu()
{
	menuFunctions::DrawMenu("ZeroTwo.pw", "By Ichigo", MenuSettings::xHud, MenuSettings::YHud, MenuSettings::menuWidth, MenuSettings::menuHeight, "White", menuColors::menuGrey, MenuSettings::MenuFlash);
}

void men::RenderWatermark()
{
	/// Left side
	int offset = 10;
	menuFunctions::DrawShaderWithText(8, offset, 0.6, "ZeroTwo.pw v2", menuColors::White, true, menuColors::Main);
	//offset += 40;

	/// Right side
	offset = (Bools::Radar && pointers::Dvar_GetBool("cl_ingame") && pointers::in_game()) ? data::radar_height + 20 : 10;

	char full[128];
	snprintf(full, 128, "resolution: %ix%i", structures::ui_context.screenWidth, structures::ui_context.screenHeight);
	Vector2 screen_size_size = menuFunctions::TextSize(full, 0.6);
	menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - screen_size_size.x, offset, 0.6, full, menuColors::White, true, menuColors::Main);
	offset += 35;

	char fps[128];
	int actual_fps = (int(structures::ui_context.FPS) / 2);
	snprintf(fps, 128, "fps: %i", actual_fps > 60 ? 60 : actual_fps);
	Vector2 fps_size = menuFunctions::TextSize(fps, 0.6);
	menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - fps_size.x, offset, 0.6, fps, menuColors::White, true, menuColors::Main);
	offset += 35;

	char temp[128];
	snprintf(temp, 128, "cpu: %ic | rsx: %ic", Bools::cpu_temp, Bools::rsx_temp);
	Vector2 temp_size = menuFunctions::TextSize(temp, 0.6);
	menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - temp_size.x, offset, 0.6, temp, menuColors::White, true, menuColors::Main);
	offset += 60;

	/*if (Bools::DebugMode) {

		Vector2 aimbot_size = menuFunctions::TextSize("debug | aimbot", 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - aimbot_size.x, offset, 0.6, "debug | aimbot", menuColors::White, true, menuColors::Main);
		offset += 35;

		char aimbot_enabled[128];
		snprintf(aimbot_enabled, 128, "enabled: %s", Bools::Aimbot ? "true" : "false");
		Vector2 aimbotenabled_size = menuFunctions::TextSize(aimbot_enabled, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - aimbotenabled_size.x, offset, 0.6, aimbot_enabled, menuColors::White, true, menuColors::Main);
		offset += 35;

		char is_targeting[128];
		snprintf(is_targeting, 128, "is targeting: %s", ti_is_targeting ? "true" : "false");
		Vector2 dsa = menuFunctions::TextSize(is_targeting, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - dsa.x, offset, 0.6, is_targeting, menuColors::White, true, menuColors::Main);
		offset += 35;

		char trace[128];
		snprintf(trace, 128, "has hit trace: %s", Bools::has_hit_trace ? "true" : "false");
		Vector2 dsssa = menuFunctions::TextSize(trace, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - dsssa.x, offset, 0.6, trace, menuColors::White, true, menuColors::Main);
		offset += 35;

		char tracet[128];
		snprintf(tracet, 128, "trace fraction: %i", int(Bools::trace_fraction * 100));
		Vector2 dddsssa = menuFunctions::TextSize(tracet, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - dddsssa.x, offset, 0.6, tracet, menuColors::White, true, menuColors::Main);
		offset += 35;

		char targetd_bone[128];
		snprintf(targetd_bone, 128, "target bone: index: %i | name: %s", target_bone, AimbottagList(target_bone));
		Vector2 dsadasd = menuFunctions::TextSize(targetd_bone, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - dsadasd.x, offset, 0.6, targetd_bone, menuColors::White, true, menuColors::Main);
		offset += 60;
	}
	else
		offset += 25;*/


	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game() && Bools::serverInformation && (cg && c_entity && active_client) && cg->Health > 0) {

		if (!cg)
			return;
		if (!c_entity)
			return;
		Vector2 severinfo_size = menuFunctions::TextSize("server information", 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - severinfo_size.x, offset, 0.6, "server information", menuColors::White, true, menuColors::Main);
		offset += 35;

		char host[128];
		snprintf(host, 128, "host: %s", pointers::Dvar_GetString("party_hostname"));
		Vector2 host_size = menuFunctions::TextSize(host, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - host_size.x, offset, 0.6, host, menuColors::White, true, menuColors::Main);
		offset += 35;

		char map[128];
		snprintf(map, 128, "map: %s", pointers::Dvar_GetString("party_mapname"));
		Vector2 map_size = menuFunctions::TextSize(map, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - map_size.x, offset, 0.6, map, menuColors::White, true, menuColors::Main);
		offset += 35;

		char gamemode[128];
		snprintf(gamemode, 128, "game mode: %s", pointers::Dvar_GetString("party_gametype"));
		Vector2 gamemode_size = menuFunctions::TextSize(gamemode, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - gamemode_size.x, offset, 0.6, gamemode, menuColors::White, true, menuColors::Main);
		offset += 60;

	}

	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game() && Bools::targetInformation && ti_is_targeting && (cg && c_entity && active_client) && cg->Health > 0) {
		if (!cg)
			return;
		if (!c_entity)
			return;
		Vector2 targetinfo_size = menuFunctions::TextSize("target information", 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - targetinfo_size.x, offset, 0.6, "target information", menuColors::White, true, menuColors::Main);
		offset += 35;

		char target_name[128];
		snprintf(target_name, 128, "name: %s", ti_name);
		Vector2 target_size = menuFunctions::TextSize(target_name, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - target_size.x, offset, 0.6, target_name, menuColors::White, true, menuColors::Main);
		offset += 35;

		char target_distance[128];
		snprintf(target_distance, 128, "distance: %im", int(ti_distance) / 10);
		Vector2 distance_size = menuFunctions::TextSize(target_distance, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - distance_size.x, offset, 0.6, target_distance, menuColors::White, true, menuColors::Main);
		offset += 35;

		char visible[128];
		snprintf(visible, 128, "%svisible", ti_visible ? "" : "not ");
		Vector2 visible_size = menuFunctions::TextSize(visible, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - visible_size.x, offset, 0.6, visible, menuColors::White, true, menuColors::Main);
		offset += 35;


		char bullet_damage[128];
		snprintf(bullet_damage, 128, "bullet damage: %i", int(ti_bullet_damage));
		Vector2 dmg_size = menuFunctions::TextSize(bullet_damage, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - dmg_size.x, offset, 0.6, bullet_damage, menuColors::White, true, menuColors::Main);
		offset += 35;

		char target_bone[128];
		snprintf(target_bone, 128, "bone: %s", ti_bone);
		Vector2 bone_size = menuFunctions::TextSize(target_bone, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - bone_size.x, offset, 0.6, target_bone, menuColors::White, true, menuColors::Main);
		offset += 35;

		char target_weapon[128];
		snprintf(target_weapon, 128, "weapon: %s", ti_weapon);
		Vector2 weapon_size = menuFunctions::TextSize(target_weapon, 0.6);
		menuFunctions::DrawShaderWithText(structures::ui_context.screenWidth - 10 - 6 - weapon_size.x, offset, 0.6, target_weapon, menuColors::White, true, menuColors::Main);
		offset += 35;
	}

	/// Bottom
	const char* t[3] = { "\x16+\x11 open", "\x5/\x6 increment | \x3 select | \x2 close", "\x5/\x6 increment | \x3 select | \x2 back" };
	Vector2 open_button_size = menuFunctions::TextSize(t[data::menuOpen], 0.6);
	menuFunctions::DrawShaderWithText(8, structures::ui_context.screenHeight - 12 - open_button_size.y, 0.6, t[data::curMenu == "Main Menu" ? data::menuOpen ? 1 : 0 : 2], menuColors::White, true, menuColors::Main);
}

void men::StartMenu() {

	if (!data::menuOpen) data::menuOpen = true;
	else data::menuOpen = false;
}

void men::InitializeMenu(char* menuName) {
	data::curMenu = menuName;
	data::curScroll[data::ScrollInt] = 1;
}

const char* aa_pitches[] = { "none", "up", "down", "emotion", "fake" };
const char* aa_yaws[] = { "none", "jitter", "spin", "reverse spin jitter", "shielding", "fake" };
const char* radarScale[] = { "0.5x", "1x", "1.5x", "2x" };
const char* espBoxTypes[] = { "none", "box", "outlined", "cornered", "3D", "pyramid"};
const char* espSnaplineTypes[] = { "none", "top", "middle", "bottom" };
const char* autowallOptimisationTypes[] = { "favour accuracy", "favour capability" };
const char* autoboneOptimisationTypes[] = { "favour optimisation", "favour performance" };
void men::RenderOptions() {
	if (data::curMenu == "Main Menu") {
		switch (data::ScrollInt)
		{
		case 0:
			//data::curMenu = "Mods";
			menuFunctions::drawBoolOption("Redbox", Bools::RedBox, "forces ac130 overlay boxes");
			menuFunctions::drawBoolOption("Laser", Bools::Laser, "forces weapon laser");
			menuFunctions::drawBoolOption("Advanced uav", Bools::UAV, "forces advanced uav");
			menuFunctions::drawBoolOption("No effects", Bools::NoFX, "removes effects");
			menuFunctions::drawBoolOption("Xray", Bools::Wallhack, "sets suface flags to allow xray");
			menuFunctions::drawBoolOption("Disable map rotation", Bools::MapRotation, "disables minimap rotation");
			menuFunctions::drawBoolOption("Display debug alignments", Bools::L33T, "shows all debug alignments");
			menuFunctions::drawOption("Spoof ip", "spoofs your ip to 1.3.3.7");
			menuFunctions::drawBoolOption("Force host", Bools::ForceHost, "forces game to initiate a lobby as host (kicks you out of current game)");
			menuFunctions::drawOption("Crash host", "crashes active host");
			menuFunctions::drawBoolOption("Disable dlc", Bools::disableDLC, "disables paid dlc packs");
			SetMenu();
			break;

		case 1:
			//data::curMenu = "Aimbot";
			menuFunctions::drawBoolOption("Enable", Bools::Aimbot, "enables main aimbot");
			menuFunctions::drawCharOption("Target bone", previewTagList(Bools::targetBone), "sets the target bone the aimbot will scan for (ignored if autobone is enabled)");
			menuFunctions::drawBoolOption("Auto shoot", Bools::autoShoot, "automatically shoots targeted player");
			menuFunctions::drawBoolOption("Autowall", Bools::autoWall, "allows aimbot to shoot through penetrationable walls");
			menuFunctions::drawCharOption("Autowall strength", autowallOptimisationTypes[Bools::autoWallStrength], "changes strength of autowall. favour accuracy, favour capability");
			menuFunctions::drawBoolOption("Autobone", Bools::AutoBone, "targets best bone based by damage and distance");
			menuFunctions::drawCharOption("Autobone strength", autoboneOptimisationTypes[Bools::autoBoneStrength], "changes strength of autobone. favour optimisation, favour performance");
			menuFunctions::drawBoolOption("Anti head glitch", Bools::antiHeadGlitch, "recalculates head position of target to counter head glitching");
			menuFunctions::drawBoolOption("No spread", Bools::NoSpread, "allows aimbot to calculate spread values and reverse them");
			menuFunctions::drawBoolOption("Silent aim", Bools::silentAimbot, "removes client based viewangle aimbot");
			menuFunctions::drawBoolOption("Aimlock", Bools::aimLock, "locks your analog stick to prevent misses");
			menuFunctions::drawBoolOption("No sway", Bools::NoSway, "removes weapon spread sway");
			menuFunctions::drawBoolOption("No flinch", Bools::noFlinch, "removes screen flinch when hit");
			SetMenu();
			break;

		case 2:
			//data::curMenu = "ESP";
			menuFunctions::drawBoolOption("Enable", Bools::EnableESP, "enables base esp");
			menuFunctions::drawBoolOption("Enemies", Bools::enemyESP, "allows enemy player rendering");
			menuFunctions::drawBoolOption("Teammates", Bools::teamESP, "allows teammate player rendering");
			menuFunctions::drawSubtab("Esp colors", "enters esp colors tab");
			menuFunctions::drawBoolOption("Names", Bools::name_esp, "renders current player name");
			menuFunctions::drawCharOption("Boxes", espBoxTypes[Bools::box_esp], "renders a bounded box. box, outlined, 3D, pyramid");
			menuFunctions::drawBoolOption("Bones", Bools::bone_esp, "renders attached lines to each bone to current player");
			menuFunctions::drawCharOption("Snaplines", espSnaplineTypes[Bools::snap_lines], "renders a line to the current player. top, middle, bottom");
			menuFunctions::drawBoolOption("View angles", Bools::vangles, "renders the view angles of the current player");
			menuFunctions::drawBoolOption("Radar", Bools::Radar, "renders custom radar");
			menuFunctions::drawCharOption("Radar scale", radarScale[Bools::RadarScaling], "sets the scale of the rader. 0.5x, 1x, 1.5x, 2x");
			menuFunctions::drawBoolOption("Compass arrows", Bools::compassArrows, "renders arrows to player who you can't see");
			menuFunctions::drawBoolOption("Healthbar", Bools::DynamicHealthBar, "renders a health bar to display your health");
			SetMenu();
			break;

		case 3:
			//data::curMenu = "Visual";
			menuFunctions::drawBoolOption("Custom crosshair", Bools::customCrosshair, "renders custom crosshair");
			menuFunctions::drawBoolOption("Remove original corsshair", Bools::removeOriginalCrosshair, "removes the games original crosshair");
			menuFunctions::drawBoolOption("Fade crosshair by accuracy", Bools::fadeColorDependingOnSpread, "fades the color of the crosshair based by your spread");
			menuFunctions::drawSubtab("Crosshair color", "enters crosshair color tab");
			menuFunctions::drawBoolOption("Remove fog", Bools::removeFog, "removes fog effects");
			menuFunctions::drawBoolOption("Fullbright", Bools::fullbright, "removes shadows and ambient lighting");
			menuFunctions::DrawIntOption("Fov", 65.f, 120.f, Bools::FOV, "sets your field of view");
			menuFunctions::drawSubtab("Custom camos", "enters custom camos tab");
			SetMenu();
			break;

		case 4:
			//data::curMenu = "Anti-Aim";
			menuFunctions::drawBoolOption("Enable", Bools::enableAntiAim, "toggles base anti-aim");
			menuFunctions::drawBoolOption("Thirdperson", Bools::ThirdPerson, "enables thirdperson");
			menuFunctions::drawCharOption("Pitch type", aa_pitches[Bools::aa_pitch], "changes your up/down view angles. up, down, emotion, fake");
			menuFunctions::drawCharOption("Yaw type", aa_yaws[Bools::aa_yaw], "changes your left/right view angles. jitter, spin, spin jitter, shielding, fake");
			SetMenu();
			break;

		case 5:

			menuFunctions::drawOption("Level 70", "sets your level to 70");
			menuFunctions::DrawIntOption("Prestige", 0, 10, Bools::setPrestige, "sets your current prestige to the index");
			menuFunctions::drawOption("Unlock all", "unlocks every unlockable item");
			menuFunctions::drawOption("Modded class names", "renames class names");

			SetMenu();
			break;

		case 6:
			for (int i = 0; i < 18; i++) {
				int ip = *(int*)(0x00a1359a + 0xd8 * i + 0x50);
				int p1 = (ip & 0xff000000) >> 24;
				int p2 = (ip & 0x00ff0000) >> 16;
				int p3 = (ip & 0x0000ff00) >> 8;
				int p4 = (ip & 0x000000ff) >> 0;
				char buf[100];
				if (p1 == 0 && p2 == 0 && p3 == 0 && p4 == 0) {
					menuFunctions::drawOption("Not connected.");
					continue;
				}

				snprintf(buf, sizeof(buf), "%s - %i.%i.%i.%i\n", getName(i), p1, p2, p3, p4);

				menuFunctions::drawOption(buf);
			}

			SetMenu();
			break;

		case 7:
			//data::curMenu = "Settings";
			menuFunctions::drawBoolOption("Target information", Bools::targetInformation, "displayers aimbot target information");
			menuFunctions::drawBoolOption("Server information", Bools::serverInformation, "displays server based information");
			menuFunctions::drawSubtab("Menu colors", "enters menu colors tab");
			menuFunctions::drawBoolOption("Automatically set menu postion", Bools::setMenuPosAuto, "animates menu to the middle of your screen.");
			menuFunctions::drawOption("Reset menu position", "resets menu position back to original");
			menuFunctions::drawOption("Move up", "moves menu up by 10 pixels");
			menuFunctions::drawOption("Move down", "moves menu down by 10 pixels");
			menuFunctions::drawOption("Move left", "moves menu left by 10 pixels");
			menuFunctions::drawOption("Move right", "moves menu right by 10 pixels");

			SetMenu();
			break;
		}
	}
	else if (data::curMenu == "Menu colors") {
		menuColors::Color pink = { 1, .5, 1, 1 };
		menuColors::Color red = { 1, 72 / 255.f, 59 / 255.f, 1 };
		menuColors::Color orange = { 1.f, 131 / 255.f, 59 / 255.f, 1 };
		menuColors::Color blue = { .5, .5, 1, 1 };
		menuColors::Color green = { 51 / 255.f, 1, 71 / 255.f, 1 };
		menuColors::Color purple = { 112 / 255.f, 51 / 255.f, 1.f, 1.f };
		menuColors::Color cyan = { 51 / 255.f, 235 / 255.f, 1, 1 };
		menuColors::Color teal = { 3 / 255.f, 252 / 255.f, 190 / 255.f, 1 };
		menuColors::Color hot_pink = { 1, 0, 217 / 255.f, 1 };
		menuFunctions::drawColorRenderOption("Pink", pink, "changes menu color to pink");
		menuFunctions::drawColorRenderOption("Red", red, "changes menu color to red");
		menuFunctions::drawColorRenderOption("Orange", orange, "changes menu color to orange");
		menuFunctions::drawColorRenderOption("Blue", blue, "changes menu color to blue");
		menuFunctions::drawColorRenderOption("Green", green, "changes menu color to green");
		menuFunctions::drawColorRenderOption("Purple", purple, "changes menu color to purple");
		menuFunctions::drawColorRenderOption("Cyan", cyan, "changes menu color to cyan");
		menuFunctions::drawColorRenderOption("Teal", teal, "changes menu color to teal");
		menuFunctions::drawColorRenderOption("Hot pink", hot_pink, "changes menu color to hot pink");
		SetMenu();

	}
	else if (data::curMenu == "Esp colors") {
		menuFunctions::DrawColIntOption("Enemy esp color r", espColors::enemy_col_r, 0, "sets red value of enemy esp color");
		menuFunctions::DrawColIntOption("Enemy esp color g", espColors::enemy_col_g, 1, "sets green value of enemy esp color");
		menuFunctions::DrawColIntOption("Enemy esp color b", espColors::enemy_col_b, 2, "sets blue value of enemy esp color");

		menuFunctions::DrawColIntOption("Team esp color r", espColors::team_col_r, 0, "sets red value of team esp color");
		menuFunctions::DrawColIntOption("Team esp color g", espColors::team_col_g, 1, "sets green value of team esp color");
		menuFunctions::DrawColIntOption("Team esp color b", espColors::team_col_b, 2, "sets blue value of team esp color");

		SetMenu();
	}
	else if (data::curMenu == "Crosshair color") {
		menuFunctions::DrawColIntOption("crosshair color r", espColors::crosshair_col_r, 0, "sets red value of crosshair color");
		menuFunctions::DrawColIntOption("crosshair color g", espColors::crosshair_col_g, 1, "sets green value of crosshair color");
		menuFunctions::DrawColIntOption("crosshair color b", espColors::crosshair_col_b, 2, "sets blue value of crosshair color");
		SetMenu();
	}
	else if (data::curMenu == "Custom camos") {
		menuFunctions::drawBoolOption("Enable", Bools::customCamo, "enables custom camo (must use desert camo)");
		menuFunctions::DrawColIntOption("camo color r", espColors::camo_col_r, 0, "sets red value of camo color");
		menuFunctions::DrawColIntOption("camo color g", espColors::camo_col_g, 1, "sets green value of camo color");
		menuFunctions::DrawColIntOption("camo color b", espColors::camo_col_b, 2, "sets blue value of camo color");
		menuFunctions::drawBoolOption("Flash color", Bools::customCamoFlash, "randomises camo color");
		SetMenu();
	}

}

void men::SetFunctionOptions() {
	if (data::curMenu == "Main Menu") {
		switch (data::ScrollInt) {
		case 0:
			switch (data::curScroll[data::ScrollInt])
			{
			case 1: RedBox_F(); break;
			case 2: Laser_F(); break;
			case 3: UAV_F(); break;
			case 4: NoFX_F(); break;
			case 5: Wallhack_F(); break;
			case 6: MapRotation_F(); break;
			case 7: L33T_F(); break;
			case 8: SpoofIP(); break;
			case 9: ForceHost_F(); break;
			case 10: crashHost(); break;
			case 11: DisableDlc(); break;
			}
			break;
		case 1:
			switch (data::curScroll[data::ScrollInt])
			{
			case 1: Bools::Aimbot = !Bools::Aimbot; break;
			case 2:
				if (Bools::targetBone == 8)
					Bools::targetBone = 0;
				else
					Bools::targetBone++;
				break;
			case 3: Bools::autoShoot = !Bools::autoShoot; break;
			case 4: Bools::autoWall = !Bools::autoWall; break;
			case 5:
				if (Bools::autoWallStrength == 1)
					Bools::autoWallStrength = 0;
				else
					Bools::autoWallStrength++;
				break;
			case 6: Bools::AutoBone = !Bools::AutoBone; break;
			case 7:
				if (Bools::autoBoneStrength == 1)
					Bools::autoBoneStrength = 0;
				else
					Bools::autoBoneStrength++;
				break;
			case 8: Bools::antiHeadGlitch = !Bools::antiHeadGlitch; break;
			case 9: NOSpread_F(); break;
			case 10: Bools::silentAimbot = !Bools::silentAimbot; break;
			case 11: Bools::aimLock = !Bools::aimLock; break;
			case 12: SetNoSway(); break;
			case 13: noFlinch_F(); break;
			}
			break;
		case 2:
			switch (data::curScroll[data::ScrollInt])
			{
			case 1:	Bools::EnableESP = !Bools::EnableESP; break;
			case 2:	Bools::enemyESP = !Bools::enemyESP; break;
			case 3:	Bools::teamESP = !Bools::teamESP; break;
			case 4: InitializeMenu("Esp colors"); break;
			case 5:	Bools::name_esp = !Bools::name_esp; break;
			case 6:
				if (Bools::box_esp == 5)
					Bools::box_esp = 0;
				else
					Bools::box_esp++;
				break;
			case 7:	Bools::bone_esp = !Bools::bone_esp; break;
			case 8:
				if (Bools::snap_lines == 3)
					Bools::snap_lines = 0;
				else
					Bools::snap_lines++;
				break;
				break;
			case 9:	Bools::vangles = !Bools::vangles; break;
			case 10:	Bools::Radar = !Bools::Radar; break;
			case 11:
				if (Bools::RadarScaling == 3)
					Bools::RadarScaling = 0;
				else
					Bools::RadarScaling++;
				break;
			case 12: Bools::compassArrows = !Bools::compassArrows; break;
			case 13: Bools::DynamicHealthBar = !Bools::DynamicHealthBar; break;
			}
			break;
		case 3:
			switch (data::curScroll[data::ScrollInt]) {
			case 1: Bools::customCrosshair = !Bools::customCrosshair; break;
			case 2: Bools::removeOriginalCrosshair = !Bools::removeOriginalCrosshair; break;
			case 3: Bools::fadeColorDependingOnSpread = !Bools::fadeColorDependingOnSpread; break;
			case 4: InitializeMenu("Crosshair color"); break;
			case 5: removeFog_F(); break;
			case 6: fullbright_F(); break;
			case 7:
				if (Bools::FOV >= 120.f)
					Bools::FOV = 65.f;
				else
					Bools::FOV += 1.5f;

				//	*(float*)(0x1D17F90 + 0xC) = Bools::FOV;
				break;
			case 8: InitializeMenu("Custom camos");
			}
			break;
		case 4:
			switch (data::curScroll[data::ScrollInt])
			{
			case 1:	Bools::enableAntiAim = !Bools::enableAntiAim; break;
			case 2: ThirdPerson_F(); break;
			case 3:
				if (Bools::aa_pitch == 4)
					Bools::aa_pitch = 0;
				else
					Bools::aa_pitch++;
				break;
			case 4:
				if (Bools::aa_yaw == 5)
					Bools::aa_yaw = 0;
				else
					Bools::aa_yaw++;
				break;
			}
			break;
		case 5:

			switch (data::curScroll[data::ScrollInt])
			{
			case 1: Level70_F(); break;
			case 2: MaxPrestige_F(); break;
			case 3: UnlockAll_F(); break;
			case 4: ClassNames(); break;
			}

			break;

			// clients has shit lol
		case 7:
			switch (data::curScroll[data::ScrollInt])
			{
			case 1: Bools::targetInformation = !Bools::targetInformation; break;
			case 2: Bools::serverInformation = !Bools::serverInformation; break;
			case 3: InitializeMenu("Menu colors"); break;
			case 4: Bools::setMenuPosAuto = !Bools::setMenuPosAuto; break;
			case 5: ResetMenuPos(); break;
			case 6: MenuSettings::YHud -= 10; break;
			case 7: MenuSettings::YHud += 10; break;
			case 8: MenuSettings::xHud -= 10; break;
			case 9: MenuSettings::xHud += 10; break;
			}
			break;
		}
	}
	else if (data::curMenu == "Menu colors")
	{

		switch (data::curScroll[data::ScrollInt]) {
		case 1:
			menuColors::inputtedColor.r = 1;// = { 1, .5, 1, 1.000f };
			menuColors::inputtedColor.g = .5;
			menuColors::inputtedColor.b = 1;
			break;
		case 2:
			//menuColors::inputtedColor = { 1, 72 / 255.f, 59 / 255.f, 1 }; 
			menuColors::inputtedColor.r = 1;
			menuColors::inputtedColor.g = 72 / 255.f;
			menuColors::inputtedColor.b = 59 / 255.f;
			break;
		case 3:
			//menuColors::inputtedColor = { 1, 131 / 255.f, 59 / 255.f, 1 }; break;
			menuColors::inputtedColor.r = 1.f;
			menuColors::inputtedColor.g = 131 / 255.f;
			menuColors::inputtedColor.b = 59 / 255.f;
			break;
		case 4:
			//menuColors::inputtedColor = { 0.5, 0.5, 1, 1 }; 
			menuColors::inputtedColor.r = 0.5f;
			menuColors::inputtedColor.g = 0.5f;
			menuColors::inputtedColor.b = 1.f;
			break;
		case 5:
			menuColors::inputtedColor.r = 51 / 255.f;
			menuColors::inputtedColor.g = 1.f;
			menuColors::inputtedColor.b = 71 / 255.f;
			break;
		case 6:
			menuColors::inputtedColor.r = 112 / 255.f;
			menuColors::inputtedColor.g = 51 / 255.f;
			menuColors::inputtedColor.b = 1.f;
			break;
		case 7:
			menuColors::inputtedColor.r = 51 / 255.f;
			menuColors::inputtedColor.g = 235 / 255.f;
			menuColors::inputtedColor.b = 1.f;
			break;
		case 8:
			menuColors::inputtedColor.r = 3 / 255.f;
			menuColors::inputtedColor.g = 252 / 255.f;
			menuColors::inputtedColor.b = 190 / 255.f;
			break;
		case 9:
			menuColors::inputtedColor.r = 1;
			menuColors::inputtedColor.g = 0;
			menuColors::inputtedColor.b = 217 / 255.f;
			break;
		}
	}
	else if (data::curMenu == "Esp colors") {
		switch (data::curScroll[data::ScrollInt]) {
		case 1:
			if (espColors::enemy_col_r > 1.f)
				espColors::enemy_col_r = 0.f;
			else
				espColors::enemy_col_r += 0.02;
			break;
		case 2:
			if (espColors::enemy_col_g > 1.f)
				espColors::enemy_col_g = 0.f;
			else
				espColors::enemy_col_g += 0.02;
			break;
		case 3:
			if (espColors::enemy_col_b > 1.f)
				espColors::enemy_col_b = 0.f;
			else
				espColors::enemy_col_b += 0.02;
			break;
		case 4:
			if (espColors::team_col_r > 1.f)
				espColors::team_col_r = 0.f;
			else
				espColors::team_col_r += 0.02;
			break;
		case 5:
			if (espColors::team_col_g > 1.f)
				espColors::team_col_g = 0.f;
			else
				espColors::team_col_g += 0.02;
			break;
		case 6:
			if (espColors::team_col_b > 1.f)
				espColors::team_col_b = 0.f;
			else
				espColors::team_col_b += 0.02;
			break;
		}
	}
	else if (data::curMenu == "Crosshair color") {
		switch (data::curScroll[data::ScrollInt]) {
		case 1:
			if (espColors::crosshair_col_r > 1.f)
				espColors::crosshair_col_r = 0.f;
			else
				espColors::crosshair_col_r += 0.02;
			break;
		case 2:
			if (espColors::crosshair_col_g > 1.f)
				espColors::crosshair_col_g = 0.f;
			else
				espColors::crosshair_col_g += 0.02;
			break;
		case 3:
			if (espColors::crosshair_col_b > 1.f)
				espColors::crosshair_col_b = 0.f;
			else
				espColors::crosshair_col_b += 0.02;
			break;
		}
	}
	else if (data::curMenu == "Custom camos") {
		switch (data::curScroll[data::ScrollInt]) {
		case 1: Bools::customCamo = !Bools::customCamo; break;
		case 2:
			if (espColors::camo_col_r > 1.f)
				espColors::camo_col_r = 0.f;
			else
				espColors::camo_col_r += 0.02;
			break;
		case 3:
			if (espColors::camo_col_g > 1.f)
				espColors::camo_col_g = 0.f;
			else
				espColors::camo_col_g += 0.02;
			break;
		case 4:
			if (espColors::camo_col_b > 1.f)
				espColors::camo_col_b = 0.f;
			else
				espColors::camo_col_b += 0.02;
			break;
		case 5: Bools::customCamoFlash = !Bools::customCamoFlash; break;
		}
	}
}

void men::ExitMenu(int exOpt) {
	if (data::curMenu == "Main Menu" && exOpt == 0) men::StartMenu();
	else if (data::curMenu == "Menu colors") InitializeMenu("Main Menu");
	else if (data::curMenu == "Esp colors") InitializeMenu("Main Menu");
	else if (data::curMenu == "Crosshair color") InitializeMenu("Main Menu");
	else if (data::curMenu == "Custom camos") InitializeMenu("Main Menu");
}

float tab_animations[7];
void tab(char* name, int x, int y, int w, int h, int index, int interval)
{
	Vector2 label_size = menuFunctions::TextSize(name, 0.55);

	bool is_on_tab = (index == interval);

	if (is_on_tab && tab_animations[index] < 1.f)
	{
		tab_animations[index] += 0.05f;
	}
	else if (!is_on_tab) {

		if (tab_animations[index] > 0.f)
			tab_animations[index] -= 0.05f;
	}

	menuColors::Color menuMainAlphaModulated = { menuColors::menuMain.r, menuColors::menuMain.g, menuColors::menuMain.b, tab_animations[index] * data::menuAlpha };
	menuFunctions::DrawText(name, x + (w / 2) - (label_size.x / 2), y + label_size.y - 1, FONT_NORMAL, 0.55, menuColors::menuWhite);
	menuFunctions::DrawText(name, x + (w / 2) - (label_size.x / 2), y + label_size.y - 1, FONT_NORMAL, 0.55, menuMainAlphaModulated);

}

void men::RenderMenuText()
{

	if (data::curMenu == "Main Menu") {
		char* pre_game_tabs[8] = { "Mods", "Aimbot", "Players", "Visual", "Antiaim", "Stats", "Clients", "Misc" };
		char* in_game_tabs[9] = { "Mods", "Aimbot", "Players", "Visual", "Antiaim", "Stats", "Clients", "Misc", "Host" };

		int tabs_to_render = isHost() ? 9 : 8;
		bool should_render_ingame_tabs = pointers::Dvar_GetBool("cl_ingame") && pointers::in_game();
		int width = MenuSettings::menuWidth / tabs_to_render;
		for (int i = 0; i < tabs_to_render; i++) {
			tab(should_render_ingame_tabs ? in_game_tabs[i] : pre_game_tabs[i], MenuSettings::xHud + (width * i), MenuSettings::YHud + 20, width, 20, i, data::ScrollInt);
		}

		// min area
		int min = 0;
		// the max size you'd want
		int max = 8;
		// get your min max xD
		int min_max = max - min;
		// create your min delta by taking away the min with your actual value
		const float value_min_delta = data::ScrollInt - min;
		// create your fraction by dividing your min delta with your min max and timeing it by your max size you actually want
		const float desired_fraction = (value_min_delta / min_max) * (MenuSettings::menuWidth);
		static float current_fraction = 0.f;
		// create the delta fraction
		const float delta = desired_fraction - current_fraction;
		// if its not the same animate.
		if (desired_fraction != current_fraction)
			current_fraction += delta * 0.11f;

		menuFunctions::DrawShader(MenuSettings::xHud + current_fraction, MenuSettings::YHud + 40, width, 1, menuColors::menuMain, "white");
	}
	else {
		tab(data::curMenu, MenuSettings::xHud, MenuSettings::YHud + 20, MenuSettings::menuWidth, 20, 1, 1);
		menuFunctions::DrawShader(MenuSettings::xHud, MenuSettings::YHud + 40, MenuSettings::menuWidth, 1, menuColors::menuMain, "white");
	}

}