
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
		this->left = 0;
		this->top = 0;
		this->right = 0;
		this->bottom = 0;
		this->backgroundColor = -1;
		this->onSelectedBackgroundColor = -1;
		this->currentBackground = -1;
		this->active = true;
	}

	int   getLeft() {
		return left;
	}

	int   getRight() {
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
	bool  isActive() {
		return active;
	}

	bool   isPointed(int xMouse, int yMouse) {
		if (xMouse <= right && xMouse >= left && yMouse <= bottom && yMouse >= top) {
			return true;
		}
		return false;
	}

	bool   isLeftMouseClicked(int xMouse, int yMouse) {

		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}

	bool   isRightMouseClicked(int xMouse, int yMouse) {
		if (isPointed(xMouse, yMouse) && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
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