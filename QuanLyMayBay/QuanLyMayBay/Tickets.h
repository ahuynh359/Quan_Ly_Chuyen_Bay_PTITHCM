#pragma once
#include<iostream>
#define MAX_SEATS 50
struct Ticket {
	char idPass[15];
	int order; //So thu tu ve
};

struct TicketList {
	Ticket** seats; // Khoi tao bang so cho
	int bookedTicket; // So ve da duoc dat
	int totalTicket;
};

void initTicketList(TicketList& list, int totalTicket, int bookedTicket) {
	list.seats = new Ticket*[MAX_SEATS];
	for (int i = 0; i < totalTicket; i++) {
		list.seats[i] = new Ticket[1];
	}
	list.totalTicket = totalTicket;
	list.bookedTicket = bookedTicket;
}






