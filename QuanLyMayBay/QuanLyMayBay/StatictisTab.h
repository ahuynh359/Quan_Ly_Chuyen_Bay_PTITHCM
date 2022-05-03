#pragma once
#include"ManagePlanesTab.h"
#include"FunctionTab.h"
class StatictisTab:FunctionTab {
private:
	PlaneList planeList;
	int index = -1;
public:
	StatictisTab() {
	}
	~StatictisTab() {

	}

	
	
	void drawUI(PlaneList &planeList) {
		this->planeList = planeList;
		drawPlaneData(4, planeList, index);

		

	}


};