#pragma once
#include<iostream>
#include"define.h"
#include"Button.h"



class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	int startPage, endPage;
	char title[30], instruction[30];
public:
	FunctionTab() {
		currentMenu = 0;
		currentPage = maxPage = 1;
		startPage = endPage = 1;
		strcpy_s(title, "");
		strcpy_s(instruction, "");
	}
	//Ve tieu de cho tab
	void virtual drawTitle(char text[30]) {
		strcpy_s(title, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(title)) / 2, SUBWINDOW_TOP + 10, title);

	}
	//Ve huong dan
	void  virtual drawInstruction(int x, int y, char text[30]) {
		strcpy_s(instruction, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		outtextxy(x, y, instruction);
	}
	void virtual  drawBackground() {
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
				(LPCWSTR)L"ID is duplicate. Do you want to adjust?",
				(LPCWSTR)L"Warning",
				MB_ICONEXCLAMATION | MB_OKCANCEL
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
		default:
			break;

		}
		return msgboxID;
		



	}

	void reset() {
		currentMenu = MAIN_MENU;
	}

	//----- MOT SO HAM


	void virtual dataPerPage() = 0;
	void virtual initEdittext() = 0;
	void virtual initButton() = 0;
	void virtual drawData() = 0;
	void virtual drawUI() = 0;
	void virtual freeMemory() = 0;

};

