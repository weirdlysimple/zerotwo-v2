namespace men {
	enum {
		MENU_Mods,
		MENU_Aimbot,
		MENU_Stats,
		MENU_Say,
		MENU_Clients,
		MENU_Settings
	};

	void RenderMenu();
	void StartMenu();
	void InitializeMenu(char* menuName);
	void RenderOptions();
	void SetFunctionOptions();
	void ExitMenu(int exOpt);
	void RenderMenuText();
	void RenderWatermark();
}