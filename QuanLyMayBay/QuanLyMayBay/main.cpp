
#include"UIController.h"
int main()
{
	init();
	//DTTT comment
	// dslk
	while (true) {
		setactivepage(1 - getactivepage());
		onUpdate();


		//clearmouseclick(WM_LBUTTONDOWN);
		setvisualpage(getactivepage());
		delay(20);

	}
	getch();
	closegraph();

	return 0;
}

