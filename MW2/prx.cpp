#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <deque>
#include <cellstatus.h>
#include <sys/prx.h>
#include <cell/sysmodule.h>
#include <sys/process.h>
#include <sys/ppu_thread.h>
#include <sys/syscall.h>
#include <sys/tty.h>
#include <ppu_intrinsics.h>
#include <ctype.h>
#include <sys/tty.h>
#include <sys/timer.h>
#include <fastmath.h>
#include <cell/pad.h>
#include <sysutil\sysutil_msgdialog.h>
#include <sys\sys_time.h>
#include <time.h>
#include <cell/cell_fs.h>
#include <cell/http.h>
#include "XOR.h"
#include "PS3.h"
#include "printf.h"
#include "Strucs.h"
#include "MenuFunctions.h"
bool DrawSnapLine;
bool EnabledESP = false;
#include "easing.h"
#include "Aimbot.h"
#include "ESP.h"
#include "server.h"
#include "DynamicHealthBar.h"
#include "customCrosshair.h"
#include "onScreenMessage.h"
#include "MenuSet.h"
#include "Menu.h"
SYS_MODULE_INFO(MW2, 0, 1, 1);
SYS_MODULE_START(_MW2_prx_entry);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_MW2_export_function, LIBNAME);
int Client;
bool slideOpen = false;
bool first_run = false;

void MenuInit() {

	if (!first_run) {
		for (int i = 0; i < 255; i++) {
			data::menu_preview[i] = "no preview";
		}
		for (int i = 0; i < 8; i++) {
			data::curScroll[i] = 1;
		}
		first_run = true;
	}

	while (!first_run)
		sys_timer_usleep(5 * 1000);

	structures::time++;
	flash(&menuColors::dflash);
	flashFaster(&menuColors::dflash2);
	customCrosshair();
	men::RenderWatermark();
	if (data::menuOpen && data::menuAlpha < 1.f)
	{
		data::menuAlpha += 0.04f;
	}
	else if (!data::menuOpen) {

		if (data::menuAlpha > 0.f)
			data::menuAlpha -= 0.04f;
	}

	menuFunctions::HandleMenuAlpha();

	menuFunctions::HandleMenuSize();

	menuFunctions::HandleMenuPos();

	if (data::menuAlpha > 0.01f)
	{
		Bools::max_scroll = data::maxScroll;
		data::maxScroll = 0;
		men::RenderMenu();
	}
	
	if (data::menuOpen) {
		menuFunctions::Scroller();
		menuFunctions::HandleColors();
		men::RenderOptions();
		men::RenderMenuText();
		menuFunctions::HandleScrollAnimation();
		//SliderOpen();
		data::menuTimer += 1;
		if (data::menuTimer > (pointers::Dvar_GetBool("cl_ingame") ? 50 : 25)) {
			if (structures::ButtonPressed(structures::DpadUp) && data::menuOpen) {
				data::curScroll[data::ScrollInt]--;
				if (data::curScroll[data::ScrollInt] < 1) data::curScroll[data::ScrollInt] = data::maxScroll;
				data::menuTimer = 0;
			}
			else if (structures::ButtonPressed(structures::DpadDown) && data::menuOpen) {
				data::curScroll[data::ScrollInt]++;
				if (data::curScroll[data::ScrollInt] > data::maxScroll) data::curScroll[data::ScrollInt] = 1;
				data::menuTimer = 0;
			}
			else if (structures::ButtonPressed(structures::Square) && data::menuOpen) {
				men::SetFunctionOptions();
				data::menuTimer = 0;
			}
			else if (structures::ButtonPressed(structures::R1) && data::menuOpen && (data::curMenu == "Main Menu")) {
				data::lastMenuSize = MenuSettings::menuHeight;
				data::ScrollInt++;
				//data::curScroll[data::ScrollInt] = 1;
				if (data::ScrollInt > data::MaxScrollInt) data::ScrollInt = 0;
				data::menuTimer = 0;
			}
			else if (structures::ButtonPressed(structures::L1) && data::menuOpen && (data::curMenu == "Main Menu")) {
				data::lastMenuSize = MenuSettings::menuHeight;
				data::ScrollInt--;
				//data::curScroll[data::ScrollInt] = 1;
				if (data::ScrollInt < 0) data::ScrollInt = data::MaxScrollInt;
				data::menuTimer = 0;
			}
			else if (structures::ButtonPressed(structures::Circle) && data::menuOpen ) {
				if (data::curMenu == "Main Menu") {
					men::ExitMenu(0);
				}
				else
					men::ExitMenu(1);
				//data::menuOpen = false;
				data::menuTimer = 0;
			}
		}
	}
	else
	{

		if (structures::ButtonPressed(structures::R3) && structures::ButtonPressed(structures::Left)) {
			men::StartMenu();
			data::menuTimer = 0;
		}
	}


}

void Menu_PaintAll_Internal_Stub(int UiContext, int init)
{
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();

}

void MenuPaint_All(int LocalClientNum, int dc_)
{

	menuMiscFunctions::getStructs();
	SetRToc(0x724C38);
	MenuInit();
	Menu_PaintAll_Internal_Stub(LocalClientNum, dc_);


}

void sR_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float* color, void* material)
{
	__asm("li %r3, 0x332;");
}

void R_AddCmdDrawStretchPic(float x, float y, float width, float height, float xScale, float yScale, float xay, float yay, const float* color, void* material)
{
	char* materialName = (char*)*(int*)material;
	if (!strcmp(materialName, "mw2_main_cloud_overlay") || !strcmp(materialName, "mw2_main_mp_image") ||
		!strcmp(materialName, "mockup_bg_glow") || !strcmp(materialName, "mw2_popup_bg_fogscroll") ||
		!strcmp(materialName, "mw2_popup_bg_fogstencil") || !strcmp(materialName, "mw2_main_background") ||
		!strcmp(materialName, "laser"))
		color = (float*)&(MenuSettings::MenuFlash ? menuColors::dflash : menuColors::menuMain);

	sR_AddCmdDrawStretchPic(x, y, width, height, xScale, yScale, xay, yay, color, material);
}

extern "C" int _MW2_export_function(void)
{
	return CELL_OK;
}

void sR_AddDObjToScene(...)
{
	__asm("li %r3, 0x8;");
}

void __cdecl R_AddDObjToScene(int obj, int pose, unsigned int entnum, unsigned int renderFxFlags, Vector3* lightingOrigin, const float* materialTime, const float* burnFraction, int altXModel, int textureOverrideIndex, int dobjConstantSet, float lightingOriginToleranceSq, float scale, bool isMarkableViewmodel)
{
	//WallHacks = !WallHacks;

	if (Bools::WallHacks && entnum < 18)
	{
		renderFxFlags = -1;
	}
	else if (Bools::EntityWAll && entnum > 18)
	{
		renderFxFlags = -1;
	}
	else if (!Bools::WallHacks && !Bools::EntityWAll && entnum > 18)
	{
		renderFxFlags = 1;
	}
	lightingOriginToleranceSq = 1;

	sR_AddDObjToScene(obj, pose, entnum, renderFxFlags, lightingOrigin, materialTime, burnFraction, altXModel, textureOverrideIndex, dobjConstantSet, lightingOriginToleranceSq, scale, isMarkableViewmodel);
}

sys_ppu_thread_t MainThread;
sys_ppu_thread_t cpu_thread;
sys_ppu_thread_t Aimbot;
sys_ppu_thread_t amazingAutoBoneThread;

void my_dialog2(int button, void* userdata)
{
	switch (button) {
	case CELL_MSGDIALOG_BUTTON_OK:

	case CELL_MSGDIALOG_BUTTON_NONE:

	case CELL_MSGDIALOG_BUTTON_ESCAPE:
		//dialog_action = 1;
		break;
	default:
		break;
	}
}

void EndFrame_Stub() {
	__nop();
}

void EndFrame()
{
	if (pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
	{
		if (!cg || !c_entity || !active_client)
			return;
		
		ESPHook();
		if (c_entity[cg->ClientNumber].Alive && cg->Health > 0) {
			AimbotHook();
		}
		healthbar();
		*(float*)(0x1D17F90 + 0xC) = Bools::FOV;

		if (Bools::customCamo) {
			menuColors::Color camo_col = { espColors::camo_col_r, espColors::camo_col_g, espColors::camo_col_b };
			if (Bools::customCamoFlash)
				camo_col = menuColors::dflash;
			else
				camo_col = { espColors::camo_col_r, espColors::camo_col_g, espColors::camo_col_b };

			int weapon_camo_offset = find_image_offset("weapon_camo_desert");
			if (weapon_camo_offset)
				set_shader_tint(weapon_camo_offset, 0x2B00, camo_col.r * 255, camo_col.g * 255, camo_col.b * 255);
		}
	}

	*(int*)(*(int*)0x723058 + 0x8) = 3;
}

void init() {
	//PatchInJump(0x38EDE8, (int)hook);
	PatchInJump(0xDB918, (int)EndFrame);

}

void Thread(uint64_t nothing)
{
	sleep(5000);
	cellMsgDialogOpen(1, "Welcome to ZeroTwo.pw!\n\By Ichigo\n\Version: V2.0\n\Please use 1280x1080 for the best experience.\n\Credits:\n\Faultz\n\Mercy", my_dialog2, (void*)0x0000aaab, NULL);
	init();
}

unsigned int get_temperature(unsigned int _dev, unsigned int* _temp)
{
	system_call_2(383, (unsigned int)_dev, (unsigned int)_temp);
	return_to_user_prog(unsigned int);
}

int* getTemps(bool Fahrenheit)
{
	unsigned int t1 = 0, t2 = 0;
	get_temperature(0, &t1);
	get_temperature(1, &t2);
	t1 = t1 >> 24; t2 = t2 >> 24;
	int temps[] = { Fahrenheit ? ((t1 * (9 / 5)) + 32) : t1, Fahrenheit ? ((t2 * (9 / 5)) + 32) : t2 };
	return temps;
}

void get_cpu_and_rsx(uint64_t) {
	while (true)
	{
		Bools::cpu_temp = getTemps(false)[0];
		Bools::rsx_temp = getTemps(false)[1];

		sleep(20000);
	}

	// unreachable for now
	sys_ppu_thread_exit(0);
}

extern "C" int _MW2_prx_entry(void)
{
	mainFuncs::hookFunctionStart(0x253670, *(uint32_t*)(MenuPaint_All), *(uint32_t*)(Menu_PaintAll_Internal_Stub), false);
	mainFuncs::hookFunctionStart(0x00097D60, *(uint32_t*)(R_AddCmdDrawStretchPic), *(uint32_t*)(sR_AddCmdDrawStretchPic), false);
	sys_ppu_thread_create(&MainThread, Thread, 0, 0x4AA, 0x100, 0, "ZeroTwoPW");
	sys_ppu_thread_create(&cpu_thread, get_cpu_and_rsx, 0, 0x4AA, 0x100, 0, "ZeroTwo.pw cpu check thread");
	//sys_ppu_thread_create(&amazingAutoBoneThread, do_autobone, 0, 0x4AA, 0x500, 0, "auto bone");
	mainFuncs::hookFunctionStart(0x0A2060, *(uint32_t*)CL_SendCmd, *(uint32_t*)CL_SendCmdStub, false);
	//mainFuncs::hookFunctionStart(0x4C6E38, *(uint32_t*)R_AddDObjToScene, *(uint32_t*)sR_AddDObjToScene, true);
	mainFuncs::hookFunctionStart(clwpAddr, *(uint32_t*)hkCL, *(uint32_t*)wp_redo, false);
	return SYS_PRX_RESIDENT;
}
