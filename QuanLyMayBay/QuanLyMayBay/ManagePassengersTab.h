#pragma once

#include "Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Passengers.h"
#include"UIController.h"
using namespace std;
// Anh dien
class ManagePassengersTab {
private:
	Button button[PASSENGER_MAX_BUTTON];
	EditText editTextLoc;
	int index = -1;
	int indexID = -1;
	int pageLimit;
	int page;
	PassengerList passengerList;
	Passenger* temp;
	enum BUTTON_NAME { trai, phai, lui };
	int n; //Tong so phan tu
	int currentMenu = 0;
	enum MENU { MENU_CHINH, MENU_HIEN_THI };
	EditText* fieldPointer = &editTextLoc, * adjustPointer;

public:
	//Khoi tao cac tham so
	ManagePassengersTab() {

		page = 1;
		initButton();
		initEditText();
		readFilePassenger(passengerList);
	}


	// ------------INIT--------------

	void initButton() {
		//------------BUTTON  TRAI  
		int left = SCREEN_WIDTH / 2 - 100;
		int top = BOTTOM_BORDER + 30;
		int right = left + 50;
		int bottom = top + 30;
		char a[15] = "<";
		//button[trai] = Button(left, top, right, bottom, textButton, WHITE, a, PASSENGER_TEXT_COLOR);

		//--------------BUTTON PHAI
		left = right + 70;
		right = left + 50;
		strcpy_s(a, ">");
		//button[phai] = Button(left, top, right, bottom, textButton, WHITE, a, PASSENGER_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
	//	button[lui] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60, textButton, WHITE, a, PLANE_TEXT_COLOR);
	}


	void initEditText(){

		//---------EDITTEXT ID FLIGHT
		int spaceEdit = 80;
		char hint[30] = "Enter here...";
		char title[30] = "ID Flight";
		char content[30] = "";
		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 100;
		int right = left + EDITEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;
		editTextLoc = EditText(hint, title, content, left, top, right, bottom, 10);
	}



	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}


	void showPage(int x, int y, int page, int limit)
	{
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


	void drawManagePassengerTab() {

		//	settextstyle(BOLD_FONT, HORIZ_DIR, 2);
			//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		button[lui].onAction();
		button[trai].onAction();
		button[phai].onAction();


		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		char a[50] = "*Enter ID Flight to filter the passengers!";
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);


		//------------ VE SO TRANG
		pageLimit = passengerList.size / 10;
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


		if (button[trai].isClicked()) {
			onButtonPage(page, true, pageLimit);
		}
		if (button[phai].isClicked()) {
			onButtonPage(page, false, pageLimit);
		}
		editTextLoc.onAction(fieldPointer);


	}

	void drawUI() {

		drawBackground();

		switch (currentMenu) {
		case MENU_CHINH: {
			//drawManagePlaneTab();
			//resetInline();
			break;
		}


		}
	}
};