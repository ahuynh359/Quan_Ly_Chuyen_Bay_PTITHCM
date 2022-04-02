#pragma once

#include "Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Planes.h"
using namespace std;
class ManagePlanesTab {
private:
	Button button[PLANE_MAX_BUTTON];
	EditText addPlaneEdittext[3];
	int index = -1;

	char soTrang[5];
	PlaneList planeList;
	enum EIDT_NAME { ID, BRAND, SEATS };
	enum BUTTON_NAME { them, hthi, trai, phai, lui, luu };
	int n; //Tong so phan tu
	int currentMenu = 0;
	enum MENU { MENU_CHINH, MENU_THEM, MENU_CHINHSUA };
	EditText* fieldPointer;
public:

	//Khoi tao cac tham
	ManagePlanesTab() {
		int textButton = COLOR(190, 193, 196);
		strcpy_s(this->soTrang, "1/2");
		n = 0;
		//-------------BUTTON THEM
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 50;
		int right = left + 50;
		int bottom = top + 50;
		char a[15] = "+";
		button[them] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//------------BUTTON XEM DS CHUYEN BAY
		top = bottom + 10;
		right = left + 50;
		bottom = top + 50;
		strcpy_s(a, "LIST");
		button[hthi] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);



		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[trai] = Button(left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);
		//--------------BUTTON PHAI
		left = right + 100;
		right = left + 50;
		strcpy_s(a, ">");
		button[phai] = Button(left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
		button[lui] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60, textButton, WHITE, a, PLANE_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[luu] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30, SUBWINDOW_BOTTOM - 50, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//---------EDITTEXT ID
		int spaceEdit = 80;
		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";
		left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		top = SUBWINDOW_TOP + 130;
		right = left + EDITEXT_WIDTH;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[ID] = EditText(hint, title, content, left, top, right, bottom, 15);


		//------------EDITTEXT BRAND
		strcpy_s(title, "BRAND");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[BRAND] = EditText(hint, title, content, left, top, right, bottom, 40);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, "20 <= seats <= 50");
		strcpy_s(title, "SEATS");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[SEATS] = EditText(hint, title, content, left, top, right, bottom, 2);

		readFilePlane(planeList);
		fieldPointer = &addPlaneEdittext[ID];




	}
	int getInput() {
		//
		int re = 0;
		for (int i = 65; i <= 90; i++) {
			if (GetAsyncKeyState((char)(i)) & 1) {
				return i;
			}
		}
		for (int i = 97; i <= 122; i++) {
			if (GetAsyncKeyState((char)(i)) & 1) {
				return i - 32;
			}
		}
		//So
		for (int i = 48; i <= 57; i++) {
			if (GetAsyncKeyState((char)i) & 1) {
				return i;
			}
		}
		if (GetAsyncKeyState(VK_BACK) & 1) return -1;
		if (GetAsyncKeyState(VK_SPACE) & 1) return ' ';
		if (GetAsyncKeyState(VK_TAB) & 1) return  (int)'\t';
		if (GetAsyncKeyState(VK_UP) & 1) return 1;
		if (GetAsyncKeyState(VK_DOWN) & 1) return 2;
		if (GetAsyncKeyState(VK_RETURN) & 1) return 3;
		return re;
	}
	void drawUI() {

		drawBackground();

		switch (currentMenu) {
		case MENU_CHINH: {
			drawManagePlaneTab();
			resetInline();
			break;
		}

		case MENU_THEM: {

			drawAddPlaneBorder();
			break;
		}
		case MENU_CHINHSUA: {
			resetInline();
			drawAjustScreen();

			break;
		}
		default: {
			break;
		}

		}
	}

	void resetInline() {
		fieldPointer = &addPlaneEdittext[ID];
		for (int i = 0; i < 3; i++) {
			addPlaneEdittext[i].clearText();
		}
	}
	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}
	void reset() {
		currentMenu = 0;

	}

	void drawAddPlaneBorder() {

		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		char a[20] = "ADD PLANE";
		button[lui].onAction();
		button[luu].onAction();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);

		for (int i = 0; i < 3; i++) {

			addPlaneEdittext[i].onAction(fieldPointer);
		}
		int c = getInput();
		if (fieldPointer != NULL) {

			if (c == -1) fieldPointer->deleteChar();
			else
				if (c == 1) {
					fieldPointer->clearCursor();
					fieldPointer->checkParseString();
					if (fieldPointer->checkParseString()) {
						if (fieldPointer == &addPlaneEdittext[BRAND])
							fieldPointer = &addPlaneEdittext[ID];

						else if (fieldPointer == &addPlaneEdittext[SEATS] && fieldPointer->checkParseInt())

							fieldPointer = &addPlaneEdittext[BRAND];


					}


				}
				else if (c == 2 || c == 3) {
					fieldPointer->clearCursor();
					fieldPointer->checkParseString();
					if (fieldPointer->checkParseString()) {
						if (fieldPointer == &addPlaneEdittext[ID])
							fieldPointer = &addPlaneEdittext[BRAND];

						else if (fieldPointer == &addPlaneEdittext[BRAND])
							fieldPointer = &addPlaneEdittext[SEATS];
					}

				}
				else if (c != 0) {

					if (fieldPointer == &addPlaneEdittext[ID]) {
						if (c <= 90 && c >= 65) {
							fieldPointer->addChar((char)c);




						}
					}
					else if (fieldPointer == &addPlaneEdittext[BRAND]) {
						if (c <= 90 && c >= 65 || c == ' ') {
							fieldPointer->addChar((char)c);

						}
					}
					else if (fieldPointer == &addPlaneEdittext[SEATS]) {
						if (c <= 57 && c >= 48) {
							fieldPointer->addChar((char)c);

						}
					}

				}

		}



		if (button[lui].isLeftMouseClicked(mousex(), mousey())) {
			currentMenu = MENU_CHINH;
			writeFilePlane(planeList);
			drawUI();
		}

		if (button[luu].isLeftMouseClicked(mousex(), mousey())) {
			if (checkSaveData()) {
				Plane* p = new Plane;
				strcpy_s(p->idPlane, addPlaneEdittext[ID].getContent());
				strcpy_s(p->type, addPlaneEdittext[BRAND].getContent());
				p->seats = addPlaneEdittext[SEATS].getIntData();
				for (int i = 0; i < 3; i++) {
					addPlaneEdittext[i].clearText();
				}
				setbkcolor(SUBWINDOW_BACKGROUND);

				char s[30] = "Succesfully";
				addPlaneEdittext[SEATS].drawAnoune(s, false);

				addPlane(planeList, p);

				resetInline();
			}


		}


	}
	void drawManagePlaneTab() {

		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		for (int i = 0; i < 4; i++) {
			button[i].onAction();
		}


		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		char a[30] = "*Right click to delete item";
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Left click to edit item");
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);


		//------------ VE SO TRANG
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(142, 154, 185));
		int w = textwidth(soTrang);
		int h = textheight(soTrang);
		outtextxy((LEFT_BORDER + RIGHT_BORDER - w) / 2, BOTTOM_BORDER + 35, soTrang);

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
			//settextjustify(CENTER_TEXT, TOP_TEXT);
			//settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}

		onItemClicked();
		if (button[them].isLeftMouseClicked(mousex(), mousey())) {


			currentMenu = MENU_THEM;
			drawUI();
		}

	}

	//Do du lieu ra bang va xu li su kien
	void onItemClicked() {



		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int preY = TOP_BORDER + 35;

		for (int i = 1; i <= planeList.size; i++) {
			int preX = LEFT_BORDER;
			int y = preY + 35;
			if (mousex() <= RIGHT_BORDER && mousex() >= LEFT_BORDER && mousey() <= (y + 35) &&
				mousey() >= (preY + 35)) {
				if (GetAsyncKeyState(VK_RBUTTON) && 0x8000) {
					index = i - 1;
					DisplayResourceNAMessageBox();
				}
				else if (GetAsyncKeyState(VK_LBUTTON) && 0x8000) {
					index = i - 1;
					currentMenu = MENU_CHINHSUA;
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
	bool checkSaveData() {
		for (int i = 0; i < 3; i++) {
			if (addPlaneEdittext[i].isEmpty()) {
				return false;
			}
			if (i == 2 && !addPlaneEdittext[i].checkInt())
				return false;
		}
		return true;
	}



	int DisplayResourceNAMessageBox()
	{
		//hiện MessageBox
		int msgboxID = MessageBox(
			GetForegroundWindow(),
			(LPCWSTR)L"Are you sure want to delete?",
			(LPCWSTR)L"Confirm",
			MB_ICONQUESTION | MB_OKCANCEL
		);

		switch (msgboxID)
		{
		case IDCANCEL:

			break;
		case IDOK: {
			if (index >= 0)
				removePlane(planeList, index);
		}
				 break;
		}

		return msgboxID;
	}

	void drawAjustScreen() {
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		char a[20] = "ADJUST PLANE";
		button[lui].onAction();
		button[luu].onAction();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);

		for (int i = 0; i < 3; i++) {
			
			addPlaneEdittext[i].onAction(fieldPointer);
		}
		int c = getInput();
		if (fieldPointer != NULL) {

			if (c == -1) fieldPointer->deleteChar();
			else
				if (c == 1) {
					fieldPointer->clearCursor();
					fieldPointer->checkParseString();
					if (fieldPointer->checkParseString()) {
						if (fieldPointer == &addPlaneEdittext[BRAND])
							fieldPointer = &addPlaneEdittext[ID];

						else if (fieldPointer == &addPlaneEdittext[SEATS] && fieldPointer->checkParseInt())

							fieldPointer = &addPlaneEdittext[BRAND];


					}


				}
				else if (c == 2 || c == 3) {
					fieldPointer->clearCursor();
					fieldPointer->checkParseString();
					if (fieldPointer->checkParseString()) {
						if (fieldPointer == &addPlaneEdittext[ID])
							fieldPointer = &addPlaneEdittext[BRAND];

						else if (fieldPointer == &addPlaneEdittext[BRAND])
							fieldPointer = &addPlaneEdittext[SEATS];
					}

				}
				else if (c != 0) {

					if (fieldPointer == &addPlaneEdittext[ID]) {
						if (c <= 90 && c >= 65) {
							fieldPointer->addChar((char)c);




						}
					}
					else if (fieldPointer == &addPlaneEdittext[BRAND]) {
						if (c <= 90 && c >= 65 || c == ' ') {
							fieldPointer->addChar((char)c);

						}
					}
					else if (fieldPointer == &addPlaneEdittext[SEATS]) {
						if (c <= 57 && c >= 48) {
							fieldPointer->addChar((char)c);

						}
					}

				}

		}



		if (button[lui].isLeftMouseClicked(mousex(), mousey())) {
			currentMenu = MENU_CHINH;
			writeFilePlane(planeList);
			drawUI();
		}

		if (button[luu].isLeftMouseClicked(mousex(), mousey())) {
			if (checkSaveData()) {
				Plane* p = new Plane;
				strcpy_s(p->idPlane, addPlaneEdittext[ID].getContent());
				strcpy_s(p->type, addPlaneEdittext[BRAND].getContent());
				p->seats = addPlaneEdittext[SEATS].getIntData();
				for (int i = 0; i < 3; i++) {
					addPlaneEdittext[i].clearText();
				}
				setbkcolor(SUBWINDOW_BACKGROUND);

				char s[30] = "Succesfully";
				addPlaneEdittext[SEATS].drawAnoune(s, false);

				addPlane(planeList, p);

				resetInline();
			}


		}
	}



};
