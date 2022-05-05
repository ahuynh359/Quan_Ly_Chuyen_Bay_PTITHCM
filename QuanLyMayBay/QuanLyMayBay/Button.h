#pragma once


#include"UI.h"
using namespace std;

class Button : public UI {
private:
	char text[20];
	int textColor;
	int textOnPointedColor;
	int currentTextColor;
	bool cliked;
	int active;
	bool isChoosen;

public:
	Button(int left, int top, int right, int bottom, int backgroundColor,
		int onSelectedBackgroundColor, char text[20], int textColor, int textOnPointedColor = BLACK) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
		strcpy_s(this->text, text);
		this->textColor = textColor;
		this->textOnPointedColor = textOnPointedColor;
		this->currentTextColor = textColor;
		this->cliked = false;
		this->active = true;
		this->isChoosen = false;

	}

	void setActive(bool s) {
		this->active = s;

	}

	void setChoosen(bool s) {
		this->isChoosen = s;
	}



	Button() :UI() {
		strcpy_s(this->text, "");
		this->textColor = -1;
		this->textOnPointedColor = -1;
		this->currentTextColor = -1;
		this->cliked = false;
		this->active = true;
		this->isChoosen = false;

	}

	void setBackground(int color) {
		this->currentBackground = color;
		drawUI();
	}

	void drawUI() {



		if (!active) {
			this->currentBackground = EDITTEXT_DISABLE_COLOR;

		}



		UI::drawUI();

		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	void drawSeatUI() {

		if (isChoosen) {
			this->currentBackground = TICKET_NOT_AVAI;
		}
		else if (!isChoosen)
			this->currentBackground = TICKET_AVAI;


		UI::drawUI();

		setcolor(currentTextColor);
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);
	}

	//Viet cho button tro len
	void onAction() {
		if (isLeftMouseClicked(mousex(), mousey()) && active) {
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
			cliked = true;
		}
		else if (isPointed(mousex(), mousey()) && active) {
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

	//Viet cho button chon 1 lan

	void onAction(Button*& button) {
		if (button == this || isLeftMouseClicked(mousex(), mousey()) && active) {
			currentBackground = onSelectedBackgroundColor;
			currentTextColor = textColor;
			cliked = true;
			button = this;
		}

		else if (button != this) {
			currentBackground = backgroundColor;
			currentTextColor = textOnPointedColor;
			cliked = false;

		}
		drawUI();
	}


	//Viet cho button ghe
	void onActionSeatButton() {

		if (isChoosen == false && isLeftMouseClicked(mousex(), mousey())) {
			currentBackground = TICKET_NOT_AVAI;
			currentTextColor = textOnPointedColor;
			cliked = true;
			isChoosen = true;

		}
		else if (isChoosen == true && isRightMouseClicked(mousex(), mousey())) {
			currentBackground = TICKET_AVAI;
			currentTextColor = textOnPointedColor;
			cliked = true;
			isChoosen = false;


		}
		else {
			currentBackground = backgroundColor;
			currentTextColor = textOnPointedColor;
			cliked = false;

		}


		drawSeatUI();

	}
	int getIntData() {
		int data = 0;
		if (strlen(text) > 0 && text != NULL)
			data = stoi(text);
		return data;

	}
	void setColor(int textColor, int backgroundColor) {
		currentBackground = onSelectedBackgroundColor;
		currentTextColor = textColor;
		drawUI();
	}

	bool isClicked() {
		return cliked;
	}







};

