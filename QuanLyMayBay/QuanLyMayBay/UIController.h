
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
		initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Manage Flights",
			(getmaxwidth() - SCREEN_WIDTH) / 2, (getmaxheight() - SCREEN_HEIGHT) / 2);



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

		int x = 25;

		for (int i = 0; i < MAX_TAB; i++) {
			tab[i] = Tab(i, x, 20, x + 200, 90, TAB_TEXT[i]);
			if (i > 0)
				tab[i].setActive(!isEmptyData);
			x += 220;
		}

		//Tab mac dinh la plane tab
		currentTab = &tab[0];


		char s[2] = "X";
		closeButton = Button(1240, 5, 1270, 35, RED, RED, s, BLACK);



	}

	~UIController() {
		for (int i = 0; i < MAX_TAB; i++) {
			delete  manageTab[i];
		}
		delete[]  manageTab;
		delete[] tab; //Xoa luon current tab
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
		closeButton.onAction();

		bool isPlaneDataEmpty = data->planeListIsEmpty();
		bool isFlightDataEmpty = data->flightListIsEmpty();
		int oldId = currentTab->getID();

		for (int i = 0; i < MAX_TAB; i++) {
			//Nhung tab > 0 set no theo du lieu plane
			if (i > 0) {
				tab[i].setActive(!isPlaneDataEmpty);
				//Tab nay set theo du lieu flight
				if (i == 2 || i == 3) {
					tab[i].setActive(!isFlightDataEmpty);
				}

			}

			tab[i].onAction(currentTab);


		}
		//Kiem tra tab hien tai co dang nhap du lieu hay khong
		if (oldId != currentTab->getID() && manageTab[oldId]->isTyping()) {
			int s = manageTab[currentTab->getID()]->drawAnounce(TAB);
			if (s != IDOK)
				currentTab = &tab[oldId];


		}
		//reset va ve noi dung cho tab
		resetAndDrawTab(currentTab->getID());



	}

	void onCloseButtonClicked(bool& isActive) {
		if (closeButton.isClicked()) {
			for (int i = 0; i < MAX_TAB; i++) {
				manageTab[i]->reset();
			}
			data->writeFile();
			data->freeMemory();
			isActive = false;
		}

	}

	//reset tat cac cac tab khong duoc chon,ve tab duoc chon
	void resetAndDrawTab(int index) {
		for (int i = 0; i < MAX_TAB; i++) {
			if (i != index) {
				manageTab[i]->reset();
			}
			else
				manageTab[i]->drawUI();
		}
	}



};

