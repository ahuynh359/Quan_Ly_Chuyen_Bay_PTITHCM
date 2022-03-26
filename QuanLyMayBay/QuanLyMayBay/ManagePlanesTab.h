#pragma once

#include "Button.h"
#include"Tab.h"

#include<fstream>
using namespace std;
class ManagePlanesTab {
private:
	Button button[PLANE_MAX_BUTTON];
	char soTrang[5];
	char planeData[50][50];
	enum BUTTON_NAME { them, hthi, trai, phai, lui, luu };
	int n; //Tong so phan tu
	int currentMenu = 0;
	enum MENU { MENU_CHINH, MENU_THEM };
public:

	ManagePlanesTab() {
		int textButton = COLOR(190, 193, 196);
		strcpy_s(this->soTrang, "1/2");
		n = 0;
		//-------------BUTTON THEM
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 50;
		int right = left + 50;
		int bottom = top + 50;
		char a[15] = "+";
		button[them] = Button(them, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//------------BUTTON XEM DS CHUYEN BAY
		top = bottom + 10;
		right = left + 50;
		bottom = top + 50;
		strcpy_s(a, "LIST");
		button[hthi] = Button(hthi, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);



		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[trai] = Button(trai, left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);

		//--------------BUTTON PHAI
		left = right + 100;
		right = left + 50;
		strcpy_s(a, ">");
		button[phai] = Button(phai, left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
		button[lui] = Button(lui, SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60, textButton, WHITE, a, PLANE_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[luu] = Button(luu, SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30, SUBWINDOW_BOTTOM - 50, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);
		readFile();
		//drawBackground();
		//initManagePlaneTab();
		//ButtonClick();



	}

	void drawUI() {
		//cleardevice();
		drawBackground();

		switch (currentMenu) {
		case MENU_CHINH: {
			drawManagePlaneTab();
			break;
		}

		case MENU_THEM: {
			drawAddPlaneBorder();
			break;
		}
		default: {
			break;
		}

		}
	}
	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}

	void readFile() {
		ifstream inp("DSMB.txt");
		if (inp.fail()) {
			printf("Khong mo duoc file\n");
			exit(1);

		}

		inp >> n;
		for (int i = 0; i < n; i++) {

			for (int j = 0; j < 4; j++) {
				inp >> planeData[i][j];
			}
		}

		inp.close();

	}
	void drawAddPlaneBorder() {
		//while (!button[lui].isLeftMouseClicked(mousex(), mousey())) {
		char a[20] = "ADD PLANE";
		button[lui].drawUI();
		button[luu].drawUI();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		//settextstyle(10, 0, 5);
		int w = textwidth(a);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - w) / 2, SUBWINDOW_TOP + 10, a);
		if (button[lui].isLeftMouseClicked(mousex(), mousey())) {
			currentMenu = MENU_CHINH;
			drawUI();
		}
		//}


	}

	void drawManagePlaneTab() {


		//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------VE BUTTON
		for (int i = 0; i < 4; i++) {
			button[i].drawUI();
		}


		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		char a[30] = "*Right click to delete item";
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Left click to edit item");
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);


		//------------ VE SO TRANG
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(142, 154, 185));
		int w = textwidth(soTrang);
		int h = textheight(soTrang);
		outtextxy((LEFT_BORDER + RIGHT_BORDER - w) / 2, BOTTOM_BORDER + 35, soTrang);

		//----------VE LINE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(LEFT_BORDER + 2, TOP_BORDER + 2, RIGHT_BORDER - 2, TOP_BORDER + 48);
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		for (int i = 1; i <= 3; i++) {
			line(LEFT_BORDER + space * i, TOP_BORDER, LEFT_BORDER + space * i, BOTTOM_BORDER);


		}

		line(LEFT_BORDER, TOP_BORDER + 50, RIGHT_BORDER, TOP_BORDER + 50);


		//-----------VE TIEU DE CHO KHUNG
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		int preX = LEFT_BORDER;
		for (int i = 1; i <= 4; i++) {
			int width = textwidth(PLANE_BUTTON_NAME[i - 1]);
			int height = textheight(PLANE_BUTTON_NAME[i - 1]);
			int x = LEFT_BORDER + space * i;
			//settextstyle(0, 0, 0);
			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}

		onItemClicked();
		if (button[them].isLeftMouseClicked(mousex(), mousey())) {


			currentMenu = MENU_THEM;
			drawUI();
		}

	}

	

	//Do du lieu ra bang va xu li su kien
	void onItemClicked() {
		int preY = TOP_BORDER + 35;
		int preX = LEFT_BORDER;

		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;

		for (int i = 1; i <= n; i++) {
			preX = LEFT_BORDER;
			int y = preY + 35;
			if (mousex() <= RIGHT_BORDER && mousex() >= LEFT_BORDER && mousey() <= (y + 35) && mousey() >= (preY + 35)) {
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(COLOR(205, 92, 92));
				for (int j = 1; j <= 4; j++) {
					int width = textwidth(planeData[j - 1]);
					int height = textheight(planeData[j - 1]);
					int x = preX + space;


					outtextxy((x + preX - width) / 2, y, planeData[j - 1]);

					preX = x;

				}
			}
			else {
				for (int j = 1; j <= 4; j++) {
					int width = textwidth(planeData[j - 1]);
					int height = textheight(planeData[j - 1]);
					int x = preX + space;


					setbkcolor(SUBWINDOW_BACKGROUND);
					setcolor(BLACK);
					outtextxy((x + preX - width) / 2, y, planeData[j - 1]);

					preX = x;

				}
			}
			preY += 35;



		}
	}


	void action() {

	}



	void veKhungXacNhanXoa() {
		drawBackground();
		setbkcolor(COLOR_BACKGROUND);
		setcolor(BLACK);



	}


};
