#pragma once
#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"

int currentTab = -1;
Tab* t = new Tab[MAX_TAB+1];
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
	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	//Khoi tao tab
	int x = 25;
	int w = 250;
	for (int i = 0; i < MAX_TAB; i++) {

		t[i] = Tab(x, TAB_TOP, w, TAB_HEIGHT, TAB_DEFAULT_BACKGROUND, TAB_ON_SELECTED_BACKGROUND, TAB_TEXT[i], TAB_TEXT_COLOR);
		
			x+= TAB_SPACE;
			w+= TAB_WIDTH;
		
		


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
		
		t[i].onClick(temp);
	}
	if (t[0].getIsSelected()) {
		managePlaneTab.initManagePlaneTab();
	}
	//Cap nhat tab khi chon

	

	//Ve subscreen
	/*setcolor(TAB_ON_SELECTED_BACKGROUND);
	rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
	setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
	bar(SUBWINDOW_LEFT+1, SUBWINDOW_TOP+1, SUBWINDOW_RIGHT-1, SUBWINDOW_BOTTOM-1);*/


	/*if (t[0]->getIsSelected()) {
		managePlaneTab.initManagePlaneTab();
		
	}
	else if (t[1]->getIsSelected()) {

	}*/

	


	

}


