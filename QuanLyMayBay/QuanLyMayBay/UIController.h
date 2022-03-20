#pragma once
#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"

int currentTab = -1;
Tab* t[MAX_TAB];
Tab* temp;
ManagePlanesTab managePlaneTab;

void init() {
	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quan Ly May Bay");
	//Khoi tao tab
	for (int i = 0; i < MAX_TAB; i++) {

		t[i] = new Tab(TAB_LEFT[i], TAB_TOP, TAB_RIGHT[i], TAB_HEIGHT, TAB_DEFAULT_BACKGROUND, TAB_ON_SELECTED_BACKGROUND, TAB_TEXT[i], TAB_TEXT_COLOR);
		TAB_LEFT[i + 1] = TAB_LEFT[i] + TAB_SPACE;
		TAB_RIGHT[i + 1] = TAB_RIGHT[i] + TAB_WIDTH;


	}

	temp = t[0];

	


}

void drawSubMenu() {
	setbkcolor(TAB_ON_SELECTED_BACKGROUND);
	setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
	bar(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
}
void createWindow() {


	//Ve background
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Cap nhat tab khi chon

	for (int i = 0; i < MAX_TAB; i++) {
		t[i]->onClick(temp);

	}

	//Ve subscreen
	/*setcolor(TAB_ON_SELECTED_BACKGROUND);
	rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
	setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
	bar(SUBWINDOW_LEFT+1, SUBWINDOW_TOP+1, SUBWINDOW_RIGHT-1, SUBWINDOW_BOTTOM-1);*/


	if (t[0]->getIsSelected()) {
		managePlaneTab.initManagePlaneTab();
	}
	else if (t[1]->getIsSelected()) {

	}

	




}


