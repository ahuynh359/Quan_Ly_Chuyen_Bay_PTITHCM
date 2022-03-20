#pragma once
#include "Button.h"
#include "Tab.h"

class ManagePlanesTab {
private:
	Button* button[PLANE_MAX_BUTTON];
	char soTrang[5];
public:

	ManagePlanesTab() {
		strcpy_s(this->soTrang, "1/2");
		for (int i = 0; i < PLANE_MAX_BUTTON; i++) {
			button[i] = NULL;
		}
	}

	~ManagePlanesTab() {
		for (int i = 0; i < PLANE_MAX_BUTTON; i++) {
			delete button[i];
		}
	}

	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}

	
	void initManagePlaneTab() {

		// Ve nen
		drawBackground();
		//-------- DANH SACH MAY BAY TEXT
		setcolor(BLACK);
		setbkcolor(SUBWINDOW_BACKGROUND);
		settextstyle(0, 0, 4);
		char DANHSACH[30] = "QUAN LI MAY BAY";
		int width = textwidth(DANHSACH);
		int height = textheight(DANHSACH);
		const int PLANE_TITLE_TEXT_X =
			((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - width) / 2);
		const int PLANE_TITLE_TEXT_Y = (SUBWINDOW_TOP + 20);
		outtextxy(PLANE_TITLE_TEXT_X, PLANE_TITLE_TEXT_Y, DANHSACH);

		//-------------BUTTON THEM CHUYEN BAY
		int left = PLANE_TITLE_TEXT_X + width + 300;
		int top = height + PLANE_TITLE_TEXT_Y + 10;
		int right = left + 70;
		int bottom = top + 70;
		settextstyle(0, 0, 3);
		char s[14] = "+";
		button[0] = new Button(0, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, s,
			PLANE_TEXT_COLOR);
		button[0]->onClick(button[0]);


		//------------BUTTON THEM DS CHUYEN BAY
		left = right + 10;
		right = left + 70;
		bottom = top + 70;
		char a[14] = "XEM";
		button[1] = new Button(1, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);
		button[1]->onClick(button[1]);

		//-------------------VE BORDER
		int leftBorder = SUBWINDOW_LEFT + 100;
		int topBorder = bottom + 10;
		int rightBorder = SUBWINDOW_RIGHT - 100;
		int bottomBorder = SUBWINDOW_BOTTOM - 100;
		rectangle(leftBorder, topBorder, rightBorder, bottomBorder);

		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		settextstyle(0, 0, 0);
		char b[50] = "*Click chuot phai de chinh sua thong tin";
		outtextxy(leftBorder + 10, bottomBorder + 20, b);


		//------------VE BUTTON  TRAI , PHAI 
		left = width + PLANE_TITLE_TEXT_X / 2 - 50;
		top = bottomBorder + 40;
		right = left + 50;
		bottom = top + 30;
		char c[14] = "<";
		 button[2] = new Button(2, left, top, right, bottom, COLOR(190, 193, 196), WHITE, c, PLANE_TEXT_COLOR);
		 button[2]->onClick(button[2]);



		 left = right + 100;
		 right = left + 50;
		 char d[14] = ">";
		 button[3] = new Button(3, left, top, right, bottom, COLOR(190, 193, 196), WHITE, d, PLANE_TEXT_COLOR);
		 button[3]->onClick(button[3]);



		 //------------ VE SO TRANG
		 setbkcolor(SUBWINDOW_BACKGROUND);
		 setcolor(COLOR(142, 154, 185));
		 settextstyle(0, 0, 0);
		 outtextxy(left - 65, top+ 5 , soTrang);

		 //----------VE LINE
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(leftBorder + 2, topBorder + 2, rightBorder - 2, topBorder + 48);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		for (int i = 1; i <= 3; i++) {
			line((leftBorder + 100) * i * 2, topBorder, (leftBorder + 100) * i * 2, bottomBorder);


		}

		line(leftBorder, topBorder + 50, rightBorder, topBorder + 50);


		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		settextstyle(0, 0, 0);
		setusercharsize(1, 2, 1, 2);
		int preX = leftBorder;
		for (int i = 1; i <= 4; i++) {
			int width = textwidth(PLANE_BUTTON_NAME[i - 1]);
			int height = textheight(PLANE_BUTTON_NAME[i - 1]);
			int x = (leftBorder + 100) * i * 2;

			outtextxy((x + preX - width) / 2, topBorder + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}




		
	}


	void readFile() {

	}


};
