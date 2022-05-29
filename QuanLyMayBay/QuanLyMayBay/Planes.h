#ifndef PLANE_H
#define PLANE_H


#include<fstream>
#include"DefineConst.h"


struct Plane {
	char idPlane[MAX_ID_PLANE + 1];
	char type[MAX_TYPE_PLANE + 1];
	int seats; //So cho  20 - 300

	//--- CHI SO PHU

	//So luot thuc hien chuyen bay
	int flyTimes = 0;
	bool isAvai = true;


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

Plane* newPlane(Plane& plane) {
	Plane* p = new Plane;
	*p = plane;
	return p;
}

void insertPlane(PlaneList& list, Plane& plane, int pos) {
	if (pos < 0)
		return;
	for (int i = list.size; i > pos; i--) {
		list.data[i] = list.data[i - 1];
	}
	list.data[pos] = newPlane(plane);
	(list.size)++;
}

//Them chuyen bay dua vao loai may bay,neu loai may bay trung, dua vao so cho
void addPlane(PlaneList& list, Plane& plane) {
	if (list.size > MAX_PLANE)
		return;
	for (int i = 0; i < list.size; i++) {
		if (strcmp(plane.type,list.data[i]->type ) < 0) {
			insertPlane(list, plane, i);
			return;
		}
		if (strcmp(plane.type,list.data[i]->type )  ==  0) {
			if (plane.seats <= list.data[i]->seats) {
				insertPlane(list, plane, i);
				return;
			}
			
		}
	}

	list.data[list.size] = newPlane(plane);
	list.size++;
	

}

int findPlane(PlaneList& list, char* idPlane) {
	for (int i = 0; i < list.size; i++) {
		if (strcmp(list.data[i]->idPlane, idPlane) == 0)
			return i;
	}
	return -1;
}



void removePlane(PlaneList& list, int index) {
	delete list.data[index];
	for (int i = index; i < list.size - 1; i++) {
		list.data[i] = list.data[i + 1];
	}
	list.size--;


}

bool checkSeat(int seat) {
	return (seat <= MAX_SEAT && seat >= MIN_SEAT);
}
bool isGreaterSeat(int oldSeat, int newSeat) {
	return (newSeat >= oldSeat);
}
void adjustPlane(PlaneList& list,int seats, int& index) {
	list.data[index]->seats = seats;
}


void swap(int& A, int& B) {

	int temp;
	temp = A;
	A = B;
	B = temp;
}
void bubbleSortPlane(PlaneList& list, int A[]) {
	for (int i = 0; i < list.size - 1; i++)
		for (int j = i + 1; j < list.size; j++)
			if (list.data[A[i]]->flyTimes < list.data[A[j]]->flyTimes)
			{
				swap(A[i], A[j]);
			}
}

void writeFilePlane(PlaneList& planeList) {

	ofstream out("PlaneData.txt", ios::binary);

	if (out.fail()) {
		printf("Cannot open file plane data\n");
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
		printf("Cannot open file plane data\n");
		return;
	}

	Plane plane;
	while (inp.read(reinterpret_cast<char*>(&plane), sizeof(Plane))) {
		addPlane(planeList, plane);
	}
	inp.close();

}



void deletePlaneList(PlaneList& planeList) {
	for (int i = 0; i < planeList.size; i++)
		delete planeList.data[i];

}

#endif

