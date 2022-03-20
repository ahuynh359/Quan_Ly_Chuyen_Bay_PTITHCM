#include "UI.h"
#ifndef TAB_H
#define TAB_H
class Tab :public UI {
protected:
	
	char text[20];
	int textColor;
	bool isSelected;

public:Tab( int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor, char text[20], int textColor) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
	strcpy_s(this->text, text);
	this->textColor = textColor;
	this->isSelected = false;
}
	  Tab() :UI() {
		  strcpy_s(text, "");
		  textColor = -1;
		  isSelected = false;
	  }
	
	  void drawUI() {
		  UI::drawUI();
		  settextstyle(DEFAULT_FONT, HORIZ_DIR, 0);
		  setcolor(textColor);
		  int textWidth = textwidth(text);
		  int textHeight = textheight(text);
		  outtextxy((left + right - textWidth) / 2, (top + bottom - textHeight) / 2, text);

	  }

	  void virtual onClick(Tab*& tab) {
		  if ((isPointed(mousex(), mousey()) && GetAsyncKeyState(VK_LBUTTON)) || tab == this) {
			  tab = this;
			  isSelected = true;
			  currenBackground = onSelectedBackgroundColor;
		  }
		  else if (tab != this) {
			  isSelected = false;
			  currenBackground = backgroundColor;
		  }
	  
		  drawUI();


	  } 

	  

	  bool getIsSelected() {
		  return isSelected;
	  }

	 
};

#endif 