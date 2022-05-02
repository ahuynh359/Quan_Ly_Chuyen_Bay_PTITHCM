
#pragma once

#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"
#include"ManageFlightsTab.h"
#include"StatictisTab.h"
#include"TicketTab.h"

class UIController {
private:
	Tab t[MAX_TAB];

	ManagePlanesTab managePlaneTab;
	ManageFlightsTab manageFlightTab;
	TicketTab ticketTab;
	StatictisTab statictisTab;

	Tab* temp;
	Button closeButton;

	PlaneList planeList;
	PTR flightList;

public:
	UIController() {
		initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights");

		//Khoi tao tab
		int x = TAB_LEFT;
		int w = x + TAB_WIDTH;
		for (int i = 0; i < MAX_TAB; i++) {

			t[i] = Tab(x, TAB_TOP, w, TAB_HEIGHT, TAB_TEXT[i], TAB_TEXT_COLOR);
			x = w + TAB_SPACE;
			w = x + TAB_WIDTH;
		}

		//Tab mac dinh la plane tab
		temp = &t[0];
		char s[2] = "X";
		closeButton = Button(SCREEN_WIDTH - 40, 0, SCREEN_WIDTH - 10, 30, RED, RED, s, BLACK);

		
		

		
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
			manageFlightTab.reset();
			managePlaneTab.drawUI();

		}
		else if (temp == &t[1]) {
			managePlaneTab.reset();
			manageFlightTab.drawUI(managePlaneTab);

		}
		else if (temp == &t[2]) {
			

		}
		else if (temp == &t[3]) {
			managePlaneTab.reset();
			manageFlightTab.reset();
			ticketTab.drawUI(manageFlightTab);
		}
		else if (temp == &t[4]) {
			statictisTab.drawUI(managePlaneTab);
		}

		closeButton.onAction();
		if (closeButton.isClicked()) {
			
			managePlaneTab.witeFile();
			manageFlightTab.writeFile();

			closegraph();
			DestroyWindow(GetForegroundWindow());

			PostQuitMessage(0);
		}

	}






};


