#pragma once


#include"UI.h"

class Button : public UI {
private:
	char text[20];
	int textColor;
	int textOnPointedColor;
	int currentTextColor;
	bool hovered;
public:
	Button(int left, int top, int right, int bottom, int backgroundColor,
		int onSelectedBackgroundColor, char text[20], int textColor, int textOnPointedColor = BLACK) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
		strcpy_s(this->text, text);
		this->textColor = textColor;
		this->textOnPointedColor = textOnPointedColor;
		this->currentTextColor = textColor;
		this->hovered = false;
	}
	Button() :UI() {
		strcpy_s(text, "");
		textColor = -1;
		this->textOnPointedColor = -1;
		this->currentTextColor = -1;
		this->hovered = false;
	}

	void drawUI() {

		if (isPointed(mousex(), mousey())) {

			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
			hovered = true;

		}
		else {
			currentBackground = backgroundColor;
			currentTextColor = textOnPointedColor;
			hovered = false;


		}

		UI::drawUI();

		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	bool isHovered() {
		return hovered;
	}








};

