#pragma once
#include"Flights.h"
#include<iostream>
#include"EditText.h"
#include"FunctionTab.h"
#include"ManageFlightsTab.h"
#include"define.h"
class TicketTab :public FunctionTab {
private:
	PTR first;
	PTR flightTemp;
	Button* pointer = &buttonTicket[0];
	Button* buttonTicket, * filterButton, * closeButton;

public:
	TicketTab() {

		initEdittext();
		initButton();
		buttonTicket = new Button[51];


		closeButton = &button[CLOSE];
	}


	void initEdittext() {
		char content[40] = "";
		char title[15] = "ID PASSENGER";
		edittext[ID_PASS] = EditText(content, title, content, SUBWINDOW_LEFT + 20, SUBWINDOW_BOTTOM - 100, SUBWINDOW_LEFT + 80,
			SUBWINDOW_BOTTOM - 20, MAX_ID_PASS);

	}
	void initButton() {

		//-----BUTTON LOC THEM CON VE
		char a[10] = "TICKET";
		button[HAVE_TICKET] = Button(RIGHT_BORDER - 110, SUBWINDOW_TOP + 2, RIGHT_BORDER - 60, SUBWINDOW_TOP + 48,
			BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);

		filterButton = &button[HAVE_TICKET];

		//-----BUTTON LOC HET CHUYEN BAY
		strcpy_s(a, "ALL");
		button[ALL] = Button(RIGHT_BORDER - 50, SUBWINDOW_TOP + 2, RIGHT_BORDER, SUBWINDOW_TOP + 48,
			BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);

		strcpy_s(a, "X");
		button[CLOSE] = Button(SUBWINDOW_LEFT + 480, SUBWINDOW_BOTTOM - 198, SUBWINDOW_LEFT + 500,
			SUBWINDOW_BOTTOM - 178, RED, WHITE, a, BUTTON_TEXT_COLOR);
	}

	void initTicketList(PTR& flight) {

		int y = TOP_BORDER + 20;
		int x = (LEFT_BORDER + RIGHT_BORDER - 680) / 2;
		char value[3];
		char a[2] = "";

		for (int i = 1; i <= flight->info.totalTicket; i++) {
			sprintf_s(value, "%d", i);
			buttonTicket[i] = Button(x, y, x + 50, y + 50, TICKET_AVAI, TICKET_CHOOSEN, value, BLACK);
			x += 70;
			if (i % 10 == 0) {
				x = (LEFT_BORDER + RIGHT_BORDER - 680) / 2;
				y += 70;

			}


		}
	}





	//-------------------------UI--------------------------
	void drawUI(ManageFlightsTab& manage) {

		this->first = manage.getFlightList();

		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}
		case TICKET_MENU: {
			drawTicketMenu();
			break;
		}

		default:
			break;

		}
	}

	void drawBorderInput() {
		int w = 500;
		int h = 200;
		setbkcolor(GREEN);
		setcolor(GREEN);
		setbkcolor(FOREGROUND_COLOR);
		setcolor(FOREGROUND_COLOR);
		bar(SUBWINDOW_LEFT, SUBWINDOW_BOTTOM - h, SUBWINDOW_LEFT + w, SUBWINDOW_BOTTOM);
	

		line(SUBWINDOW_LEFT, SUBWINDOW_BOTTOM - h, SUBWINDOW_LEFT + w, SUBWINDOW_BOTTOM - h);
		line(SUBWINDOW_LEFT + w, SUBWINDOW_BOTTOM - h, SUBWINDOW_LEFT + w, SUBWINDOW_BOTTOM);

	}
	void drawInputID() {
		setlinestyle(0, 0, 3);



		EditText* e = &edittext[ID_PASS];
		edittext[ID_PASS].onAction(e);
		drawBorderInput();
		button[CLOSE].onAction(closeButton);
		if (button[CLOSE].isClicked()) {
			currentMenu = TICKET_MENU;
			closeButton = NULL;
			return;

		}
		
	}
	void drawMainMenu() {



		//-----------------VE HUONG DAN TEXT
		char a[40] = "*Left click to book/cancel ticket";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		int s = drawFlightData(6, first, flightTemp);

		if (s == 1) {
			initTicketList(flightTemp);
			delay(50);
			currentMenu = TICKET_MENU;
			return;
		}




		button[HAVE_TICKET].onAction(filterButton);
		button[ALL].onAction(filterButton);



	}
	void drawTicketMenu() {

		drawInstructionInline();

		button[BACK].onAction();



		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
			return;
		}

		for (int i = 1; i <= flightTemp->info.totalTicket; i++) {
			buttonTicket[i].onAction(pointer);

		}

		if (pointer != NULL) {

			drawInputID();
		}

	}


	//-------------------------------------
	void drawInstructionInline() {

		char s[30];
		char a[2] = "";
		int left = SUBWINDOW_RIGHT - 50;
		int top = BOTTOM_BORDER - 20;

		strcpy_s(s, "Available");
		drawSmallBox(left, top, 20, 20, TICKET_AVAI, s);


		top += 30;
		strcpy_s(s, "Not available");
		drawSmallBox(left, top, 20, 20, TICKET_NOT_AVAI, s);

		top += 30;
		strcpy_s(s, "Is Choosen");
		drawSmallBox(left, top, 20, 20, TICKET_CHOOSEN, s);
	}
	void drawSmallBox(int x, int y, int width, int height, int color, char title[20]) {

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy(x - textwidth(title) - 10, (2 * y + height - textheight(title)) / 2, title);


		setcolor(color);

		setfillstyle(1, color);
		bar(x, y, x + width, y + height);


	}

};