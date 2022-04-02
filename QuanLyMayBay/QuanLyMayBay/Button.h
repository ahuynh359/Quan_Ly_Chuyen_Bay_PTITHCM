#pragma once


#include"UI.h"

class Button : public UI {
private:
	char text[20];
	int textColor;
	int textOnPointedColor;
	int currentTextColor;

public:
	Button(int left, int top, int right, int bottom, int backgroundColor,
		int onSelectedBackgroundColor, char text[20], int textColor, int textOnPointedColor = BLACK) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
		strcpy_s(this->text, text);
		this->textColor = textColor;
		this->textOnPointedColor = textOnPointedColor;
		this->currentTextColor = textColor;

	}
	Button() :UI() {
		strcpy_s(this->text, "");
		this->textColor = -1;
		this->textOnPointedColor = -1;
		this->currentTextColor = -1;

	}

	void drawUI() {



		UI::drawUI();

		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	void onAction() {
		if (isPointed(mousex(), mousey())) {
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
		}
		else {
			currentBackground = backgroundColor;
			currentTextColor = textOnPointedColor;

		}
		drawUI();
	}







};

