#pragma once
#include"graphics.h"
#pragma comment(lib,"graphics.lib")
//----------------SCREEN----------
//#define SCREEN_WIDTH 1920
//#define SCREEN_HIGHT 1080

int SCREEN_WIDTH = GetSystemMetrics(SM_CXSCREEN);
int SCREEN_HEIGHT = GetSystemMetrics(SM_CYSCREEN);

//--------------SUBWINDOW---------------
#define SUBWINDOW_LEFT 25  
#define SUBWINDOW_TOP 120
int SUBWINDOW_RIGHT = SCREEN_WIDTH - SUBWINDOW_LEFT ;
int SUBWINDOW_BOTTOM = SCREEN_HEIGHT - SUBWINDOW_TOP/2;
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
 char TAB_TEXT[MAX_TAB+1][30] = {
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


//----------------------SUBSCREEN----------------
#define SUBSCREEN_WIDTH 1808
#define SUBSCREEN_HEIGHT 886
#define SUBSCREEN_DEFAULT_BACKGROUND COLOR(237, 244, 248)
#define SUBSCREEN_MARGIN_LEFT 55
#define SUBSCREEN_MARGIN_TOP 160


//------------------EDITTEXT
#define EDITTEXT_WIDTH 483
#define EDITTEXT_HEIGHT 69


//-----------------BACKGROUND COLOR
#define BACKGROUND_COLOR COLOR(255, 246, 245)






