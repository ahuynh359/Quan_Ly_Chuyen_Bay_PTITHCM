
#include"UIController.h"


void disableCloseButton() {
	EnableMenuItem(GetSystemMenu(GetForegroundWindow(), FALSE), SC_CLOSE,
		MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
}

int main()
{

	UIController ui;
	disableCloseButton();

	bool isActive = true;

	while (isActive) {
		
		setactivepage(1 - getactivepage());

		ui.onUpdate();
		ui.onCloseButtonClicked(isActive);

		setvisualpage(getactivepage());

		clearmouseclick(VK_LBUTTON);
		clearmouseclick(VK_RBUTTON);

		
		
	}

	

	closegraph();
	return 0;
}

