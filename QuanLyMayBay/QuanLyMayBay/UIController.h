
#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"
#include"ManageFlightsTab.h"
#include"TicketTab.h"
#include"ManagePassengersTab.h"
#include"StatictisTab.h"
#include"Data.h"


using namespace std;
class UIController {
private:

	Tab* tab, * currentTab;

	Data* data;
	FunctionTab** manageTab;

	Button closeButton;
public:
	UIController() {
		initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights");

		tab = new Tab[MAX_TAB];

		//Khoi tao tab
		int x = TAB_LEFT;
		for (int i = 0; i < MAX_TAB; i++) {
			tab[i] = Tab(i, x, TAB_TOP, x + TAB_WIDTH, TAB_HEIGHT, TAB_TEXT[i]);
			x += TAB_WIDTH + TAB_SPACE;
		}

		//Tab mac dinh la plane tab
		currentTab = &tab[0];


		char s[2] = "X";
		closeButton = Button(SCREEN_WIDTH - 40, 0, SCREEN_WIDTH - 10, 30, RED, RED, s, BLACK);

		data = new Data();

		manageTab = new FunctionTab * [MAX_TAB];

		manageTab[0] = new ManagePlanesTab(data);
		manageTab[1] = new ManageFlightsTab(data);
		manageTab[2] = new ManagePassengersTab(data);
		manageTab[3] = new TicketTab(data);
		manageTab[4] = new StatictisTab(data);

	}

	~UIController() {
		delete tab;
		delete currentTab;
		delete data;

		for (int i = 0; i < MAX_TAB; i++) {
			delete manageTab[i];
		}

		delete  manageTab;
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
			tab[i].onAction(currentTab);
		}

		closeButton.onAction();


		int id = currentTab->getID();

		resetTab(id);
	
		manageTab[id]->drawUI();

		if (closeButton.isClicked()) {
			onCloseButtonClicked();
		}

	}

	void onCloseButtonClicked() {

		data->writeFile();
		data->freeMemory();
		closegraph();
		DestroyWindow(GetForegroundWindow());
		PostQuitMessage(0);


	}

	void resetTab(int index) {
		for (int i = 0; i < MAX_TAB; i++) {
			if (i != index) {
				manageTab[i]->reset();
			}
		}
	}



};


#endif