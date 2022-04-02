#pragma once
#include"UI.h"

#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	char hint[30], title[30], content[30], anounce[30];
	int maxChar;
	bool isSelected;
	int index;
	int vaildAnounceColor = RED;
	int invalidAnounceColor = GREEN;
	int curAnounceColor;


public:
	EditText(char hint[30], char title[30], char content[30], int left, int top, int right, int bottom,int maxChar) :UI
	(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {

		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, "");
		strcpy_s(this->anounce, "");
		this->backgroundColor = EDITEXT_BACKGROUND_COLOR;
		this->onSelectedBackgroundColor = COLOR(191,207,255);
		this->isSelected = false;
		this->maxChar = maxChar;
		this->curAnounceColor = vaildAnounceColor;
		this->index = 0;


	}
	EditText() :UI() {
		strcpy_s(this->hint, "");
		strcpy_s(this->title, "");
		strcpy_s(this->content, "");
		strcpy_s(this->anounce, "");
		this->isSelected = false;
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
		else if(strlen(content) > 0)  {
			setbkcolor(currentBackground);

			//Ve noi dung nguoi dung nhap
			setcolor(BLACK);
			h = textheight(content);
			outtextxy(left + 5, (top + bottom - h) / 2, content);

		}

		




	}

	void drawAnoune(char anounce[30],bool isVaild) {
		strcpy_s(this->anounce, anounce);
		if (isVaild) {
			curAnounceColor = vaildAnounceColor;
		}
		else
			curAnounceColor = invalidAnounceColor;
	}

	void onAction(EditText*& editext) {
		if (isLeftMouseClicked(mousex(), mousey()) || editext == this) {
			isSelected = true;
			editext = this;
			currentBackground = onSelectedBackgroundColor;
			/*if (content[index] == '\0' && content[index-1] != '_') {
				content[index++] = '_';
				content[index] = '\0';
			}*/
				
			if (strlen(content) == 0) {
				content[index++] = '_';
				content[index] = '\0';
			}
			

		}
		
		else if (editext != this ) {
			isSelected = false;
			currentBackground = backgroundColor; 
			
			
		}

		drawUI();

	}

	//Ham lay du lieu duoc nhap
	char* getData() {
		int n = strlen(content);
		if (content[n - 1] == ' ' || content[n - 1] == '\0')
			return content;
		return NULL;
	}

	void clearText(EditText *&editText) {
		index = 0;
		content[index] = '\0';
		anounce[index] = '\0';

	}

	void customInitChar( char text[30]) {
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
		content[index-1] = c;
		content[index++] = '_';
		content[index] = '\0';
		//drawUI();

	}

	bool checkParseInt() {
	
		for (size_t i = 0; i < strlen(content); i++) {
			if (!(content[i]<='9' && content[i]>='0')) {
				
				return false;

			}

		}
		return true;

	}

	bool checkParseString() {
		for (size_t i = 0; i < strlen(content); i++) {
			if (!(content[i] <= 'z' && content[i] >= 'a' || content[i] <= 'Z' && content[i] >= 'A' || content[i] == ' ')) {


		}
		return true;
				return false;

			}
	}


	void deleteChar() {
		if (strlen(content) == 0)
			return;
		content[--index] = '_';
		content[index] = '\0';

		
	}

	void clearCursor() {
		if (content[--index] == '_')
			content[index] = '\0';
	}



};
#endif