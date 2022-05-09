#pragma once
#include"ManagePlanesTab.h"
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

	}



	void drawUI() {
		
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

		drawStatictisData(sortedPlane, 3, d->planeList);


	}


};