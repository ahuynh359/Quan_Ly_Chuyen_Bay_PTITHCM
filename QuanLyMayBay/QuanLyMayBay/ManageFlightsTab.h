#pragma once


#include"Button.h"
#include"EditText.h"
#include"Flights.h"
#include"FunctionTab.h"


class ManageFlightsTab:public FunctionTab {
private:
	Button button[MAX_BUTTON];
	EditText edittext[MAX_EDITTEXT],addEdittext[MAX_EDITTEXT];

	int indexID = -1;

	PTR first;
	Flight tempFlight;
	EditText* buttonPointer, * edittextPointer,*addPointer;

	PlaneList planeList;
	ManagePlanesTab managePlane;
public:


	ManageFlightsTab() {
		
		
		readFileFlight(first);
		initButton();
		initEdittext();
		edittextPointer = NULL;
		addPointer = &addEdittext[ID_FLIGHT];

		planeList = managePlane.getPlaneList();
	}

	~ManageFlightsTab() {
		deleteList(first);
	}

	void initButton() {
		//-------------BUTTON THEM
		int left = SUBWINDOW_RIGHT - 70;
		int top = SUBWINDOW_TOP + 60;
		int right = left + 50;
		int bottom = top + 50;
		char a[15] = "ADD";
		button[ADD] = Button(left, top, right, bottom, BUTTON_BACKGROUND, WHITE, a,
			BUTTON_TEXT_COLOR);


		//------------BUTTON  TRAI  
		left = SCREEN_WIDTH / 2 - 100;
		top = BOTTOM_BORDER + 30;
		right = left + 50;
		bottom = top + 30;
		strcpy_s(a, "<");
		button[LEFT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);
		//--------------BUTTON PHAI
		left = right + 70;
		right = left + 50;
		strcpy_s(a, ">");
		button[RIGHT] = Button(left, top, right, bottom, BUTTON_PAGE, WHITE, a, BUTTON_TEXT_COLOR);


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
	void initEdittext() {

		int left = LEFT_BORDER;
		int top = SUBWINDOW_TOP + 10;
		int right = left + 150;
		int bottom = top + EDITTEXT_HEIGHT;

		char hint[30] = "";
		char title[30] = "FLIGHT ID";
		char content[30] = "";

		edittext[ID_FLIGHT]=  EditText(hint, title, content, left, top, right, bottom, 15);


		//------------EDITTEXT DAY
		strcpy_s(title, "TIME");
		left = right + EDITTEXT_SPACE*2;
		right = left + 70;
		edittext[DAY] = EditText(hint, title, content, left, top, right, bottom, 2,40);

		//------------EDITTEXT MONTH
		strcpy_s(title, "/");
		left = right + 30 ;
		right = left + 70;
		edittext[MONTH] = EditText(hint, title, content, left, top, right, bottom, 2,15);

		//------------EDITTEXT YEAR
		strcpy_s(title, "/");
		left = right + 30;
		right = left + 70;
		edittext[YEAR] = EditText(hint, title, content, left, top, right, bottom, 4,15);


		//------------EDITTEXT ARRIVE
		strcpy_s(title, "ARRIVE");
		left = right + EDITTEXT_SPACE*2;
		right = SUBWINDOW_RIGHT - 20 ;
		edittext[ARRIVE] = EditText(hint, title, content, left, top, right, bottom, 40,55);

		initCompoAddFlight(); //Khoi tao cho man hinh them

		
	
	}
	void initCompoAddFlight() {
		int left = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - EDITTEXT_WIDTH + 90) / 2;
		int top = SUBWINDOW_TOP + 70;
		int right = left + EDITTEXT_WIDTH;
		int bottom = top + EDITTEXT_HEIGHT;

		//------------EDITTEXT ID FLIGHT
		char hint[30] = "Do not leave empty!";
		char title[30] = "FLIGHT ID";
		char content[30] = "";
		addEdittext[ID_FLIGHT] = EditText(hint, title, content, left, top, right, bottom, 15);

		//------------EDITTEXT ID PLANE
		strcpy_s(title, "PLANE ID");
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[ID_PLANE] = EditText(hint, title, content, left, top, right, bottom, 15);

		//------------EDITTEXT ARRIVE
		strcpy_s(title, "ARRIVE");
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[ARRIVE] = EditText(hint, title, content, left, top, right, bottom, 15);
		
		//------------EDITTEXT ARRIVE
		strcpy_s(title, "STATUS");
		strcpy_s(hint, "");
		strcpy_s(content, "HAVE TICKET");
		right = left + 100;
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[STATUS] = EditText(hint, title, content, left, top, right, bottom, 15);
		addEdittext[STATUS].customInitChar(content);
		addEdittext[STATUS].setActive(false);
	

		//------------EDITTEXT DAY
		strcpy_s(content, "");
		strcpy_s(hint, "dd");
		strcpy_s(title, "TIME");
		right = left + 50;
		top = bottom + EDITTEXT_MIN_SPACE;
		bottom = top + EDITTEXT_HEIGHT;
		addEdittext[DAY] = EditText(hint, title, content, left, top, right, bottom, 2);

		//------------EDITTEXT MONTH
		strcpy_s(hint, "mm");
		strcpy_s(title, "/");
		left = right + 15;
		right = left + 70;
		addEdittext[MONTH] = EditText(hint, title, content, left, top, right, bottom, 2,10);

		//------------EDITTEXT YEAR
		strcpy_s(hint, "yyyy");
		strcpy_s(title, "/");
		left = right + 15;
		right = left + 70;
		addEdittext[YEAR] = EditText(hint, title, content, left, top, right, bottom, 4,10);

		//------------EDITTEXT HOUR
		strcpy_s(hint, "h");
		strcpy_s(title, "AT");
		left = right + 70;
		right = left + 70;
		addEdittext[HOUR] = EditText(hint, title, content, left, top, right, bottom, 4,25);

		//------------EDITTEXT MINUTE
		strcpy_s(hint, "mm");
		strcpy_s(title, ":");
		left = right + 15;
		right = left + 70;
		addEdittext[MINUTE] = EditText(hint, title, content, left, top, right, bottom, 4,10);


		
		


	}

	void moveEdittextDown() {
		if (addPointer == &addEdittext[ID_FLIGHT])
			addPointer = &addEdittext[ID_PLANE];
		else if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ARRIVE];
		else if(addPointer = &addEdittext[ARRIVE])
			addPointer = &addEdittext[DAY];
		else if(addPointer == &addEdittext[DAY])
			addPointer = &addEdittext[MONTH];
		else if (addPointer == &addEdittext[MONTH])
			addPointer = &addEdittext[YEAR];
		else if (addPointer == &addEdittext[YEAR])
			addPointer = &addEdittext[HOUR];
		else if (addPointer == &addEdittext[HOUR])
			addPointer = &addEdittext[MINUTE];


	}
	void moveEdittextUp() {
		if (addPointer == &addEdittext[ID_PLANE])
			addPointer = &addEdittext[ID_FLIGHT];
		else if (addPointer == &addEdittext[ARRIVE])
			addPointer = &addEdittext[ID_PLANE];
		else if (addPointer = &addEdittext[MONTH])
			addPointer = &addEdittext[ARRIVE];
		else if (addPointer == &addEdittext[MONTH])
			addPointer = &addEdittext[DAY];
		else if (addPointer == &addEdittext[YEAR])
			addPointer = &addEdittext[MONTH];
		else if (addPointer == &addEdittext[HOUR])
			addPointer = &addEdittext[YEAR];
		else if (addPointer == &addEdittext[MINUTE])
			addPointer = &addEdittext[HOUR];

	}
	

	bool checkEdittextError(EditText*& edittextPointer) {
		edittextPointer->clearCursor();

		if (edittextPointer->isEmpty()) {
			drawAnounce(EMPTY);
			return false;
		}

		if (edittextPointer == &edittext[ID_FLIGHT]) {
			
			if (checkDupIDFlight(first, edittextPointer->getCharData())) {
				drawAnounce(DUP);
				return false;
			}
		}
	
		if (edittextPointer == &edittext[ID_PLANE]) {
		
			if (findPlane(planeList, edittextPointer->getCharData())) {
				drawAnounce(PLANE_NOT_EXIST);
				return false;
			}
		}
	

		if (edittextPointer == &edittext[DAY]) {
			
			
			if (!checkDay(edittextPointer->getIntData())) {
				drawAnounce(DAY_ERROR);
				return false;
			}
			
		}

		if (edittextPointer == &edittext[MONTH]) {
			
			
			if (!checkMonth(edittextPointer->getIntData())) {
				drawAnounce(MONTH_ERROR);
				return false;
			}
			
		}

		if (edittextPointer == &edittext[YEAR]) {
		
			
		//	if (!checkPassTime(edittextPointer->getIntData())) {
				//drawAnounce(TIME_ERROR);
			//	return false;
		//	}
			
		}




		return true;
	}
	void dataPerPage() {
		maxPage = ceil((size(first) + 0.0) / 10);

		if (currentPage > maxPage)
			currentPage--;

		currentPage = max(1, currentPage);
		maxPage = max(maxPage, 1);

		startPage = currentPage - 1;
		startPage = startPage * 10 + 1;

		//Toi da 10 du lieu 1 trang
		endPage = min(startPage + 9, size(first));
	}
	/*void inputHandel(EditText*& edittextPointer) {
		int c = FunctionTab::getInput();

		if (edittextPointer != NULL) {
			switch (c) {
			case -1: {
				edittextPointer->deleteChar();
				break;
			}
			case 1: {
				if (!checkEdittextError(edittextPointer, adjust)) {

				}
				else
					moveEdittextUp(edittextPointer);


				break;
			}
			case 3: case 2: {

				if (!checkEdittextError(edittextPointer, adjust)) {

				}
				else
					moveEdittextDown(edittextPointer);
				break;
			}
			default: {


				if (edittextPointer == &edittext[ID_PLANE]) {
					if ((c <= 90 && c >= 65) || (c <= 57 && c >= 48))
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[TYPE]) {
					if (c <= 90 && c >= 65 || c == ' ')
						edittextPointer->addChar((char)c);

				}
				else if (edittextPointer == &edittext[SEATS]) {
					if (c <= 57 && c >= 48)
						edittextPointer->addChar((char)c);

				}



				break;


			}
			}
		}

	}*/

	void  drawData() {
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(COLOR(50, 45, 188));


		dataPerPage();
		showPage(SCREEN_WIDTH / 2 - 35, BOTTOM_BORDER + 35, currentPage, maxPage);

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 10;
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20 - 3;
		int preY = TOP_BORDER + 70;

		int cnt = 0;
		PTR k = first;
		while (k != NULL) {
			if (cnt >= startPage && cnt <= endPage) {
				int preX = LEFT_BORDER;

				setcolor(BLACK);



				if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
					if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
						int s = drawAnounce(DELETE);
						
					}



					else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
					{
						

					}
					setcolor(ON_SELECTED_DATA_COLOR);
				}


				//STT
				char charValue[50];
				sprintf_s(charValue, sizeof(charValue), "%d", startPage);
				int width = textwidth(charValue);
				int height = textheight(charValue);
				int x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//ID Flight
				width = textwidth(k->info.idFlight);
				height = textheight(k->info.idFlight);
				x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, k->info.idFlight);
				preX = x;

				//ID Plane
				width = textwidth(k->info.idPlane);
				height = textheight(k->info.idPlane);
				x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, k->info.idPlane);
				preX = x;

				//Day
				sprintf_s(charValue, sizeof(charValue), "%d", k->info.date.day);
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//Month
				sprintf_s(charValue, sizeof(charValue), "%d", k->info.date.month);
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + 10;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//Year
				sprintf_s(charValue, sizeof(charValue), "%d", k->info.date.year);
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + 10;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//Hour
				sprintf_s(charValue, sizeof(charValue), "%d", k->info.date.hour);
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + 10;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//Minute
				sprintf_s(charValue, sizeof(charValue), "%d", k->info.date.minute);
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + 10;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;

				//Arrive
				width = textwidth(k->info.arrive);
				height = textheight(k->info.arrive);
				x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, k->info.arrive);
				preX = x;

				//Statis
				
				switch (k->info.status) {
				case 0: {
					strcpy_s(charValue, "CANCLED");
					break;
				}
				case 1: {
					strcpy_s(charValue, "TICKET AVAILABLE");
					break;
				}
				case 2: {
					strcpy_s(charValue, "SOLD OUT");
					break;
				}
				case 3: {
					strcpy_s(charValue, "COMPLETED");
					break;
				}
				default:
					break;
				}
				width = textwidth(charValue);
				height = textheight(charValue);
				x = preX + spaceX;
				outtextxy((x + preX - width) / 2, preY, charValue);
				preX = x;


				preY += spaceY;
				startPage++;
			}

			cnt++;
			k = k->next;
		}



	}
	void  drawUI() {
		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}
		case ADD_MENU: {
		
			drawAddMenu();
			break;
		}
		default:
			break;
		}
	}
	void drawMainMenu() {
		edittext[ID_FLIGHT].onAction(edittextPointer);
		edittext[DAY].onAction(edittextPointer);
		edittext[MONTH].onAction(edittextPointer);
		edittext[YEAR].onAction(edittextPointer);
		edittext[ARRIVE].onAction(edittextPointer);

		button[ADD].onAction();
		button[LEFT].onAction();
		button[RIGHT].onAction();

		drawData();

		//-------------------VE BORDER
		setcolor(BLACK);
		rectangle(LEFT_BORDER, TOP_BORDER + 10, RIGHT_BORDER, BOTTOM_BORDER + 10);

		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Left click to cancle flight";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit flight");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);
		strcpy_s(a, " Use left/right/enter button");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 60, a);


		//----------VE MAU NEN
		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		setfillstyle(0, TAB_ON_SELECTED_BACKGROUND);
		bar(LEFT_BORDER + 2, TOP_BORDER + 12, RIGHT_BORDER - 2, TOP_BORDER + 60);


		//----------VE LINE TUNG COT
		setcolor(BLACK);
		setlinestyle(0, 0, 3);
		int space = (RIGHT_BORDER + LEFT_BORDER) / 8;
		int l = LEFT_BORDER + space;
		for (int i = 1; i <= 5; i++) {
			line(l, TOP_BORDER + 10, l, BOTTOM_BORDER + 10);
			l = l + space;
		}

		//VE LINE DONG DAU TIEN
		line(LEFT_BORDER, TOP_BORDER + 60, RIGHT_BORDER, TOP_BORDER + 60);

		//-----------VE TIEU DE CHO KHUNG
		l = LEFT_BORDER + space;
		int preX = LEFT_BORDER;

		setbkcolor(TAB_ON_SELECTED_BACKGROUND);
		setcolor(BLACK);
		for (int i = 1; i <= 6; i++) {
			int width = textwidth(FLIGHT_TITLE[i - 1]);
			int height = textheight(FLIGHT_TITLE[i - 1]);
			outtextxy((l + preX - width) / 2, TOP_BORDER + 25, FLIGHT_TITLE[i - 1]);
			preX = l;
			l += space;
		}
		if (button[ADD].isClicked()) {
			currentMenu = ADD_MENU;
			drawUI();
		}

		if (button[LEFT].isClicked()) {
			onButtonPage(currentPage, TRUE, maxPage);
		}
		if (button[RIGHT].isClicked()) {
			onButtonPage(currentPage, FALSE, maxPage);

		}


	}
	void drawAddMenu() {
		addEdittext[ID_FLIGHT].onAction(addPointer);
		addEdittext[ID_PLANE].onAction(addPointer);
		addEdittext[ARRIVE].onAction(addPointer);
		addEdittext[STATUS].onAction(addPointer);
		addEdittext[DAY].onAction(addPointer);
		addEdittext[MONTH].onAction(addPointer);
		addEdittext[YEAR].onAction(addPointer);
		addEdittext[HOUR].onAction(addPointer);
		addEdittext[MINUTE].onAction(addPointer);

		button[SAVE].onAction();


	}
	void  freeMemory() {

	}




};