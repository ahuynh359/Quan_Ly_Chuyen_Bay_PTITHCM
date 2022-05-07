#pragma once
#ifndef DATA_H
#define DATA_H

#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"


class Data {
private:
	PlaneList planeList;
	PTR flightList;
	AVLTree passengerList;

	friend class ManagePlanesTab;
	friend class ManageFlightsTab;
	friend class ManagePassengersTab;
	friend class TicketTab;
	friend class StatictisTab;
public:
	Data() {
		readFilePlane(planeList);
		initializeList(flightList);
		readFileFlight(flightList);

		createPassengerList(passengerList);
		readFilePassenger(passengerList);
	}
	~Data() {

	}
	void freeMemory() {
		deletePlaneList(planeList);
		deleteFlightList(flightList);
		removeAll(passengerList);
	}
	void writeFile() {
		writeFilePlane(planeList);
		writeFileFlight(flightList);
		writeFilePassenger(passengerList);
	}
};
#endif