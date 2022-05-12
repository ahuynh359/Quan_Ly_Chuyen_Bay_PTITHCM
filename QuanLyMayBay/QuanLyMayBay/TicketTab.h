#pragma once

#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"
#include"Data.h"
#include"ManageFlightsTab.h"

class TicketTab :public ManageFlightsTab {
private:
	PTR flightTemp;
	Button* buttonTicket, * closeButton, * genderButton, * ticketPointer;
	EditText* addEdittextPointer;

	Data* d;
public:

	TicketTab() {
		initSearchEdittext();
		initEdittext();

		buttonTicket = new Button[51]; //Khoi tao so ghe
		closeButton = &button[CLOSE];
		addEdittextPointer = NULL;
		genderButton = NULL;
		ticketPointer = NULL;
	}
	TicketTab(Data* d) {
		this->d = d;

		initEdittext();

		buttonTicket = new Button[51]; //Khoi tao so ghe
		closeButton = &button[CLOSE];
		addEdittextPointer = NULL;
		genderButton = NULL;
		ticketPointer = NULL;


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
		addEdittextPointer = NULL;
		genderButton = NULL;

	}


	void initAddMenu(bool s) {
		edittext[FIRST_NAME].setActive(s);
		edittext[LAST_NAME].setActive(s);
		edittext[FIRST_NAME].setActive(s);
		button[FEMALE].setActive(s);
		button[MALE].setActive(s);

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
		clearEditext();
	}


	void moveEdittextUp() {
		if (addEdittextPointer == &edittext[LAST_NAME]) {
			addEdittextPointer = &edittext[FIRST_NAME];
		}
		else if (addEdittextPointer == &edittext[FIRST_NAME]) {
			addEdittextPointer = &edittext[ID_PASS];

		}
	}
	void moveEdittextDown() {
		if (addEdittextPointer == &edittext[ID_PASS]) {
			AVLTree passenger = findPassenger(d->passengerList, edittext[ID_PASS].getCharData());
			if (passenger != NULL) {
				customEdittext(passenger);

			}
			addEdittextPointer = &edittext[FIRST_NAME];
		}
		else if (addEdittextPointer == &edittext[FIRST_NAME]) {
			addEdittextPointer = &edittext[LAST_NAME];
		}

	}
	bool checkEdittextError() {
		addEdittextPointer->clearCursor();

		if (addEdittextPointer == &edittext[ID_PASS]) {
			if (addEdittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
			if (!checkIDPassenger(edittext[ID_PASS].getCharData())) {
				drawAnounce(ID_PASS_ERROR);
				return false;
			}
			int s = checkDupIDOnFlight(flightTemp, edittext[ID_PASS].getCharData());
			if (s != -1) {
				char mess[200] = "Duplicate ID in seat number ";
				char a[3];
				sprintf_s(a, "%d", s);
				strcat_s(mess, a);
				MessageBox(GetForegroundWindow(), (LPCWSTR)convertCharArrayToLPCWSTR(mess), (LPCWSTR)convertCharArrayToLPCWSTR("WARNING"), MB_ICONWARNING | MB_OK);
				return false;
			}
			initAddMenu(true);
		}



		if (addEdittextPointer == &edittext[FIRST_NAME]) {
			if (addEdittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
		}

		edittext[FIRST_NAME].standarContent();

		if (addEdittextPointer == &edittext[LAST_NAME]) {
			if (addEdittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}

		}
		edittext[LAST_NAME].standarContent();
		return true;


	}

	void inputHandel() {
		int c = FunctionTab::getInput();

		if (addEdittextPointer != NULL) {
			switch (c) {
			case -1: {
				addEdittextPointer->deleteChar();
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


				if (addEdittextPointer == &edittext[ID_PASS]) {
					if (c <= 57 && c >= 48)
						addEdittextPointer->addChar((char)c);

				}
				else if (addEdittextPointer == &edittext[FIRST_NAME] || addEdittextPointer == &edittext[LAST_NAME]) {
					if (c <= 90 && c >= 65 || c == ' ' || c <= 122 && c >= 97)
						addEdittextPointer->addCharName((char)c);

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
			addEdittextPointer = &edittext[ID_PASS];
			return false;
		}

		if (!checkIDPassenger(edittext[ID_PASS].getCharData())) {
			drawAnounce(ID_PASS_ERROR);
			addEdittextPointer = &edittext[ID_PASS];
			return false;
		}

		int s = checkDupIDOnFlight(flightTemp, edittext[ID_PASS].getCharData());
		if (s != -1) {
			char mess[200] = "Duplicate ID in seat number ";
			char a[3];
			sprintf_s(a, "%d", s);
			strcat_s(mess, a);
			MessageBox(GetForegroundWindow(), (LPCWSTR)convertCharArrayToLPCWSTR(mess), (LPCWSTR)convertCharArrayToLPCWSTR("WARNING"), MB_ICONWARNING | MB_OK);
			addEdittextPointer = &edittext[ID_PASS];
			return false;
		}
		initAddMenu(true);

		if (edittext[FIRST_NAME].isEmpty()) {
			drawAnounce(EMPTY);
			addEdittextPointer = &edittext[FIRST_NAME];
			return false;
		}

		edittext[FIRST_NAME].standarContent();


		if (edittext[LAST_NAME].isEmpty()) {
			drawAnounce(EMPTY);
			addEdittextPointer = &edittext[LAST_NAME];
			return false;
		}
		edittext[LAST_NAME].standarContent();

		if (genderButton == NULL) {
			drawAnounce(GENDER_ERROR);
			return false;
		}


		return true;
	}

	//-------------------------UI--------------------------
	void drawUI() {

		FunctionTab::drawBackground();
		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}
		case TICKET_MENU: {
			drawTicketMenu();
			break;
		}

		case ADD_MENU: {
			drawAddMenu();
			break;
		}

		default:
			break;

		}
	}
	void drawMainMenu() {


		inputMainMenuHandel();
		//-----------------VE HUONG DAN TEXT
		char a[40] = "*Left click to book/cancel ticket";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		int s;

		s = drawFlightData(flightTemp, d->flightList, true);

		if (s == 1) {
			Date d = flightTemp->info.date;



			//Khong cho dat ve 30 phut cuoi
			if (!checkTimeBeforeMinute(d, 30)) {
				drawAnounce(THIRTY_MINUTE);
				return;
			}
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
				addEdittextPointer = &edittext[ID_PASS];
				initAddMenu(false);

				delay(50);
				currentMenu = ADD_MENU;
				return;

			}
			else
				if (ticketPointer->getIsChoosen() && ticketPointer->getIsRightClick()) {

					int s = drawAnounce(CANCLE_TICKET);
					switch (s) {
					case IDOK: {
						ticketPointer->setChoosen(false);
						ticketPointer->drawSeatUI();
						char a[MAX_ID_PASS + 1] = "0";
						bookTicket(flightTemp, ticketPointer->getIntData() - 1, a);
						ticketPointer = NULL;
						break;
					}
					default:
						break;
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
	void drawAddMenu() {

		button[BACK].onAction();
		button[SAVE].onAction();
		button[FEMALE].onAction(genderButton);
		button[MALE].onAction(genderButton);

		drawGenderText();

		edittext[ID_PASS].onAction(addEdittextPointer);
		edittext[FIRST_NAME].onAction(addEdittextPointer);
		edittext[LAST_NAME].onAction(addEdittextPointer);


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

