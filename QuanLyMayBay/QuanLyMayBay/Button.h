#pragma once


#include"UI.h"

class Button : public UI {
private:
	int id;
	bool animation;
	char text[20];
	int textColor;
	int textOnPointedColor;
	int currentTextColor;
	bool isSelected;
public:
	Button(int id, int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor, char text[20], int textColor, int textOnPointedColor) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
		strcpy_s(this->text, text);
		animation = false;
		this->id = id;
		this->textColor = textColor;
		this->textOnPointedColor = textOnPointedColor;
		this->currentTextColor = textColor;
		this->isSelected = false;
	}
	Button() :UI() {
		id = -1;
		strcpy_s(text, "");
		textColor = -1;
		animation = false;
		this->textOnPointedColor = -1;
		this->currentTextColor = -1;
		this->isSelected = false;
	}

	void drawUI() {

		if (isPointed(mousex(), mousey())) {

			currenBackground = WHITE;
			currentTextColor = textColor;

		}
		else {
			currenBackground = backgroundColor;
			currentTextColor = textOnPointedColor;


		}

		UI::drawUI();
		settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	void onClick(Button*& button) {
		if ((isPointed(mousex(), mousey()) && GetAsyncKeyState(VK_LBUTTON)) || button == this) {
			button = this;
			isSelected = true;
			currenBackground = onSelectedBackgroundColor;
			
		}
		else if (button != this) {
			isSelected = false;
			currenBackground = backgroundColor;
		}
		drawUI();

	}

	

};

 