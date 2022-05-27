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


void createFlightList(PTR& first)
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

void adjustFlight(PTR& flight, Date& date) {
	flight->info.date = date;
}

bool isPrefix(const char* pre, const char* str) {
	if (strlen(pre) > strlen(str))
		return false;
	for (int i = 0; i < strlen(pre); i++)
		if (pre[i] != str[i])
			return false;

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


bool checkCancleFlight(PTR& first) {
	if (first->info.status == HAVE_TICKET || first->info.status == OUT_OF_TICKET) {
		first->info.status = CANCEL_TICKET;
		return true;
	}
	return false;
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

int countTicketLeft(PTR& first) {
	int cnt = 0;
	for (int i = 0; i < first->info.totalTicket; i++) {
		if (strcmp(first->info.ticketList[i], "0") == 0)
			cnt++;
	}
	return cnt;
}

void checkCompletedAll(PTR& first, PlaneList& planeList) {
	for (PTR k = first; k != NULL; k = k->next) {
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
	flight.ticketList = new char* [51];
	for (int i = 0; i < flight.totalTicket; i++) {
		flight.ticketList[i] = new char[MAX_ID_PASS + 1];
		strcpy_s(flight.ticketList[i], 2, s);
	}

}

//kiem tra CMND trung tren 1 chuyen bay, tra ve so ghe bi trung
int checkDupIDOnFlight(PTR& first, char id[MAX_ID_PASS + 1]) {
	for (int i = 0; i < first->info.totalTicket; i++) {
		if (strcmp(first->info.ticketList[i], id) == 0) {
			return i + 1;
		}
	}
	return -1;
}

// Kiem tra 1 hanh khach chi duoc dat 2 chuyen bay co >= abs(12)
PTR checkPassOnOtherFlightIn12Hours(PTR& first, PTR& flight, char id[MAX_ID_PASS + 1]) {
	for (PTR k = first; k != NULL; k = k->next) {
		if (k != flight) {
			for (int i = 0; i < k->info.totalTicket; i++) {
				if (strcmp(k->info.ticketList[i], id) == 0 && strcmp(id, "0") != 0 &&
					!in12Hour(flight->info.date, k->info.date) && (k->info.status == 1 || k->info.status == 2)) {

					return k;
				}
			}
		}
	}
	return NULL;
}

PTR canEditTime(PTR& first, PTR& flight, Date date) {
	for (PTR k = first; k != NULL; k = k->next) {
		if (k != flight) {
			for (int i = 0; i < flight->info.totalTicket; i++) {
				if (strcmp(flight->info.ticketList[i], "0") != 0 && checkDupIDOnFlight(k, flight->info.ticketList[i]) != -1 &&
					!in12Hour(k->info.date, date) && (k->info.status == 1 || k->info.status == 2)) {
					printf("%d\n", checkDupIDOnFlight(k, flight->info.ticketList[i]));
					return k;
				}
			}
		}
	}
	return NULL;
}

void adjustTicketList(PTR& first, int totalTicket, char id[MAX_ID_PLANE + 1]) {

	char s[MAX_ID_PASS + 1] = "0";

	for (PTR k = first; k != NULL; k = k->next) {
		if (strcmp(k->info.idPlane, id) == 0) {

			for (int i = k->info.totalTicket; i < totalTicket; i++) {
				k->info.ticketList[i] = new char[MAX_ID_PASS + 1];
				strcpy_s(k->info.ticketList[i], 2, s);
			}
			k->info.totalTicket = totalTicket;

		}

	}

}

void bookTicket(PTR& first, int index, char id[MAX_ID_PASS + 1]) {
	strcpy_s(first->info.ticketList[index], MAX_ID_PASS + 1, id);
}



void writeFileFlight(PTR& first) {
	ofstream out("FlightData.txt", ios::binary);

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
			delete []  t->info.ticketList[i];
		}
		delete[] t->info.ticketList;
		delete t;
	}
}

#endif