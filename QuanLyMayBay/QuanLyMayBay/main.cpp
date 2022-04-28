
#include"UIController.h"
#include "Planes.h"

void removeExitButton()
{
	HWND hwnd = GetConsoleWindow();
	HMENU hmenu = GetSystemMenu(GetForegroundWindow(), FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}
int main()
{

	UIController ui;

	removeExitButton();


	while (true) {
		
		setactivepage(1 - getactivepage());
		ui.onUpdate();
		setvisualpage(getactivepage());
		clearmouseclick(WM_LBUTTONDOWN);
		delay(20);
	}

	
	

	return 0;
}

