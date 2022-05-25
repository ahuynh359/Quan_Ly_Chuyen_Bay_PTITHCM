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
	int currentMenu, currentPage,currentFilterPage;
	int startPage, endPage;


	Button button[MAX_BUTTON];
	EditText edittext[MAX_EDITTEXT];

	EditText* buttonPointer, * edittextPointer;


public:

	FunctionTab() {
		currentMenu = 0;
		currentPage = startPage = currentFilterPage =  endPage = 1;


		initButton();


	}
	 ~FunctionTab() {
		delete buttonPointer;
		delete edittextPointer;
	}

	//------------KHOI TAO
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

		//-----------BUTTON CANCLE TICKET
		strcpy_s(a, "CANCLE");
		button[CANCLE] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30,
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

	//----------------VE CHU / BACKGROUND
	void drawTitle(int x, int y, char text[70]) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(3, 53, 252));
		outtextxy(x, y, text);


	}
	void drawTitle(char text[50]) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(3, 53, 252));
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(text)) / 2, SUBWINDOW_TOP + 50, text);


	}
	void drawInstruction(int x, int y, char text[50]) {
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
	void drawText(int x, int y, char s[50], int color) {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(color);
		outtextxy(x, y, s);
	}
	void drawText(int x, int y, int w, char s[50]) {
		int width = textwidth(s);
		int height = textheight(s);
		outtextxy((x + w - width) / 2, y, s);
	}

	wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
	{
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

	//-------HAM XU LI SO TRANG
	void  onButtonPage(int size,int &currentPage) {
		button[LEFT].onAction();
		button[RIGHT].onAction();

		endPage = ceil((size + 0.0) / 10);
		endPage = max(1, endPage);

		startPage = (currentPage - 1) * 10;
		

		//Xu li khi xoa 
		if (currentPage > endPage) {
			currentPage--;
			currentPage = max(1, currentPage);
		}

		if (button[LEFT].isClicked()) {
			currentPage--;
			currentPage = max(1, currentPage);
			delay(100);
		}
		if (button[RIGHT].isClicked()) {
			currentPage++;
			currentPage = min(currentPage, endPage);
			delay(100);

		}
	}
	void  showPage(int &currentPage)
	{
		setcolor(PAGE_COLOR);
		setbkcolor(SUBWINDOW_BACKGROUND);


		char s[5] = "";
		sprintf_s(s, "%d", currentPage);

		int x = button[LEFT].getRight() + 20;
		int y = (button[LEFT].getTop() + button[LEFT].getBottom() - textheight(s)) / 2;


		outtextxy(x, y, s);

		x += textwidth(s);
		strcpy_s(s, " / ");
		outtextxy(x, y, s);

		x += textwidth(s);
		sprintf_s(s, "%d", endPage);
		outtextxy(x, y, s);
	}




	//-------XU LI INPUT
	int  getInput() {
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
	bool   isPointed(int left, int top, int right, int bottom) {
		if (mousex() <= right && mousex() >= left && mousey() <= bottom && mousey() >= top) {
			return true;
		}
		return false;
	}
	bool  isLeftMouseClicked(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(VK_LBUTTON) & 1) {
			return true;
		}
		return false;
	}
	
	bool  isRightMouseClicked(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(VK_RBUTTON) & 1) {
			return true;
		}
		return false;
	}


	//-------- HAM HIEN THI LOI
	int  drawAnounce(int id) {
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
		case REMOVE_CONFIRM: {
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


		case CANCLE_FLIGHT_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This flight is completed or cancled,can't be cancled",
				(LPCWSTR)L"Error",
				MB_ICONERROR | MB_OK
			);

			break;
		}
		case FLIGHT_IS_DONE: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This flight is completed or cancled!",
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
				(LPCWSTR)L"Warning",
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


		case GENDER_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Gender is not checked!",
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
				(LPCWSTR)L"Plane list is Full",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		case REMOVE_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Has been established flight, can't delete it",
				(LPCWSTR)L"Error",
				MB_ICONERROR | MB_OK
			);
			break;
		}
		case ADJUST_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"This flight is completed or cancled,can't be adjusted",
				(LPCWSTR)L"Error",
				MB_ICONERROR | MB_OK
			);
			break;
		}
		case BEFORE_ONE_HOUR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Time must >= an hour from now",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OK
			);
			break;
		}
		case CANCEL_CONFIRM: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Cancle confirm?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
			);
			break;
		}
		case THIRTY_MINUTE: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"Flight takes off in 30 minute, can't adjust any information",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
			);
			break;
		}

		case ID_PASS_ERROR: {
			msgboxID = MessageBox(
				GetForegroundWindow(),
				(LPCWSTR)L"ID must have 12 letters",
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

	


	/*
	* stt = 0 -> drawPlane
	* stt = 1 -> drawFlight
	* stt = 2 -> drawPassenger
	* stt = 3 -> draw Ticket
	* stt = 4 -> drawStatictis
	*/
	void drawBorder(int n, int stt, bool isEmpty) {


		int x = LEFT_BORDER;
		int y = TOP_BORDER + 50;
		int space = (RIGHT_BORDER + LEFT_BORDER) / (n + 1);

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

			if (!isEmpty)
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
			case 3: {
				drawText(x, (TOP_BORDER + y - textheight(TICKET_TAB[i])) / 2, x1, TICKET_TAB[i]);
				break;
			}
			case 4: {
				drawText(x, (TOP_BORDER + y - textheight(STATICITS_TITLE[i])) / 2, x1, STATICITS_TITLE[i]);
				break;
			}

			default:
				break;
			}


			x = x1;



		}
		if (isEmpty) {
			char s[100] = "DATA IS EMPTY!";
			drawText((LEFT_BORDER + RIGHT_BORDER - textwidth(s)) / 2, TOP_BORDER + 70, s, RED);
		}



	}




	void virtual drawUI() = 0;
	void virtual reset() = 0;


};

#endif