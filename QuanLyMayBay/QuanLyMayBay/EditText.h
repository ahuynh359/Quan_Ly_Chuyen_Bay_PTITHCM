#pragma once
#include"UI.h"
class EditText :public UI {
private:
	char hint[30],title[30],content[30];
	int id;
	

public:
	EditText(int id, char hint[30], char title[30],char content[30], int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor) :UI
		(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor){
		this->id = -1;
		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, content);


}

	void drawUI() {

	}
};