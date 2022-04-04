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
	EditText adjustPlaneEdittext[3];
	int index = -1;

	int pageLimit;
	int page;
	PlaneList planeList;
	Plane* temp;
	enum EIDT_NAME { ID, BRAND, SEATS };
	enum BUTTON_NAME { them, hthi, trai, phai, lui, luu };
	int n; //Tong so phan tu
	int currentMenu = 0;
	enum MENU { MENU_CHINH, MENU_THEM, MENU_CHINHSUA, MENU_HIEN_THI };
	EditText* fieldPointer, * adjustPointer;
public:

	//Khoi tao cac tham
	ManagePlanesTab() {
		int textButton = COLOR(190, 193, 196);
		page = 1;
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
		button[luu]  = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30, SUBWINDOW_BOTTOM - 50, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//---------EDITTEXT ID
		int spaceEdit = 80;
		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";
		left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		top = SUBWINDOW_TOP + 100;
		right = left + EDITEXT_WIDTH;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[ID] = adjustPlaneEdittext[ID] = EditText(hint, title, content, left, top, right, bottom, 15);


		//------------EDITTEXT BRAND
		strcpy_s(title, "BRAND");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[BRAND] = adjustPlaneEdittext[BRAND] = EditText(hint, title, content, left, top, right, bottom, 40);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, "20 <= seats <= 50");
		strcpy_s(title, "SEATS");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		addPlaneEdittext[SEATS] = adjustPlaneEdittext[SEATS] = EditText(hint, title, content, left, top, right, bottom, 2);

		readFilePlane(planeList);
		fieldPointer = &addPlaneEdittext[ID];
		adjustPointer = &adjustPlaneEdittext[ID];




	}
	void onButtonPage(int page, bool isMinus, int limit) {
		switch (isMinus) {
		case true: {
			if (page <= 1)
				break;

			(this->page) -= 1;
			delay(100);
			break;
		}
				 //Is Plus
		case false: {
			if (page >= limit + 1)
				return;


			(this->page) += 1;
			delay(100);
			break;
		}


		default:
			break;
		}
	}
	void showPage(int x, int y, int page, int limit)
	{
		//  Page: page / limit
		setcolor(PAGE_COLOR);
		setbkcolor(SUBWINDOW_BACKGROUND);
		char s[5] = "";
		sprintf_s(s, "%d", page);
		outtextxy(x, y, s);
		x += textwidth(s);
		strcpy_s(s, " / ");
		outtextxy(x, y, s);
		x += textwidth(s);
		sprintf_s(s, "%d", limit);
		outtextxy(x, y, s);
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

			drawAjustScreen();

			break;
		}
		case MENU_HIEN_THI: {
			drawShowTab();
			break;
		}
		default:
			break;



		}

	}

	void drawShowTab() {
		char a[20] = "STATISTIC PLANE";
		//button[save].onAction();
		button[lui].onAction();
		button[trai].onAction();
		button[phai].onAction();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);

	
		pageLimit = planeList.size / 10;
		sprintf_s(a, "%d", page);
		showPage((LEFT_BORDER + RIGHT_BORDER - textwidth(a)) / 2 - 25, BOTTOM_BORDER + 35, page, pageLimit + 1);

		//----------VE LINE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(LEFT_BORDER + 2, TOP_BORDER + 2, RIGHT_BORDER - 2, TOP_BORDER + 48);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 3;
		for (int i = 1; i <= 1; i++) {
			line(LEFT_BORDER + space * i, TOP_BORDER, LEFT_BORDER + space * i, BOTTOM_BORDER);


		}

		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);


		//-----------VE TIEU DE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		int preX = LEFT_BORDER;
		for (int i = 1; i <= 2; i++) {
			int width = textwidth(PLANE_BUTTON_NAME[i - 1]);
			int height = textheight(PLANE_BUTTON_NAME[i - 1]);
			int x = LEFT_BORDER + space * i;
			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}



		if (button[lui].isClicked()) {
			currentMenu = MENU_CHINH;

			drawUI();
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
		//-----------------VE HUONG DAN TEXT
		char a[30] = "ADD PLANE";
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);
		strcpy_s(a, "*Use keyboard to navigate");
		setcolor(GREEN);

		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);


		button[lui].onAction();
		button[luu].onAction();

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



		if (button[lui].isClicked()) {
			currentMenu = MENU_CHINH;
			writeFilePlane(planeList);
			drawUI();
		}

		if (button[luu].isClicked()) {
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

		//	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		button[them].onAction();
		button[hthi].onAction();
		button[trai].onAction();
		button[phai].onAction();





		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		char a[30] = "*Right click to delete item";
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Left click to edit item");
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);


		//------------ VE SO TRANG
		pageLimit = planeList.size / 10;
		sprintf_s(a, "%d", page);
		showPage((LEFT_BORDER + RIGHT_BORDER - textwidth(a)) / 2 - 25, BOTTOM_BORDER + 35, page, pageLimit + 1);

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

		onItemClicked(page);
		if (button[them].isClicked()) {


			currentMenu = MENU_THEM;
			drawUI();
		}
		if (button[trai].isClicked()) {
			onButtonPage(page, true, pageLimit);
		}
		if (button[phai].isClicked()) {
			onButtonPage(page, false, pageLimit);


		}
		if (button[hthi].isClicked()) {
			currentMenu = MENU_HIEN_THI;
			drawUI();
		}

	}

	//Do du lieu ra bang va xu li su kien
	void onItemClicked(int page) {



		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int preY = TOP_BORDER + 35;
		int i = 10;
		int maxSize = 1;
		if (page == 1)
			i = 1;
		else {
			i = page - 1;
			i = i * 10 + 1;
		}

		maxSize = min(i + 9, planeList.size);
		/*if (planeList.data[i-1] == NULL) {
			(this->pageLimit) = planeList.size / 10;
			if ((this->page) > 1)
				(this->page)--;
			char a[30] = "";
			sprintf_s(a, "%d", page);
			showPage((LEFT_BORDER + RIGHT_BORDER - textwidth(a)) / 2 - 25, BOTTOM_BORDER + 35, this->page, pageLimit + 1);
		}
			*/
		for (; i <= maxSize; i++) {

			int preX = LEFT_BORDER;
			int y = preY + 35;
			if (mousex() <= RIGHT_BORDER && mousex() >= LEFT_BORDER && mousey() <= (y + 35) &&
				mousey() >= (preY + 35)) {
				if (GetAsyncKeyState(VK_RBUTTON) && 0x8000) {
					index = i - 1;
					displayMessageBox();


				}
				else if (GetAsyncKeyState(VK_LBUTTON) && 0x8000) {
					index = i - 1;
					temp = planeList.data[i - 1];
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

		}
		return true;
	}



	int displayMessageBox()
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
			pageLimit = planeList.size / 10;

		}
				 return 1;
		}

		return 0;
	}

	void ThongBao(int x, int y, char noti[50], int mauChu, int mauNen)
	{
		setbkcolor(mauNen);
		setcolor(mauChu);
		outtextxy(x, y, noti);
		Sleep(1000);
		setfillstyle(SOLID_FILL, mauNen);
		bar(x, y, x + textwidth(noti), y + textheight(noti));
	}
	void drawAjustScreen() {

		char a[20] = "ADJUST PLANE";
		button[lui].onAction();
		button[luu].onAction();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);

		for (int i = 0; i < 3; i++) {

			adjustPlaneEdittext[i].onAction(adjustPointer);
		}
		/*int c = getInput();
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

		}*/




		if (button[lui].isClicked()) {
			currentMenu = MENU_CHINH;

			drawUI();
		}

		if (button[luu].isClicked()) {

		}


	}



};
