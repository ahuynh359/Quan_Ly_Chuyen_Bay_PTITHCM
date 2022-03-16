

#include"define.h"
#include"graphics.h"
#pragma comment(lib,"graphics.lib")
class UI {
protected:
	int width, height;
	int x, y;
	int backgroundColor, onSelectedBackgroundColor,currenBackground;
public:
	UI(int x, int y,int width,int height,int backgroundColor,int onSelectedBackgroundColor) {
		this->width = width;
		this->x = x;
		this->height = height;
		this->y = y;
		this->backgroundColor = backgroundColor;
		this->onSelectedBackgroundColor = onSelectedBackgroundColor;
		this->currenBackground = backgroundColor;

	}
	void virtual drawUI() {
		setbkcolor(currenBackground);
		setfillstyle(SOLID_FILL, currenBackground);
		bar(x , y , width , height );

	}

	bool virtual isPointed(int xMouse,int yMouse) {
		if (xMouse <= x + width  && xMouse >=  width-x  && yMouse <= y + height  && yMouse >= height - y ) {
			return true;
		}
		return false;
	}
};
