#include "UI.h"

#include"DefineConst.h"
#ifndef TAB_H
#define TAB_H
class Tab :public UI {
private:

	char text[20];
	int id;
	

public:Tab(int id,int left, int top, int right, int bottom, char text[20]) 
	:UI(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor) {

	strcpy_s(this->text, text);
	this->backgroundColor = TAB_DEFAULT_BACKGROUND;
	this->onSelectedBackgroundColor = TAB_ON_SELECTED_BACKGROUND;
	this->id = id;
}
	  Tab() :UI() {
		  strcpy_s(text, "");
		  id = 0;
	  }


	  void  drawUI() {
		  UI::drawUI();

		  setcolor(BLACK);
		  outtextxy((left + right - textwidth(text)) / 2, (top + bottom - textheight(text)) / 2, text);
	  }

	  int getID() {
		  return id;
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