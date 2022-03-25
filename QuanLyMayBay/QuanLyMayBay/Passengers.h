#pragma once;
#include <iostream>
using namespace std;


struct Passenger {
	//1. data
	char lastName[10];
	char firstName[50];
	int sex; 
	/*
	* 0 NAM
	* 1 NU
	*/
	char idPass[15];

	//2. pointer
	Passenger* pleft;
	Passenger* pright;

};

typedef struct Passenger* tree;

struct PassengerList {
	tree list = NULL;   // mot cay ds mac dinh la null, co the viet: Passenger *list = NULL;
	int size = 0;

};

