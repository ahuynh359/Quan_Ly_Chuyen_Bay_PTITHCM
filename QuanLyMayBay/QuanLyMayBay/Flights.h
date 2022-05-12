#pragma once


#include<fstream>
#include"Day.h"



#ifndef FLIGHT_H
#define FLIGHT_H
struct Flight {
	char idFlight[MAX_ID_FLIGHT + 1];
	Date date;
	char arrive[MAX_ARRIVE + 1];
	char idPlane[MAX_ID_PLANE + 1];
	/*
	* 0 huy chuyen
	* 1 con ve
	* 2 het ve
	* 3 hoan tat
	*/
	int status;

	//-----CHI SO PHU
	char** ticketList;
	int totalTicket = 0;


};

struct FlightNode
{
	Flight info;
	FlightNode* next;
};
typedef FlightNode* PTR;


void initializeList(PTR& first)
{
	first = NULL;
}



PTR newNode(Flight& flight)
{
	PTR p = new FlightNode;
	p->info = flight;
	p->next = NULL;
	return p;
}

bool isEmpty(PTR& first)
{
	return(first == NULL ? true : false);
}

void insertAfter(PTR& first, Flight& flight)
{
	PTR temp = newNode(flight);
	if (first == NULL) {
		first = temp;
		first->next = NULL;
	}
	else
	{
		PTR p = first;
		while (p->next != NULL)
			p = p->next;
		p->next = temp;

	}
}

int size(PTR& first) {
	int cnt = 0;
	if (first == NULL)
		return cnt;
	for (PTR k = first; k != NULL; k = k->next) {
		cnt++;
	}
	return cnt;
}

bool adjustFlight(PTR& flight, Date date) {
	if (checkTime(date)) {
		flight->info.date = date;
		return true;
	}
	return false;
}

bool isPrefix(const char* pre, const char* str) {
	if (strlen(pre) > strlen(str)) return false;
	for (int i = 0; i < strlen(pre); i++) {
		if (pre[i] != str[i]) return false;
	}
	return true;
}





PTR findFlight(PTR& first, char  id[MAX_ID_FLIGHT + 1])
{
	for (PTR p = first; p != NULL; p = p->next)
		if (strcmp(p->info.idFlight, id) == 0)
			return p;
	return NULL;
}

PTR findFlightByIdPlane(PTR& first, char id[MAX_ID_PLANE + 1]) {
	for (PTR k = first; k != NULL; k = k->next) {
		if (strcmp(k->info.idPlane, id) == 0)
			return k;
	}
	return NULL;
}

//Huy ve khi chua hoan tat
int checkCancleFlight(PTR& first) {
	if (first->info.status == HAVE_TICKET || first->info.status == OUT_OF_TICKET) {
		first->info.status = CANCEL_TICKET;
		return 1;
	}
	return 0;
}

void checkCompleted(PlaneList& planeList, PTR& temp) {
	if (temp->info.status == HAVE_TICKET || temp->info.status == OUT_OF_TICKET) {
		Date now = getCurTime();
		if (calSpaceTime(now, temp->info.date) >= 0) {
			temp->info.status = COMPLETE_TICKET;
			planeList.data[findPlane(planeList, temp->info.idPlane)]->flyTimes++;
		}
	}
}

int countTicketLeft(PTR& flightList) {
	int cnt = 0;
	for (int i = 0; i < flightList->info.totalTicket; i++) {
		if (strcmp(flightList->info.ticketList[i], "0") == 0)
			cnt++;
	}
	return cnt;
}

void checkCompletedAll(PTR& flightList, PlaneList& planeList) {
	for (PTR k = flightList; k != NULL; k = k->next) {
		checkCompleted(planeList, k);
	}
}


//-------------TICKET
void initTicketList(PlaneList& planeList, Flight& flight) {
	flight.status = HAVE_TICKET;

	Plane* p = planeList.data[findPlane(planeList, flight.idPlane)];

	p->isAvai = false;

	flight.totalTicket = p->seats;

	char s[MAX_ID_PASS + 1] = "0";
	flight.ticketList = new char* [flight.totalTicket + 1];
	for (int i = 0; i < flight.totalTicket; i++) {
		flight.ticketList[i] = new char[MAX_ID_PASS + 1];
		strcpy_s(flight.ticketList[i], 2, s);
	}

}

//kiem tra CMND trung tren 1 chuyen bay, tra ve so ghe bi trung
int checkDupIDOnFlight(PTR& flightList, char id[MAX_ID_PASS + 1]) {
	for (int i = 0; i < flightList->info.totalTicket; i++) {
		if (strcmp(flightList->info.ticketList[i], id) == 0) {
			return i + 1;
		}
	}
	return -1;
}

void bookTicket(PTR& first, int index, char id[MAX_ID_PASS + 1]) {
	strcpy_s(first->info.ticketList[index], MAX_ID_PASS + 1, id);
}

void cancleTicket(PTR& first, int index, char id[MAX_ID_PASS + 1]) {
	char s[MAX_ID_PASS + 1] = "0";
	strcpy_s(first->info.ticketList[index], 2, s);


}

void writeFileFlight(PTR& first) {
	ofstream out("FlightData.txt", ios::trunc, ios::binary);

	if (out.fail()) {
		printf("Cant open file Flight Data\n");
		return;
	}

	for (PTR k = first; k != NULL; k = k->next) {
		out.write(reinterpret_cast<char*>(&k->info), sizeof(Flight));
		for (int i = 0; i < k->info.totalTicket; i++) {
			out.write(reinterpret_cast<char*>(&(*k->info.ticketList[i])), sizeof(char[MAX_ID_PASS + 1]));
		}
	}


	out.close();
}

void readFileFlight(PTR& first) {
	ifstream inp("FlightData.txt", ios::binary);

	if (inp.fail()) {
		printf("Cant open file Flight Data\n");
		return;
	}
	Flight flight;

	while (inp.read(reinterpret_cast<char*>(&flight), sizeof(flight))) {
		flight.ticketList = new char* [flight.totalTicket + 1];
		for (int i = 0; i < flight.totalTicket; i++) {
			flight.ticketList[i] = new char[MAX_ID_PASS + 1];
		}
		for (int i = 0; i < flight.totalTicket; i++) {
			inp.read(reinterpret_cast<char*>(&*(flight.ticketList[i])), sizeof(char[MAX_ID_PASS + 1]));
		}

		insertAfter(first, flight);
	}
	inp.close();

}

void deleteFlightList(PTR& first)
{
	PTR temp = first;
	while (temp != NULL) {
		PTR t = temp;
		temp = temp->next;
		for (int i = 0; i < t->info.totalTicket; i++) {
			delete t->info.ticketList[i];
		}
		delete t->info.ticketList;
		delete t;
	}
}

#endif