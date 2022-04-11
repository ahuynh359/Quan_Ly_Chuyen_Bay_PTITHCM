#pragma once
#include<iostream>
#include"define.h"
#include"Button.h"

class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	char title[30], instruction[30];
	
	FunctionTab() {
		currentMenu = currentPage = maxPage = 0;
		strcpy_s(title, "");
		strcpy_s(instruction, "");
	}
	//Ve tieu de cho tab
	void drawTitle(char text[30]) {
		strcpy_s(title, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(title)) / 2, SUBWINDOW_TOP + 10, title);

	}
	//Ve huong dan
	void drawInstruction(char text[30]) {
		strcpy_s(instruction, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		outtextxy(LEFT_BORDER, BOTTOM_BORDER + 50, instruction);
	}

	//------Lay du lieu tu ban phim-----------
	int getInput() {
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
		return 0;
	}

	
	void virtual initEdittext() = 0;
	void virtual initButton() = 0;

};

