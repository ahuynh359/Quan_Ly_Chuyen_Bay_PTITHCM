#pragma once
#include"graphics.h"
#pragma comment(lib,"graphics.lib")
//----------------SCREEN----------
int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

//--------------SUBWINDOW---------------
#define SUBWINDOW_LEFT 25  
#define SUBWINDOW_TOP 120
int SUBWINDOW_RIGHT = SCREEN_WIDTH - SUBWINDOW_LEFT;
int SUBWINDOW_BOTTOM = SCREEN_HEIGHT;
#define SUBWINDOW_BACKGROUND COLOR(232,242,247)

//-------------------------TAB --------------------
#define MAX_TAB 5
#define TAB_WIDTH 250
#define TAB_HEIGHT 100
#define TAB_SPACE 250
#define TAB_TOP 30
#define TAB_LEFT 25
#define TAB_RIGHT 250
#define TAB_DEFAULT_BACKGROUND COLOR(241, 208, 215)
#define TAB_ON_SELECTED_BACKGROUND COLOR(167, 206, 225)
#define TAB_TEXT_COLOR BLACK
char TAB_TEXT_VI[MAX_TAB][30] = {
   "QUAN LI MAY BAY",
   "QUAN LI CHUYEN BAY",
   "QUAN LI HANH KHACH",
   "DAT VE",
   "HUY VE"
};
char TAB_TEXT[MAX_TAB][30] = {
   "PLANES",
   "FLIGHTS",
   "CUSTOMER",
   "BOOK TICKET",
   "CANCEL TICKET"
};


//--------------BORDER
int LEFT_BORDER = SUBWINDOW_LEFT + 100;
int TOP_BORDER = SUBWINDOW_TOP + 50;
int RIGHT_BORDER = SUBWINDOW_RIGHT - 100;
int BOTTOM_BORDER = SUBWINDOW_BOTTOM - 120;


//-----------------BACKGROUND COLOR
#define BACKGROUND_COLOR COLOR(255, 246, 245)

//---------------MANAGE PLANE TAB-------------
#define PLANE_MAX_BUTTON 6
#define PLANE_TEXT_COLOR COLOR(0, 133, 190)
char PLANE_BUTTON_NAME[5][20]{
	"Number",
	"Flight Number",
	"Brand",
	"Seats"
};
char PLANE_ADDPLANE_EDITTEXT_NAME[4][10]{
	"ID",
	"Brand",
	"Seats"
};


//--------------EDIT TEXT
#define EDITEXT_WIDTH 160
#define EDITTEXT_HEIGHT 70
#define EDITEXT_TEXT_COLOR COLOR(0, 133, 190)
#define EDITEXT_BACKGROUND_COLOR COLOR(227, 228, 230)
#define EDITEXT_HINT_COLOR COLOR(137, 137, 137)
#define EDITEXT_INPUT_COLOR COLOR(222, 222, 224)













