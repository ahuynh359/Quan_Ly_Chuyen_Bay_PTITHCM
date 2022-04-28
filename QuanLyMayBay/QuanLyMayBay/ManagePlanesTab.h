#pragma once

#include "Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Planes.h"
#include"FunctionTab.h"


class ManagePlanesTab :public FunctionTab {
private:
	PlaneList planeList;

	Button button[MAX_BUTTON];
	EditText edittext[MAX_EDITTEXT];
	EditText* buttonPointer, * edittextPointer, * adjustEditextPointer;
	int indexID = -1;
public:


	ManagePlanesTab() {

		initButton();
		initEdittext();
		readFilePlane(planeList);

		edittextPointer = &edittext[ID_PLANE];
		adjustEditextPointer = &edittext[TYPE];
	}
	~ManagePlanesTab() {
		writeFilePlane(planeList);
		delete buttonPointer;
		delete edittextPointer;
		delete adjustEditextPointer;
	}

	//------------INIT--------
	void initButton() {

		//-------------BUTTON THEM
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 50;
		int right = left + 50;
		int bottom = top + 50;
		char a[15] = "ADD";
		button[ADD] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a,
			BUTTON_TEXT_COLOR);


		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[LEFT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);
		//--------------BUTTON PHAI
		left = right + 70;
		right = left + 50;
		strcpy_s(a, ">");
		button[RIGHT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
		button[BACK] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60,
			BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[SAVE] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30,
			SUBWINDOW_BOTTOM - 50, BUTTON_BACKGROUND, WHITE, a, BUTTON_TEXT_COLOR);


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

		edittext[ID_PLANE] = EditText(hint, title, content, left, top, right, bottom, MAX_ID_PLANE);
		strcpy_s(title, "Can't be modified");


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
	void resetInLine() {
		edittext[ID_PLANE].clearText();
		edittext[TYPE].clearText();
		edittext[SEATS].clearText();
	}
	void freeMemory() {
		currentMenu = MAIN_MENU;
		writeFilePlane(planeList);

	}


	void resetEdittext() {
		edittext[ID_PLANE].clearText();
		edittext[TYPE].clearText();
		edittext[SEATS].clearText();

	}
	void dataPerPage() {

		maxPage = ceil((planeList.size + 0.0) / 10);

		if (currentPage > maxPage)
			currentPage--;

		currentPage = max(1, currentPage);
		maxPage = max(maxPage, 1);

		startPage = currentPage - 1;
		startPage = startPage * 10 + 1;

		//Toi da 10 du lieu 1 trang
		endPage = min(startPage + 9, planeList.size);
	}

	void moveEdittextDown(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[ID_PLANE])
			edittextPointer = &edittext[TYPE];
		else if (edittextPointer == &edittext[TYPE])
			edittextPointer = &edittext[SEATS];

	}
	void moveEdittextUp(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[TYPE])
			edittextPointer = &edittext[ID_PLANE];
		else if (edittextPointer == &edittext[SEATS])
			edittextPointer = &edittext[TYPE];

	}

	bool checkEdittextError(EditText*& edittextPointer, bool adjust = 0) {
		edittextPointer->clearCursor();

	//	if (!adjust) {
			if (edittextPointer == &edittext[ID_PLANE]) {
				if (edittextPointer->isEmpty()) {
					drawAnounce(EMPTY);
					return false;
				}
				if (checkDupIDPlane(planeList, edittextPointer->getCharData())) {
					drawAnounce(DUP);
					return false;
				}
			}
		//}
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
	bool checkSaveData(EditText*& edittextPointer, bool adjust = 0) {
		edittext[ID_PLANE].clearCursor();
		edittext[TYPE].clearCursor();
		edittext[SEATS].clearCursor();
		if (!adjust) {
			if (edittext[ID_PLANE].isEmpty()) {
				drawAnounce(EMPTY);
				edittextPointer = &edittext[ID_PLANE];
				return false;
			}

			if (checkDupIDPlane(planeList, edittext[ID_PLANE].getCharData())) {
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
		return true;
	}
	void setAdjustScreen(Plane *p) {
		edittext[ID_PLANE].setActive(false);
		edittext[ID_PLANE].customInitChar(p->idPlane);
		edittext[TYPE].customInitChar(p->type);
		edittext[SEATS].customInitNum(p->seats);

	}
	void setAddScreen() {
		edittext[ID_PLANE].setActive(true);
	}
	void inputHandel(EditText*& edittextPointer,bool adjust) {
		int c = FunctionTab::getInput();

		if (edittextPointer != NULL) {
			switch (c) {
			case -1: {
				edittextPointer->deleteChar();
				break;
			}
			case 1: {
				if (!checkEdittextError(edittextPointer,adjust)) {

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
			drawManagePlaneTab();
			break;
		}

		case ADD_MENU: {
			setAddScreen();
			drawAddPlaneBorder();
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
	void drawData() {

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));


		dataPerPage();
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;


		for (int i = startPage; i <= endPage; i++) {

			int preX = LEFT_BORDER;

			setcolor(BLACK);



			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
					int s = drawAnounce(DELETE);
					switch (s) {
					case IDOK: {
						removePlane(planeList, i - 1);
						break;
					}
					case IDCANCEL: {
						break;
					}
					default:
						break;
					}

				}



				else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
				{
					setAdjustScreen(planeList.data[i - 1]);
					currentMenu = ADJUST_MENU;
					indexID = i - 1;

				}
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			//STT
			char charValue[50];
			sprintf_s(charValue, sizeof(charValue), "%d", i);
			int width = textwidth(charValue);
			int height = textheight(charValue);
			int x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, charValue);
			preX = x;

			//ID
			width = textwidth(planeList.data[i - 1]->idPlane);
			height = textheight(planeList.data[i - 1]->idPlane);
			x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, planeList.data[i - 1]->idPlane);
			preX = x;

			//TYPE
			width = textwidth(planeList.data[i - 1]->type);
			height = textheight(planeList.data[i - 1]->type);
			x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, planeList.data[i - 1]->type);
			preX = x;

			//SEATS
			sprintf_s(charValue, sizeof(charValue), "%d", planeList.data[i - 1]->seats);
			width = textwidth(charValue);
			height = textheight(charValue);
			x = preX + spaceX;
			outtextxy((x + preX - width) / 2, preY, charValue);


			preY += spaceY;

		}




	}
	void drawManagePlaneTab() {


		//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		button[ADD].onAction();
		button[SHOW].onAction();
		button[LEFT].onAction();
		button[RIGHT].onAction();


		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Left click to delete item";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit item");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);


		//----------VE MAU NEN
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(LEFT_BORDER + 2, TOP_BORDER + 2, RIGHT_BORDER - 2, TOP_BORDER + 48);


		//----------VE LINE TUNG COT
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int l = LEFT_BORDER + space;
		for (int i = 1; i <= 3; i++) {
			line(l, TOP_BORDER,l , BOTTOM_BORDER);
			l = l + space;

		}

		//VE LINE DONG DAU TIEN
		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);


		drawData();


		//-----------VE TIEU DE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		int preX = LEFT_BORDER;
		for (int i = 1; i <= 4; i++) {
			int width = textwidth(PLANE_TITLE[i - 1]);
			int height = textheight(PLANE_TITLE[i - 1]);
			int x = LEFT_BORDER + space * i;
			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_TITLE[i - 1]);
			preX = x;
		}


		if (button[ADD].isClicked()) {
			currentMenu = ADD_MENU;
			drawUI();
		}
		else if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		else if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}
		else if (button[SHOW].isClicked()) {
			currentMenu = SHOW_MENU;
			drawUI();
		}

	}
	void drawAddPlaneBorder() {


		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		button[BACK].onAction();
		button[SAVE].onAction();



		edittext[ID_PLANE].onAction(edittextPointer);
		edittext[TYPE].onAction(edittextPointer);
		edittext[SEATS].onAction(edittextPointer);

		inputHandel(edittextPointer,false);




		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetEdittext();
				edittextPointer = &edittext[ID_PLANE];
				currentMenu = MAIN_MENU;
				drawUI();
				break;
			}
			case IDCANCEL: {
				break;
			}
			default:
				break;
			}

		}
		 if (button[SAVE].isClicked()) {
			Plane p = getPlaneData();
			if (!checkSaveData(edittextPointer,false)) {

			}
			else {
				addPlane(planeList, p);

				drawAnounce(SUCCESS);
				resetEdittext();
				edittextPointer = &edittext[ID_PLANE];


			}


		}


	}
	void drawAjustScreen() {


		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		button[BACK].onAction();
		button[SAVE].onAction();



		edittext[ID_PLANE].onAction(adjustEditextPointer);
		edittext[TYPE].onAction(adjustEditextPointer);
		edittext[SEATS].onAction(adjustEditextPointer);

		inputHandel(adjustEditextPointer,1);
		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetEdittext();
				adjustEditextPointer = &edittext[TYPE];
				currentMenu = MAIN_MENU;
				drawUI();
				break;
			}
			case IDCANCEL: {
				break;
			}
			default:
				break;
			}

		}
		if (button[SAVE].isClicked()) {
			Plane p = getPlaneData();
			if (!checkSaveData(adjustEditextPointer,1)) {

			}
			else {
				adjustPlane(planeList, p, indexID);

				drawAnounce(SUCCESS);
				resetEdittext();
				adjustEditextPointer = &edittext[TYPE];
				currentMenu = MAIN_MENU;
				drawUI();
			}


		}

	}


	//----------------------DATA
	PlaneList getPlaneList() {
		return planeList;
	}


};
