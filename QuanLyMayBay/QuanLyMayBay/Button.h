#pragma once


#include"UI.h"

class Button : public UI {
private:
	char text[20];
	int textColor;
	int textOnPointedColor;
	int currentTextColor;
	bool cliked;

public:
	Button(int left, int top, int right, int bottom, int backgroundColor,
		int onSelectedBackgroundColor, char text[20], int textColor, int textOnPointedColor = BLACK) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
		strcpy_s(this->text, text);
		this->textColor = textColor;
		this->textOnPointedColor = textOnPointedColor;
		this->currentTextColor = textColor;
		this->cliked = false;

	}
	Button() :UI() {
		strcpy_s(this->text, "");
		this->textColor = -1;
		this->textOnPointedColor = -1;
		this->currentTextColor = -1;
		this->cliked = false;
	}

	void drawUI() {



		UI::drawUI();

		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	void onAction() {
		if (isLeftMouseClicked(mousex(), mousey())) {
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
			cliked = true;
		}
		else if (isPointed(mousex(), mousey())) {
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
			cliked = false;


		}
		else {
			currentBackground = backgroundColor;
			currentTextColor = textOnPointedColor;
			cliked = false;

		}
		drawUI();
	}

	//Viet cho button ghe
	void onAction(Button*& button,bool isBooked = 0) {
		if (isLeftMouseClicked(mousex(), mousey()) ) {
			button = this;
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;

		}

		else if (button != this) {
			if (isBooked) {
				currentBackground = TICKET_NOT_AVAI;
				currentTextColor = textOnPointedColor;
			}
			else {
				currentBackground = backgroundColor;
				currentTextColor = textOnPointedColor;
			}
		}

		drawUI();

	}

	void setColor(int textColor,int backgroundColor) {
		currentBackground = onSelectedBackgroundColor;
		currentTextColor = textColor;
		drawUI();
	}

	bool isClicked() {
		return cliked;
	}







};

