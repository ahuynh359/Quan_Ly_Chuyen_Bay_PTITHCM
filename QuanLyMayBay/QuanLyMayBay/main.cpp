
#include"UIController.h"
int main()
{
	UIController ui;
	while (true) {
		setactivepage(1 - getactivepage());
		ui.onUpdate();
		setvisualpage(getactivepage());
		clearmouseclick(WM_LBUTTONDOWN);
		
		delay(20);
	}

	getch();
	closegraph();

	return 0;
}

