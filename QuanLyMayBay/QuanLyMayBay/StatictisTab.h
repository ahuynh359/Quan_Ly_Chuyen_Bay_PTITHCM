#pragma once

#include"FunctionTab.h"
#include"Data.h"

class StatictisTab :public FunctionTab {
private:
	Data* d;

public:
	StatictisTab(Data* d) {
		this->d = d;
	}
	~StatictisTab() {
		delete d;
	}

	void reset() {

	}

	void drawUI() {
		FunctionTab::drawBackground();

		char a[70] = "STATISTICS THE NUMBER FLYTIMES IN DESCENDING ORDER";
		int x = (SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(a)) / 2;
		int y = SUBWINDOW_TOP + 20;
		drawTitle(x, y, a);

		int size = d->planeList.size;

		int* sortedPlane;
		sortedPlane = new int[size];

		for (int i = 0; i < size; i++)
			sortedPlane[i] = i;
		bubbleSortPlane(d->planeList, sortedPlane);

		drawStatictisData(sortedPlane);


	}
	void drawStatictisData(int* a) {

		int spaceX = (RIGHT_BORDER + LEFT_BORDER) / 4;
		int spaceY = (TOP_BORDER + BOTTOM_BORDER) / 23;
		int preY = TOP_BORDER + 60;

		checkCompletedAll(d->flightList, d->planeList);
		onButtonPage(d->planeList.size, currentPage);
		showPage(currentPage);
		drawBorder(3, 4, isEmpty(d->planeList));


		setbkcolor(SUBWINDOW_BACKGROUND);

		for (int i = startPage ; i < d->planeList.size && i < (startPage + 10); i++) {

			int preX = LEFT_BORDER;
			setcolor(BLACK);
			//VE STT
			char temp[3];
			sprintf_s(temp, "%d", i + 1);
			int x = preX + 100;
			drawText(preX, preY, x, temp);
			preX = x;

			//VE ID PLANE
			x = preX + spaceX;
			drawText(preX, preY, x, d->planeList.data[a[i]]->idPlane);
			preX = x;

			//VE SO LUOT HIEN
			x = RIGHT_BORDER;
			sprintf_s(temp, "%d", d->planeList.data[a[i]]->flyTimes);
			drawText(preX, preY, x, temp);
			preX = x;



			preY += spaceY;

		}

	}

};