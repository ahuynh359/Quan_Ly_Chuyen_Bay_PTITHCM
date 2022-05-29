
#include<fstream>
#include<iostream>

#ifndef PASS_H
#define PASS_H


struct Passenger {
	char lastName[MAX_LAST_NAME + 1];
	char firstName[MAX_FIRST_NAME + 1];

	/*
	* 0 NAM
	* 1 NU
	*/
	bool gender;
	char idPass[MAX_ID_PASS + 1];
};

struct NodePass {
	Passenger data;
	NodePass* pleft;
	NodePass* pright;
	int height;
};

typedef struct NodePass* AVLTree;

void createPassengerList(AVLTree& root) {
	root = NULL;
}


AVLTree createTree(Passenger& data) {
	AVLTree newPass = new NodePass;
	newPass->data = data;
	newPass->pleft = NULL;
	newPass->pright = NULL;
	newPass->height = 1;
	return newPass;

}

bool checkIDPassenger(char s[MAX_ID_PASS]) {
	if (strlen(s) == 12)
		return true;
	return false;
}



int findHeight(AVLTree& root) {
	if (root == NULL)
		return 0;
	return root->height;

}

// XOAY PHAI
AVLTree rotateRight(AVLTree& root) {
	AVLTree x = root->pleft;
	AVLTree y = x->pright;

	x->pright = root;
	root->pleft = y;

	root->height = max(findHeight(root->pleft), findHeight(root->pright)) + 1;
	x->height = max(findHeight(x->pleft), findHeight(x->pright)) + 1;

	return x;
}

// XOAY TRAI
AVLTree rotateLeft(AVLTree& root) {
	AVLTree x = root->pright;
	AVLTree y = x->pleft;

	x->pleft = root;
	root->pright = y;

	root->height = max(findHeight(root->pleft), findHeight(root->pright)) + 1;
	x->height = max(findHeight(x->pleft), findHeight(x->pright)) + 1;

	return x;

}



int getBalanceFactor(AVLTree& root) {
	if (root == NULL)
		return 0;
	return findHeight(root->pleft) - findHeight(root->pright);

}

void removeAll(AVLTree& t) {
	if (t != NULL) {
		removeAll(t->pleft);
		removeAll(t->pright);
		delete t;
	}
}



AVLTree findPassenger(AVLTree& root, char foundID[MAX_ID_PASS + 1]) {
	if (root != NULL) {
		if (strcmp(root->data.idPass, foundID) == 0)
			return root;

		else if (strcmp(foundID, root->data.idPass) > 0)
			return findPassenger(root->pright, foundID);

		else if (strcmp(foundID, root->data.idPass) < 0)
			return findPassenger(root->pleft, foundID);
	}
	return NULL;
}

void adjustPassenger(Passenger& p, AVLTree& temp) {
	temp->data = p;
}



AVLTree addPassenger(AVLTree& root, Passenger& data) {
	// Tim vi tri thich hop de them nut

	if (root == NULL) {
		return createTree(data);
	}


	if (strcmp(data.idPass, root->data.idPass) < 0)
		root->pleft = addPassenger(root->pleft, data);
	else if (strcmp(data.idPass, root->data.idPass) > 0)
		root->pright = addPassenger(root->pright, data);
	else
		return root;

	// Cap nhat lai chieu cao cho cay
	root->height = max(findHeight(root->pleft), findHeight(root->pright)) + 1;

	// Cap nhat lai he so can bang
	int balance = getBalanceFactor(root);

	// Neu cay mat can bang -> Co 4 truong hop
	// 1. Trai - Trai
	if (balance > 1 && strcmp(data.idPass, root->pleft->data.idPass) < 0)
		return rotateRight(root);

	//2. Phai - Phai
	if (balance < -1 && strcmp(data.idPass, root->pright->data.idPass) > 0)
		return rotateLeft(root);

	//3. Trai - Phai
	if (balance > 1 && strcmp(data.idPass, root->pleft->data.idPass) > 0) {
		root->pleft = rotateLeft(root->pleft);
		return rotateRight(root);
	}

	//4. Phai - Trai
	if (balance < -1 && strcmp(data.idPass, root->pright->data.idPass) < 0) {
		root->pright = rotateRight(root->pright);
		return rotateLeft(root);
	}

	return root;
}




void savePassengerData(AVLTree& passengerList, ofstream& out) {
	if (passengerList != NULL) {
		out.write(reinterpret_cast<char*>(&passengerList->data), sizeof(Passenger));
		savePassengerData(passengerList->pleft, out);
		savePassengerData(passengerList->pright, out);
	}
	
}

void writeFilePassenger(AVLTree& passengerList) {
	ofstream out("PassData.txt", ios::binary);


	if (out.fail()) {
		printf("Passenger Data File cannot be opened!");
		return;
	}

	savePassengerData(passengerList, out);


	out.close();
}


void readFilePassenger(AVLTree& passengerList) {
	Passenger passenger;
	ifstream inp("PassData.txt", ios::binary);

	if (inp.fail()) {
		printf("Passenger Data File cannot be opened!");
		return;

	}
	while (inp.read(reinterpret_cast<char*>(&passenger), sizeof(Passenger))) {
		passengerList = addPassenger(passengerList, passenger);
	}

	inp.close();

}

#endif