#pragma once
#include"UI.h"
#include<iostream>



using namespace std;
#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	char hint[30], title[30], content[50];
	unsigned int maxChar;
	int index;
	bool active,isCliked;
	unsigned int space;



public:
	EditText(char hint[30], char title[30], char content[50], int left, int top, int right, int bottom, unsigned int maxChar,unsigned int space = 80 ) :UI
	(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {

		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, "");
		this->backgroundColor = EDITEXT_BACKGROUND_COLOR;
		this->onSelectedBackgroundColor = EDITEXT_ON_SELECTED_COLOR;
		this->maxChar = maxChar + 1;
		this->index = 0;
		this->active = true;
		this->isCliked = false;
		this->space = space;
		
	}
	EditText() :UI() {
		strcpy_s(this->hint, "");
		strcpy_s(this->title, "");
		strcpy_s(this->content, "");
		this->maxChar = 0;
		this->index = 0;
		this->active = true;
		this->isCliked = false;
		this->space = space;
		
		
	}


	void setBackground(int background) {
		this->backgroundColor = background;
	}

	void drawTitle() {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(EDITTEXT_TITLE_COLOR);
		int h = textheight(title);
		outtextxy(left - space , (top + bottom - h) / 2, title);
		
	}
	void drawUI() {


		//Ve title
		drawTitle();

		if (!active) {
			this->backgroundColor = EDITTEXT_DISABLE_COLOR;
		}

		UI::drawUI();

		if (strlen(content) == 0) {

			setcolor(EDITEXT_HINT_COLOR);
			int h = textheight(hint);
			outtextxy(left + 5 , (top + bottom - h) / 2, hint);

		}
		else if (strlen(content) > 0) {
			setbkcolor(currentBackground);
			setcolor(BLACK);
			int h = textheight(content);
			outtextxy(left + 5, (top + bottom - h) / 2, content);

		}

		
		if(isLeftMouseClicked(mousex(), mousey())) {
			this->isCliked = true;

		} else 
			this->isCliked = false;

	
	}

	void setActive(bool s) {
		this->active = s;
	}

	bool getIsCliked() {
		return isCliked;
	}


	void onAction(EditText*& editext) {
		if (editext == this  && active ) {

			editext = this;
			currentBackground = onSelectedBackgroundColor;
			
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


	void customInitChar(char text[50]) {
		strcpy_s(content, text);
		index = strlen(content);

	}
	void customInitNum(int num) {
		char tmp[30] = "";
		sprintf_s(tmp, "%d", num);
		strcpy_s(content, tmp);
		index = strlen(content);

	}

	void addChar(char c) {
		if (index == maxChar)
			return;
		content[index - 1] = c;
		content[index] = '_';
		content[++index] = '\0';


	}


	bool isEmpty() {
		return strlen(content) == 0;
	}
	bool checkInt() {
		for (int i = 0; i < strlen(content);i++) {
			if(!(content[i] <= '9' && content[i] >='0'))
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
		if (isExistDash(this->content))
			if (content[--index] == '_')
				content[index] = '\0';
	}
	char* getCharData() {
		return content;
	}
	int getIntData() {
		int data = 0;
		if (strlen(content) > 0 && content != NULL)
			data = stoi(content);
		return data;

	}

	void clearText() {
		index = 0;
		content[index] = '\0';
	

	}


};
#endif