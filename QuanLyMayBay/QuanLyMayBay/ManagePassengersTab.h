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
		//AVLTree root = findPassenger(d->)
		cout << flightTemp->info.totalTicket << "FLIGHT\n";
		//drawPassengerData(5, flightTemp, d->passengerList);
	}
};
