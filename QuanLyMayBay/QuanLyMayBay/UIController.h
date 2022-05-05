
#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"Tab.h"
#include"Button.h"
#include"ManagePlanesTab.h"
#include"ManageFlightsTab.h"
#include"StatictisTab.h"
#include"TicketTab.h"
#include"ManagePassengersTab.h"
#include"Data.h"
using namespace std;
class UIController {
private:
	Tab t[MAX_TAB];
	Data* data;

	ManagePlanesTab managePlaneTab;
	ManageFlightsTab manageFlightTab;
	ManagePassengersTab managePassengerTab;
	TicketTab ticketTab;
	//StatictisTab* statictisTab;
	
	Tab* temp;
	Button closeButton;

	
	

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

		data = new Data();

		managePlaneTab =  ManagePlanesTab(data);
		manageFlightTab =  ManageFlightsTab(data);
		ticketTab = TicketTab(data);
		managePassengerTab = ManagePassengersTab(data);

	}

	
	~UIController() {

		
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
			ticketTab.reset();
			managePlaneTab.drawUI();
		}
		else if (temp == &t[1]) {
			managePlaneTab.reset();
			ticketTab.reset();
			manageFlightTab.drawUI();
		}
		else if (temp == &t[2]) {
			managePlaneTab.reset();
			manageFlightTab.reset();
			ticketTab.reset();
			managePassengerTab.drawUI();

		}
		else if (temp == &t[3]) {
			managePlaneTab.reset();
			manageFlightTab.reset();
			ticketTab.drawUI();
		}
		else if (temp == &t[4]) {
			managePlaneTab.reset();
			manageFlightTab.reset();
			ticketTab.reset();
		}

		closeButton.onAction();
		if (closeButton.isClicked()) {
			data->writeFile();
			data->freeMemory();
			
			
			closegraph();
			DestroyWindow(GetForegroundWindow());

			PostQuitMessage(0);
			
		}

	}
	




};


#endif