#pragma once

#include "Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Planes.h"
#include"FunctionTab.h"


class ManagePlanesTab :public FunctionTab {
private:
	Button button[PLANE_MAX_BUTTON];
	EditText addPlaneEdittext[PLANE_MAX_EDITTEXT];
	EditText adjustPlaneEdittext[PLANE_MAX_EDITTEXT];
	int index = -1;
	int indexID = -1;

	PlaneList planeList;

	EditText* fieldPointer, * adjustPointer;
	bool edittexTwo = false;
public:


	ManagePlanesTab() {

		initButton();
		initEdittext();
		readFilePlane(planeList);
		fieldPointer = &addPlaneEdittext[ID];
		adjustPointer = &adjustPlaneEdittext[ID];
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

		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 100;
		int right = left + EDITEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;

		addPlaneEdittext[ID] = adjustPlaneEdittext[ID] = EditText(hint, title, content, left, top, right,
			bottom, 15);
		adjustPlaneEdittext[ID].setBackground(LIGHTGRAY);
		strcpy_s(title, "Can't be modified");


		//------------EDITTEXT BRAND
		strcpy_s(title, "BRAND");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[BRAND] = adjustPlaneEdittext[BRAND] = EditText(hint, title, content, left, top, right, bottom, 40);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, "20 <= seats <= 50");
		strcpy_s(title, "SEATS");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[SEATS] = adjustPlaneEdittext[SEATS] = EditText(hint, title, content, left, top, right, bottom, 2);



	}


	void resetInline() {
		fieldPointer = &addPlaneEdittext[ID];
		for (int i = 0; i < 3; i++) {
			addPlaneEdittext[i].clearText();
		}

		for (int i = 0; i < 3; i++) {
			adjustPlaneEdittext[i].clearText();
		}
	}
	void reset() {
		currentMenu = 0;

	}

	void onItemClicked(int currentPage) {

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int preY = TOP_BORDER + 35;
		int i = 10;
		int maxSize = 1;
		if (currentPage == 1)
			i = 1;
		else {
			i = currentPage - 1;
			i = i * 10 + 1;
		}

		maxSize = min(i + 9, planeList.size);


		for (; i <= maxSize; i++) {

			int preX = LEFT_BORDER;
			int y = preY + 35;
			if (isPointed(LEFT_BORDER, (preY + 35), RIGHT_BORDER, (y + 35))) {
				if (isLeftMouseClicked(LEFT_BORDER, (preY + 35), RIGHT_BORDER, (y + 35)))
				{
					indexID = i - 1;
					displayMessageBox(indexID);

				}
				else if (isRightMouseClicked(LEFT_BORDER, (preY + 35), RIGHT_BORDER, (y + 35)))
				{
					indexID = i - 1;
					if (planeList.data[indexID] != NULL) {
						adjustPlaneEdittext[ID].customInitChar(planeList.data[indexID]->idPlane);
						adjustPlaneEdittext[BRAND].customInitChar(planeList.data[indexID]->type);
						adjustPlaneEdittext[SEATS].customInitNum(planeList.data[indexID]->seats);
						adjustPointer = &adjustPlaneEdittext[ID];
					}
					currentMenu = ADJUST_MENU;

				}
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(COLOR(205, 92, 92));
			}
			else {
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(BLACK);
			}
			//STT
			char charValue[50];
			sprintf_s(charValue, sizeof(charValue), "%d", i);
			int width = textwidth(charValue);
			int height = textheight(charValue);
			int x = preX + space;
			outtextxy((x + preX - width) / 2, y, charValue);
			preX = x;
			//ID
			width = textwidth(planeList.data[i - 1]->idPlane);
			height = textheight(planeList.data[i - 1]->idPlane);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, planeList.data[i - 1]->idPlane);
			preX = x;
			//BRAND
			width = textwidth(planeList.data[i - 1]->type);
			height = textheight(planeList.data[i - 1]->type);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, planeList.data[i - 1]->type);
			preX = x;
			//SEATS
			sprintf_s(charValue, sizeof(charValue), "%d", planeList.data[i - 1]->seats);
			width = textwidth(charValue);
			height = textheight(charValue);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, charValue);
			preX = x;

			preY += 35;

		}




	}
	bool checkSaveData(EditText addPlaneEdittext[3], bool isAdjust = false) {

		for (int i = 0; i < 3; i++) {
			addPlaneEdittext[i].clearCursor();
		}
		int i;
		if (isAdjust)
			i = 1;
		else
			i = 0;
		bool s = true;
		for (; i < 3; i++) {
			if (addPlaneEdittext[i].isEmpty()) {
				addPlaneEdittext[i].checkEmpty();
				s = false;
			}
			else
				if (i == 2 && !addPlaneEdittext[i].checkInt()) {
					addPlaneEdittext[i].checkParseInt();
					s = false;
				}

		}


		return s;
	}
	int displayMessageBox(int index)
	{
		int msgboxID;

		//hiện MessageBox
		msgboxID = MessageBox(
			GetForegroundWindow(),
			(LPCWSTR)L"Are you sure want to delete?",
			(LPCWSTR)L"Confirm",
			MB_ICONQUESTION | MB_OKCANCEL
		);

		switch (msgboxID) {
		case IDCANCEL:

			break;
		case IDOK: {
			if (index >= 0)
				removePlane(planeList, index);
			maxPage = planeList.size / 10;

		}
				 return 1;
		}

		return 0;
	}
	void inputHandel(EditText adjustPlaneEdittext[3], EditText*& adjustPointer, bool isAdjust = 0) {
		int c = FunctionTab::getInput();

		if (adjustPointer != NULL) {

			if (c == -1) adjustPointer->deleteChar();
			else
				if (c == 1) { //UP
					adjustPointer->clearCursor();
					if (isAdjust) {
						if (index == 2)
							index--;
					}
					else
						if (index > 0)
							index--;
					adjustPointer = &adjustPlaneEdittext[index];

				}



				else if (c == 2) { //DOWN
					adjustPointer->clearCursor();

					if (!adjustPointer->checkEmpty()) {


						if (index < 2)
							index++;
						adjustPointer = &adjustPlaneEdittext[index];
					}


				}


				else if (c != 0) {

					if (adjustPointer == &adjustPlaneEdittext[ID]) {
						if (c <= 90 && c >= 65)
							adjustPointer->addChar((char)c);

					}
					else if (adjustPointer == &adjustPlaneEdittext[BRAND]) {
						if (c <= 90 && c >= 65 || c == ' ')
							adjustPointer->addChar((char)c);

					}
					else if (adjustPointer == &adjustPlaneEdittext[SEATS]) {
						if (c <= 57 && c >= 48)
							adjustPointer->addChar((char)c);

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
			resetInline();
			break;
		}

		case ADD_MENU: {

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

	void drawManagePlaneTab() {

		//	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		button[ADD].onAction();
		button[SHOW].onAction();
		button[LEFT].onAction();
		button[RIGHT].onAction();





		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		char a[30] = "*Right click to delete item";
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Left click to edit item");
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);


		//------------ VE SO TRANG
		maxPage = planeList.size / 10;
		sprintf_s(a, "%d", currentPage);
		showPage((LEFT_BORDER + RIGHT_BORDER - textwidth(a)) / 2 - 25, BOTTOM_BORDER + 35, currentPage, maxPage + 1);

		//----------VE LINE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(LEFT_BORDER + 2, TOP_BORDER + 2, RIGHT_BORDER - 2, TOP_BORDER + 48);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		for (int i = 1; i <= 3; i++) {
			line(LEFT_BORDER + space * i, TOP_BORDER, LEFT_BORDER + space * i, BOTTOM_BORDER);


		}

		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);


		//-----------VE TIEU DE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		int preX = LEFT_BORDER;
		for (int i = 1; i <= 4; i++) {
			int width = textwidth(PLANE_BUTTON_NAME[i - 1]);
			int height = textheight(PLANE_BUTTON_NAME[i - 1]);
			int x = LEFT_BORDER + space * i;
			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}

		onItemClicked(currentPage);
		if (button[ADD].isClicked()) {


			currentMenu = ADD_MENU;
			drawUI();
		}
		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);


		}
		if (button[SHOW].isClicked()) {
			currentMenu = SHOW_MENU;
			drawUI();
		}

	}
	

	void drawAddPlaneBorder() {
		//-----------------VE HUONG DAN TEXT
		char a[30] = "ADD PLANE";
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);
		strcpy_s(a, "*Use keyboard to navigate");
		setcolor(GREEN);

		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);



		for (int i = 0; i < 3; i++) {

			addPlaneEdittext[i].onAction(fieldPointer);
		}
		inputHandel(addPlaneEdittext, fieldPointer);



		button[BACK].onAction();
		button[SAVE].onAction();


		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
			writeFilePlane(planeList);
			drawUI();
		}

		if (button[SAVE].isClicked()) {
			if (checkSaveData(addPlaneEdittext)) {
				Plane p;
				strcpy_s(p.idPlane, addPlaneEdittext[ID].getContent());
				strcpy_s(p.type, addPlaneEdittext[BRAND].getContent());
				p.seats = addPlaneEdittext[SEATS].getIntData();


				addPlane(planeList, p);



				resetInline();
			}


		}


	}
	void drawAjustScreen() {

		char a[20] = "ADJUST PLANE";
		button[BACK].onAction();
		button[SAVE].onAction();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);
		if (!edittexTwo) {
			index = 1;
			adjustPointer = &adjustPlaneEdittext[index];
			edittexTwo = true;
		}

		for (int i = 0; i < 3; i++) {

			adjustPlaneEdittext[i].onAction(adjustPointer);
		}

		inputHandel(adjustPlaneEdittext, adjustPointer, true);



		if (button[BACK].isClicked()) {
			currentMenu = MAIN_MENU;
			edittexTwo = false;
			drawUI();
		}

		if (button[SAVE].isClicked()) {

			if (checkSaveData(adjustPlaneEdittext, true)) {
				Plane* p = new Plane;
				for (int i = 0; i < 3; i++) {
					adjustPlaneEdittext[i].clearCursor();
				}
				strcpy_s(p->idPlane, adjustPlaneEdittext[ID].getContent());
				strcpy_s(p->type, adjustPlaneEdittext[BRAND].getContent());
				p->seats = adjustPlaneEdittext[SEATS].getIntData();



				planeList.data[indexID] = p;
				edittexTwo = false;
				currentMenu = MAIN_MENU;
				drawUI();
			}
			//}
			//else {
				//char s[30] = "Failed";
				//ThongBao(700, 700, s, GREEN, SUBWINDOW_BACKGROUND);
			//}
		}


	}



};
