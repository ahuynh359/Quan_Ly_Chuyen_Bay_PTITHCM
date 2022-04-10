#pragma once
#include<iostream>
#include"define.h"
#include"Button.h"

class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	char title[30], instruction[30];
	Button* button;
	FunctionTab(int buttonMax) {
		currentMenu = currentMenu = maxPage = 0;
		button = new Button[buttonMax];
		strcpy_s(title, "");
		strcpy_s(instruction, "");

	}
	FunctionTab() {
		currentMenu = currentMenu = maxPage = 0;
		button = new Button[0];
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
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, instruction);
	}
};

