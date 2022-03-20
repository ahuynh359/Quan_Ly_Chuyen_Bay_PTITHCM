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
int SUBWINDOW_BOTTOM = SCREEN_HEIGHT - SUBWINDOW_TOP / 2;
#define SUBWINDOW_BACKGROUND COLOR(232,242,247)

//-------------------------TAB --------------------
#define MAX_TAB 5
#define TAB_WIDTH 250
#define TAB_HEIGHT 100
#define TAB_SPACE 250
#define TAB_TOP 30
#define TAB_DEFAULT_BACKGROUND COLOR(241, 208, 215)
#define TAB_ON_SELECTED_BACKGROUND COLOR(167, 206, 225)
#define TAB_TEXT_COLOR BLACK
char TAB_TEXT[MAX_TAB][30] = {
   "QUAN LI MAY BAY",
   "QUAN LI CHUYEN BAY",
   "QUAN LI HANH KHACH",
   "DAT VE",
   "HUY VE"
};
int TAB_LEFT[MAX_TAB + 1] = {
   25,0,0,0,0
};

int TAB_RIGHT[MAX_TAB + 1] = {
   250,0,0,0,0
}
;



//-----------------BACKGROUND COLOR
#define BACKGROUND_COLOR COLOR(255, 246, 245)

//---------------MANAGE PLANE TAB-------------
#define PLANE_MAX_BUTTON 7
#define PLANE_TEXT_COLOR COLOR(0, 133, 190)
char PLANE_BUTTON_NAME[5][20]{
	"STT",
	"So hieu may bay",
	"Loai may bay",
	"So cho"
};













