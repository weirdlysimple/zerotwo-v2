#pragma once


void customCrosshair() {

	if (!cg || !c_entity || !active_client)
		return;

	if (!pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
		return;

	float crosshair_length = (8 + (cg->SpreadMultiplier / 4));
	int crosshair_size = 2;

	float x = cg->RefDef.Width / 2 - 8 - crosshair_length;
	float y = cg->RefDef.Width / 2 - crosshair_size + crosshair_length;

	float x2 = cg->RefDef.Height / 2 - 8 - crosshair_length;
	float y2 = cg->RefDef.Height / 2 - crosshair_size + crosshair_length;

	int min_spread = 0;
	int max_spread = 255;

	menuColors::Color crosshair_col;

	if (Bools::removeOriginalCrosshair)
		*(bool*)(0x1D275F0 + 0xC) = false;
	else
		*(bool*)(0x1D275F0 + 0xC) = true;

	if (Bools::fadeColorDependingOnSpread) {
		menuColors::Color Red = { 1, 0, 0, 1 };
		menuColors::Color Green = { 0, 1, 0, 1 };

		float val = cg->SpreadMultiplier / 255;

		float red = val;
		float green = 1 - val;

		menuColors::Color col = { red, green, 0, 1 };
		crosshair_col = col;
	}
	else {
		crosshair_col = { espColors::crosshair_col_r, espColors::crosshair_col_g, espColors::crosshair_col_b, 1 };
	}

	if (Bools::customCrosshair) {
		//left
		menuFunctions::DrawShader(x, cg->RefDef.Height / 2 - crosshair_size, 8, crosshair_size, crosshair_col, "white");
		//right
		menuFunctions::DrawShader(y, cg->RefDef.Height / 2 - crosshair_size, 8, crosshair_size, crosshair_col, "white");
		//top
		menuFunctions::DrawShader(cg->RefDef.Width / 2 - crosshair_size, x2, crosshair_size, 8, crosshair_col, "white");
		//bottom
		menuFunctions::DrawShader(cg->RefDef.Width / 2 - crosshair_size, y2, crosshair_size, 8, crosshair_col, "white");
	}
}