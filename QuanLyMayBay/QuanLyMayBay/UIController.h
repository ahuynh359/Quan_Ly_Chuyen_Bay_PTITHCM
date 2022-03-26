#pragma once
#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"

int currentTab = -1;
Tab t[MAX_TAB];
ManagePlanesTab managePlaneTab;
Tab* temp;
void drawSubMenu() {
	setbkcolor(TAB_ON_SELECTED_BACKGROUND);
	setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
	bar(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
}

void drawBackground() {
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void init() {
	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights");
	//Khoi tao tab
	int x = TAB_LEFT;
	int w = TAB_RIGHT;
	for (int i = 0; i < MAX_TAB; i++) {
		t[i] = Tab(x, TAB_TOP, w, TAB_HEIGHT, TAB_TEXT[i], TAB_TEXT_COLOR);
		x += TAB_SPACE;
		w += TAB_WIDTH;

	}
	managePlaneTab = ManagePlanesTab();

	temp = &t[0];
	for (int i = 0; i < MAX_TAB; i++) {
		t[i].drawUI();
	}



}


void onUpdate() {
	drawBackground();
	drawSubMenu();
	for (int i = 0; i < MAX_TAB; i++) {
		t[i].onAction(temp);
	}

	if (t[0].getIsSelected()) {

		//managePlaneTab = ManagePlanesTab();
		managePlaneTab.drawUI();


	}

}




