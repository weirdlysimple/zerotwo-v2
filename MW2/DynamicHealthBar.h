
void healthbar() {

	if (!cg)
		return;

	if (!pointers::Dvar_GetBool("cl_ingame") && pointers::in_game())
		return;

	if (!Bools::DynamicHealthBar)
		return;


	Vector2 screen_size = Vector2(structures::ui_context.screenWidth, structures::ui_context.screenHeight);

	float health = (cg->Health / 100.f);
	
	char health_buffer[128];
	snprintf(health_buffer, 128, "health: %i/100hp", cg->Health);

	float green = health;
	float red = 1 - health;
	menuColors::Color fuck_you_math_kys_nigger = { red, green, 0, 1 };

	Vector2 healthbar_label_size = menuFunctions::TextSize(health_buffer, 0.5);

	int healthbar_width = 150;
	// min area
	int min = 0;
	// the max size you'd want
	int max = 100;
	// get your min max xD
	int min_max = max - min;
	// create your min delta by taking away the min with your actual value
	const float value_min_delta = cg->Health - min;
	// create your fraction by dividing your min delta with your min max and timeing it by your max size you actually want
	const float desired_fraction = (value_min_delta / min_max) * healthbar_width;
	static float current_fraction = 0.f;
	// create the delta fraction
	const float delta = desired_fraction - current_fraction;
	// if its not the same animate.
	if (desired_fraction != current_fraction)
		current_fraction += delta * 0.12f;

	menuFunctions::DrawShader(screen_size.x / 2 - healthbar_width/2, screen_size.y - 25, healthbar_width, 15, menuColors::dimmedBlack, "white");
	menuFunctions::DrawShader(screen_size.x / 2 - (healthbar_width/2) - 1, screen_size.y - 24, current_fraction, 13, fuck_you_math_kys_nigger, "white");
	menuFunctions::DrawText(health_buffer, screen_size.x / 2 - (healthbar_label_size.x / 2), screen_size.y - 29 + healthbar_label_size.y, FONT_NORMAL, 0.5, menuColors::White);

}