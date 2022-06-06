#pragma once


#include"Planes.h"
#include"FunctionTab.h"
#include"Data.h"



class ManagePlanesTab :public FunctionTab {


private:

	EditText* adjustEditextPointer = NULL;
	Data* d = NULL;
	//Index cua may bay duoc chon
	int indexID = -1;




public:
	ManagePlanesTab() {

	}
	ManagePlanesTab(Data* d) {
		this->d = d;
		initEdittext();
	}

	~ManagePlanesTab() {
	}



	//Khoi tao edittext
	void initEdittext() {

		//---------EDITTEXT ID
		char hint[30] = "Data must be entered!";
		char title[30] = "ID";
		char content[30] = "";

		int left = 430;
		int top = 250;

		//------------EDITTEXT ID PLANE
		edittext[ID_PLANE] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, MAX_ID_PLANE);


		//------------EDITTEXT TYPE
		strcpy_s(hint, "Max 40 character");
		strcpy_s(title, "TYPE");
		top += 120;
		edittext[TYPE] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, MAX_TYPE_PLANE);

		//-------------EDITTEXT SEATS
		strcpy_s(hint, "20-300");
		strcpy_s(title, "SEATS");
		top += 120;
		edittext[SEATS] = EditText(hint, title, content, left, top, left + EDITTEXT_WIDTH, top + EDITTEXT_HEIGHT, 3);



	}
	//Khoi tao edittext cho menu chinh sua may bay
	void initAdjustMenu(Plane* p) {

		edittext[ID_PLANE].setActive(false);

		//Da thanh lap chuyen bay chi cho sua so ghe theo chieu tang dan
		if (!p->isAvai) {

			edittext[TYPE].setActive(false);
			adjustEditextPointer = &edittext[SEATS];

		}
		//Nguoc lai cho sua loai may bay va so ghe
		else {
			edittext[TYPE].setActive(true);
			adjustEditextPointer = &edittext[TYPE];
		}

		edittext[ID_PLANE].customInitChar(p->idPlane);
		edittext[TYPE].customInitChar(p->type);
		edittext[SEATS].customInitNum(p->seats);

	}
	//Khoi tao edittext cho menu them may bay
	void initAddMenu() {

		edittextPointer = &edittext[ID_PLANE];
		edittext[ID_PLANE].setActive(true);
		edittext[TYPE].setActive(true);

	}



	//Lay du lieu may bay tu edittext
	Plane getPlaneData() {
		Plane p;
		strcpy_s(p.idPlane, edittext[ID_PLANE].getCharData());
		strcpy_s(p.type, edittext[TYPE].getCharData());
		p.seats = edittext[SEATS].getIntData();
		return p;

	}

	
	//Xoa  het du lieu 3 edittext
	void resetEdittext() {

		edittext[ID_PLANE].clearText();
		edittext[TYPE].clearText();
		edittext[SEATS].clearText();

		edittextPointer = NULL;
		adjustEditextPointer = NULL;


	}
	//Reset tab manage plane
	void reset() {
		typing = false;
		currentMenu = MAIN_MENU;
		currentPage = 1;
		resetEdittext();
	}



	/*Neu adjust la true thi ap dung cho adjust menu, nguoc lai add menu
	* Kiem tra loi tung edittext khi them hoac sua may bay
	*/
	bool checkEdittextError(EditText*& edittextPointer, bool adjust = false) {

		edittextPointer->clearCursor();

		//Kiem tra edittext rong
		if (edittextPointer->isEmpty()) {
			drawAnounce(EMPTY);
			return false;
		}

		if (!adjust)
			if (edittextPointer == &edittext[ID_PLANE])
				//Kiem tra ID May bay co trung lap khong
				if (findPlane(d->planeList, edittextPointer->getCharData()) != -1) {
					edittext[ID_PLANE].clearText();
					drawAnounce(DUP);
					return false;
				}

		edittext[TYPE].standarContent();

		//Kiem tra so ghe nam tu 20 - 300
		if (edittextPointer == &edittext[SEATS]) {
			if (!checkSeat(edittextPointer->getIntData())) {
				edittext[SEATS].clearText();
				drawAnounce(SEAT_ERROR);
				return false;
			}
		}

		//Neu da thanh lap chuyen bay kiem tra so ghe hien tai >= so ghe cu
		if (adjust && !d->planeList.data[indexID]->isAvai) {
			if (!isGreaterSeat(d->planeList.data[indexID]->seats, edittext[SEATS].getIntData())) {
				drawAnounce(GREATER_SEAT);
				edittext[SEATS].clearText();
				edittextPointer = &edittext[SEATS];
				return false;
			}
		}

		return true;
	}
	/*Neu adjust la true thi ap dung cho adjust menu, nguoc lai add menu
	* Check toan bo het 3 edittext de luu du lieu
	*/
	bool checkSaveData(EditText*& edittextPointer, bool adjust = false) {

		edittext[ID_PLANE].clearCursor();
		edittext[TYPE].clearCursor();
		edittext[SEATS].clearCursor();

		if (!adjust) {
			if (edittext[ID_PLANE].isEmpty()) {
				drawAnounce(EMPTY);
				edittextPointer = &edittext[ID_PLANE];
				return false;
			}
			//Kiem tra co trung ID hay khong
			if (findPlane(d->planeList, edittext[ID_PLANE].getCharData()) != -1) {
				drawAnounce(DUP);
				edittext[ID_PLANE].clearText();
				edittextPointer = &edittext[ID_PLANE];
				return false;
			}

		}

		if (edittext[TYPE].isEmpty()) {
			drawAnounce(EMPTY);
			edittextPointer = &edittext[TYPE];
			return false;
		}

		edittext[TYPE].standarContent();

		if (edittext[SEATS].isEmpty()) {
			drawAnounce(EMPTY);
			edittext[SEATS].clearText();
			edittextPointer = &edittext[SEATS];
			return false;
		}

		//Kiem tra so cho 20 - 300
		if (!checkSeat(edittext[SEATS].getIntData())) {
			drawAnounce(SEAT_ERROR);
			edittext[SEATS].clearText();
			edittextPointer = &edittext[SEATS];
			return false;
		}
		//Neu may bay da thanh lap chyen kiem tra so cho hien tai > so cho cu
		if (adjust && !d->planeList.data[indexID]->isAvai) {
			if (!isGreaterSeat(d->planeList.data[indexID]->seats, edittext[SEATS].getIntData())) {
				drawAnounce(GREATER_SEAT);
				edittext[SEATS].clearText();
				edittextPointer = &edittext[SEATS];
				return false;
			}
		}





		return true;
	}


	//Xu li su kien ban phim nhap edittext
	void inputHandel(EditText*& edittextPointer, bool adjust) {
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
					if (c <= 90 && c >= 65 || (c <= 57 && c >= 48) || c == ' ' || c <= 122 && c >= 97)
						edittextPointer->addCharName((char)c);

				}
				else if (edittextPointer == &edittext[SEATS]) {
					if (c <= 57 && c >= 48)
						edittextPointer->addChar((char)c);

				}

				break;


			}
			}
		}

	}
	void moveEdittextDown(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[ID_PLANE])
			edittextPointer = &edittext[TYPE];
		else if (edittextPointer == &edittext[TYPE]) {
			edittextPointer = &edittext[SEATS];

		}

	}
	void moveEdittextUp(EditText*& edittextPointer) {
		if (edittextPointer == &edittext[TYPE]) {
			if (edittext[ID_PLANE].isActive())
				edittextPointer = &edittext[ID_PLANE];

		}
		else if (edittextPointer == &edittext[SEATS])
			if (edittext[TYPE].isActive())
				edittextPointer = &edittext[TYPE];

	}

	//---------------------------------UI-------------------------
	void drawUI() {
		FunctionTab::drawBackground();
		typing = false;
		switch (currentMenu) {
		case MAIN_MENU: {
			drawMainMenu();
			break;
		}

		case ADD_MENU: {
			drawAddMenu();
			break;
		}
		case ADJUST_MENU: {
			drawAjustMenu();
			break;
		}

		default:
			break;



		}

	}
	void drawMainMenu() {

		//Ve button add
		button[ADD].onAction();

		//Ve title
		char title[15] = "PLANE DATA";
		int x = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(title)) / 2;
		int y = SUBWINDOW_TOP + 20;
		drawTitle(x, y, title);


		//Ve huong dan su dung
		char a[30] = "*Left click to delete";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);
		strcpy_s(a, " Right click to edit");
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 40, a);

		//Neu nut them duoc bam
		if (button[ADD].isClicked()) {
			//Day du lieu
			if (d->planeList.size == MAX_PLANE) {
				drawAnounce(FULL_LIST);
			}
			else {
				initAddMenu();
				currentMenu = ADD_MENU;
			}

		}

		//Ve bang du lieu
		int s = drawPlaneData(d->planeList, indexID);

		if (s == 1) {
			int s = drawAnounce(REMOVE_CONFIRM);

			switch (s) {
			case IDOK: {
				//Chi remove khi chua thanh lap chuyen bay
				if (d->planeList.data[indexID]->isAvai)
					removePlane(d->planeList, indexID);
				else
					drawAnounce(REMOVE_ERROR);
				break;
			}
			default:
				break;
			}
		}
		else if (s == 2) {


			initAdjustMenu(d->planeList.data[indexID]);
			currentMenu = ADJUST_MENU;

		}







	}
	void drawAddMenu() {
		typing = true;
		//Ve huong dan
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		//Ve title
		strcpy_s(a, "ADD PLANE");
		drawTitle(a);

		button[BACK].onAction();
		button[SAVE].onAction();

		//ve edittext
		edittext[ID_PLANE].onAction(edittextPointer);
		edittext[TYPE].onAction(edittextPointer);
		edittext[SEATS].onAction(edittextPointer);

		//xu li ban phim
		inputHandel(edittextPointer, false);


		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);

			switch (s) {
			case IDOK: {
				resetEdittext();
				currentMenu = MAIN_MENU;
				break;
			}
			default:
				break;
			}

		}
		if (button[SAVE].isClicked()) {

			if (!checkSaveData(edittextPointer, false)) {

			}
			else {
				Plane p = getPlaneData();
				addPlane(d->planeList, p);

				drawAnounce(SUCCESS);

				resetEdittext();
				initAddMenu();


			}


		}


	}
	void drawAjustMenu() {
		typing = true;
		//-----------------VE HUONG DAN TEXT
		char a[30] = "*Use Up/Down/Enter button";
		drawInstruction(LEFT_BORDER - 10, BOTTOM_BORDER + 20, a);

		strcpy_s(a, "ADJUST PLANE");
		drawTitle(a);


		button[BACK].onAction();
		button[SAVE].onAction();

		edittext[ID_PLANE].onAction(adjustEditextPointer);
		edittext[TYPE].onAction(adjustEditextPointer);
		edittext[SEATS].onAction(adjustEditextPointer);


		inputHandel(adjustEditextPointer, true);


		if (!d->planeList.data[indexID]->isAvai) {
			char ss[30] = "Must >= current seats";
			drawText(edittext[SEATS].getLeft(),
				edittext[SEATS].getTop() -textheight(ss) - 10, ss, RED);

		}


		if (button[BACK].isClicked()) {
			int s = drawAnounce(PREVIOUS);
			switch (s) {
			case IDOK: {
				resetEdittext();
				currentMenu = MAIN_MENU;
				break;
			}

			default:
				break;
			}

		}
		else if (button[SAVE].isClicked()) {

			if (!checkSaveData(adjustEditextPointer, 1)) {

			}
			else {
				
				Plane* p = d->planeList.data[indexID];
				p->seats = edittext[SEATS].getIntData();
				//Neu da thanh lap chuyen bay thi cap nhat luon total ticket
				if (!p->isAvai) {
					adjustTicketList(d->flightList, edittext[SEATS].getIntData(), edittext[ID_PLANE].getCharData());

				} else 
					strcpy_s(p->type, edittext[TYPE].getCharData());

				drawAnounce(SUCCESS);

				resetEdittext();
				currentMenu = MAIN_MENU;
			}


		}



	}


	//----------------------DATA -----------------
	void drawOnePlane(PlaneList& planeList, int preX, int preY, int i) {
		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 6;

		//VE STT
		char temp[30];
		sprintf_s(temp, "%d", i + 1);
		int x = preX + 100;
		drawText(preX, preY, x, temp);
		preX = x;

		//VE ID PLANE
		x = preX + spaceX;
		drawText(preX, preY, x, planeList.data[i]->idPlane);
		preX = x;

		//VE TYPE
		x += (spaceX + 200);
		drawText(preX, preY, x, planeList.data[i]->type);
		preX = x;

		//VE SEATS
		sprintf_s(temp, "%d", planeList.data[i]->seats);
		x = preX + spaceX;
		drawText(preX, preY, x, temp);
		preX = x;


		//VE TRANG THAI
		x = RIGHT_BORDER;
		if (planeList.data[i]->isAvai)
			strcpy_s(temp, "Avai");
		else
			strcpy_s(temp, "Not avai");
		drawText(preX, preY, x, temp);




	}
	int  drawPlaneData(PlaneList& planeList, int& indexID) {

		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 20;
		int preY = TOP_BORDER + 60;

		drawBorder(5, 0, isEmpty(planeList)); //Draw border va title
		onButtonPage(planeList.size, currentPage); //Su kien nut left / right
		showPage(currentPage); //Hien thi trang

		indexID = -1;

		for (int i = startPage; i < min(planeList.size, (startPage + 10)); i++) {


			indexID = i;

			int preX = LEFT_BORDER;
			setcolor(BLACK);


			if (isPointed(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				setcolor(ON_SELECTED_DATA_COLOR);
			}


			drawOnePlane(planeList, preX, preY, i);

			if (isLeftMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY)) {
				return 1;

			}

			else if (isRightMouseClicked(LEFT_BORDER, preY, RIGHT_BORDER, preY + spaceY))
			{
				return 2;

			}


			preY += spaceY;

		}

		return -1;


	}




};
