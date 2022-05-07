
#include"UIController.h"


void removeExitButton()
{
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(GetForegroundWindow(), FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}


int main()
{


	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights");
	
	
	UIController ui;

	removeExitButton();

	while (true) {
		
		setactivepage(1 - getactivepage());
		ui.onUpdate();
		setvisualpage(getactivepage());
		clearmouseclick(WM_LBUTTONDOWN);
		delay(50);
	}

	
	return 0;
}

