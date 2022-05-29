
#include"UIController.h"


int main()
{

	UIController ui;

	bool isActive = true;

	while (isActive) {
	
		setactivepage(1 - getactivepage());

		ui.onUpdate();
		ui.onCloseButtonClicked(isActive);


		setvisualpage(getactivepage());
		clearmouseclick(WM_LBUTTONDOWN);
		clearmouseclick(WM_RBUTTONDOWN);

		
		delay(20);
	}

	closegraph();
	return 0;
}

