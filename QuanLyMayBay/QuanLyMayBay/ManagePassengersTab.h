#pragma once

#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"
#include"FunctionTab.h"

class ManagePassengersTab :public FunctionTab {
private:
	int index = -1;
	int indexID = -1;

	AVLTree passengerList;
	AVLTree passTemp;
	Passenger* temp;
	int size = 0;

public:
	//Khoi tao cac tham so
	ManagePassengersTab() {
		createPassengerList(passengerList);
		//readFilePassenger(passengerList);

		
	}

	void drawUI() {
		drawPassengerData(4,passengerList, passTemp);
	}
	void writeFile() {
		writeFilePassenger(passengerList);
	}
	AVLTree getPassList() {
		return passengerList;
	}
};