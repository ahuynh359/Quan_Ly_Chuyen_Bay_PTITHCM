
#include"UIController.h"


void removeExitButton()
{
	HMENU hmenu = GetSystemMenu(GetForegroundWindow(), FALSE);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
}


int main()
{


	UIController ui;
	removeExitButton();

	bool isActive = true;

	while (isActive) {
		setactivepage(1 - getactivepage());

		ui.onUpdate();
		ui.onCloseButtonClicked(isActive);


		setvisualpage(getactivepage());
		
		delay(20);
	}

	closegraph();
	return 0;
}

