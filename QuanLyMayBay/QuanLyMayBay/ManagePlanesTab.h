#pragma once
#include"Tab.h"
#include"Button.h"

class ManagePlanesTab {
private:
	Button* button[PLANE_MAX_BUTTON];
	enum BUTTON_NAME {them,xemDS,xoa,sua,trai,phai};
	
	
public:

	
	void initManagePlaneTab() {


		//Ve nen
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1, SUBWINDOW_BOTTOM - 1);


		//DANH SACH MAY BAY TEXT
		setcolor(BLACK);
		setbkcolor(SUBWINDOW_BACKGROUND);
		settextstyle(0, 0, 4);
		
		//Text
		char DANHSACH[30] = "QUAN LI MAY BAY";
		int width = textwidth(DANHSACH);
		int height = textheight(DANHSACH);
		const int PLANE_TITLE_TEXT_X = ((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - width) / 2);
		const int PLANE_TITLE_TEXT_Y = (SUBWINDOW_TOP + 50);
		outtextxy(PLANE_TITLE_TEXT_X, PLANE_TITLE_TEXT_Y, DANHSACH);

		//Button them chuyen bay
		int l = PLANE_TITLE_TEXT_X + width + 300;
		int t = height + PLANE_TITLE_TEXT_Y + 20;
		int r = l + 70;
		int b = t + 70;
		settextstyle(0, 0, 10);
		char s[14] = "+";
		button[0] = new Button(0, l, t, r, b
			, TAB_DEFAULT_BACKGROUND, WHITE, s, PLANE_TEXT_COLOR, BLACK);
		
		
		button[0]->onClick(button[0]);
		//Button xem danh sach
		l = r + 10;
		r = l + 70;
		b = t + 70;
		char a[14] = "XEM";
		button[1] = new Button(1, l, t, r, b, TAB_DEFAULT_BACKGROUND, WHITE, a, PLANE_TEXT_COLOR, BLACK);
		button[1]->drawUI();
		button[1]->onClick(button[1]);

		//Ve border 
		l = SUBWINDOW_LEFT + 100;
		t = t + 100;
		r = SUBWINDOW_RIGHT - 100;
		b = SUBWINDOW_BOTTOM - 50;
		rectangle(l, t, r, b);


		





	}


};