#pragma once

#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"
#include"BookTicketTab.h"
#include"ManageFlightsTab.h"


class UIController {
private:
	Tab t[MAX_TAB];
	ManagePlanesTab managePlaneTab;
	BookTicket bookTicketTab;
	ManageFlightsTab manageFlightTab;
	Tab* temp;

public:
	UIController() {
		initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights");
		//Khoi tao tab
		int x = TAB_LEFT;
		int w = x + TAB_WIDTH;
		for (int i = 0; i < MAX_TAB; i++) {

			t[i] = Tab(x, TAB_TOP, w, TAB_HEIGHT, TAB_TEXT[i], TAB_TEXT_COLOR);

			x = w + TAB_SPACE;
			w += TAB_WIDTH + TAB_SPACE;
		}
		//managePlaneTab = ManagePlanesTab();

		temp = &t[0];


	}
	~UIController() {
		delete temp;
	}

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



	void onUpdate() {
		drawBackground();
		drawSubMenu();
		for (int i = 0; i < MAX_TAB; i++) {
			t[i].onAction(temp);
		}

		if (temp == &t[0]) {
			managePlaneTab.drawUI();

		}
		else if (temp == &t[1]) {
			managePlaneTab.reset();
			manageFlightTab.drawUI();

		}
		else if (temp == &t[2]) {

			managePlaneTab.reset();
			bookTicketTab.drawUI();

		}

	}



};