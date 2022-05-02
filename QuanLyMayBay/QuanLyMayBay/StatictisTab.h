#pragma once
#include"ManagePlanesTab.h"
#include"FunctionTab.h"
class StatictisTab :public ManagePlanesTab {
private:
public:
	StatictisTab() {
	}
	~StatictisTab() {

	}



	void drawData(PlaneList list) {
		
		setcolor(COLOR(50, 45, 188));

		//dataPerPage(planeList.size);
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		button[LEFT].onAction();
		button[RIGHT].onAction();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);
		}

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 4;
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;


		for (int i = startPage; i <= endPage; i++) {

			int preX = LEFT_BORDER;
			setbkcolor(SUBWINDOW_BACKGROUND);
			setcolor(BLACK);
			

			//STT
			char charValue[50];
			sprintf_s(charValue, sizeof(charValue), "%d", i);
			int width = textwidth(charValue);
			int height = textheight(charValue);
			int x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, charValue);
			preX = x;

			//ID
			width = textwidth(list.data[i - 1]->idPlane);
			height = textheight(list.data[i - 1]->idPlane);
			x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, list.data[i - 1]->idPlane);
			preX = x;


			preX = x;

			//FLY TIME
			sprintf_s(charValue, sizeof(charValue), "%d", list.data[i - 1]->flyTimes);
			width = textwidth(charValue);
			height = textheight(charValue);
			x = preX + spaceX;
			outtextxy((preX+RIGHT_BORDER)/2, preY, charValue);


			preY += spaceY;

		}

	}
	
	
	void drawUI() {
		
		

		

	}


};