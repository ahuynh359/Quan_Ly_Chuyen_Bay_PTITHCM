#pragma once
#include "Button.h"
#include "Tab.h"
#include<fstream>
using namespace std;
class ManagePlanesTab {
private:
	Button* button[PLANE_MAX_BUTTON];
	char soTrang[5];
	char planeData[50][50];
public:

	ManagePlanesTab() {
		strcpy_s(this->soTrang, "1/2");
		for (int i = 0; i < PLANE_MAX_BUTTON; i++) {
			button[i] = NULL;
		}
		readFile();

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

	void readFile() {
		ifstream inp("DSMB.txt");
		if (inp.fail()) {
			printf("Khong mo duoc file\n");
			exit(1);

		}

		int n;
		inp >> n;
		for (int i = 0; i < n; i++) {

			for (int j = 0; j < 4; j++) {
				inp >> planeData[i][j];

			}
		}

		inp.close();

	}
	void initManagePlaneTab() {

		// Ve nen
		drawBackground();
		

		//-------------BUTTON THEM CHUYEN BAY
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 50;
		int right = left + 50;
		int bottom = top + 50;
		//settextstyle(0, 0, 3);
		char s[14] = "+";
		button[0] = new Button(0, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, s,
			PLANE_TEXT_COLOR);
		button[0]->drawUI();


		//------------BUTTON XEM DS CHUYEN BAY
		top = bottom + 10;
		right = left + 50;
		bottom = top + 50;
		char a[14] = "XEM";
		button[1] = new Button(1, left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);
		button[1]->drawUI();


		//-------------------VE BORDER
		rectangle(LEFT_BORDER, TOP_BORDER, RIGHT_BORDER, BOTTOM_BORDER);

		//-----------------VE HUONG DAN TEXT
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		//settextstyle(0, 0, 0);
		char b[2][50] = { "*Chuot phai de xoa thong tin" ,
						"Chuot trai de sua thong tin"};
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, b[0]);
		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 40, b[1]);


		//------------VE BUTTON  TRAI , PHAI 
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
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
		//settextstyle(0, 0, 0);
		outtextxy(left - 65, top + 5, soTrang);

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


		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		//settextstyle(0, 0, 0);
		setusercharsize(1, 2, 1, 2);
		int preX = LEFT_BORDER;
		for (int i = 1; i <= 4; i++) {
			int width = textwidth(PLANE_BUTTON_NAME[i - 1]);
			int height = textheight(PLANE_BUTTON_NAME[i - 1]);
			int x = LEFT_BORDER + space * i;

			outtextxy((x + preX - width) / 2, TOP_BORDER + 15, PLANE_BUTTON_NAME[i - 1]);
			preX = x;
		}

		onItemClicked();

		
	}

	void onItemClicked() {
		int preY = TOP_BORDER + 25;

		int preX = LEFT_BORDER;
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));
		//settextstyle(0, 0, 0);
		setusercharsize(1, 2, 1, 1);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		for (int i = 1; i <= 10; i++) {

			preX = LEFT_BORDER;
			int y = preY + 30;
			if (mousex() <= RIGHT_BORDER && mousex() >= LEFT_BORDER && mousey() <= (y + 30) && mousey() >= (preY + 30)) {
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(COLOR(205,92,92));
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
				preY += 30;

				

		}
	}




	void veKhungXacNhanXoa() {

	}


};
