#pragma once


#ifndef MANAGE_PLANE_H
#define MANAGE_PLANE_H

#include"Planes.h"
#include"Flights.h"
#include"Passengers.h"
#include"FunctionTab.h"
#include"Data.h"
using namespace std;
class ManagePlanesTab :public FunctionTab {


private:

	EditText* adjustEditextPointer;
	Data *d;
	int indexID = -1;
	int currentSeats = 0;
public:
	ManagePlanesTab() {

	}
	ManagePlanesTab(Data* d) {
		this->d = d;
		initEdittext();

		edittextPointer = &edittext[ID_PLANE];
		


	}
	~ManagePlanesTab() {
		//delete adjustEditextPointer;
		
	}

	void initEdittext() {

		//---------EDITTEXT ID
		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";

		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITTEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 100;
		int right = left + EDITTEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;

		//------------EDITTEXT ID PLANE
		edittext[ID_PLANE] = EditText(hint, title, content, left, top, right, bottom, MAX_ID_PLANE);


		//------------EDITTEXT TYPE
		strcpy_s(title, "TYPE");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[TYPE] = EditText(hint, title, content, left, top, right, bottom, MAX_TYPE_PLANE);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, "20-50");
		strcpy_s(title, "SEATS");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[SEATS] = EditText(hint, title, content, left, top, right, bottom, 2);



	}
	void initAdjustMenu(Plane* p, bool isAvai) {


		//Neu da thanh lap chuyen bay nhung chua bay
		edittext[ID_PLANE].setActive(false);


		if (!isAvai) {
			edittext[TYPE].setActive(false);
			adjustEditextPointer = &edittext[SEATS];

		}
		else {
			edittext[TYPE].setActive(true);
			adjustEditextPointer = &edittext[TYPE];
		}

		edittext[ID_PLANE].customInitChar(p->idPlane);
		edittext[TYPE].customInitChar(p->type);
		edittext[SEATS].customInitNum(p->seats);

	}
	void initAddMenu() {
		edittextPointer = &edittext[ID_PLANE];
		edittext[ID_PLANE].setActive(true);
		edittext[TYPE].setActive(true);
		
	}

	

	//Lay du lieu may bay tu edittext
	Plane getPlaneData() {
		Plane p;

		edittext[ID_PLANE].clearCursor();
		strcpy_s(p.idPlane, edittext[ID_PLANE].getCharData());

		edittext[TYPE].clearCursor();
		strcpy_s(p.type, edittext[TYPE].getCharData());

		edittext[SEATS].clearCursor();
		p.seats = edittext[SEATS].getIntData();

		return p;

	}

	//Xoa  het du lieu 3 edittext
	void resetEdittext() {
		edittext[ID_PLANE].clearText();
		edittext[TYPE].clearText();
		edittext[SEATS].clearText();

	}
	void reset() {
		FunctionTab::reset();

	}




	void moveEdittextDown(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[ID_PLANE])
			edittextPointer = &edittext[TYPE];
		else if (edittextPointer == &edittext[TYPE]) {
			edittextPointer->standarContent();
			edittextPointer = &edittext[SEATS];

		}

	}
	void moveEdittextUp(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[TYPE]) {
			edittextPointer->standarContent();
			if (edittext[ID_PLANE].isActive())
				edittextPointer = &edittext[ID_PLANE];

		}
		else if (edittextPointer == &edittext[SEATS])
			if (edittext[TYPE].isActive())
				edittextPointer = &edittext[TYPE];

	}

	//Neu adjust = 1 thi ap dung cho adjust screen ko check plane ID
	bool checkEdittextError(EditText*& edittextPointer, bool adjust = false) {
		edittextPointer->clearCursor();

		if (!adjust) {
			if (edittextPointer == &edittext[ID_PLANE]) {
				if (edittextPointer->isEmpty()) {
					drawAnounce(EMPTY);
					return false;
				}
				if (checkDupIDPlane(d->planeList, edittextPointer->getCharData())) {
					drawAnounce(DUP);
					return false;
				}
			}
		}



		if (edittextPointer == &edittext[TYPE]) {
			if (edittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
		}



		if (edittextPointer == &edittext[SEATS]) {
			if (edittextPointer->isEmpty()) {
				drawAnounce(EMPTY);
				return false;
			}
			if (!checkSeat(edittextPointer->getIntData())) {
				drawAnounce(SEAT_ERROR);
				return false;
			}
		}




		return true;
	}
	bool checkSaveData(EditText*& edittextPointer, bool adjust = false) {

		edittext[ID_PLANE].clearCursor();
		edittext[TYPE].clearCursor();
		edittext[SEATS].clearCursor();

		if (!adjust) {
			if (edittext[ID_PLANE].isEmpty()) {
				drawAnounce(EMPTY);
				edittextPointer = &edittext[ID_PLANE];
				return false;
			}

			if (checkDupIDPlane(d->planeList, edittext[ID_PLANE].getCharData())) {
				drawAnounce(DUP);
				edittextPointer = &edittext[ID_PLANE];
				return false;
			}
		}



		if (edittext[TYPE].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[TYPE];
			return false;
		}

		edittext[TYPE].standarContent();


		if (edittext[SEATS].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[SEATS];
			return false;
		}

		if (!checkSeat(edittext[SEATS].getIntData())) {
			drawAnounce(SEAT_ERROR);
			edittextPointer = &edittext[SEATS];
			return false;
		}

		if (!isGreaterSeat(currentSeats, edittext[SEATS].getIntData())) {
			drawAnounce(GREATER_SEAT);
			edittextPointer = &edittext[SEATS];
			return false;
		}



		return true;
	}


	//Xu li su kien ban phim nhap edittext
	void inputHandel(EditText*& edittextPointer, bool adjust) {
		int c = FunctionTab::getInput();

		if (edittextPointer != NULL) {
			switch (c) {
			case -1: {
				edittextPointer->deleteChar();
				break;
			}
			case 1: {
				if (!checkEdittextError(edittextPointer, adjust)) {

				}
				else
					moveEdittextUp(edittextPointer);


				break;
			}
			case 3: case 2: {

				if (!checkEdittextError(edittextPointer, adjust)) {

				}
				else
					moveEdittextDown(edittextPointer);
				break;
			}
			default: {


				if (edittextPointer == &edittext[ID_PLANE]) {
					if ((c <= 90 && c >= 65) || (c <= 57 && c >= 48))
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[TYPE]) {
					if (c <= 90 && c >= 65 || c == ' ')
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[SEATS]) {
					if (c <= 57 && c >= 48)
						edittextPointer->addChar((char)c);

				}



				break;


			}
			}
		}

	}



	//---------------------------------UI-------------------------
	void drawUI() {
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
		case ADJUST_MENU: {
			drawAjustMenu();
			break;
		}

		default:
			break;



		}

	}
	void drawMainMenu() {

		//-----------VE BUTTON
		button[ADD].onAction();
		button[SHOW].onAction();


		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Left click to delete item";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit item");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);
		

		strcpy_s(a, "LIST OF PLANE");
		drawTitle((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 20, a);


		int s = FunctionTab::drawPlaneData(4, d->planeList, indexID);
		if (s == 1) {
			int s = drawAnounce(DELETE);
			switch (s) {
			case IDOK: {
				removePlane(d->planeList, indexID);
				break;
			}
			case IDCANCEL: {
				break;
			}
			default:
				break;
			}

		}
		else if (s == 2) {

			currentSeats = d->planeList.data[indexID]->seats;

			initAdjustMenu(d->planeList.data[indexID], d->planeList.data[indexID]->isAvai);
			currentMenu = ADJUST_MENU;
			return;
			
		}


		if (button[ADD].isClicked()) {
			initAddMenu();
			currentMenu = ADD_MENU;
		}

		else if (button[SHOW].isClicked()) {
			currentMenu = SHOW_MENU;
		}

	}
	void drawAddMenu() {

		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		button[BACK].onAction();
		button[SAVE].onAction();


		edittext[ID_PLANE].onAction(edittextPointer);
		edittext[TYPE].onAction(edittextPointer);
		edittext[SEATS].onAction(edittextPointer);

		inputHandel(edittextPointer, false);


		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetEdittext();
				edittextPointer = &edittext[ID_PLANE];
				currentMenu = MAIN_MENU;
				break;
			}
			default:
				break;
			}

		}
		if (button[SAVE].isClicked()) {

			if (!checkSaveData(edittextPointer, false)) {

			}
			else {
				Plane p = getPlaneData();
				addPlane(d->planeList, p);
				drawAnounce(SUCCESS);
				resetEdittext();
				edittextPointer = &edittext[ID_PLANE];


			}


		}


	}
	void drawAjustMenu() {

		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		button[BACK].onAction();
		button[SAVE].onAction();

		edittext[ID_PLANE].onAction(adjustEditextPointer);
		edittext[TYPE].onAction(adjustEditextPointer);
		edittext[SEATS].onAction(adjustEditextPointer);

		inputHandel(adjustEditextPointer, 1);

		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetEdittext();
				currentMenu = MAIN_MENU;
				break;
			}

			default:
				break;
			}

		}
		else if (button[SAVE].isClicked()) {

			if (!checkSaveData(adjustEditextPointer, 1)) {

			}
			else {
				Plane p = getPlaneData();
				adjustPlane(d->planeList, p, this->indexID);
				drawAnounce(SUCCESS);
				resetEdittext();
				currentMenu = MAIN_MENU;
			}


		}



	}



		


	

};
#endif