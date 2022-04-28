

#include"DataConst.h"
#ifndef PLANE_H
#define PLANE_H
#include<iostream>
#include<fstream>


struct Plane {
	char idPlane[MAX_ID_PLANE + 1];
	char type[MAX_TYPE_PLANE + 1];
	int seats; //So cho >= 20

	// CHI SO PHU
	int flyTimes = 0; 
	


};


struct PlaneList {
	int size = 0;
	Plane* data[MAX_PLANE];

};

bool isEmpty(PlaneList& list) {
	return (list.size == 0 ? true : false);
}

bool isFull(PlaneList& list) {
	return (list.size >= MAX_PLANE ? true : false);
}

Plane* newPlane(Plane plane) {
	Plane* p = new Plane;
	*p = plane;
	return p;
}

void addPlane(PlaneList& list, Plane plane) {
	list.data[list.size] = newPlane(plane);
	list.size++;

}

int findPlane(PlaneList& list, char idPlane[MAX_ID_PLANE + 1]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0)
			return i;
	}
	return -1;
}

void removePlane(PlaneList& list, int index) {
	
	for (int i = index; i < list.size - 1; i++) {
		list.data[i] = list.data[i + 1];
	}
	list.size--;
	

}

bool checkDupIDPlane(PlaneList& list, char id[MAX_ID_PLANE + 1]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, id) == 0) {
			return true;
		}
	}
	return false;
}
bool checkSeat(int seat) {
	return (seat <= 50 && seat >= 20);
}
void adjustPlane(PlaneList& list, Plane& plane,int index) {
	if (index < 0 || index > list.size - 1)
		return;
	*list.data[index] = plane;
}

void writeFilePlane(PlaneList& planeList) {

	ofstream out("PlaneData.txt", ios::binary);

	if (out.fail()) {
		cout << "Khong mo duoc file DSMB\n";
		return;
	}

	for (int i = 0; i < planeList.size; i++) {
		out.write(reinterpret_cast<char*>(planeList.data[i]), sizeof(Plane));

	}

	out.close();


}

void readFilePlane(PlaneList& planeList) {
	ifstream inp("PlaneData.txt", ios::binary);

	if (inp.fail()) {
		cout << "Khong mo duoc file DSCB\n";
		return;
	}

	Plane plane;
	while (inp.read(reinterpret_cast<char*>(&plane), sizeof(Plane))) {
		addPlane(planeList, plane);
	}
	inp.close();

}

#endif

