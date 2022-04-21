#pragma once

#include"DataConst.h"
#include<iostream>
#include"Tickets.h"
#include<fstream>
#include<string>


struct Date {
	int day = 0;
	int month = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;
};

struct Flight {
	char idFlight[MAX_ID_FLIGHT];
	Date departure;
	char arrive[MAX_ARRIVE];
	int status; // 0 huy chuyen - 1 con ve - 2 het ve - 3 hoan tat 
	char idPlane[MAX_ID];

	TicketList ticketList;
	//CHI SO PHU
	bool active = true;
};

struct FlightNode
{
	Flight info;
	FlightNode* next;
};
typedef FlightNode* PTR;


void initialize(PTR& First)
{
	First = NULL;
}

PTR newNode(Flight& x)
{
	PTR p = new FlightNode;
	p->info = x;
	p->next = NULL;
	return p;
}
PTR newNode() {
	PTR p = new FlightNode;
	return p;
}

void insertFirst(PTR& First, Flight x)
{
	PTR p = newNode(x);
	p->next = First;
	First = p;
}

void insertAfter(PTR& p, PTR q)
{
	if (p == NULL)
		return;
	else
	{
		PTR first = p;
		while (first->next != NULL)
			p = p->next;
		p->next = q;

	}
}

int size(PTR& p) {
	int cnt = 0;
	for (PTR k = p; k != NULL; k = k->next) {
		cnt++;
	}
	return cnt;
}

void readFileFlight(PTR& flightNode) {
	ifstream inp("FlightData.txt");
	string line;
	Flight x;
	int n;
	inp >> n;
	inp.ignore();
	for (int i = 0; i < n; i++) {
		PTR flight = newNode();
		getline(inp, line);    strcpy_s(flight->info.idFlight, line.c_str());
		getline(inp, line);    strcpy_s(flight->info.arrive, line.c_str());
		getline(inp, line);    flight->info.departure.day = atoi(line.c_str());
		getline(inp, line);    flight->info.departure.month = atoi(line.c_str());
		getline(inp, line);    flight->info.departure.year = atoi(line.c_str());
		getline(inp, line);    flight->info.departure.hour = atoi(line.c_str());
		getline(inp, line);    flight->info.departure.minute = atoi(line.c_str());
		getline(inp, line);	   flight->info.status = atoi(line.c_str());
		getline(inp, line);	   strcpy_s(flight->info.idPlane, line.c_str());

		insertAfter(flightNode, flight);




	}
	inp.close();

}

bool checkDupID(PTR& First, char id[30]) {
	for (PTR p = First; p != NULL; p = p->next) {
		if (strcmp(p->info.idFlight, id) == 0) {
			return true;
		}
	}
	return false;
}

void writeFileFlight(PTR& flightNode) {
	ofstream out("FlightData.txt", ios::trunc);
	int si = size(flightNode);
	out << si << '\n';
	for (int i = 0; i < si; i++) {
		out << flightNode->info.idFlight << '\n';
		out << flightNode->info.departure.day << '\n';
		out << flightNode->info.departure.month << '\n';
		out << flightNode->info.departure.year << '\n';
		out << flightNode->info.departure.hour << '\n';
		out << flightNode->info.departure.minute << '\n';
		out << flightNode->info.arrive << '\n';
		out << flightNode->info.status << '\n';
		out << flightNode->info.idPlane << '\n';

	}
	out.close();
}

PTR searchInfo(PTR First, char  id[15])
{
	for (PTR p = First; p != NULL; p = p->next)
		if (strcmp(p->info.idFlight, id) == 0)
			return p;
	return NULL;
}

bool empty(PTR& First)
{
	return(First == NULL ? true : false);
}

void deleteFirst(PTR& First)
{
	if (First == NULL)
		return;
	PTR p = First;
	First = p->next;
	delete p;
}

//void  deleteAfter(PTR& p,char id[30])
//{
//	PTR q = p;
//	if ((p == NULL) || (p->next == NULL))
//		return;
//	q = p->next;
//	p->next = q->next;
//	delete q;
//}

//incomplete
//int deleteInfo(PTR& First, Flight x)
//{
//	PTR p = First;
//	if (First == NULL) return 0;
//	if (First->info.idFlight == x.idFlight) {
//		deleteFirst(First); return 1;
//	}
//
//	for (p = First; p->next != NULL && p->next->info.idFlight != x.idFlight; p = p->next);
//	if (p->next != NULL) {
//		deleteAfter(p);  return 1;
//	}
//	return 0;
//}
/*
void deleteAllInfo(PTR& First, Flight x)
{
	PTR q, p = First;
	if (First == NULL) { return 0; }
	while (p->next != NULL)
	{
		if (p->next->info == x)
		{
			q = p->next;
			p->next = q->next;
			delete q;
		}
		else p = p->next;
	}
	if (First->info == x) {
		p = First;
		First = First->next;
		delete p;
	}
}
*/
void clearList(PTR& First)
{
	PTR p;
	while (First != NULL)
	{
		p = First;
		First = First->next;
		delete p;
	}
}


/*
void selectionSort(PTR& First)
{
	PTR p, q, pmin;
	Flight min;

	for (p = First; p->next != NULL; p = p->next)
	{
		min = p->info;
		pmin = p;
		for (q = p->next; q != NULL; q = q->next)
			if (q->info < min)
			{
				min = q->info;
				pmin = q;
			}
		// hoan doi truong info cua hai nut p va pmin

		pmin->info = p->info;
		p->info = min;
	}
}

void insert_Order(PTR& First, Flight x)
{
	PTR p, t, s;  // t la nut truoc, s la nut sau
	p = new FlightNode;
	p->info = x;
	for (s = First; s != NULL && s->info < x; t = s, s = s->next);
	if (s == First)  // them nut vao dau danh sach lien ket
	{
		p->next = First;
		First = p;
	}
	else           // them nut p vao truoc nut s
	{
		p->next = s;
		t->next = p;
	}
}

void insertOrder(PTR& First, Flight x)
{
	PTR q, p;  // q la nut truoc, p la nut sau
	q = NULL;
	for (p = First; p != NULL && p->info < x; p = p->next)
		q = p;
	if (q == NULL)  // them nut vao dau danh sach lien ket
		insertFirst(First, x);
	else           // them nut vao sau nut q
		insertAfter(q, x);
}

PTR mergeOrder(PTR& First1, PTR& First2)
{
	PTR p1, p2, p3;
	PTR First3 = new FlightNode; // tạo vùng nhớ tạm
	p1 = First1; p2 = First2; p3 = First3;
	while (p1 != NULL && p2 != NULL)
		if (p1->info < p2->info)
		{
			p3->next = p1;      p3 = p1;      p1 = p1->next;
		}
		else
		{
			p3->next = p2;      p3 = p2;      p2 = p2->next;
		}

	if (p1 == NULL)      p3->next = p2;
	else p3->next = p1;

	p3 = First3;    First3 = p3->next;    delete p3; // xóa
	First1 = First2 = NULL;
	return First3;
}

*/


