#pragma once
#include"graphics.h"
#pragma comment(lib,"graphics.lib")
#ifndef DEFINE_H
#define DEFINE_H
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
#define TAB_WIDTH 200
#define TAB_HEIGHT 100
#define TAB_SPACE 50
#define TAB_TOP 30
#define TAB_LEFT 25
#define TAB_RIGHT 250
#define TAB_DEFAULT_BACKGROUND COLOR(241, 208, 215)
#define TAB_ON_SELECTED_BACKGROUND COLOR(167, 206, 225)
#define TAB_TEXT_COLOR BLACK

char TAB_TEXT[MAX_TAB][30] = {
   "PLANES",
   "FLIGHTS",
   "CUSTOMER",
   "TICKET",
   "STATISTIC"

};
//------------BUTTON

#define BUTTON_PAGE COLOR(190, 193, 196)
#define BUTTON_BACKGROUND COLOR(167, 206, 225)
#define BUTTON_TEXT_COLOR COLOR(0, 133, 190)


//--------------BORDER
int LEFT_BORDER = SUBWINDOW_LEFT + 100;
int TOP_BORDER = SUBWINDOW_TOP + 50;
int RIGHT_BORDER = SUBWINDOW_RIGHT - 100;
int BOTTOM_BORDER = SUBWINDOW_BOTTOM - 120;


//-----------------BACKGROUND COLOR
#define BACKGROUND_COLOR COLOR(255, 246, 245)


//---------------MANAGE PLANE TAB-------------
#define PLANE_MAX_BUTTON 8
#define PLANE_MAX_EDITTEXT 3
#define PLANE_TEXT_COLOR COLOR(0, 133, 190)
char PLANE_BUTTON_NAME[5][20]{
	"Number",
	"Flight Number",
	"Brand",
	"Seats"
};



#define PAGE_COLOR COLOR(142, 154, 185)
#define LIMIT_PAGE 5


//---------------MANAGE PASSENGER TAB-------------
#define PASSENGER_MAX_BUTTON 5
#define PASSENGER_TEXT_COLOR COLOR(0, 133, 190)
char PASSENGER_BUTTON_NAME[6][20]{
	"Number",
	"ID Passenger",
	"Full Name",
	"Last Name",
	"Gender"
};
#define PAGE_COLOR COLOR(142, 154, 185)
#define LIMIT_PAGE_PASSENGER 3




//--------------EDIT TEXT
#define EDITEXT_WIDTH 500
#define EDITTEXT_HEIGHT 50
#define EDITEXT_TEXT_COLOR COLOR(0, 133, 190)
#define EDITEXT_BACKGROUND_COLOR COLOR(227, 228, 230)
#define EDITEXT_HINT_COLOR COLOR(137, 137, 137)
#define EDITEXT_INPUT_COLOR COLOR(222, 222, 224)
#define EDITTEXT_SPACE 80


//--------------KEY
#define ENTER 13
#define BACK_SPACE 8
#define SPACE 32

//---------------MANAGE FLIGHT TAB-------------
#define FLIGHT_MAX_BUTTON 8
#define FLIGHT_TEXT_COLOR COLOR(0, 133, 190)

char FLIGHT_BUTTON_NAME[8][20]{
	"Number",
	"ID Flight",
	"ID Plane",
	"Date",
	"Time",
	"Arrive",
	"Status"
};
char FLIGHT_ADDFLIGHT_EDITTEXT_NAME[7][10]{
	"ID",
	"Date",
	"Time",
	"IdPlane",
	"Arrive",
	"Status"
};


//TICKET TAB
#define TICKET_AVAI COLOR(144,151,155)
#define TICKET_CHOOSEN COLOR(0,247,16)
#define TICKET_NOT_AVAI COLOR(255,136,136)


//-----ENUM BUTTON EDITTEXT NAME
enum EIDT_NAME { ID, BRAND, SEATS ,DAY,MONTH,YEAR,HOUR,MINUTE};
enum BUTTON_NAME { ADD, SHOW, LEFT, RIGHT, BACK, SAVE };
enum MENU { MAIN_MENU, ADD_MENU, ADJUST_MENU, SHOW_MENU };

#endif









