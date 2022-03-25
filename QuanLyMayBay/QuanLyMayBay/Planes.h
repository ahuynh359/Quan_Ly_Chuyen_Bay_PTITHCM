#pragma once;
#define MAX_ID 15
#define MAX_PLANE 300
#define MAX_TYPE 40
#include<iostream>
using namespace std;

struct Plane {
	char idPlane[MAX_ID];
	char type[MAX_TYPE];
	int seats;
};

<<<<<<< Updated upstream
public:
	PlaneList() {
		for (int i = 0; i < MAX_PLANE; i++) {
			data[i] = new Plane();
		}
	}

	~PlaneList() {
		for (int i = 0; i < MAX_PLANE; i++) {
			delete data[i];
		}
	}

	void addPlane() {

	}

	void deletePlane() {
=======
struct PlaneList {
	int size = 0;
	Plane* data[MAX_PLANE]; 

};
>>>>>>> Stashed changes

void add(PlaneList &list) {
	Plane* plane = new Plane();
	cout << "Nhap so hieu MB:";
	cin >> plane->idPlane;
	cout << "Nhap loai may bay:";
	cin >> plane->type;
	while (plane->seats < 20) {
		cout << "Nhap so cho:";
		cin >> plane->seats;
	}
	list.data[(++list.size)] = plane;
}


