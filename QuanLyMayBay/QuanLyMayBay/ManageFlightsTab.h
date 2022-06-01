#pragma once

#include"Planes.h"
#include"Flights.h"
#include"FunctionTab.h"
#include"ManagePlanesTab.h"
#include"Data.h"


class ManageFlightsTab :public FunctionTab {

protected:
	EditText addEdittext[MAX_EDITTEXT];
	EditText* addPointer = NULL;

	int indexID = -1;
	PTR flightTemp = NULL;

	Data* d = NULL;

	ManagePlanesTab manage;

public:
	ManageFlightsTab() {

	}

	ManageFlightsTab(Data* data) {
		this->d = data;
		initEdittext();
		initSearchEdittext();
	}

	~ManageFlightsTab() {
		printf("Manage Flight Constructor\n");
		delete addPointer;
		delete flightTemp;
	}



	//----------HAM KHOI TAO
	//Khoi tao edittext cho nhap va sua thong tin
	void initEdittext() {

		char hint[30] = "Do not leave empty!";
		char title[30] = "FLIGHT ID";
		char content[30] = "";

		int left = 430;
		int top = 200;
		int right = left + EDITTEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;
		int spaceY = 90;
		int spaceX = 90;

		//------------EDITTEXT ID FLIGHT

		addEdittext[ID_FLIGHT] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, MAX_ID_FLIGHT);

		//------------EDITTEXT ID PLANE
		strcpy_s(title, "PLANE ID");
		strcpy_s(hint, "Max 15 character");
		top += spaceY;
		addEdittext[ID_PLANE] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, MAX_ID_PLANE);

		//-----------BUTTON TIM KIEM MAY BAY
		strcpy_s(title, "FIND");
		button[FIND] = Button(right + 10, top, right + 10 + BUTTON_WIDTH, top + EDITTEXT_HEIGHT, BUTTON_BACKGROUND,
			WHITE, title,
			BUTTON_TEXT_COLOR);


		//------------EDITTEXT ARRIVE 
		strcpy_s(title, "ARRIVE");
		strcpy_s(hint, "Max 40 character");
		top += spaceY;
		addEdittext[ARRIVE] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, 40);

		//EDITTEXT STATUS
		strcpy_s(title, "STATUS");
		strcpy_s(content, "HAVE TICKET");
		top += spaceY;
		addEdittext[STATUS] = EditText(hint, title, content, left, top, left + textwidth(content) + 10, top + EDITTEXT_HEIGHT, 40);
		addEdittext[STATUS].setActive(false);

		//------------EDITTEXT DAY

		strcpy_s(title, "TIME");
		top += spaceY;
		addEdittext[DAY] = EditText(hint, title, content, left, top, left + EDITTEXT_MIN_WIDTH, top + EDITTEXT_HEIGHT, 2);

		//------------EDITTEXT MONTH

		strcpy_s(title, "/");
		left += spaceX;
		addEdittext[MONTH] = EditText(hint, title, content, left, top, left + EDITTEXT_MIN_WIDTH, top + EDITTEXT_HEIGHT, 2, 10);


		//------------EDITTEXT YEAR

		left += spaceX;
		addEdittext[YEAR] = EditText(hint, title, content, left, top, left + EDITTEXT_MIN_WIDTH, top + EDITTEXT_HEIGHT, 4, 10);


		//------------EDITTEXT HOUR

		strcpy_s(title, "AT");
		left += spaceX + 20;
		addEdittext[HOUR] = EditText(hint, title, content, left, top, left + EDITTEXT_MIN_WIDTH, top + EDITTEXT_HEIGHT, 2, 25);


		//------------EDITTEXT MINUTE

		strcpy_s(title, ":");
		left += spaceX;
		addEdittext[MINUTE] = EditText(hint, title, content, left, top, left + EDITTEXT_MIN_WIDTH, top + EDITTEXT_HEIGHT, 2, 10);




	}
	//Khoi tao edittext cho phan loc thong tin
	void  initSearchEdittext() {
		int left = LEFT_BORDER;
		int top = SUBWINDOW_TOP + 5;
		int right = left + 150;
		int bottom = top + EDITTEXT_HEIGHT;

		char hint[30] = "Max 15 character";
		char title[30] = "FLIGHT ID";
		char content[30] = "";

		//------------EDITTEXT ID FLIGHT
		edittext[ID_FLIGHT] = EditText(hint, title, content, left, top, right, bottom, MAX_ID_FLIGHT);


		//------------EDITTEXT DAY
		strcpy_s(title, "TIME");
		strcpy_s(hint, "dd");
		left = right + EDITTEXT_SPACE;
		right = left + 70;
		edittext[DAY] = EditText(hint, title, content, left, top, right, bottom, 2, 40);

		//------------EDITTEXT MONTH
		strcpy_s(title, "/");
		strcpy_s(hint, "mm");
		left = right + 30;
		right = left + 70;
		edittext[MONTH] = EditText(hint, title, content, left, top, right, bottom, 2, 15);

		//------------EDITTEXT YEAR
		strcpy_s(title, "/");
		strcpy_s(hint, "yyyy");
		left = right + 30;
		right = left + 70;
		edittext[YEAR] = EditText(hint, title, content, left, top, right, bottom, 4, 15);


		//------------EDITTEXT ARRIVE
		strcpy_s(title, "ARRIVE");
		strcpy_s(hint, "Max 40 character");
		left = right + EDITTEXT_SPACE;
		right = RIGHT_BORDER;
		edittext[ARRIVE] = EditText(hint, title, content, left, top, right, bottom, 40, 55);
	}
	//Khoi tao cho man hinh them chuyen bay
	void initAddMenu() {
		addPointer = &addEdittext[ID_FLIGHT];
		char s[30] = "HAVE TICKET";

		addEdittext[ID_FLIGHT].setActive(true);
		addEdittext[ID_PLANE].setActive(true);
		addEdittext[ARRIVE].setActive(true);

		addEdittext[STATUS].customInitChar(s);
		addEdittext[STATUS].setActive(false);

		addEdittext[MINUTE].customInitChar(getCurTime().minute);
		addEdittext[HOUR].customInitChar(getCurTime().hour);
		addEdittext[YEAR].customInitChar(getCurTime().year);
		addEdittext[MONTH].customInitChar(getCurTime().month);
		addEdittext[DAY].customInitChar(getCurTime().day);

	}
	//Khoi tao man hinh chinh sua chuyen bay
	void initAdjustScreen() {
		addPointer = &addEdittext[DAY];

		addEdittext[ID_FLIGHT].customInitChar(flightTemp->info.idFlight);
		addEdittext[ID_FLIGHT].setActive(false);
		addEdittext[ID_PLANE].customInitChar(flightTemp->info.idPlane);
		addEdittext[ID_PLANE].setActive(false);
		addEdittext[ARRIVE].customInitChar(flightTemp->info.arrive);
		addEdittext[ARRIVE].setActive(false);

		char s[40] = "HAVE TICKET";
		if (flightTemp->info.status == 2)
			strcpy_s(s, "SOLD OUT");
		addEdittext[STATUS].customInitChar(s);
		addEdittext[STATUS].setActive(false);

		addEdittext[DAY].customInitChar(flightTemp->info.date.day);
		addEdittext[MONTH].customInitChar(flightTemp->info.date.month);
		addEdittext[YEAR].customInitChar(flightTemp->info.date.year);
		addEdittext[HOUR].customInitChar(flightTemp->info.date.hour);
		addEdittext[MINUTE].customInitChar(flightTemp->info.date.minute);
	}


	//----------RESET
	//reset tab flight 
	void reset() {
		currentMenu = MAIN_MENU;
		flightTemp = NULL;
		currentPage = 1;
		resetAddEdittext();
		resetSearchEdittext();
	}
	//reset cac edittext
	void resetAddEdittext() {
		addEdittext[ID_FLIGHT].clearText();
		addEdittext[ID_PLANE].clearText();
		addEdittext[ARRIVE].clearText();
		addEdittext[STATUS].clearText();
		addEdittext[DAY].clearText();
		addEdittext[MONTH].clearText();
		addEdittext[YEAR].clearText();
		addEdittext[HOUR].clearText();
		addEdittext[MINUTE].clearText();
		addPointer = NULL;

	}
	void  resetSearchEdittext() {
		edittext[ID_FLIGHT].clearText();
		edittext[DAY].clearText();
		edittext[MONTH].clearText();
		edittext[YEAR].clearText();
		edittext[ARRIVE].clearText();
		edittextPointer = NULL;
	}


	//----------HAM XU LI EDITTEXT
	//Kiem tra tat cac cach search edittext co empty hay khong
	bool  checkAllEdittextIsEmpty() {
		if (edittext[ID_FLIGHT].isEmpty() &&
			edittext[DAY].isEmpty() &&
			edittext[MONTH].isEmpty() &&
			edittext[YEAR].isEmpty() &&
			edittext[ARRIVE].isEmpty()) {
			return true;
		}
		return false;
	}
	void moveEdittextDown() {
		if (addPointer == &addEdittext[ID_FLIGHT])
			addPointer = &addEdittext[ID_PLANE];
		else if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ARRIVE];
		else if (addPointer = &addEdittext[ARRIVE]) {
			addPointer = &addEdittext[DAY];

		}



	}
	void moveEdittextUp() {
		if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ID_FLIGHT];
		else if (addPointer == &addEdittext[ARRIVE]) {
			addPointer = &addEdittext[ID_PLANE];

		}
		else if (addPointer = &addEdittext[DAY])
			addPointer = &addEdittext[ARRIVE];



	}
	void moveEdittextRight() {
		if (addPointer == &addEdittext[DAY])
			addPointer = &addEdittext[MONTH];
		else if (addPointer == &addEdittext[MONTH])
			addPointer = &addEdittext[YEAR];
		else if (addPointer == &addEdittext[YEAR])
			addPointer = &addEdittext[HOUR];
		else if (addPointer == &addEdittext[HOUR])
			addPointer = &addEdittext[MINUTE];
	}
	void moveEdittextLeft() {
		if (addPointer == &addEdittext[MONTH])
			addPointer = &addEdittext[DAY];
		else if (addPointer == &addEdittext[YEAR])
			addPointer = &addEdittext[MONTH];
		else if (addPointer == &addEdittext[HOUR])
			addPointer = &addEdittext[YEAR];
		else if (addPointer == &addEdittext[MINUTE])
			addPointer = &addEdittext[HOUR];
	}
	void clearAddEdittextCursor() {
		addEdittext[ID_FLIGHT].clearCursor();
		addEdittext[ID_PLANE].clearCursor();
		addEdittext[DAY].clearCursor();
		addEdittext[MONTH].clearCursor();
		addEdittext[YEAR].clearCursor();
		addEdittext[HOUR].clearCursor();
		addEdittext[MINUTE].clearCursor();
		addEdittext[ARRIVE].clearCursor();
	}
	void  clearSearchEdittextCursor() {
		edittext[ID_FLIGHT].clearCursor();
		edittext[DAY].clearCursor();
		edittext[MONTH].clearCursor();
		edittext[YEAR].clearCursor();
		edittext[ARRIVE].clearCursor();

	}


	//------GET DATA
	//Ham lay du lieu thoi gian tu edittext
	Date   getDate() {
		Date d;
		strcpy_s(d.day, addEdittext[DAY].getCharData());
		strcpy_s(d.month, addEdittext[MONTH].getCharData());
		strcpy_s(d.year, addEdittext[YEAR].getCharData());
		strcpy_s(d.hour, addEdittext[HOUR].getCharData());
		strcpy_s(d.minute, addEdittext[MINUTE].getCharData());
		format(d);
		return d;

	}
	//Ham lay du lieu thoi gian tu search edittext
	Date  getDateFromSearch() {
		Date date;
		strcpy_s(date.day, edittext[DAY].getCharData());
		strcpy_s(date.month, edittext[MONTH].getCharData());
		strcpy_s(date.year, edittext[YEAR].getCharData());

		char s[3] = "00";
		strcpy_s(date.hour, s);
		strcpy_s(date.minute, s);

		format(date);
		return date;

	}
	//Lay chuyen bay
	Flight getFlight() {
		Flight f;
		strcpy_s(f.idFlight, addEdittext[ID_FLIGHT].getCharData());
		strcpy_s(f.idPlane, addEdittext[ID_PLANE].getCharData());
		strcpy_s(f.arrive, addEdittext[ARRIVE].getCharData());


		Date date = getDate();
		f.date = date;

		initTicketList(d->planeList, f);

		return f;
	}


	//----------HAM XU LI INPUT
	//Ham kiem tra tat ca du lieu de luu
	bool checkSaveData(bool isAdjust = 0) {

		clearAddEdittextCursor();

		if (!isAdjust) {
			if (addEdittext[ID_FLIGHT].isEmpty()) {
				drawAnounce(EMPTY);
				addPointer = &addEdittext[ID_FLIGHT];
				return false;
			}

			//Kiem tra trung ID Flight
			if (findFlight(d->flightList, addPointer->getCharData()) != NULL) {
				drawAnounce(DUP);
				addPointer = &addEdittext[ID_FLIGHT];
				return false;
			}

			if (addEdittext[ID_PLANE].isEmpty()) {
				drawAnounce(EMPTY);
				addPointer = &addEdittext[ID_PLANE];
				return false;
			}

			//Kiem tra ID PLane ton tai hay khong
			if (findPlane(d->planeList, addEdittext[ID_PLANE].getCharData()) == -1) {
				drawAnounce(PLANE_NOT_EXIST);
				addPointer = &edittext[ID_PLANE];
				return false;
			}

			if (addEdittext[ARRIVE].isEmpty()) {
				drawAnounce(EMPTY);
				addPointer = &addEdittext[ARRIVE];
				return false;
			}
		}

		addEdittext[ARRIVE].standarContent();

		if (addEdittext[DAY].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[DAY];
			return false;

		}

		if (!checkDay(addEdittext[DAY].getCharData())) {
			drawAnounce(DAY_ERROR);
			addPointer = &addEdittext[DAY];
			return false;
		}
		if (addEdittext[MONTH].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[MONTH];
			return false;

		}

		if (!checkMonth(addEdittext[MONTH].getCharData())) {
			drawAnounce(MONTH_ERROR);
			addPointer = &addEdittext[MONTH];
			return false;
		}
		if (addEdittext[YEAR].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[YEAR];
			return false;

		}

		if (!checkYear(addEdittext[YEAR].getCharData())) {
			drawAnounce(YEAR_ERROR);
			addPointer = &addEdittext[YEAR];
			return false;
		}
		if (addEdittext[HOUR].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[HOUR];
			return false;

		}

		if (!checkHour(addEdittext[HOUR].getCharData())) {
			drawAnounce(HOUR_ERROR);
			addPointer = &addEdittext[HOUR];
			return false;
		}
		if (addEdittext[MINUTE].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[MINUTE];
			return false;

		}

		if (!checkMinute(addEdittext[MINUTE].getCharData())) {
			drawAnounce(MINUTE_ERROR);
			addPointer = &addEdittext[MINUTE];
			return false;
		}
		Date date = getDate();

		//Ngay gio co hop le hay khong
		if (!checkTime(date)) {
			addPointer = &addEdittext[DAY];

			drawAnounce(TIME_ERROR);
			return false;
		}

		//Thoi gian khoi hanh > hien tai + 60
		if (!checkTimeBeforeMinute(date, 60)) {
			addPointer = &addEdittext[DAY];

			drawAnounce(BEFORE_ONE_HOUR);
			return false;
		}




		//CHeck co chuyen bay nao khac cung ID PLANE TRONG 12 tieng
		for (PTR k = d->flightList; k != NULL; k = k->next) {
			if ((!in12Hour(date, k->info.date) &&
				strcmp(k->info.idFlight, addEdittext[ID_FLIGHT].getCharData()) != 0
				&& strcmp(k->info.idPlane, addEdittext[ID_PLANE].getCharData()) == 0 &&
				k->info.status == 1 || k->info.status == 2)
				) {
				char mess[200] = "Unable to establish flight\n Because there is other flight\n ID: ";
				strcat_s(mess, k->info.idFlight);
				strcat_s(mess, "\n Time: ");
				strcat_s(mess, getDateString(k->info.date));
				strcat_s(mess, "\n Time must >= 12 hours from this flight");
				MessageBox(GetForegroundWindow(), (LPCWSTR)convertCharArrayToLPCWSTR(mess), (LPCWSTR)convertCharArrayToLPCWSTR("WARNING"), MB_ICONWARNING | MB_OK);
				addPointer = &addEdittext[ID_FLIGHT];

				return false;

			}
		}
		//Kiem tra co cung hanh khach nao dat 2 chuyen ma cho sua hay khong
		if (isAdjust) {

			PTR a = canEditTime(d->flightList, flightTemp, getDate());
			if (a != NULL) {
				char mess[300] = "Unable to edit time flight\n Because there is other flight\n ID: ";
				strcat_s(mess, a->info.idFlight);
				strcat_s(mess, "\n Time: ");
				strcat_s(mess, getDateString(a->info.date));

				strcat_s(mess, "\n Time must >= 12 hours from this flight");
				MessageBox(GetForegroundWindow(), (LPCWSTR)convertCharArrayToLPCWSTR(mess), (LPCWSTR)convertCharArrayToLPCWSTR("WARNING"), MB_ICONWARNING | MB_OK);
				addPointer = &addEdittext[ID_FLIGHT];
				return false;
			}


		}




		return true;
	}
	//Ham kiem tra tung loi edittext de luu
	bool checkEdittextError() {
		addPointer->clearCursor();

		if (addPointer->isEmpty()) {
			drawAnounce(EMPTY);
			return false;
		}

		if (addPointer == &addEdittext[ID_FLIGHT]) {
			//Kiem tra trung id flight
			if (findFlight(d->flightList, addPointer->getCharData()) != NULL) {
				addEdittext[ID_FLIGHT].clearText();

				drawAnounce(DUP);
				return false;
			}
		}

		if (addPointer == &addEdittext[ID_PLANE]) {
			//Kiem tra id plane co ton tai
			if (findPlane(d->planeList, addPointer->getCharData()) == -1) {
				drawAnounce(PLANE_NOT_EXIST);
				addEdittext[ID_PLANE].clearText();

				return false;
			}
		}


		if (addPointer == &addEdittext[DAY]) {
			if (!checkDay(addPointer->getCharData())) {
				drawAnounce(DAY_ERROR);
				return false;
			}

		}

		if (addPointer == &addEdittext[MONTH]) {


			if (!checkMonth(addPointer->getCharData())) {
				drawAnounce(MONTH_ERROR);
				return false;
			}

		}

		if (addPointer == &addEdittext[YEAR]) {


			if (!checkYear(addPointer->getCharData())) {
				drawAnounce(YEAR_ERROR);
				return false;
			}


		}

		if (addPointer == &addEdittext[HOUR]) {


			if (!checkHour(addPointer->getCharData())) {
				drawAnounce(HOUR_ERROR);
				return false;
			}


		}

		if (addPointer == &addEdittext[MINUTE]) {


			if (!checkMinute(addPointer->getCharData())) {
				drawAnounce(MINUTE_ERROR);
				return false;
			}


		}




		return true;
	}
	//Ham xu li input
	void inputHandel(bool isAdjust = false) {
		int c = FunctionTab::getInput();

		if (addPointer != NULL) {
			switch (c) {
			case -1: {
				addPointer->deleteChar();
				break;
			}

			case 1: {
				if (!isAdjust) {
					if (!checkEdittextError()) {

					}
					else
						moveEdittextUp();
				}



				break;
			}
			case 2: case 3: case 5: {

				if (!checkEdittextError()) {
				}
				else
				{
					if (addPointer == &addEdittext[ID_FLIGHT] || addPointer == &addEdittext[ID_PLANE] ||
						addPointer == &addEdittext[ARRIVE])
						moveEdittextDown();
					else
						moveEdittextRight();
				}

				break;
			}

			case 4: {
				if (!checkEdittextError()) {
				}
				else
					moveEdittextLeft();
				break;
			}
			default: {

				//Cho nhap chu hoa va so
				if (addPointer == &addEdittext[ID_FLIGHT] || addPointer == &addEdittext[ID_PLANE]) {
					if ((c <= 90 && c >= 65) || (c <= 57 && c >= 48))
						addPointer->addChar((char)c);

				}
				//cho nhap chu hoa
				else if (addPointer == &addEdittext[ARRIVE]) {
					if (c <= 90 && c >= 65)
						addPointer->addChar((char)c);

				}
				//cho nhap so
				else if (addPointer == &addEdittext[HOUR] || addPointer == &addEdittext[MINUTE] || addPointer == &addEdittext[DAY]
					|| addPointer == &addEdittext[MONTH] || addPointer == &addEdittext[YEAR]) {
					if (c <= 57 && c >= 48)
						addPointer->addChar((char)c);

				}



				break;


			}
			}
		}

	}
	//Ham xu li input cho search
	void  inputMainMenuHandel() {

		edittext[ID_FLIGHT].onAction(edittextPointer, true);
		edittext[DAY].onAction(edittextPointer, true);
		edittext[MONTH].onAction(edittextPointer, true);
		edittext[YEAR].onAction(edittextPointer, true);
		edittext[ID_FLIGHT].onAction(edittextPointer, true);
		edittext[ARRIVE].onAction(edittextPointer, true);


		int c = getInput();

		if (edittextPointer != NULL) {
			switch (c) {
			case -1: {
				edittextPointer->deleteChar();
				break;
			}

			default: {


				if (edittextPointer == &edittext[ID_FLIGHT]) {
					if ((c <= 90 && c >= 65) || (c <= 57 && c >= 48))
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[ARRIVE]) {
					if (c <= 90 && c >= 65)
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[DAY]
					|| edittextPointer == &edittext[MONTH] || edittextPointer == &edittext[YEAR]) {
					if (c <= 57 && c >= 48)
						edittextPointer->addChar((char)c);

				}



				break;


			}
			}
		}
	}

	//--------------------UI-------------------
	void  drawUI() {

		FunctionTab::drawBackground();

		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}
		case ADD_MENU: {

			drawAddMenu();
			break;
		}
		case FIND_PLANE_MENU: {

			drawFindPlane();
			break;
		}
		case ADJUST_MENU: {

			drawAjustScreen();
			break;
		}
		default:
			break;
		}
	}
	void drawMainMenu() {


		button[ADD].onAction();


		//Xu li ban phim cho loc thong tin
		inputMainMenuHandel();


		//Neu tat ca cac truong loc thong tin trong thi ve du lieu bth
		int s;
		if (checkAllEdittextIsEmpty())
			s = drawFlightData(flightTemp, d->flightList, d->planeList);

		else {
			currentPage = 1;
			clearSearchEdittextCursor();
			s = drawFilterData(flightTemp, d->flightList);

		}



		if (s == 1) {
			int d = drawAnounce(CANCEL_CONFIRM);
			switch (d) {
			case IDOK: {
				//Chi duoc cancle khi con ve hoac het ve
				if (!checkCancleFlight(flightTemp)) {
					drawAnounce(CANCLE_FLIGHT_ERROR);

				}
				else

					drawAnounce(SUCCESS);
				break;
			}
			default:
				break;
			}
		}
		else if (s == 2) {
			//Khong cho chinh sua neu bi huy hoăc hoan tat
			if (flightTemp->info.status == 0 || flightTemp->info.status == 3) {
				drawAnounce(ADJUST_ERROR);
				return;
			}
			//Khong cho chinh sua trong 30 phut cuoi
			if (!checkTimeBeforeMinute(flightTemp->info.date, 30)) {
				drawAnounce(THIRTY_MINUTE);
				return;
			}

			initAdjustScreen();
			currentMenu = ADJUST_MENU;
		}

		//-----------------VE HUONG DAN TEXT
		char a[40] = "*Left click to cancle flight";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit time flight");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);



		if (button[ADD].isClicked()) {
			resetAddEdittext();
			initAddMenu();
			currentMenu = ADD_MENU;

		}


	}
	void drawAddMenu() {
		addEdittext[ID_FLIGHT].onAction(addPointer);
		addEdittext[ID_PLANE].onAction(addPointer);
		addEdittext[ARRIVE].onAction(addPointer);
		addEdittext[STATUS].onAction(addPointer);
		addEdittext[DAY].onAction(addPointer);
		addEdittext[MONTH].onAction(addPointer);
		addEdittext[YEAR].onAction(addPointer);
		addEdittext[HOUR].onAction(addPointer);
		addEdittext[MINUTE].onAction(addPointer);

		button[SAVE].onAction();
		button[BACK].onAction();
		button[FIND].onAction();



		char s[200] = "Time >= an hour from now";
		drawText(addEdittext[DAY].getLeft(),
			addEdittext[DAY].getTop() - textheight(s) - 10, s, RED);

		strcpy_s(s, "ADD FLIGHT");
		drawTitle(s);

		//-----------------VE HUONG DAN TEXT
		strcpy_s(s, "*Use Up/Down/Left/Right/Enter button");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 30, s);

		inputHandel();

		if (button[SAVE].isClicked()) {
			if (!checkSaveData()) {


			}
			else {

				Flight p = getFlight();
				insertAfter(d->flightList, p);
				drawAnounce(SUCCESS);
				resetAddEdittext();
				initAddMenu();

			}
		}

		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetSearchEdittext();
				resetAddEdittext();
				currentMenu = MAIN_MENU;
				break;
			}
			default:
				break;
			}

		}

		if (button[FIND].isClicked()) {
			manage.setCurrentPage(1);
			delay(50);
			currentMenu = FIND_PLANE_MENU;

		}


	}
	void drawAjustScreen() {

		char s[200] = "ADJUST FLIGHT";
		drawTitle(s);

		strcpy_s(s, "*Use left/right key to navigate");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, s);

		strcpy_s(s, "Time >= an hour from now");
		drawText(addEdittext[DAY].getLeft(),
			addEdittext[DAY].getTop() - textheight(s) - 10, s, RED);

		addEdittext[ID_FLIGHT].onAction(addPointer);
		addEdittext[ID_PLANE].onAction(addPointer);
		addEdittext[ARRIVE].onAction(addPointer);
		addEdittext[STATUS].onAction(addPointer);
		addEdittext[DAY].onAction(addPointer);
		addEdittext[MONTH].onAction(addPointer);
		addEdittext[YEAR].onAction(addPointer);
		addEdittext[HOUR].onAction(addPointer);
		addEdittext[MINUTE].onAction(addPointer);

		inputHandel(true);

		button[BACK].onAction();
		button[SAVE].onAction();




		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				reset();
				break;
			}
			default:
				break;
			}

		}

		if (button[SAVE].isClicked()) {
			//Khong cho chinh sua neu  hoan tat
			if (flightTemp->info.status == 3) {
				reset();
				drawAnounce(ADJUST_ERROR);
				return;
			}
			//Neu luc save da lo qua 30 phut tu dong out ma ko cho luu
			if (!checkTimeBeforeMinute(flightTemp->info.date, 30)) {
				reset();
				drawAnounce(THIRTY_MINUTE);
				return;

			}
			if (!checkSaveData(1)) {

			}
			else
			{
				Date date = getDate();
				adjustFlight(flightTemp, date);
				reset();
				drawAnounce(SUCCESS);


			}
		}

	}
	void drawFindPlane() {

		int s = manage.drawPlaneData(d->planeList, indexID);
		if (s == 1) {
			addEdittext[ID_PLANE].customInitChar(d->planeList.data[indexID]->idPlane);
			currentMenu = ADD_MENU;
			delay(50);

		}

		button[BACK].onAction();

		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				currentMenu = ADD_MENU;
				break;
			}
			default:
				break;
			}
		}


	}

	//---------------DRAW DATA---------------
	void drawOneFlight(int preY, int i, PTR& k) {
		setbkcolor(SUBWINDOW_BACKGROUND);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 8;
		int preX = LEFT_BORDER;

		//VE STT
		char temp[200];
		sprintf_s(temp, "%d", i + 1);
		int x = preX + 100;
		drawText(preX, preY, x, temp);
		preX = x;

		//VE ID FLIGHT
		x = preX + spaceX;
		drawText(preX, preY, x, k->info.idFlight);
		preX = x;

		//VE ID PLANE
		x = preX + spaceX;
		drawText(preX, preY, x, k->info.idPlane);
		preX = x;


		//VE TIME
		sprintf_s(temp, getDateString(k->info.date));
		x = preX + spaceX;
		drawText(preX, preY, x, temp);
		preX = x;


		//VE ARRIVE
		x = preX + spaceX;
		drawText(preX, preY, x, k->info.arrive);
		preX = x;


		//VE TRANG THAI
		x = preX + spaceX;
		switch (k->info.status) {
		case 0: {
			strcpy_s(temp, "CANCLED");
			break;
		}
		case 1: {
			strcpy_s(temp, "HAVE TICKET");
			break;
		}
		case 2: {
			strcpy_s(temp, "SOLD OUT");
			break;
		}
		case 3: {
			strcpy_s(temp, "COMPLETED");
			break;
		}
		default:
			break;
		}
		drawText(preX, preY, x, temp);
		preX = x;


		//VE VE CON/TONG VE
		x = RIGHT_BORDER;
		sprintf_s(temp, "%d", countTicketLeft(k));
		strcat_s(temp, " / ");
		char a[200];
		sprintf_s(a, "%d", k->info.totalTicket);
		strcat_s(temp, a);
		drawText(preX, preY, x, temp);






	}
	//Ve bang du lieu data
	int drawFlightData(PTR& flightTemp, PTR& flightList, PlaneList& planeList) {

		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;


		drawBorder(7, 1, isEmpty(flightList));

		checkCompletedAll(flightList, planeList);// Tu dong chuyen sang completed/cancle
		onButtonPage(size(flightList), currentPage); //Su kien nut left / right
		showPage(currentPage); //Hien thi trang


		int cnt = 0;
		PTR k = flightList;


		while (k != NULL && cnt < startPage) {
			k = k->next;
			cnt++;
		}

		int res = -1;
		flightTemp = NULL;
		for (int i = startPage; k != NULL && i < (startPage + 10); i++) {

			flightTemp = k;
			int preX = LEFT_BORDER;

			setcolor(BLACK);
			//tu dong cap nhat  het ve
			if (k->info.status == 1 || k->info.status == 2)
				checkFull(k);
			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			drawOneFlight(preY, i, k);

			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				return 1;

			}

			if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{
				return 2;

			}
			preY += spaceY;
			k = k->next;
		}


		return -1;


	}
	//Ve data khi loc
	int drawFilterData(PTR& flightTemp, PTR& flightList, bool haveTicket = false) {

		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;
		PTR* beginPage = new PTR[size(flightList) + 2];
		beginPage[1] = NULL;
		int pageSize = 0;


		clearSearchEdittextCursor();
		Date date = getDateFromSearch();

		int size = 0;
		int cnt = 1;
		int t = 1;

		for (PTR k = flightList; k != NULL; k = k->next) {
			if (
				(edittext[ID_FLIGHT].isEmpty() || isPrefix(edittext[ID_FLIGHT].getCharData(), k->info.idFlight))
				&& (edittext[DAY].isEmpty() || strcmp(date.day, k->info.date.day) == 0)
				&& (edittext[MONTH].isEmpty() || strcmp(date.month, k->info.date.month) == 0)
				&& (edittext[YEAR].isEmpty() || isPrefix(date.year, k->info.date.year))
				&& (edittext[ARRIVE].isEmpty() || isPrefix(edittext[ARRIVE].getCharData(), k->info.arrive))
				)
			{

				if (cnt % 10 == 1) {
					pageSize++;
					beginPage[pageSize] = new FlightNode;
					beginPage[pageSize] = k;

					cnt = 1;
				}
				cnt++;
				size++;



			}
		}





		drawBorder(7, 1, size == 0);
		onButtonPage(size, currentFilterPage); //Su kien nut left / right
		showPage(currentFilterPage); //Hien thi trang


		PTR k = beginPage[currentFilterPage];
		int i = startPage;


		while (k != NULL && i < (startPage + 10)) {
			flightTemp = NULL;

			if (
				(edittext[ID_FLIGHT].isEmpty() || isPrefix(edittext[ID_FLIGHT].getCharData(), k->info.idFlight))
				&& (edittext[DAY].isEmpty() || strcmp(date.day, k->info.date.day) == 0)
				&& (edittext[MONTH].isEmpty() || strcmp(date.month, k->info.date.month) == 0)
				&& (edittext[YEAR].isEmpty() || isPrefix(date.year, k->info.date.year))
				&& (edittext[ARRIVE].isEmpty() || isPrefix(edittext[ARRIVE].getCharData(), k->info.arrive))
				)
			{
				if (!haveTicket || (haveTicket && k->info.status == 2 || k->info.status == 1)) {
					flightTemp = k;
					int preX = LEFT_BORDER;

					setcolor(BLACK);


					if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
						setcolor(ON_SELECTED_DATA_COLOR);
					}


					drawOneFlight(preY, i, k);

					if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
						return  1;

					}

					else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
					{
						return   2;

					}
					preY += spaceY;
					i++;
				}
			}
			k = k->next;
		}


		return -1;


	}




};