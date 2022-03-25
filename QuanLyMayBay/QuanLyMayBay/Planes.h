#pragma once;
#define MAX_ID 15
#define MAX_PLANE 300
#define MAX_TYPE 40

struct Plane {
	char idPlane[MAX_ID];
	char type[MAX_TYPE];
	int seats;
};
class PlaneList {
private:
	Plane* data[MAX_PLANE];

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

	}

	void editPlane() {

	}
};