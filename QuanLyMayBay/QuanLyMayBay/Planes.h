

#include"DataConst.h"
#ifndef PLANE_H
#define PLANE_H
#include<iostream>
#include<fstream>
using namespace std;

struct Plane {
	char idPlane[MAX_ID];
	char type[MAX_TYPE];
	int seats; //So cho >= 20

	// CHI SO PHU
	int flyTimes = 0; // so luot thuc hien
	bool active = true;


};


struct PlaneList {
	int size = 0;
	Plane* data[MAX_PLANE];

};

//Ham tim may bay 
Plane* findPlane(PlaneList& list, char idPlane[MAX_ID]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0)
			return list.data[i];
	}
	return NULL;
}

//Tra ve vi tri may bay
int getIndexPlane(PlaneList& list, char idPlane[MAX_ID]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0) {
			return i;
		}
	}
	return -1;
}

//Remove may bay
int removePlane(PlaneList& list, int index) {
	if (index < 0 || index > list.size - 1)
		return 0;
	for (int i = index; i < list.size - 1; i++) {
		list.data[i] = list.data[i + 1];
	}
	list.size--;
	return 1;

}


void addPlane(PlaneList& list, Plane* plane) {
		list.data[list.size] = plane;
		list.size++;
	
}

bool checkDupID(PlaneList& list, char id[30]) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, id) == 0) {
			return true;
		}
	}
	return false;
}


void readFilePlane(PlaneList &planeList) {
	ifstream inp("PlaneData.txt");
	string line;

	int n;
	inp >> n;
	inp.ignore();
	for (int i = 0; i < n; i++) {
		Plane* plane = new Plane();
		getline(inp, line);    strcpy_s(plane->idPlane, line.c_str());
		getline(inp, line);		strcpy_s(plane->type, line.c_str());
		getline(inp, line);		plane->seats = atoi(line.c_str());

		addPlane(planeList, plane);



	}
	inp.close();

}

void writeFilePlane(PlaneList& planeList) {
	ofstream out("PlaneData.txt", ios::trunc);
	out << planeList.size << '\n';
	for (int i = 0; i < planeList.size; i++) {
		out << planeList.data[i]->idPlane << '\n';
		out << planeList.data[i]->type << '\n';
		out << planeList.data[i]->seats << '\n';


	}
	out.close();
}

#endif

