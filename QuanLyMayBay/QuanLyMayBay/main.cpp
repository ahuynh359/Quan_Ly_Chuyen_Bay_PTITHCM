
#include"UIController.h"
int main()
{
	init();
	while (true) {
		setactivepage(1 - getactivepage());
		onUpdate();
		setvisualpage(getactivepage());
		clearmouseclick(WM_LBUTTONDOWN);
		
		delay(20);
	}

	getch();
	closegraph();

	return 0;
}

