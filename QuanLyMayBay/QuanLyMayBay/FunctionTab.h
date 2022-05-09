#pragma once

#ifndef FUNCTION_TAB_H
#define FUNCTION_TAB_H


#include"DefineConst.h"
#include"Button.h"
#include"EditText.h"
#include"Flights.h"
#include"Planes.h"
#include"Passengers.h"
#include"Data.h"

using namespace std;

class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	int startPage, endPage;

	Button button[MAX_BUTTON];
	EditText edittext[MAX_EDITTEXT];

	EditText* buttonPointer, * edittextPointer;


public:

	FunctionTab() {
		currentMenu = 0;
		currentPage = maxPage = 1;
		startPage = endPage = 1;

		initEdittext();
		initButton();


	}

	~FunctionTab() {

	}

	bool checkAllEdittextIsEmpty() {
		if (edittext[ID_FLIGHT].isEmpty() &&
			edittext[DAY].isEmpty() &&
			edittext[MONTH].isEmpty() &&
			edittext[YEAR].isEmpty() &&
			edittext[ARRIVE].isEmpty()


			) {
			return true;
		}
		return false;
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
	void drawTitle(int x, int y, char text[70]) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(3, 53, 252));
		outtextxy(x, y, text);


	}

	//Ve tieu de cho tab
	void drawTitle(char text[30]) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(3, 53, 252));
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(text)) / 2, SUBWINDOW_TOP + 30, text);


	}
	//Ve huong dan
	void drawInstruction(int x, int y, char text[30]) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		outtextxy(x, y, text);
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
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(WM_LBUTTONDBLCLK)) {
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
		case SEAT_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Seats is 20-50",
				(LPCWSTR)L"Warning",
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

		case DUP_ID_PASS: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"ID has been booked",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}

		case CANCLE_TICKET: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Do you want to cancle ticket?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}

		case FULL_PLANE: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Plane List is Full",
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

	void virtual drawUI() = 0;



	void virtual reset() {
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

	Date getDate() {

		Date d;

		strcpy_s(d.day, edittext[DAY].getCharData());
		strcpy_s(d.month, edittext[MONTH].getCharData());
		strcpy_s(d.year, edittext[YEAR].getCharData());
		strcpy_s(d.hour, edittext[HOUR].getCharData());
		strcpy_s(d.minute, edittext[MINUTE].getCharData());

		format(d);



		return d;

	}
	void handelFilter(PTR &flightList) {


		edittext[ID_FLIGHT].clearCursor();
		edittext[DAY].clearCursor();
		edittext[MONTH].clearCursor();
		edittext[YEAR].clearCursor();
		edittext[ARRIVE].clearCursor();
		Date date = getDate();
		format(date);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (7);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;
		drawBorder(6, spaceX, 1);
		setbkcolor(SUBWINDOW_BACKGROUND);

		setcolor(COLOR(50, 45, 188));


		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		setbkcolor(SUBWINDOW_BACKGROUND);
		PTR k = flightList;
		int cnt = 0;
		for (int i = 0; k != NULL && i < 10; i++)
		{
			if (
				(strlen(edittext[ID_FLIGHT].getCharData()) == 0 || strcmp(edittext[ID_FLIGHT].getCharData(), k->info.idFlight) == 0)
				&& (strlen(edittext[DAY].getCharData()) == 0 || strcmp(edittext[DAY].getCharData(), k->info.date.day) == 0)
				&& (strlen(edittext[MONTH].getCharData()) == 0 || strcmp(edittext[MONTH].getCharData(), k->info.date.month) == 0)
				&& (strlen(edittext[YEAR].getCharData()) == 0 || strcmp(edittext[YEAR].getCharData(), k->info.date.year) == 0)
				&& (strlen(edittext[ARRIVE].getCharData()) == 0 || strcmp(edittext[ARRIVE].getCharData(), k->info.arrive) == 0)
				)
			{


				int preX = LEFT_BORDER;


				setcolor(BLACK);

				cnt++;

				//VE STT
				char temp[40];
				sprintf_s(temp, "%d",cnt);
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



			}

			k = k->next;

		}
	}


	/*
	* stt = 0 -> drawPlane
	* stt = 1 -> drawFlight
	* stt = 2 -> drawPassenger
	*/
	void drawBorder(int n, const int space, int stt) {



		button[LEFT].onAction();
		button[RIGHT].onAction();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}


		int x = LEFT_BORDER;
		int y = TOP_BORDER + 50;

		//----------VE MAU NEN CHO TUA DE
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(x, TOP_BORDER, RIGHT_BORDER, y);


		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);

		//-------------------VE BORDER
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//VE LINE NGANG DONG DAU TIEN
		line(x, y, RIGHT_BORDER, y);


		int x1 = 0;
		for (int i = 0; i < n; i++) {

			if (i == 0)
				x1 = x + 100; //STT
			else if (i == n - 1) //Cuoi
				x1 = RIGHT_BORDER;
			else if (i == 2 && stt == 0) //Type cua may bay
				x1 += space + 200;
			else
				x1 += space;


			line(x1, TOP_BORDER, x1, BOTTOM_BORDER);

			switch (stt) {
			case 0: {
				drawText(x, (TOP_BORDER + y - textheight(PLANE_TITLE[i])) / 2, x1, PLANE_TITLE[i]);

				break;
			}
			case 1: {
				drawText(x, (TOP_BORDER + y - textheight(FLIGHT_TITLE[i])) / 2, x1, FLIGHT_TITLE[i]);
				break;
			}
			case 2: {
				drawText(x, (TOP_BORDER + y - textheight(PASS_TITLE[i])) / 2, x1, PASS_TITLE[i]);
				break;
			}
			default:
				break;
			}


			x = x1;



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
	int  drawPlaneData(int n, PlaneList& planeList, int& index) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;

		drawBorder(n, spaceX, 0);


		dataPerPage(planeList.size);
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);



		for (int i = startPage - 1; i < endPage; i++) {
			index = i;
			int preX = LEFT_BORDER;
			setcolor(BLACK);

			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {


				return 1;

			}

			else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{


				return 2;

			}

			//VE STT
			char temp[3];
			sprintf_s(temp, "%d", i + 1);
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
	int drawFlightData(int n, PTR& flightList, PTR& flight) {
		setbkcolor(SUBWINDOW_BACKGROUND);

		setcolor(COLOR(50, 45, 188));

		button[LEFT].onAction();
		button[RIGHT].onAction();
		inputMainMenuHandel();

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, true, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, false, maxPage);

		}

		dataPerPage(size(flightList));
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;

		drawBorder(n, spaceX, 1);

		int cnt = 1;
		PTR k = flightList;
		setbkcolor(SUBWINDOW_BACKGROUND);


		if (!checkAllEdittextIsEmpty()) {
			handelFilter(flightList);
		}
		else {
			while (k != NULL && cnt < startPage) {
				cnt++;
				k = k->next;
			}


			for (int i = startPage; i <= endPage; i++) {

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


		}
		flight = NULL;
		return -1;
	}
	void drawPassengerData(int n, PTR& flightList, AVLTree& root) {
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
		int cnt = 0;
		for (int i = 0; i < flightList->info.totalTicket; i++)
			if (strcmp(flightList->info.ticketList[i], "0") != 0)
				cnt++;



		dataPerPage(cnt);
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;

		drawBorder(n, spaceX, 2);

		cnt = 1;


		setbkcolor(SUBWINDOW_BACKGROUND);


		for (int i = 0; i < flightList->info.totalTicket; i++) {


			AVLTree p = findPassenger(root, flightList->info.ticketList[i]);



			if (p == NULL)
				continue;

			int preX = LEFT_BORDER;


			setcolor(BLACK);



			//VE STT
			char temp[40];
			sprintf_s(temp, "%d", cnt);
			int x = preX + 100;
			drawText(preX, preY, x, temp);
			preX = x;
			cnt++;

			//VE SO VE


			x = preX + spaceX;
			sprintf_s(temp, "%d", i + 1);
			drawText(preX, preY, x, temp);
			preX = x;



			//VE First Name
			x = preX + spaceX;
			drawText(preX, preY, x, p->data.firstName);
			preX = x;


			//VE Last Name
			x = preX + spaceX;
			drawText(preX, preY, x, p->data.lastName);
			preX = x;



			//VE CMND
			x = RIGHT_BORDER;
			drawText(preX, preY, x, p->data.idPass);
			preX = x;




			preY += spaceY;



		}


	}

	void drawStatictisData(int* a, int n, PlaneList& planeList) {
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
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;

		drawBorder(n, spaceX, 0);

		dataPerPage(planeList.size);
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);



		for (int i = startPage - 1; i < endPage; i++) {

			int preX = LEFT_BORDER;
			setcolor(BLACK);



			//VE STT
			char temp[3];
			sprintf_s(temp, "%d", i + 1);
			int x = preX + 100;
			drawText(preX, preY, x, temp);
			preX = x;

			//VE ID PLANE
			x = preX + spaceX;
			drawText(preX, preY, x, planeList.data[a[i]]->idPlane);
			preX = x;

			//VE SO LUOT HIEN
			x += (spaceX + 200);
			sprintf_s(temp, "%d", planeList.data[a[i]]->flyTimes);
			drawText(preX, preY, x, temp);
			preX = x;



			preY += spaceY;

		}

	}



	void freeMemory() {
		delete buttonPointer;
		delete edittextPointer;

	}


};

#endif