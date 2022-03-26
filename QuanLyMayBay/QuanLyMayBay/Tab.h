#include "UI.h"

#ifndef TAB_H
#define TAB_H
class Tab :public UI {
protected:

	char text[20];
	int textColor;
	bool isSelected;

public:Tab(int left, int top, int right, int bottom, char text[20], int textColor) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
	strcpy_s(this->text, text);
	this->textColor = textColor;
	this->isSelected = false;
	this->backgroundColor = TAB_DEFAULT_BACKGROUND;
	this->onSelectedBackgroundColor = TAB_ON_SELECTED_BACKGROUND;
}
	  Tab() :UI() {
		  strcpy_s(text, "");
		  textColor = -1;
		  isSelected = false;
	  }
	  void  drawUI() {
		  UI::drawUI();
		  setcolor(textColor);
		 // settextstyle(10, 0, 2);
		  //setusercharsize(2, 1, 3, 2);
		  outtextxy((left + right - textwidth(text)) / 2, (top + bottom - textheight(text)) / 2, text);


	  }


	  void onAction(Tab*& tab) {
		  if (isLeftMouseClicked(mousex(), mousey()) || tab == this) {
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