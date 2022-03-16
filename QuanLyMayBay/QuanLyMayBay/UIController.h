#pragma once
#include"Tab.h"

void createWindow() {
	initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quan Ly Thu Vien");

	//Ve background
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//Ve tab
	for (int i = 0; i < MAX_TAB; i++) {
		Tab t(TAB_LEFT[i], TAB_TOP, TAB_RIGHT[i], TAB_HEIGHT, TAB_DEFAULT_BACKGROUND, TAB_ON_SELECTED_BACKGROUND, TAB_TEXT[i], TAB_TEXT_COLOR);

		if (i == 0)
			t.setIsSelected(true);
		
		t.drawUI();
		t.drawText();
		TAB_LEFT[i + 1] = TAB_LEFT[i] + TAB_SPACE;
		TAB_RIGHT[i + 1] = TAB_RIGHT[i] + TAB_WIDTH;
	}

	//Ve submenu
	setbkcolor(TAB_ON_SELECTED_BACKGROUND);
	setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
	bar(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);

}
