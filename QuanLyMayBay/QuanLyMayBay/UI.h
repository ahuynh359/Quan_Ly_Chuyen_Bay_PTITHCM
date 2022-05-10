
#include"DefineConst.h"
#include"graphics.h"
#pragma comment(lib,"graphics.lib")

#ifndef UI_H
#define UI_H

class UI {
protected:
	int left, top;
	int right, bottom;
	int backgroundColor, onSelectedBackgroundColor, currentBackground;

public:
	UI(int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->backgroundColor = backgroundColor;
		this->onSelectedBackgroundColor = onSelectedBackgroundColor;
		this->currentBackground = backgroundColor;

	}
	UI() {
		left = 0; top = 0;
		right = 0; bottom = 0;
		backgroundColor = -1;
		onSelectedBackgroundColor = -1;
		currentBackground = -1;
	}
protected:

	

	bool virtual isPointed(int xMouse, int yMouse) {
		if (xMouse <= right && xMouse >= left && yMouse <= bottom && yMouse >= top) {
			return true;
		}
		return false;
	}

	bool virtual isLeftMouseClicked(int xMouse, int yMouse) {
		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}

	bool virtual isRightMouseClicked(int xMouse, int yMouse) {
		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}


	void virtual drawUI() {
		setbkcolor(currentBackground);
		setfillstyle(SOLID_FILL, currentBackground);
		bar(left, top, right, bottom);

	}

	






};

#endif 