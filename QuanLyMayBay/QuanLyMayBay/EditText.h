#pragma once
#include"UI.h"
class EditText :public UI {
private:
	char hint[30],title[30],content[30];
	int id;
	const int SPACE = 20;
	

public:
	EditText(int id, char hint[30], char title[30],char content[30], int left, int top, int right, int bottom, int backgroundColor, int onSelectedBackgroundColor) :UI
		(left, top, right, bottom, backgroundColor, onSelectedBackgroundColor){
		this->id = -1;
		strcpy_s(this->hint, hint);
		strcpy_s(this->title, title);
		strcpy_s(this->content, content);


}

	void drawUI() {
		//Ve title
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(PLANE_TEXT_COLOR);
		//settextstyle(10, 0, 2);
		int h = textheight(title);
		outtextxy(left - 90,( top+bottom-h)/2, title);

		//Ve edittext
		UI::drawUI();
		if (strlen(content) == 0) {
			//Ve hint
			setbkcolor(backgroundColor);
			setcolor(EDITEXT_HINT_COLOR);
			h = textheight(hint);
			outtextxy(left + 5, (top + bottom - h) / 2, hint);

		}
		else {
			//Ve noi dung nguoi dung nhap
			setbkcolor(backgroundColor);
			setcolor(YELLOW);
			outtextxy(left + 10, (top - bottom - h) / 2, content);
			
		}
		



	}

	//Ham lay du lieu duoc nhap
	char* getData() {
		int n = strcpy(content);
		if (content[n - 1] == ' ' || content[n - 1] == '\0')
			return content;
		return NULL;
	}


	
};