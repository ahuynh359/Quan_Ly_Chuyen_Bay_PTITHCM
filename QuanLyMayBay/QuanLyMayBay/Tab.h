#include "UI.h"
class Tab :public UI {
private:
	char text[20];
	int textColor;
	bool isSelected;
public:Tab(int x, int y,int width, int height, int backgroundColor, int onSelectedBackgroundColor, char text[20], int textColor) :UI(x, y, width, height, backgroundColor, onSelectedBackgroundColor) {
	strcpy_s(this->text, text);
	this->textColor = textColor;
	this->isSelected = false;
}
	  void drawUI() {
		  if (isSelected) {
			  currenBackground = onSelectedBackgroundColor;

		  } else
		  currenBackground = backgroundColor;
		  UI::drawUI();
	  }
	  void drawText() {
		  
		  
		  drawUI();
		  settextstyle(10, HORIZ_DIR, 1);
		  setcolor(textColor);
		  int textWidth = textwidth(text);
		  int textHeight = textheight(text);
		  outtextxy((width+x-textWidth)/2 , (height+y-textHeight)/2, text);
		  

	  }

	  void setIsSelected(bool s) {
		  this->isSelected = s;
	  }
};

