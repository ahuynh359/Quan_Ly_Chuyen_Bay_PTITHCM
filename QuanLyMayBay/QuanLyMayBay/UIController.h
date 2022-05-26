
#pragma once

#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"
#include"ManageFlightsTab.h"
#include"TicketTab.h"
#include"ManagePassengersTab.h"
#include"StatictisTab.h"
#include"Data.h"

class UIController {
private:

	Tab* tab, * currentTab;
	Data* data;
	FunctionTab** manageTab;

	Button closeButton;
public:
	UIController() {
		printf("%d", getmaxwidth());
		initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights",
			(getmaxwidth() - SCREEN_WIDTH)/2,(getmaxheight() - SCREEN_HEIGHT)/2);


		data = new Data();

		manageTab = new FunctionTab * [MAX_TAB];

		manageTab[0] = new ManagePlanesTab(data);
		manageTab[1] = new ManageFlightsTab(data);
		manageTab[2] = new ManagePassengersTab(data);
		manageTab[3] = new TicketTab(data);
		manageTab[4] = new StatictisTab(data);

		tab = new Tab[MAX_TAB];

		//Khoi tao tab
		bool isEmptyData = data->planeListIsEmpty();
		int x = TAB_LEFT;
		for (int i = 0; i < MAX_TAB; i++) {
			tab[i] = Tab(i, x, TAB_TOP, x + TAB_WIDTH, TAB_HEIGHT, TAB_TEXT[i]);
			if (i > 0)
				tab[i].setActive(!isEmptyData);
			x += TAB_WIDTH + TAB_SPACE;
		}

		//Tab mac dinh la plane tab
		currentTab = &tab[0];


		char s[2] = "X";
		closeButton = Button(SCREEN_WIDTH - 40, 0, SCREEN_WIDTH - 10, 30, RED, RED, s, BLACK);



	}

	~UIController() {
		delete tab; //Xoa luon current tab
		delete data;
	}

	void drawBackground() {
		setbkcolor(BACKGROUND_COLOR);
		cleardevice();
		setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
		bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	void onUpdate() {

		drawBackground();

		bool isPlaneDataEmpty = data->planeListIsEmpty();
		bool isFlightDataEmpty = data->flightListIsEmpty();


		for (int i = 0; i < MAX_TAB; i++) {
			//Nhung tab > 0 set no theo du lieu plane
			if (i > 0) {


				tab[i].setActive(!isPlaneDataEmpty);
				if (i == 2 || i == 3) {
					tab[i].setActive(!isFlightDataEmpty);
				}

			}
			tab[i].onAction(currentTab);
		}

		closeButton.onAction();



		int id = currentTab->getID();



		//reset tat cac cac tab khong duoc chon,ve tab duoc chon
		resetTab(id);
		manageTab[id]->drawUI();


	}

	void onCloseButtonClicked(bool& isActive) {
		if (closeButton.isClicked()) {
			data->writeFile();
			data->freeMemory();
			isActive = false;
		}




	}

	void resetTab(int index) {
		for (int i = 0; i < MAX_TAB; i++) {
			if (i != index) {
				manageTab[i]->reset();
			}
		}
	}



};

