#pragma once

#include"Button.h"
#include"Tab.h"
#include"EditText.h"
#include"Flights.h"
#include"FunctionTab.h"


class ManageFlightsTab:public FunctionTab {
private:
	Button button[FLIGHT_MAX_BUTTON];
	EditText addFlightEdittext[11];
	EditText adjustFlightEdittext[11];
	int index = -1;
	int indexID = -1;
	PTR First;
	FlightNode* flightNode;
	Flight temp;

	EditText* fieldPointer, * adjustPointer;
public:


	ManageFlightsTab() {
		
		
		readFileFlight(flightNode);
		initButton();
		initEditText();

		fieldPointer = &addFlightEdittext[index];
		adjustPointer = &adjustFlightEdittext[ID];




	}

	void initButton() {
		//-------------BUTTON THEM
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 50;
		int right = left + 50;
		int bottom = top + 50;
		char a[15] = "+";
		button[ADD] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a,
			PLANE_TEXT_COLOR);


		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[LEFT] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a, BUTTON_TEXT_COLOR);
		//--------------BUTTON PHAI
		left = right + 70;
		right = left + 50;
		strcpy_s(a, ">");
		button[RIGHT] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a, BUTTON_TEXT_COLOR);


		//-----------BUTTON QUAY LUI
		strcpy_s(a, "<");
		button[BACK] = Button(SUBWINDOW_LEFT + 10, SUBWINDOW_TOP + 10, SUBWINDOW_LEFT + 60, SUBWINDOW_TOP + 60, BUTTON_BACKGROUND, WHITE, a, 
			BUTTON_TEXT_COLOR);

		//-----------BUTTON LUU
		strcpy_s(a, "SAVE");
		button[SAVE] = Button(SUBWINDOW_RIGHT - 100, SUBWINDOW_BOTTOM - 100, SUBWINDOW_RIGHT - 30, SUBWINDOW_BOTTOM - 50, BUTTON_BACKGROUND, 
			WHITE, a,
			BUTTON_TEXT_COLOR);
	}

	void initEditText() {

		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 100;
		int right = left + EDITEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;

		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";

		addFlightEdittext[ID] = adjustFlightEdittext[ID] = EditText(hint, title, content, left, top, right, bottom, 15);


		//------------EDITTEXT DAY
		strcpy_s(title, "DAY");
		top = bottom + EDITTEXT_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addFlightEdittext[DAY] = adjustFlightEdittext[DAY] = EditText(hint, title, content, left, top, right, bottom, 40);

		//------------EDITTEXT MONTH
		strcpy_s(title, "MONTH");
		left = left + right;
		right = left + EDITEXT_WIDTH;
		top = top + bottom;
		bottom = top + EDITTEXT_HEIGHT;
		addFlightEdittext[MONTH] = adjustFlightEdittext[MONTH] = EditText(hint, title, content, left, top, right, bottom, 40);

		//------------EDITTEXT YEAR
		strcpy_s(title, "YEAR");
		left = left + right;
		right = left + EDITEXT_WIDTH;
		top = top + bottom;
		bottom = top + EDITTEXT_HEIGHT;
		addFlightEdittext[YEAR] = adjustFlightEdittext[YEAR] = EditText(hint, title, content, left, top, right, bottom, 40);

		//------------EDITTEXT HOUR
		strcpy_s(title, "HOUR");
		left = left + right;
		right = left + EDITEXT_WIDTH;
		top = top + bottom;
		bottom = top + EDITTEXT_HEIGHT;
		addFlightEdittext[HOUR] = adjustFlightEdittext[HOUR] = EditText(hint, title, content, left, top, right, bottom, 40);

		//------------EDITTEXT MINUTE
		strcpy_s(title, "MINUTE");
		left = left + right;
		right = left + EDITEXT_WIDTH;
		top = top + bottom;
		bottom = top + EDITTEXT_HEIGHT;
		addFlightEdittext[MINUTE] = adjustFlightEdittext[MINUTE] = EditText(hint, title, content, left, top, right, bottom, 40);

		
		
	
	}






	/*
	void drawAddFlightBorder() {
		//-----------------VE HUONG DAN TEXT
		char a[30] = "ADD FLIGHT";
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2, SUBWINDOW_TOP + 10, a);
		strcpy_s(a, "*Use keyboard to navigate");
		setcolor(GREEN);

		outtextxy(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);


		button[lui].onAction();
		button[luu].onAction();

		for (int i = 0; i < 3; i++) {

			addFlightEdittext[i].onAction(fieldPointer);
		}
		int c = getInput();
		if (fieldPointer != NULL) {

			if (c == -1) fieldPointer->deleteChar();
			else
				if (c == 1) {
					fieldPointer->clearCursor();
					fieldPointer->checkEmpty();
					bool s = true;
					if (!fieldPointer->checkEmpty()) {
						if (fieldPointer == &addFlightEdittext[STATUS]) {
							fieldPointer->checkParseInt();
							if (!fieldPointer->checkParseInt()) {
								s = false;
							}
						}
						if (s) {
							index--;
							index = max(index, 0);
							fieldPointer = &addFlightEdittext[index];
						}
					}


				}
				else if (c == 2) {
					fieldPointer->clearCursor();
					fieldPointer->checkEmpty();
					bool s = true;
					if (!fieldPointer->checkEmpty()) {
						if (fieldPointer == &addFlightEdittext[ID]) {
							fieldPointer->checkDup(checkDupID(flightNode, fieldPointer->getContent()));
							if (fieldPointer->checkDup(checkDupID(flightNode, fieldPointer->getContent()))) {
								s = false;
							}
						}
						if (s) {
							index++;
							index = min(index, 2);
							fieldPointer = &addFlightEdittext[index];
						}


					}





				}
				else if (c != 0) {

					if (fieldPointer == &addFlightEdittext[ID]) {
						if (c <= 90 && c >= 65)
							fieldPointer->addChar((char)c);

					}
					else if (fieldPointer == &addFlightEdittext[IDPLANE]) {
						if (c <= 90 && c >= 65 || c == ' ')
							fieldPointer->addChar((char)c);

					}
					else if (fieldPointer == &addFlightEdittext[STATUS]) {
						if (c <= 57 && c >= 48)
							fieldPointer->addChar((char)c);

					}


				}


		}
		if (button[lui].isClicked()) {
			currentMenu = MENU_CHINH;
			writeFileFlight(flightNode);
			drawUI();
		}

		if (button[luu].isClicked()) {
			if (checkSaveData()) {
				Flight p;
				strcpy_s(p.idFlight, addFlightEdittext[ID].getContent());
				strcpy_s(p.arrive, addFlightEdittext[ARRIVE].getContent());
				strcpy_s(p.idPlane, addFlightEdittext[IDPLANE].getContent());
				p.departure.day = addFlightEdittext[DAY].getIntData();
				p.departure.month = addFlightEdittext[MONTH].getIntData();
				p.departure.year = addFlightEdittext[YEAR].getIntData();
				p.departure.hour = addFlightEdittext[HOUR].getIntData();
				p.departure.minute = addFlightEdittext[MINUTE].getIntData();
				p.status = addFlightEdittext[STATUS].getIntData();
				for (int i = 0; i < 3; i++) {
					addFlightEdittext[i].clearText();
				}
				setbkcolor(SUBWINDOW_BACKGROUND);

				char s[30] = "Succesfully";
				addFlightEdittext[STATUS].drawAnoune(s, false);
				PTR temp = newNode();
				temp->next = NULL;
				temp->info = p;
				insertAfter(flightNode, temp);

				resetInline();
			}


		}


	}

	*/
};