#pragma once
#include"UI.h"
#include<iostream>
#include<Windows.h>
#include <cstdlib>
using namespace std;
#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	char hint[30], title[30], content[30], anounce[30];
	int maxChar;
	int index;
	int vaildAnounceColor = RED;
	int invalidAnounceColor = GREEN;
	int curAnounceColor;


public:
	EditText(char hint[30], char title[30], char content[30], int left, int top, int right, int bottom, int maxChar) :UI
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



	void drawUI() {


		//Ve title
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(PLANE_TEXT_COLOR);
		//settextstyle(10, 0, 2);
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
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(curAnounceColor);
		if (strlen(anounce) > 0) {
			outtextxy(left + 5, bottom + 10, anounce);
			delay(1000);
			//strcpy_s(anounce, "");
		}
		int startTime = 0;
		
		



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
		if ( editext == this) {
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
			checkParseString();

		}

		else if (editext != this ) {
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
		if(strlen(content) > 0)
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
		return strlen(content) == 0;
	}
	bool checkInt() {
		if (getIntData() < 20 || getIntData() > 50) {
			return false;
		}
		return true;
	}

	bool checkParseString() {
		char s[30] = "Can't leave empty";
		if (strlen(content) == 0 ) {
			drawAnoune(s, true);
			return false;
		}
		
		return true;
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
		 content[index] = '\0';
		 anounce[index] = '\0';
		 
	 }


};
#endif