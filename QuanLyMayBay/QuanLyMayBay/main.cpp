
#include"UIController.h"
int main()
{
	init();
	bool isActive = true;
	while (isActive) {
		setactivepage(1 - getactivepage());
		onUpdate();
		setvisualpage(getactivepage());
		drawSubMenu();
		if (kbhit()) {
			char s = getch();
			if (s == 'a')
				break;
		}
		delay(20);
	}

	//getch();
	closegraph();

	return 0;
}

