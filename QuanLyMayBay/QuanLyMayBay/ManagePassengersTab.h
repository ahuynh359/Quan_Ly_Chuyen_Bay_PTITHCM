#pragma once

#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"
#include"FunctionTab.h"
#include"Data.h"
class ManagePassengersTab :public FunctionTab {
private:
	int index = -1;
	int indexID = -1;
	 Data* d;
	AVLTree passTemp;
	PTR flightTemp;
	Passenger* temp;
	int size = 0;

public:
	ManagePassengersTab() {

	}
	//Khoi tao cac tham so
	ManagePassengersTab(Data* d) {
		this->d = d;

		
	}

	void drawUI() {
		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}

		case SHOW_MENU: {
			drawShowMenu();
			break;
		}
		default:
			break;
		}
	}

	void drawMainMenu() {
		

		//-----------------VE HUONG DAN TEXT
		char a[40] = "*Left click to see passenger list";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		int s = drawFlightData(6, d->flightList, flightTemp);

		if (s == 1) {
			
			currentMenu = SHOW_MENU;
			
		}

		

	

	}

	
	void drawShowMenu() {

		int y = SUBWINDOW_TOP + 5 ;

		char s[40] = "LIST OF PASSENGERS ON FLIGHT ";
		strcat_s(s, flightTemp->info.idFlight);
		int x = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(s)) / 2 ;
		 
		drawTitle(x, y, s);

		strcpy_s(s,"Date time: ");
		strcat_s(s, getDateString(flightTemp->info.date));
		y += textheight(s) + 10;
		drawTitle(x- 10, y, s);
		x += textwidth(s) + 10;
		strcpy_s(s, "Arrive: ");
		strcat_s(s, flightTemp->info.arrive);
		
		drawTitle(x, y, s);
		drawPassengerData(5, flightTemp, d->passengerList);
	
		button[BACK].onAction();
		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
		}
	}
};
