﻿#pragma once


#include"Flights.h"
#include"FunctionTab.h"
#include"ManagePlanesTab.h"

class ManageFlightsTab :public FunctionTab {
protected:
	EditText addEdittext[MAX_EDITTEXT];

	int indexID = -1;

	PTR first;
	PTR tempFlight;
	EditText * addPointer;

	PlaneList planeList;
	ManagePlanesTab managePlane;

	char dataPerPage[60][41];
public:

	ManageFlightsTab() {

		initializeList(first);
		readFileFlight(first);
		initEdittext();

		edittextPointer = NULL;
		addPointer = &addEdittext[ID_FLIGHT];

		
	}

	~ManageFlightsTab() {
		deleteList(first);
		delete addPointer;
		
	}
	
	void initEdittext() {

		int left = LEFT_BORDER;
		int top = SUBWINDOW_TOP + 5;
		int right = left + 150;
		int bottom = top + EDITTEXT_HEIGHT;

		char hint[30] = "";
		char title[30] = "FLIGHT ID";
		char content[30] = "";

		//------------EDITTEXT ID FLIGHT
		edittext[ID_FLIGHT] = EditText(hint, title, content, left, top, right, bottom, 15);


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
		strcpy_s(hint, "");
		left = right + EDITTEXT_SPACE;
		right = RIGHT_BORDER;
		edittext[ARRIVE] = EditText(hint, title, content, left, top, right, bottom, 40, 55);


		initCompoAddFlight();


	}
	void initCompoAddFlight() {
		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITTEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 70;
		int right = left + EDITTEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;

		//------------EDITTEXT ID FLIGHT
		char hint[30] = "Do not leave empty!";
		char title[30] = "FLIGHT ID";
		char content[30] = "";
		addEdittext[ID_FLIGHT] = EditText(hint, title, content, left, top, right, bottom, 15);

		//------------EDITTEXT ID PLANE
		strcpy_s(title, "PLANE ID");
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[ID_PLANE] = EditText(hint, title, content, left, top, right, bottom, 15);

		//-----------BUTTON TIM KIEM MAY BAY
		strcpy_s(title, "FIND");
		button[FIND] = Button(right + 10, top, right + 60, bottom, BUTTON_BACKGROUND,
			WHITE, title,
			BUTTON_TEXT_COLOR);


		//------------EDITTEXT ARRIVE
		strcpy_s(title, "ARRIVE");
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[ARRIVE] = EditText(hint, title, content, left, top, right, bottom, 15);

		//------------EDITTEXT ARRIVE
		strcpy_s(title, "STATUS");
		strcpy_s(hint, "");
		strcpy_s(content, "HAVE TICKET");
		right = left + 100;
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[STATUS] = EditText(hint, title, content, left, top, right, bottom, 15);



		//------------EDITTEXT DAY

		strcpy_s(title, "TIME");
		right = left + 50;
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[DAY] = EditText(hint, title, content, left, top, right, bottom, 2);

		//------------EDITTEXT MONTH

		strcpy_s(title, "/");
		left = right + 15;
		right = left + 70;
		addEdittext[MONTH] = EditText(hint, title, content, left, top, right, bottom, 2, 10);


		//------------EDITTEXT YEAR

		strcpy_s(title, "/");
		left = right + 15;
		right = left + 70;
		addEdittext[YEAR] = EditText(hint, title, content, left, top, right, bottom, 4, 10);


		//------------EDITTEXT HOUR

		strcpy_s(title, "AT");
		left = right + 70;
		right = left + 70;
		addEdittext[HOUR] = EditText(hint, title, content, left, top, right, bottom, 4, 25);


		//------------EDITTEXT MINUTE

		strcpy_s(title, ":");
		left = right + 15;
		right = left + 70;
		addEdittext[MINUTE] = EditText(hint, title, content, left, top, right, bottom, 4, 10);



		customEdittext();



	}
	void initAdjustScreen() {
		addPointer = &addEdittext[DAY];


		addEdittext[ID_FLIGHT].customInitChar(tempFlight->info.idFlight);
		addEdittext[ID_FLIGHT].setActive(false);


		addEdittext[ID_PLANE].customInitChar(tempFlight->info.idPlane);
		addEdittext[ID_PLANE].setActive(false);


		addEdittext[ARRIVE].customInitChar(tempFlight->info.arrive);
		addEdittext[ARRIVE].setActive(false);


		addEdittext[STATUS].customInitChar(tempFlight->info.arrive);


		addEdittext[DAY].customInitNum(tempFlight->info.date.day);


		addEdittext[MONTH].customInitNum(tempFlight->info.date.month);


		addEdittext[YEAR].customInitNum(tempFlight->info.date.year);



		addEdittext[HOUR].customInitNum(tempFlight->info.date.hour);


		addEdittext[MINUTE].customInitNum(tempFlight->info.date.minute);
	}

	void reset() {
		FunctionTab::reset();
		resetEdittext();
		writeFileFlight(first);
	}
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

		addPointer = &addEdittext[ID_FLIGHT];
	}
	void resetEdittext() {
		edittext[ID_FLIGHT].clearText();
		edittext[DAY].clearText();
		edittext[MONTH].clearText();
		edittext[YEAR].clearText();
		edittext[ARRIVE].clearText();

		edittextPointer = NULL;
	}
	void customEdittext() {
		char s[30] = "HAVE TICKET";

		addEdittext[STATUS].customInitChar(s);
		addEdittext[STATUS].setActive(false);
		addEdittext[MINUTE].customInitNum(getCurTime().minute);
		addEdittext[HOUR].customInitNum(getCurTime().hour);
		addEdittext[YEAR].customInitNum(getCurTime().year);
		addEdittext[MONTH].customInitNum(getCurTime().month);
		addEdittext[DAY].customInitNum(getCurTime().day);


	}

	
	void moveEdittextDown() {
		if (addPointer == &addEdittext[ID_FLIGHT])
			addPointer = &addEdittext[ID_PLANE];
		else if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ARRIVE];
		else if (addPointer = &addEdittext[ARRIVE])
			addPointer = &addEdittext[DAY];



	}
	void moveEdittextUp() {
		if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ID_FLIGHT];
		else if (addPointer == &addEdittext[ARRIVE])
			addPointer = &addEdittext[ID_PLANE];
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

	
	Date getDate() {
		Date d;
		d.day = addEdittext[DAY].getIntData();
		d.month = addEdittext[MONTH].getIntData();
		d.year = addEdittext[YEAR].getIntData();
		d.hour = addEdittext[HOUR].getIntData();
		d.minute = addEdittext[MINUTE].getIntData();
		return d;
	}
	Flight getFlight() {
		Flight f;
		strcpy_s(f.idFlight, addEdittext[ID_FLIGHT].getCharData());
		strcpy_s(f.idPlane, addEdittext[ID_PLANE].getCharData());
		strcpy_s(f.arrive, addEdittext[ARRIVE].getCharData());

		f.status = 1;
		f.date.day = addEdittext[DAY].getIntData();
		f.date.month = addEdittext[MONTH].getIntData();
		f.date.year = addEdittext[YEAR].getIntData();
		f.date.hour = addEdittext[HOUR].getIntData();
		f.date.minute = addEdittext[MINUTE].getIntData();
		return f;
	}

	bool checkSaveData(bool isAdjust = 0) {

		addEdittext[ID_FLIGHT].clearCursor();
		addEdittext[ID_PLANE].clearCursor();
		addEdittext[DAY].clearCursor();
		addEdittext[MONTH].clearCursor();
		addEdittext[YEAR].clearCursor();
		addEdittext[HOUR].clearCursor();
		addEdittext[MINUTE].clearCursor();
		addEdittext[ARRIVE].clearCursor();

		if (!isAdjust) {
			if (addEdittext[ID_FLIGHT].isEmpty()) {
				drawAnounce(EMPTY);
				addPointer = &addEdittext[ID_FLIGHT];
				return false;
			}

			if (checkDupIDFlight(first, addEdittext[ID_FLIGHT].getCharData())) {
				drawAnounce(DUP);
				addPointer = &addEdittext[ID_FLIGHT];
				return false;
			}

			if (addEdittext[ID_PLANE].isEmpty()) {
				drawAnounce(EMPTY);
				addPointer = &addEdittext[ID_PLANE];
				return false;
			}

			if (findPlane(planeList, addEdittext[ID_PLANE].getCharData()) == -1) {
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
		if (addEdittext[DAY].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[DAY];
			return false;

		}

		if (!checkDay(addEdittext[DAY].getIntData())) {
			drawAnounce(DAY_ERROR);
			addPointer = &addEdittext[DAY];
			return false;
		}
		if (addEdittext[MONTH].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[MONTH];
			return false;

		}

		if (!checkMonth(addEdittext[MONTH].getIntData())) {
			drawAnounce(MONTH_ERROR);
			addPointer = &addEdittext[MONTH];
			return false;
		}
		if (addEdittext[YEAR].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[YEAR];
			return false;

		}

		if (!checkYear(addEdittext[YEAR].getIntData())) {
			drawAnounce(YEAR_ERROR);
			addPointer = &addEdittext[YEAR];
			return false;
		}
		if (addEdittext[HOUR].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[HOUR];
			return false;

		}

		if (!checkHour(addEdittext[HOUR].getIntData())) {
			drawAnounce(HOUR_ERROR);
			addPointer = &addEdittext[HOUR];
			return false;
		}
		if (addEdittext[MINUTE].isEmpty()) {
			drawAnounce(EMPTY);
			addPointer = &addEdittext[MINUTE];
			return false;

		}

		if (!checkMinute(addEdittext[MINUTE].getIntData())) {
			drawAnounce(MINUTE_ERROR);
			addPointer = &addEdittext[MINUTE];
			return false;
		}



		if (!checkFutureTime(getDate())) {
			drawAnounce(TIME_ERROR);
			return false;
		}




		return true;
	}
	bool checkEdittextError() {
		addPointer->clearCursor();

		if (addPointer->isEmpty()) {
			drawAnounce(EMPTY);
			return false;
		}

		if (addPointer == &addEdittext[ID_FLIGHT]) {

			if (checkDupIDFlight(first, addPointer->getCharData())) {
				drawAnounce(DUP);
				return false;
			}
		}

		if (addPointer == &addEdittext[ID_PLANE]) {

			if (findPlane(planeList, addPointer->getCharData()) == -1) {
				drawAnounce(PLANE_NOT_EXIST);
				return false;
			}
		}


		if (addPointer == &addEdittext[DAY]) {


			if (!checkDay(addPointer->getIntData())) {
				drawAnounce(DAY_ERROR);
				return false;
			}

		}

		if (addPointer == &addEdittext[MONTH]) {


			if (!checkMonth(addPointer->getIntData())) {
				drawAnounce(MONTH_ERROR);
				return false;
			}

		}

		if (addPointer == &addEdittext[YEAR]) {


			if (!checkYear(addPointer->getIntData())) {
				drawAnounce(YEAR_ERROR);
				return false;
			}


		}

		if (addPointer == &addEdittext[HOUR]) {


			if (!checkHour(addPointer->getIntData())) {
				drawAnounce(HOUR_ERROR);
				return false;
			}


		}

		if (addPointer == &addEdittext[MINUTE]) {


			if (!checkMinute(addPointer->getIntData())) {
				drawAnounce(MINUTE_ERROR);
				return false;
			}


		}




		return true;
	}
	

	void inputHandel() {
		int c = FunctionTab::getInput();

		if (addPointer != NULL) {
			switch (c) {
			case -1: {
				addPointer->deleteChar();
				break;
			}
			case 1: {
				if (!checkEdittextError()) {

				}
				else
					moveEdittextUp();


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


				if (addPointer == &addEdittext[ID_FLIGHT] || addPointer == &addEdittext[ID_PLANE]) {
					if ((c <= 90 && c >= 65) || (c <= 57 && c >= 48))
						addPointer->addChar((char)c);

				}
				else if (addPointer == &addEdittext[ARRIVE]) {
					if (c <= 90 && c >= 65 || c == ' ')
						addPointer->addChar((char)c);

				}
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
	void inputMainMenuHandel() {

		if (edittext[ID_FLIGHT].getIsCliked())
			edittextPointer = &edittext[ID_FLIGHT];
		else if (edittext[ID_FLIGHT].getIsCliked())
			edittextPointer = &edittext[ID_FLIGHT];
		else if (edittext[DAY].getIsCliked())
			edittextPointer = &edittext[DAY];
		else if (edittext[MONTH].getIsCliked())
			edittextPointer = &edittext[MONTH];
		else if (edittext[YEAR].getIsCliked())
			edittextPointer = &edittext[YEAR];
		else if (edittext[ARRIVE].getIsCliked())
			edittextPointer = &edittext[ARRIVE];

		int c = FunctionTab::getInput();

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
					if (c <= 90 && c >= 65 || c == ' ')
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


	void  drawUI() {
	
		switch (currentMenu) {
		case MAIN_MENU: {
			resetAddEdittext();
			drawMainMenu();
			break;
		}
		case ADD_MENU: {

			drawAddMenu();
			break;
		}
		case FIND_PLANE: {
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
		drawBackground();

		edittext[ID_FLIGHT].onAction(edittextPointer);
		edittext[DAY].onAction(edittextPointer);
		edittext[MONTH].onAction(edittextPointer);
		edittext[YEAR].onAction(edittextPointer);
		edittext[ARRIVE].onAction(edittextPointer);

		button[ADD].onAction();
		button[LEFT].onAction();
		button[RIGHT].onAction();

		int s= drawFlightData(6, first, tempFlight);
		if (s == 1) {
			drawAnounce(SUCCESS);
		}
		inputMainMenuHandel();
		

		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Left click to cancle flight";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit flight");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);
		strcpy_s(a, " Use left/right/enter button");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 60, a);


		
		if (button[ADD].isClicked()) {
			resetEdittext();
			customEdittext();
			currentMenu = ADD_MENU;
			drawUI();
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

		inputHandel();

		if (button[SAVE].isClicked()) {
			if (!checkSaveData()) {


			}
			else {
				Flight p = getFlight();
				insertAfter(first, p);
				drawAnounce(SUCCESS);
				resetAddEdittext();

				customEdittext();


			}
		}

		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
			drawUI();
		}

		if (button[FIND].isClicked()) {
			currentMenu = FIND_PLANE;
			drawUI();
		}


	}
	void drawAjustScreen() {
		addEdittext[ID_FLIGHT].onAction(addPointer);
		addEdittext[ID_PLANE].onAction(addPointer);
		addEdittext[ARRIVE].onAction(addPointer);
		addEdittext[STATUS].onAction(addPointer);
		addEdittext[DAY].onAction(addPointer);
		addEdittext[MONTH].onAction(addPointer);
		addEdittext[YEAR].onAction(addPointer);
		addEdittext[HOUR].onAction(addPointer);
		addEdittext[MINUTE].onAction(addPointer);
		inputHandel();

		button[BACK].onAction();
		button[SAVE].onAction();

		

		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
			drawUI();
		}
		if (button[SAVE].isClicked()) {
			if (!checkSaveData(1)) {

			}
			else
			{
				adjustFlight(tempFlight, getDate());
				drawAnounce(SUCCESS);
				currentMenu = MAIN_MENU;
				drawUI();
			}
		}

	}
	void drawFindPlane() {

		
		int s = drawPlaneData(4, planeList,indexID);
		if (s == 1) {
			addEdittext[ID_PLANE].customInitChar(planeList.data[indexID]->idPlane);
			currentMenu = ADD_MENU;

		}
		
	}
	



};