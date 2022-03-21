
#include"UIController.h"
using namespace std;
int main()
{
	init();
	//DT comment
	//DT COMMETN TIEP
	
	while (true) {
		setactivepage(1 - getactivepage());
		createWindow();
		//eventHandle(t);
	

		clearmouseclick(WM_LBUTTONDOWN);
		setvisualpage(getactivepage());
		delay(20);

	}
	getch();
	closegraph();
	
	return 0;
}

