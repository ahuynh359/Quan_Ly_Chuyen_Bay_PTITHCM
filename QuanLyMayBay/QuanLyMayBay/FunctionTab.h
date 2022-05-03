#pragma once

#ifndef FUNCTION_TAB_H
#define FUNCTION_TAB_H

#include"define.h"
#include"Button.h"
#include"EditText.h"
#include"Flights.h"
#include"Planes.h"
#include"Passengers.h"



class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	int startPage, endPage;
	char title[40], instruction[40];

	Button button[MAX_BUTTON];
	EditText edittext[MAX_EDITTEXT];

	EditText* buttonPointer, * edittextPointer;

	
public:
	FunctionTab() {
		currentMenu = 0;
		currentPage = maxPage = 1;
		startPage = endPage = 1;
		strcpy_s(title, "");
		strcpy_s(instruction, "");

		initButton();
		

	}

	~FunctionTab() {
		delete buttonPointer;
		delete edittextPointer;
	}

	

	void  initButton() {
		//------------BUTTON  TRAI  
		int left = SCREEN_WIDTH / 2 - 100;
		int top = BOTTOM_BORDER + 30;
		int right = left + 50;
		int bottom = top + 30;
		char a[10] = "<";
		button[LEFT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);

		//--------------BUTTON PHAI
		left = right + 70;
		right = left + 50;
		strcpy_s(a, ">");
		button[RIGHT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "< BACK");
		button[BACK] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60,
			BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[SAVE] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30,
			SUBWINDOW_BOTTOM - 50, BUTTON_BACKGROUND, WHITE, a, BUTTON_TEXT_COLOR);

		//-------------BUTTON THEM
		left = SUBWINDOW_RIGHT - 70;
		top = SUBWINDOW_TOP + 50;
		right = left + 50;
		bottom = top + 50;
		strcpy_s(a, "ADD");
		button[ADD] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a,
			BUTTON_TEXT_COLOR);

	}

	//Ve tieu de cho tab
	void drawTitle(char text[30]) {
		strcpy_s(title, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(title)) / 2, SUBWINDOW_TOP + 10, title);

	}
	//Ve huong dan
	void drawInstruction(int x, int y, char text[30]) {
		strcpy_s(instruction, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		outtextxy(x, y, instruction);
	}
	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}


	//-------HAM XU LI SO TRANG
	void virtual onButtonPage(int page, bool isMinus, int limit) {
		switch (isMinus) {

		case true: {
			if (page <= 1)
				break;

			(this->currentPage) -= 1;
			delay(100);
			break;
		}

		case false: {
			if (page >= limit + 1)
				return;


			(this->currentPage) += 1;
			delay(100);
			break;
		}



		}
	}
	void  virtual showPage(int x, int y, int page, int limit)
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


	//-------XU LI INPUT
	int virtual getInput() {
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
		if (GetAsyncKeyState(VK_LEFT) & 1) return 4;
		if (GetAsyncKeyState(VK_RIGHT) & 1) return 5;


		return 0;
	}
	bool virtual  isPointed(int left, int top, int right, int bottom) {
		if (mousex() <= right && mousex() >= left && mousey() <= bottom && mousey() >= top) {
			return true;
		}
		return false;
	}
	bool virtual isLeftMouseClicked(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}
	bool virtual isDoubleClick(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(WM_LBUTTONDBLCLK) ) {
			return true;
		}
		return false;
	}
	bool virtual isRightMouseClicked(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}

	int virtual drawAnounce(int id) {
		int msgboxID = -1;
		switch (id) {
		case EMPTY: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Do not leave empty",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		case SEAT_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Seats is between 20-50",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		case DUP: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"ID is duplicate!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);


			break;
		}
		case SUCCESS: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Successfully",
				(LPCWSTR)L"Message",
				MB_ICONINFORMATION | MB_OK
			);
			break;
		}
		case DELETE: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Do you want to delete?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
			);

			break;
		}
		case PREVIOUS: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Do you want to go back?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
			);

			break;
		}
		case CANCLE_FLIGHT_SUCCESS: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Do you want to cancel this flight?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
			);

			break;
		}

		case CANCLE_FLIGHT_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This flight has been cancelled!",
				(LPCWSTR)L"Error",
				MB_ICONERROR | MB_OK
			);

			break;
		}
		case FLIGHT_IS_DONE: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This flight is completed!",
				(LPCWSTR)L"Error",
				MB_ICONERROR | MB_OK
			);

			break;
		}
		case PLANE_NOT_EXIST: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This plane is not exist!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case DAY_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Day is between 1 - 31!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case MONTH_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Month is between 1 - 12!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case TIME_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Time is not vaild!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case YEAR_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Year is management for 2 years!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}

		case HOUR_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Hour is between 0 - 23!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case MINUTE_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Minute is between 0 - 59!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);

			break;
		}
		case GREATER_SEAT: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Seats >= current seats",
				(LPCWSTR)L"This plane has been established flight",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		
		case ID_PASS_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"ID Passenger must have 12 letters",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		case GENDER_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Gender is not checked!",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		default:
			break;

		}
		return msgboxID;




	}

	void reset() {
		currentMenu = MAIN_MENU;
	}



	void dataPerPage(int size) {

		maxPage = ceil((size + 0.0) / 10);

		if (currentPage > maxPage)
			currentPage--;

		currentPage = max(1, currentPage);
		maxPage = max(maxPage, 1);

		startPage = currentPage - 1;
		startPage = startPage * 10 + 1;

		//Toi da 10 du lieu 1 trang
		endPage = min(startPage + 9, size);
	}

	void drawText(int x, int y, int w, char s[40]) {
		int width = textwidth(s);
		int height = textheight(s);
		outtextxy((x + w - width) / 2, y, s);
	}

	void drawBackgroundBorder(int color) {
		//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//----------VE MAU NEN
		setbkcolor(color);
		setcolor(color);
		setfillstyle(0, color);
		bar(LEFT_BORDER + 2, TOP_BORDER + 2, RIGHT_BORDER - 2, TOP_BORDER + 48);

	}



	void drawBorderPlane(int n, const int space) {
		drawBackgroundBorder(TAB_ON_SELECTED_BACKGROUND);

		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);

		//VE LINE NGANG DONG DAU TIEN
		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);

		int preX = LEFT_BORDER;
		int x = preX + 100;
		int y = TOP_BORDER + 15;

		for (int i = 0; i < n - 1; i++) {

			line(x, TOP_BORDER, x, BOTTOM_BORDER);
			drawText(preX, y, x, PLANE_TITLE[i]);

			preX = x;

			if (i == 1)
				x += space + 200;
			else if (i == n - 2)
				x = RIGHT_BORDER;
			else
				x += space;

		}

		drawText(preX, y, x, PLANE_TITLE[n - 1]);

	}
	int  drawPlaneData(int n, PlaneList& planeList,int &index) {

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		button[LEFT].onAction();
		button[RIGHT].onAction();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;

		drawBorderPlane(n, spaceX);


		dataPerPage(planeList.size);
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);



		for (int i = startPage - 1 ; i < endPage; i++) {

			int preX = LEFT_BORDER;
			setcolor(BLACK);

			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				index = i ;
				return 1;

			}

			else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{
				index = i ;

				return 2;

			}

			//VE STT
			char temp[3];
			sprintf_s(temp, "%d", i+1);
			int x = preX + 100;
			drawText(preX, preY, x, temp);
			preX = x;

			//VE ID PLANE
			x = preX + spaceX;
			drawText(preX, preY, x, planeList.data[i]->idPlane);
			preX = x;

			//VE TYPE
			x += (spaceX + 200);
			drawText(preX, preY, x, planeList.data[i]->type);
			preX = x;

			//VE SEATS
			sprintf_s(temp, "%d", planeList.data[i]->seats);
			x = RIGHT_BORDER;
			drawText(preX, preY, x, temp);




			preY += spaceY;

		}
		index = -1;
		return -1;


	}

	void drawBorderFlight(int n, const int space) {
		drawBackgroundBorder(TAB_ON_SELECTED_BACKGROUND);

		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);

		//VE LINE NGANG DONG DAU TIEN
		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);

		int preX = LEFT_BORDER;
		int x = preX + 100;
		int y = TOP_BORDER + 15;

		for (int i = 0; i < n - 1; i++) {

			line(x, TOP_BORDER, x, BOTTOM_BORDER);
			drawText(preX, y, x, FLIGHT_TITLE[i]);

			preX = x;


			if (i == n - 2)
				x = RIGHT_BORDER;
			else x += space;


		}

		drawText(preX, y, x, FLIGHT_TITLE[n - 1]);
	}
	int drawFlightData(int n, PTR& flightList,PTR &flight) {
		setbkcolor(SUBWINDOW_BACKGROUND);

		setcolor(COLOR(50, 45, 188));

		button[LEFT].onAction();
		button[RIGHT].onAction();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}

		dataPerPage(size(flightList));
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;

		drawBorderFlight(n, spaceX);
		int cnt = 1;
		PTR k = flightList;

		while (k != NULL && cnt < startPage) {
			cnt++;
			k = k->next;
		}
		setbkcolor(SUBWINDOW_BACKGROUND);

		
		for (int i = startPage;  i <= endPage; i++) {

			if (k == NULL) {
					flight = NULL;
					return -1;

			}
			int preX = LEFT_BORDER;

			
			setcolor(BLACK);

			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}

			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				flight = k;
				return 1;

			}

			else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{
				flight = k;


				return 2;

			}

			//VE STT
			char temp[40];
			sprintf_s(temp, "%d", i);
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
			sprintf_s(temp, "%s%s%s%s%s%s%s%s%s", k->info.date.day, "/", k->info.date.month, "/",
				k->info.date.year, " ", k->info.date.hour, ":", k->info.date.minute);
			x = preX + spaceX;
			drawText(preX, preY, x, temp);
			preX = x;


			//VE ARRIVE
			x = preX + spaceX;
			drawText(preX, preY, x, k->info.arrive);
			preX = x;


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


			x = RIGHT_BORDER;
			drawText(preX, preY, x, temp);

			preY += spaceY;

			k = k->next;

		}
		flight = NULL;
		return -1;
	}



	void drawBorderPassenger(int n, const int space) {
		drawBackgroundBorder(TAB_ON_SELECTED_BACKGROUND);

		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);

		//VE LINE NGANG DONG DAU TIEN
		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);

		int preX = LEFT_BORDER;
		int x = preX + 100;
		int y = TOP_BORDER + 15;

		for (int i = 0; i < n - 1; i++) {

			line(x, TOP_BORDER, x, BOTTOM_BORDER);
			drawText(preX, y, x, PASS_TITLE[i]);

			preX = x;

			if (i == 0)
				x += 100;
			else if (i == n - 2)
				x = RIGHT_BORDER;
			else
				x += space;

		}

		drawText(preX, y, x, PASS_TITLE[n - 1]);

	}
	int  drawPassengerData(int n, AVLTree& root, AVLTree &index) {

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		button[LEFT].onAction();
		button[RIGHT].onAction();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;

		drawBorderPassenger(n, spaceX);

		int s = 0;
		size(root, s);
		dataPerPage(s);

		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		AVLTree k = root;
		s = 0;
		while (k != NULL && s < startPage) {
			s++;
			cout << k->data.firstName << '\n';
			k = k->pleft;
			k = k->pright;
			
		}

		
		for (int i = startPage - 1; i < endPage; i++) {
			if (k == NULL) {
				index = NULL;
				return -1;

			}
				
			int preX = LEFT_BORDER;
			setcolor(BLACK);

			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				index = k;
				return 1;

			}

			else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{
				index = k;

				return 2;

			}

			//VE STT
			char temp[3];
			sprintf_s(temp, "%d", i + 1);
			int x = preX + 100;
			drawText(preX, preY, x, temp);
			preX = x;

			x = preX + spaceX;
			drawText(preX, preY, x, k->data.firstName);
			preX = x;

			x = preX + spaceX;
			drawText(preX, preY, x, k->data.lastName);
			preX = x;


			x = RIGHT_BORDER;
			drawText(preX, preY, x, temp);




			preY += spaceY;
			k = k->pleft;
			k = k->pright;
		}
		index = NULL;
		return -1;


	}




};

#endif