#pragma once
#include"UI.h"

#ifndef EDITTEXT_H
#define EDITTEXT_H
class EditText :public UI {
private:
	char hint[30], title[30], content[30];
	
	bool isSelected;


public:
	EditText(char hint[30], char title[30], char content[30], int left, int top, int right, int bottom) :UI
	(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {

		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, content);
		this->backgroundColor = EDITEXT_BACKGROUND_COLOR;
		this->onSelectedBackgroundColor = COLOR(191,207,255);
		this->isSelected = false;

	}
	EditText() :UI() {
		strcpy_s(this->hint, "");
		strcpy_s(this->title, "");
		strcpy_s(this->content, "");
		this->isSelected = false;

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

	void onAction(EditText*& editext) {
		if (isLeftMouseClicked(mousex(), mousey()) || editext == this) {
			isSelected = true;
			editext = this;
			currentBackground = onSelectedBackgroundColor;
			strcpy_s(content, "_");
			
			
				while (kbhit()) {
					int n = strlen(content);
					char a = getch();
					if (a == BACK_SPACE) {
						if (n > 1) {
							content[n--] = ' ';
							content[n] = '-';

						}
					}
					if (a == KEY_UP)
						return;
					if (a <= '9' && a >= '0') {
						content[n++] = a;
					}
					drawUI();


			
			}

		}
		else if (editext != this && strlen(content) == 1) {
			isSelected = false;
			//strcpy_s(content, "AHIHI");
			content[strlen(content) - 1] = '\0';

			currentBackground = backgroundColor;
		}
		else if (editext != this && strlen(content) > 1) {
			isSelected = false;
			content[strlen(content) - 1] = '\0';
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
		setfillstyle(SOLID_FILL, onSelectedBackgroundColor);
		bar(left, top, right, bottom);

	}



};
#endif