
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
	bool active;

public:
	UI(int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		this->backgroundColor = backgroundColor;
		this->onSelectedBackgroundColor = onSelectedBackgroundColor;
		this->currentBackground = backgroundColor;
		this->active = true;

	}
	UI() {
		left = 0; top = 0;
		right = 0; bottom = 0;
		backgroundColor = -1;
		onSelectedBackgroundColor = -1;
		currentBackground = -1;
	}

	int  getLeft() {
		return left;
	}

	int  getRight() {
		return right;
	}

	int  getTop() {
		return top;
	}

	int  getBottom() {
		return bottom;
	}

	void  setActive(bool active) {
		this->active = active;
	}
	bool   isActive() {
		return active;
	}

	bool  isPointed(int xMouse, int yMouse) {
		if (xMouse <= right && xMouse >= left && yMouse <= bottom && yMouse >= top) {
			return true;
		}
		return false;
	}

	bool  isLeftMouseClicked(int xMouse, int yMouse) {

		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_LBUTTON) & 1) {
			return true;
		}
		return false;
	}

	bool  isRightMouseClicked(int xMouse, int yMouse) {
		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_RBUTTON) & 1) {
			return true;
		}
		return false;
	}

protected:




	void virtual drawUI() {

		if (!active) {
			currentBackground = DISABLE_COLOR;
		}

		setbkcolor(currentBackground);
		setfillstyle(SOLID_FILL, currentBackground);
		bar(left, top, right, bottom);

	}








};

#endif 