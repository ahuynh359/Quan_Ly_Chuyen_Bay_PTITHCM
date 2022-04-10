#pragma once
#include"Flights.h"
#include<iostream>
#include"FunctionTab.h"
class BookTicketTab :public FunctionTab {
private:
	PTR flightList;
	enum MENU { MENU_CHINH, MENU_VE };

public:
	BookTicketTab() {
		initialize(flightList);

	}

	void drawUI() {
		switch (currentMenu) {
		case MENU_CHINH: {
			drawAvailableFlights();
			break;
		}
		case MENU_VE: {
			drawTicket();
			break;
		}
		default: {
			break;

		}

		}
	}

	void drawAvailableFlights() {
		char s[30] = "AVAILABLE FLIGHTS";
		drawTitle(s);


		drawTicketCell(LEFT_BORDER + 10, BOTTOM_BORDER - 70, 0, 1);
		drawTicketCell(LEFT_BORDER + 10, BOTTOM_BORDER - 200, 1, 2);
		drawTicketCell(LEFT_BORDER + 10, BOTTOM_BORDER - 300, 2, 3);


		drawInstruction();


	}




	void drawTicket() {


	}

	/*
	* 0 chua dat
	* 1 dang chon
	* 2 da dat
	*/
	void drawTicketCell(int x, int y, int status, int order) {
		int color = WHITE;

		setbkcolor(SUBWINDOW_BACKGROUND);

		switch (status) {
		case 0: {
			color = TICKET_AVAI;
			break;
		}
		case 1: {
			color = TICKET_CHOOSEN;
			break;
		}
		case 2: {
			color = TICKET_NOT_AVAI;
			break;
		}

		}
		setcolor(color);
		setfillstyle(1, color);
		bar(x, y, x + 50, y + 50);

		setbkcolor(color);
		setcolor(WHITE);
		char s[3];
		sprintf_s(s, "%d", order);
		outtextxy((2 * x + 50 - textwidth(s)) / 2, (2 * y + 50 - textheight(s)) / 2, s);

	}
	void drawInstruction() {
		char s[30] = "*Left click to view tickets";
		FunctionTab::drawInstruction(s);

		int left = RIGHT_BORDER - 50;
		int top = BOTTOM_BORDER - 50;
		setcolor(TICKET_AVAI);
		bar(left, top, left + 20, top + 20);

		top += 30;
		setcolor(TICKET_NOT_AVAI);
		bar(left, top, left + 20, top + 20);
	}

};