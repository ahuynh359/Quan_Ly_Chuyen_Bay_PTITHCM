#pragma once
#include"UI.h"
#include<iostream>



using namespace std;
#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	char hint[30], title[30], content[30], anounce[30];
	unsigned int maxChar;
	int index;
	int vaildAnounceColor = RED;
	int invalidAnounceColor = GREEN;
	int curAnounceColor;


public:
	EditText(char hint[30], char title[30], char content[30], int left, int top, int right, int bottom, unsigned int maxChar) :UI
	(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {

		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, "");
		strcpy_s(this->anounce, "");
		this->backgroundColor = EDITEXT_BACKGROUND_COLOR;
		this->onSelectedBackgroundColor = COLOR(191, 207, 255);
		this->maxChar = maxChar + 1;
		this->curAnounceColor = vaildAnounceColor;
		this->index = 0;


	}
	EditText() :UI() {
		strcpy_s(this->hint, "");
		strcpy_s(this->title, "");
		strcpy_s(this->content, "");
		strcpy_s(this->anounce, "");
		this->maxChar = 0;
		this->curAnounceColor = vaildAnounceColor;
		index = 0;


	}


	void setBackground(int background) {
		this->backgroundColor = background;
	}
	void drawUI() {


		//Ve title
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(PLANE_TEXT_COLOR);
		int h = textheight(title);
		outtextxy(left - 90, (top + bottom - h) / 2, title);

		//Ve edittext
		UI::drawUI();
		if (strlen(content) == 0) {
			//Ve hint
			//setbkcolor(BLACK);
			setcolor(EDITEXT_HINT_COLOR);
			h = textheight(hint);
			outtextxy(left + 5, (top + bottom - h) / 2, hint);

		}
		else if (strlen(content) > 0) {
			setbkcolor(currentBackground);

			//Ve noi dung nguoi dung nhap
			setcolor(BLACK);
			h = textheight(content);
			outtextxy(left + 5, (top + bottom - h) / 2, content);

		}
		if (strlen(anounce) > 0) {
			setbkcolor(SUBWINDOW_BACKGROUND);
			setcolor(curAnounceColor);

			outtextxy(left + 5, bottom + 10, anounce);





		}










	}
	void sleep(float seconds) {
		clock_t startClock = clock();
		float secondsAhead = seconds * CLOCKS_PER_SEC;
		// do nothing until the elapsed time has passed.
		while (clock() < startClock + secondsAhead);
		return;
	}
	void drawAnoune(char anounce[30], bool isVaild) {
		strcpy_s(this->anounce, anounce);
		if (isVaild) {
			curAnounceColor = vaildAnounceColor;
		}
		else
			curAnounceColor = invalidAnounceColor;
	}

	void onAction(EditText*& editext) {
		if (editext == this) {
			editext = this;
			currentBackground = onSelectedBackgroundColor;
			/*if (content[index] == '\0' && content[index-1] != '_') {
				content[index++] = '_';
				content[index] = '\0';
			}*/

			if (strlen(content) == 0 || !isExistDash(content) && strlen(content) < maxChar) {
				content[index++] = '_';
				content[index] = '\0';

			}


		}

		else if (editext != this) {
			currentBackground = backgroundColor;
			if (isExistDash(content)) {
				content[--index] = '\0';

			}



		}

		drawUI();


	}
	bool isExistDash(char content[30]) {
		for (int i = 0; i < strlen(content); i++) {
			if (content[i] == '_')
				return true;
		}
		return false;
	}
	bool isMaxChar() {
		return strlen(content) == maxChar;
	}

	int getIntData() {
		int data = 0;
		if (strlen(content) > 0 && content != NULL)
			data = stoi(content);
		return data;

	}
	void customInitChar(char text[30]) {
		strcpy_s(content, text);
		index = strlen(content);
		anounce[0] = '\0';
	}
	void customInitNum(int num) {
		char tmp[30] = "";
		sprintf_s(tmp, "%d", num);
		strcpy_s(content, tmp);
		index = strlen(content);
		anounce[0] = '\0';
	}

	void addChar(char c) {
		if (index == maxChar)
			return;
		content[index - 1] = c;
		content[index] = '_';
		content[++index] = '\0';
		//drawUI();

	}

	bool checkParseInt() {

		char s[30] = "20 <= seats <= 50";

		if (getIntData() < 20 || getIntData() > 50) {
			drawAnoune(s, true);
			return false;
		}
		return true;

	}

	bool isEmpty() {
		return strlen(content) == 0 ;
	}
	bool checkInt() {
		if (getIntData() >= 20 && getIntData() <= 50) {
			return true;
		}
		return false;
	}

	bool checkEmpty() {
		char s[30] = "Can't leave empty";
		if (strlen(content) == 0) {
			drawAnoune(s, true);
			return true;
		}


		return false;
	}

	bool checkDup(bool isDup) {
		char s[30] = "Duplicated";
		if (isDup) {
			drawAnoune(s, true);
			return true;
		}
		return false;
	}


	void deleteChar() {
		if (strlen(content) == 1)
			return;
		index -= 2;
		content[index] = '_';
		content[++index] = '\0';


	}

	void clearCursor() {
		if (content[--index] == '_')
			content[index] = '\0';
		strcpy_s(anounce, "");
	}
	char* getContent() {

		return content;
	}

	void clearText() {
		index = 0;
		strcpy_s(this->content, "");
		strcpy_s(this->anounce, "");

	}


};
#endif