#include "UI.h"

#ifndef TAB_H
#define TAB_H
class Tab :public UI {
protected:

	char text[20];
	int textColor;

public:Tab(int left, int top, int right, int bottom, char text[20], int textColor) :UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {
	strcpy_s(this->text, text);
	this->textColor = textColor;
	this->backgroundColor = TAB_DEFAULT_BACKGROUND;
	this->onSelectedBackgroundColor = TAB_ON_SELECTED_BACKGROUND;
}
	  Tab() :UI() {
		  strcpy_s(text, "");
		  textColor = -1;
	  }
	  void  drawUI() {
		  UI::drawUI();
		  setcolor(textColor);
		  outtextxy((left + right - textwidth(text)) / 2, (top + bottom - textheight(text)) / 2, text);


	  }

	  void onAction(Tab*& tab) {
		  if (isLeftMouseClicked(mousex(), mousey()) || tab == this) {
			  tab = this;
			  currentBackground = onSelectedBackgroundColor;
		  }
		  else if (tab != this) {
			  currentBackground = backgroundColor;
		  }

		  drawUI();
	  }




};

#endif 