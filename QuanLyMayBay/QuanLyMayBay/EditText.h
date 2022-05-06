#pragma once
#include"UI.h"


using namespace std;
#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	
	char hint[30], title[30], content[50];
	unsigned int maxChar;
	int index;
	bool active, isCliked;
	unsigned int space;



public:
	EditText(char hint[30], char title[30], char content[50], int left, int top, int right, int bottom, unsigned int maxChar, unsigned int space = 80) :UI
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
		this->space = 80;


	}


	void setBackground(int background) {
		this->backgroundColor = background;
	}

	void drawTitle() {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(EDITTEXT_TITLE_COLOR);
		int h = textheight(title);
		outtextxy(left - space, (top + bottom - h) / 2, title);

	}

	void drawUI() {


		//Ve title
		drawTitle();

		if (!active) {
			this->currentBackground = EDITTEXT_DISABLE_COLOR;
			
		} 

		UI::drawUI();

		if ( strlen(content) == 0 ) {
			if (active)
				setcolor(EDITEXT_HINT_COLOR);
			else setcolor(BLACK);
			int h = textheight(hint);
			outtextxy(left + 5, (top + bottom - h) / 2, hint);

		}
		else if(strlen(content) > 0) {
			setbkcolor(currentBackground);
			setcolor(BLACK);
			int h = textheight(content);
			outtextxy(left + 5, (top + bottom - h) / 2, content);

		}


		if (isLeftMouseClicked(mousex(), mousey())) {
			this->isCliked = true;

		}
		else
			this->isCliked = false;


	}

	bool isActive() {
		return active;
	}

	void setActive(bool s) {
		this->active = s;
	}

	bool getIsCliked() {
		return isCliked;
	}


	void onAction(EditText*& editext) {
		
		if (editext == this && active) {
			isCliked = true;
			editext = this;
			currentBackground = onSelectedBackgroundColor;

			//Them con tro
			if (strlen(content) == 0 || !isExistDash(content) && strlen(content) < maxChar) {
				content[index++] = '_';
				content[index] = '\0';

			}
			

		}

		else if (editext != this) {
			isCliked = false;
			currentBackground = backgroundColor;
			//Xoa con tro
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
		if (isMaxChar())
			return;
		if (content[index - 2] == ' ' && c == ' ')
			return;
		content[index - 1] = c;
		content[index] = '_';
		content[++index] = '\0';


	}

	void deleteChar(char s[40], int index)
	{
		
		int n = strlen(s);
		for (int i = index; i < n-1; i++)
			s[i] = s[i + 1];
		s[n - 1] = '\0';
		(this->index)--;

	}
	void standarContent() {
		//if (checkSpace()) {
		//	clearText();
		//	//return;
		//}
		while (content[0] == ' ')
			deleteChar(content, 0);
		
			while (content[index-1] == ' ')
				deleteChar(content, index-1);
		while (content[index-1] == ' ')
				deleteChar(content, index-1);
		
		for (int i = 0; i < strlen(content) - 1; i++)
			
				if (content[i] == ' ' && content[i + 1] == ' ')
				{
					deleteChar(content, i);
					i--;
				}
		
	}
	//Ham check toan khoang trang
	bool checkSpace() {
		int n;
		if (isExistDash(content))
			n = strlen(content) - 1;
		else
			n = strlen(content);
		for (int i = 0; i < n; i++) {
			if (content[i] != ' ')
				return false;
		}
		return true;
	}


	bool isEmpty() {
		return strlen(content) == 0 || checkSpace();
	}
	bool checkInt() {
		for (int i = 0; i < strlen(content); i++) {
			if (!(content[i] <= '9' && content[i] >= '0'))
				return false;
		}
		return true;
	}


	void deleteChar() {
		if (content[0] == '_')
			return;
		if (strlen(content) == 1)
			return;
		index -= 2;
		content[index] = '_';
		content[++index] = '\0';


	}

	void clearCursor() {
		if (isExistDash(this->content))
			content[--index] = '\0';
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