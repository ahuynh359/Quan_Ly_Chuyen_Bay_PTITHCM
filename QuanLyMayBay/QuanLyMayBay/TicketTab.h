#pragma once



#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"
#include"Data.h"
#include"FunctionTab.h"

class TicketTab :public FunctionTab {
private:
	PTR flightTemp;


	Button* buttonTicket, * filterButton, * closeButton, * genderButton, * ticketPointer;

	PlaneList planeList;
	AVLTree temp;
	Data* d;
public:
	TicketTab() {

	}

	TicketTab(Data* d) {
		this->d = d;

		initEdittext();
		initButton();

		buttonTicket = new Button[51]; //Khoi tao so ghe

		genderButton = &button[FEMALE];
		closeButton = &button[CLOSE];

		ticketPointer = NULL;

	}
	void customEdittext(AVLTree& pass) {
		edittext[FIRST_NAME].customInitChar(pass->data.firstName);
		edittext[LAST_NAME].customInitChar(pass->data.lastName);
		if (pass->data.gender == 0)
			genderButton = &button[MALE];
		else genderButton = &button[FEMALE];
	}
	Passenger getPassenger() {
		Passenger p;

		strcpy_s(p.idPass, edittext[ID_PASS].getCharData());
		strcpy_s(p.firstName, edittext[FIRST_NAME].getCharData());
		strcpy_s(p.lastName, edittext[LAST_NAME].getCharData());

		if (genderButton == &button[FEMALE])
			p.gender = true;
		else if (genderButton == &button[MALE])
			p.gender = false;
		return p;

	}


	void clearEditext() {
		edittext[ID_PASS].clearText();
		edittext[LAST_NAME].clearText();
		edittext[FIRST_NAME].clearText();
		genderButton = NULL;

	}
	void initEdittext() {

		//---------EDITTEXT ID
		char hint[30] = "Data must be entered!";
		char title[30] = "ID PASS";
		char content[30] = "";

		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITTEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 100;
		int right = left + EDITTEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;


		//------------EDITTEXT ID PASS

		strcpy_s(title, "ID PASS");
		edittext[ID_PASS] = EditText(hint, title, content, left, top, right, bottom, MAX_ID_PASS);



		//------------EDITTEXT SURNAME
		strcpy_s(title, "FIRST NAME");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[FIRST_NAME] = EditText(hint, title, content, left, top, right, bottom, MAX_FIRST_NAME, 130);

		//-------------EDITTEXT NAME
		strcpy_s(title, "LAST NAME");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[LAST_NAME] = EditText(hint, title, content, left, top, right, bottom, MAX_LAST_NAME, 130);




		top = bottom + 65;
		strcpy_s(title, "FE");
		button[FEMALE] = Button(left, top, left + 30, top + 30, EDITEXT_BACKGROUND_COLOR, COLOR(214, 131, 191), title, BLACK);

		left += 50;
		strcpy_s(title, "M");
		button[MALE] = Button(left, top, left + 30, top + 30, EDITEXT_BACKGROUND_COLOR, COLOR(135, 206, 222), title, BLACK);





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









	}
	void initAdjustMenu(bool s) {


		if (!s) {
			edittext[FIRST_NAME].setActive(false);
			edittext[LAST_NAME].setActive(false);
			edittext[FIRST_NAME].setActive(false);
			button[FEMALE].setActive(false);
			button[MALE].setActive(false);

		}
		else {
			edittext[FIRST_NAME].setActive(true);
			edittext[LAST_NAME].setActive(true);
			edittext[FIRST_NAME].setActive(true);
			button[FEMALE].setActive(true);
			button[MALE].setActive(true);
		}
	}
	void initTicketList(PTR& flight) {

		int y = TOP_BORDER + 20;
		int x = (LEFT_BORDER + RIGHT_BORDER - 680) / 2;
		char value[3];
		char a[2] = "";
		for (int i = 1; i <= flight->info.totalTicket; i++) {
			sprintf_s(value, "%d", i);

			buttonTicket[i] = Button(x, y, x + 50, y + 50, TICKET_AVAI, TICKET_NOT_AVAI, value, BLACK);
			if (strcmp(flight->info.ticketList[i - 1], "0") != 0) {
				buttonTicket[i].setChoosen(true);
			}

			x += 70;
			if (i % 10 == 0) {
				x = (LEFT_BORDER + RIGHT_BORDER - 680) / 2;
				y += 70;

			}


		}
	}
	void reset() {
		FunctionTab::reset();
	}


	void moveEdittextUp() {
		if (edittextPointer == &edittext[LAST_NAME]) {
			edittextPointer = &edittext[FIRST_NAME];
		}
		else if (edittextPointer == &edittext[FIRST_NAME])
			edittextPointer = &edittext[ID_PASS];
	}
	void moveEdittextDown() {
		if (edittextPointer == &edittext[ID_PASS]) {
			AVLTree passenger = findPassenger(d->passengerList, edittext[ID_PASS].getCharData());
			if (passenger != NULL) {
				customEdittext(passenger);

			}
			edittextPointer = &edittext[FIRST_NAME];
		}
		else if (edittextPointer == &edittext[FIRST_NAME]) {
			edittextPointer = &edittext[LAST_NAME];
		}

	}
	bool checkEdittextError() {
		edittextPointer->clearCursor();

		if (edittextPointer == &edittext[ID_PASS]) {
			if (edittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
			if (!checkIDPassenger(edittext[ID_PASS].getCharData())) {
				drawAnounce(ID_PASS_ERROR);
				return false;
			}
			if (!ableToBook(flightTemp, edittext[ID_PASS].getCharData())) {
				drawAnounce(DUP_ID_PASS);
				return false;
			}
			initAdjustMenu(true);
		}



		if (edittextPointer == &edittext[FIRST_NAME]) {
			if (edittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
		}



		if (edittextPointer == &edittext[LAST_NAME]) {
			if (edittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}

		}

		return true;


	}

	void inputHandel() {
		int c = FunctionTab::getInput();

		if (edittextPointer != NULL) {
			switch (c) {
			case -1: {
				edittextPointer->deleteChar();
				break;
			}
			case 1: {
				if (!checkEdittextError()) {

				}
				else
					moveEdittextUp();


				break;
			}
			case 3: case 2: {

				if (!checkEdittextError()) {

				}
				else
					moveEdittextDown();
				break;
			}
			default: {


				if (edittextPointer == &edittext[ID_PASS]) {
					if (c <= 57 && c >= 48)
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[FIRST_NAME] || edittextPointer == &edittext[LAST_NAME]) {
					if (c <= 90 && c >= 65 || c == ' ' || c <= 122 && c >= 97)
						edittextPointer->addCharName((char)c);

				}




				break;


			}
			}
		}

	}
	bool checkSaveData() {
		edittext[ID_PASS].clearCursor();
		edittext[FIRST_NAME].clearCursor();
		edittext[LAST_NAME].clearCursor();


		if (edittext[ID_PASS].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[ID_PASS];
			return false;
		}

		if (!checkIDPassenger(edittext[ID_PASS].getCharData())) {
			drawAnounce(ID_PASS_ERROR);
			edittextPointer = &edittext[ID_PASS];
			return false;
		}


		if (!ableToBook(flightTemp, edittext[ID_PASS].getCharData())) {
			drawAnounce(DUP_ID_PASS);
			edittextPointer = &edittext[ID_PASS];
			return false;
		}



		if (edittext[FIRST_NAME].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[FIRST_NAME];
			return false;
		}



		if (edittext[LAST_NAME].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[LAST_NAME];
			return false;
		}

		if (genderButton == NULL) {
			drawAnounce(GENDER_ERROR);
			return false;
		}


		return true;
	}

	//-------------------------UI--------------------------
	void drawUI() {


		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}
		case TICKET_MENU: {
			drawTicketMenu();
			break;
		}

		case ADJUST_MENU: {
			drawAdjustMenu();
			break;
		}

		default:
			break;

		}
	}
	void drawMainMenu() {

		//-----------------VE HUONG DAN TEXT
		char a[40] = "*Left click to book/cancel ticket";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		int s = drawFlightData(6, d->flightList, flightTemp);


		button[HAVE_TICKET].onAction(filterButton);
		button[ALL].onAction(filterButton);

		if (s == 1) {
			initTicketList(flightTemp);
			delay(50);
			currentMenu = TICKET_MENU;
		}


	}

	void drawTicketMenu() {

		drawInstructionInline();

		for (int i = 1; i <= flightTemp->info.totalTicket; i++)
			buttonTicket[i].onActionSeatButton(ticketPointer);


		if (ticketPointer != NULL) {
			if (!ticketPointer->getIsChoosen() && ticketPointer->getIsLeftClick()) {
				edittextPointer = &edittext[ID_PASS];
				initAdjustMenu(false);

				delay(50);
				currentMenu = ADJUST_MENU;
				return;

			}
			else
				if (ticketPointer->getIsChoosen() && ticketPointer->getIsRightClick()) {
					cout << "AHIHI RIGHT CLICK\n";

					int s = drawAnounce(CANCLE_TICKET);
					if (s == IDOK) {
						ticketPointer->setChoosen(false);
						ticketPointer->drawSeatUI();
						char a[MAX_ID_PASS + 1] = "0";
						bookTicket(flightTemp, ticketPointer->getIntData() - 1, a);
						ticketPointer = NULL;
					}
					delay(50);

				}
		}
	

		button[BACK].onAction();

		if (button[BACK].isClicked()) {
			ticketPointer = NULL;
			delay(50);
			currentMenu = MAIN_MENU;
			return;
		}




	}
	void drawGenderText() {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(EDITTEXT_TITLE_COLOR);
		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITTEXT_WIDTH + 90) / 2 - 130;
		int top = SUBWINDOW_TOP + 450;
		char a[30] = "GENDER";
		drawText(left, top, left + textwidth(a), a);
	}
	void drawAdjustMenu() {

		button[BACK].onAction();
		button[SAVE].onAction();
		button[FEMALE].onAction(genderButton);
		button[MALE].onAction(genderButton);

		drawGenderText();

		edittext[ID_PASS].onAction(edittextPointer);
		edittext[FIRST_NAME].onAction(edittextPointer);
		edittext[LAST_NAME].onAction(edittextPointer);


		inputHandel();

		if (button[BACK].isClicked()) {
			ticketPointer = NULL;
			delay(50);
			currentMenu = TICKET_MENU;
		}
		if (button[SAVE].isClicked()) {
			if (!checkSaveData()) {

			}
			else {
				Passenger p = getPassenger();
				traverse(d->passengerList);
				d->passengerList = addPassenger(d->passengerList, p);
				ticketPointer->setChoosen(true);
				
				drawAnounce(SUCCESS);
				clearEditext();
				bookTicket(flightTemp, ticketPointer->getIntData() - 1, p.idPass);
				currentMenu = TICKET_MENU;
				ticketPointer = NULL;
			}
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

