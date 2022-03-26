#pragma once

#include "Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Planes.h"
#include<fstream>
using namespace std;
class ManagePlanesTab {
private:
	Button button[PLANE_MAX_BUTTON];
	EditText edittext[3];


	char soTrang[5];
	PlaneList planeList;
	enum EIDT_NAME { ID, BRAND, SEATS };
	enum BUTTON_NAME { them, hthi, trai, phai, lui, luu };
	int n; //Tong so phan tu
	int currentMenu = 0;
	enum MENU { MENU_CHINH, MENU_THEM };
	EditText* temp = &edittext[0];
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
		button[them] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//------------BUTTON XEM DS CHUYEN BAY
		top = bottom + 10;
		right = left + 50;
		bottom = top + 50;
		strcpy_s(a, "LIST");
		button[hthi] = Button(left, top, right, bottom, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);



		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[trai] = Button(left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);
		//--------------BUTTON PHAI
		left = right + 100;
		right = left + 50;
		strcpy_s(a, ">");
		button[phai] = Button(left, top, right, bottom, textButton, WHITE, a, PLANE_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
		button[lui] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60, textButton, WHITE, a, PLANE_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[luu] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30, SUBWINDOW_BOTTOM - 50, TAB_ON_SELECTED_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);

		//---------EDITTEXT ID
		int spaceEdit = 80;
		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";
		left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		top = SUBWINDOW_TOP + 130;
		right = left + EDITEXT_WIDTH;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[ID] = EditText(hint, title, content, left, top, right, bottom);


		//------------EDITTEXT BRAND
		strcpy_s(title, "BRAND");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[BRAND] = EditText(hint, title, content, left, top, right, bottom);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, ">= 20");
		strcpy_s(title, "SEATS");
		top = bottom + spaceEdit;
		bottom = top + EDITTEXT_HEIGHT;
		edittext[SEATS] = EditText(hint, title, content, left, top, right, bottom);

		readFile();
		//drawBackground();
		//initManagePlaneTab();
		//ButtonClick();



	}

	void drawUI() {
		//cleardevice();
		//settextstyle(10, 0, 2);
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
	void reset() {
		currentMenu = 0;
	}

	void readFile() {
		ifstream inp("DSMB.txt");
		string line;
		
		int n;
		inp >> n;
		inp.ignore();
		for (int i = 0; i < n; i++) {
			Plane* plane = new Plane();
			getline(inp, line);    strcpy_s(plane->idPlane, line.c_str());
			getline(inp, line);		strcpy_s(plane->type, line.c_str());
			getline(inp, line);		plane->seats = atoi(line.c_str());

			addPlane(planeList,plane);
			


		}
		inp.close();

	}
	void drawAddPlaneBorder() {
		//while (!button[lui].isLeftMouseClicked(mousex(), mousey())) {
		for (int i = 0; i < 3; i++)
			edittext[i].drawUI();
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		char a[20] = "ADD PLANE";
		button[lui].drawUI();
		button[luu].drawUI();
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);

		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);

		for (int i = 0; i < 3; i++) {

			edittext[i].onAction(temp);
		}


		if (button[lui].isLeftMouseClicked(mousex(), mousey())) {
			currentMenu = MENU_CHINH;
			drawUI();
		}


	}
	void drawManagePlaneTab() {

		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
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
			//settextjustify(CENTER_TEXT, TOP_TEXT);
			//settextstyle(BOLD_FONT, HORIZ_DIR, 2);
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



		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));

		int space = (RIGHT_BORDER + LEFT_BORDER) / 5;
		int preY = TOP_BORDER + 35;
	
		for (int i = 1; i <= planeList.size; i++) {
			int preX = LEFT_BORDER;
			int y = preY + 35;
			if (mousex() <= RIGHT_BORDER && mousex() >= LEFT_BORDER && mousey() <= (y + 35) &&
				mousey() >= (preY + 35)) {
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(COLOR(205, 92, 92));
			}
			else {
				setbkcolor(SUBWINDOW_BACKGROUND);
				setcolor(BLACK);
			}
			//STT
			char charValue[50];
			sprintf_s(charValue, sizeof(charValue), "%d", i);
			int width = textwidth(charValue);
			int height = textheight(charValue);
			int x = preX + space ;
			outtextxy((x + preX - width) / 2, y, charValue);
			preX = x;
			//ID
			width = textwidth(planeList.data[i-1]->idPlane);
			height = textheight(planeList.data[i-1]->idPlane);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, planeList.data[i-1]->idPlane);
			preX = x;
			//BRAND
			width = textwidth(planeList.data[i-1]->type);
			height = textheight(planeList.data[i-1]->type);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, planeList.data[i-1]->type);
			preX = x;
			//SEATS
			sprintf_s(charValue,sizeof(charValue), "%d", planeList.data[i-1]->seats);
			width = textwidth(charValue);
			height = textheight(charValue);
			x = preX + space;
			outtextxy((x + preX - width) / 2, y, charValue);
			preX = x;

			preY += 35;

		}
	



	}





};
