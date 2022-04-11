#pragma once;
#include"Flights.h"
#include<iostream>
#include"EditText.h"
#include"FunctionTab.h"
class BookTicketTab :public FunctionTab {
private:
	PTR flightList;
	enum MENU { MENU_CHINH, MENU_VE, MENU_TTIN };
	EditText editText[4];
	Button button[4];
	Button* ticketButton;
	enum EDITTEXT_NAME { ID1, ID2, HO, TEN };
	enum BUTTON_NAME { TRAI, GAI, LUU, QVE };
	EditText* editextPointer;
	TicketList list;
	Button* temp;

public:
	BookTicketTab() {
		initialize(flightList);

		initEdittext();
		initButton();
		editextPointer = &editText[ID1];
		createData();
		temp = &button[0];
	}

	void createData() {
		ticketButton = new Button[50];
		initTicketList(list, 50);
		list.ticket[0] = "adsds";
		list.ticket[1] = "abc";

		int x = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - 925) / 2;
		int y = SUBWINDOW_TOP + 50;
		for (int i = 0; i < 30; i++) {
			if (i % 10 == 0) {
				x = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - 925) / 2;
				y += 60;

			}

			char text[30];

			sprintf_s(text, "%d", i + 1);
			ticketButton[i] = Button(x, y, x + 50, y + 50, TICKET_AVAI, TICKET_CHOOSEN, text, WHITE);



			x += 100;

		}



	}
	void initButton() {
		char text[30] = "SAVE";
		int left, top, right, bottom;

		left = ((LEFT_BORDER + RIGHT_BORDER) / 2) - 100;
		top = SUBWINDOW_BOTTOM - 110;
		right = ((LEFT_BORDER + RIGHT_BORDER) / 2) - 30;
		bottom = SUBWINDOW_BOTTOM - 80;
		button[LUU] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, text,
			PLANE_TEXT_COLOR);

		//-----------BUTTON QUAY LUI
		strcpy_s(text, "<");
		left = SUBWINDOW_LEFT + 10;
		top = SUBWINDOW_TOP + 10;
		right = SUBWINDOW_LEFT + 60;
		bottom = SUBWINDOW_TOP + 60;
		button[QVE] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, text, PLANE_TEXT_COLOR);

	}

	void initEdittext() {
		char hint[30] = "Only Num";
		char title[30] = "Enter ID";
		char content[30] = "";
		editText[ID1] = EditText(hint, title, content, LEFT_BORDER + 100, BOTTOM_BORDER - 40, ((LEFT_BORDER + RIGHT_BORDER) / 2) - 30, SUBWINDOW_BOTTOM - 120, 12);

	}

	void drawUI() {
		switch (currentMenu) {
		case MENU_CHINH: {
			drawTicketTab(list);
			break;
		}
		case MENU_VE: {
			drawTicketTab(list);
			break;
		}
		case MENU_TTIN: {
			break;
		}
		default: {
			break;

		}

		}
	}

	void drawPassenger() {

	}

	void drawIDInputBorder() {

		setcolor(BLACK);
		rectangle(LEFT_BORDER, BOTTOM_BORDER - 50, (LEFT_BORDER + RIGHT_BORDER) / 2, SUBWINDOW_BOTTOM - 70);


		editText[ID1].onAction(editextPointer);
		inputHandelForID();


		char s[30] = "Only Num";
		editText[ID1].drawAnoune(s, true);

		button[LUU].onAction();
	}

	void inputHandelForID() {
		int c = FunctionTab::getInput();

		if (editextPointer == &editText[ID1]) {

			if (c == -1) editextPointer->deleteChar();
			else if (c != 0) {
				if (c <= 57 && c >= 48)
					editextPointer->addChar((char)c);

			}


		}

	}

	void drawAvailableFlightsTab() {
		char s[30] = "AVAILABLE FLIGHTS";
		drawTitle(s);


		//drawTicketSeats(LEFT_BORDER + 10, BOTTOM_BORDER - 70, 0, 1);
		//drawTicketSeats(LEFT_BORDER + 10, BOTTOM_BORDER - 200, 1, 2);
		//drawTicketSeats(LEFT_BORDER + 10, BOTTOM_BORDER - 300, 2, 3);


		strcpy_s(s, "*Left click to view tickets");
		FunctionTab::drawInstruction(s);

		drawIDInputBorder();


	}

	void drawTicketTab(TicketList& list) {

		char s[30] = "TICKET";
		FunctionTab::drawTitle(s);

		for (int i = 0; i < 30; i++) {

			ticketButton[i].onAction(temp, (list.ticket[i].length() > 0 ? 1 : 0));
		}


		drawInstructionInline();
		button[QVE].onAction();

	}




	//Ham ve instruction
	void drawInstructionInline() {

		char s[30];
		int left = RIGHT_BORDER - 100;
		int top = BOTTOM_BORDER - 50;

		strcpy_s(s, "Available");
		drawSmallBox(left, top, s, TICKET_AVAI);

		top += 30;
		strcpy_s(s, "Not available");
		drawSmallBox(left, top, s, TICKET_NOT_AVAI);

		top += 30;
		strcpy_s(s, "Is Choosen");
		drawSmallBox(left, top, s, TICKET_CHOOSEN);
	}

	//Ham ve o mau huong dan
	void drawSmallBox(int x, int y, char s[30], int color) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(color);
		setfillstyle(1, color);
		bar(x, y, x + 20, y + 20);
		setcolor(BLACK);
		outtextxy(x + 30, (2 * y + 20 - textheight(s)) / 2, s);

	}

};