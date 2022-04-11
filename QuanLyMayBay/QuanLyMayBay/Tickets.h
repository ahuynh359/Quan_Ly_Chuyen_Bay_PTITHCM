#pragma once
#include<iostream>
#include<fstream>
#include<string>




struct TicketList {
	string* ticket; // Khoi tao bang so cho nhieu nhat 50 ghe, moi ghe la mot so cmnd
	int bookedTicket; // So ve da duoc dat
	int totalTicket;
};

void initTicketList(TicketList& list, int totalTicket) {
	list.totalTicket = totalTicket;
	list.bookedTicket = 0;
	list.ticket = new string[totalTicket];
	for (int i = 0; i < totalTicket; i++)
		list.ticket[i] = "";
	
}

bool insertTicket(TicketList& list, int order, char idPass[12]) {
	if (list.ticket[order-1].length() > 0)
		return false;
	list.ticket[order - 1] = idPass;
	list.bookedTicket++;
	return true;
}

bool deleteTicket(TicketList& list, int order) {
	if (list.ticket[order - 1].length() > 0) {
		list.ticket[order - 1] = "";
		return true;
	}
	return false;

}

void saveListTicket(TicketList& list) {
	ofstream of("TicketData.txt");
	if (of.fail()) {
		printf("Cannot open the file");
		return;
	}
	for (int i = 0; i < list.totalTicket; i++) {

	}
	of.close();
}






