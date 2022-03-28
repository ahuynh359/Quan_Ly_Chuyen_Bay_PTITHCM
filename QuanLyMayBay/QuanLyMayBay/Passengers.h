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
};


struct NodePass {
	Passenger data;
	//2. pointer
	NodePass* pleft;
	NodePass* pright;
	int height;    // chieu cao cua cay
};

typedef struct NodePass* AVLTree;

struct PassengerList {
	AVLTree list = NULL;   // mot cay ds mac dinh la null, co the viet: NodePass *list = NULL;
	int size = 0;

};


// TIM GIA TRI LON NHAT GIUA a & b
int findMax(int a, int b) {
	if (a > b)
		return a;
	return b;

}


// TIM CHIEU CAO CUA CAY
int findHeight(AVLTree root) {
	if (root == NULL)
		return 0;
	return root->height;

}


// TAO CAY
AVLTree createTree(Passenger data) {
	AVLTree newPass = new NodePass;
	newPass->data = data;
	newPass->pleft = NULL;
	newPass->pright = NULL;
	newPass->height = 1;
	return newPass;

}


// XOAY PHAI
AVLTree rotateRight(AVLTree y) {
	AVLTree x = y->pleft;
	AVLTree T2 = x->pright;

	// Thuc hien xoay
	x->pright = y;
	x->pleft = T2;

	// Cap nhat chieu cao
	y->height = findMax(height(y->pleft), height(y->pright)) + 1;
	x->height = findMax(height(x->pleft), height(x->pright)) + 1;

	// Tra ve node moi
	return x;
}


// XOAY TRAI
AVLTree rotateLeft(AVLTree x) {
	AVLTree y = x->pright;
	AVLTree T2 = y->pleft;

	// Thuc hien xoay
	y->pleft = x;
	x->pright = T2;

	// Cap nhat chieu cao
	y->height = findMax(height(y->pleft), height(y->pright)) + 1;
	x->height = findMax(height(x->pleft), height(x->pright)) + 1;

	// Tra ve node moi
	return x;
}


// LAY HE SO CAN BANG
int getBalanceFactor(AVLTree root) {
	if (root == NULL)
		return 0;
	return height(root->pleft) - height(root->pright);

}

/*
// CAP NHAT HE SO CAN BANG
AVLTree updateBalanceFactor(AVLTree root, Passenger data) {
	// Cap nhat lai chieu cao cho cay
	root->height = 1 + findMax(height(root->pleft), height(root->pright);

	// Cap nhat lai he so can bang
	int balance = getBalanceFactor(root);

	// Neu cay mat can bang -> Co 4 truong hop
	// 1. Trai - Trai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
		return rotateRight(root);

	//2. Phai - Phai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
		return rotateLeft(root);

	//3. Trai - Phai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
	{
		root->pleft = rotateLeft(root->pleft);
		return rotateRight(root);
	}

	//4. Phai - Trai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
	{
		root->pright = rotateRight(root->pleft);
		return rotateLeft(root);
	}

	return root;
}
*/


// CHEN NUT
AVLTree addPassenger(AVLTree& root, Passenger data) {
	// Tim vi tri thich hop de them nut
	if (root == NULL)
		return createTree(data);
	if (data.idPass < root->data.idPass)
		root->pleft = addPassenger(root->pleft, data);
	else if (data.idPass > root->data.idPass)
		root->pright = addPassenger(root->pright, data);
	else return root;

	/*updateBalanceFactor(root, data);*/

	// Cap nhat lai chieu cao cho cay
	root->height = 1 + findMax(height(root->pleft), height(root->pright);

	// Cap nhat lai he so can bang
	int balance = getBalanceFactor(root);
	
	// Neu cay mat can bang -> Co 4 truong hop
	// 1. Trai - Trai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
		return rotateRight(root);

	//2. Phai - Phai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
		return rotateLeft(root);

	//3. Trai - Phai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
	{
		root->pleft = rotateLeft(root->pleft);
		return rotateRight(root);
	}

	//4. Phai - Trai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
	{
		root->pright = rotateRight(root->pleft);
		return rotateLeft(root);
	}

	return root;

}


// TRA VE GIA TRI BEN TRAI THAP NHAT
AVLTree findMinValue(AVLTree root) {
	AVLTree current = root;
	while (current->pleft != NULL)
		current = current->pleft;
	return current;

}


// XOA NUT THEO CMND
AVLTree deletePassenger(AVLTree& root, Passenger data) {

	// Tim vi tri ung voi nut can xoa
	if (root == NULL)
		return root;
	if (data.idPass < root->data.idPass)
		root->pleft = deletePassenger(root->pleft, data);
	else if (data.idPass > root->data.idPass)
		root->pright = deletePassenger(root->pright, data);
	// Tim ra CMND bang CMND trong cay AVL -> la nut can xoa
	else
	{
		// TH1: Co 1 cay con hoac 0 cay con
		if (root->pleft == NULL || root->pleft == NULL)
		{
			AVLTree temp = root->pleft ? root->pleft : root->pright;
			// TH 1a: Khong co nhanh con
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}

			// TH 1b: Co 1 nhanh con Trai/Phai
			else
			{
				*root = *temp;   // Truyen dia chi cua *temp cho *root
				free(temp);      // Giai phong vung nho temp vi khong dung toi nua
			}
		}

		// TH2: Co 2 nhanh con
		else
		{
			/*Node thay the la node trai nho nhat cua nhanh ben PHAI*/
			/*Vi no lon hon tat ca node ben o nhanh ben trai va nho hon tat
			ca node o nhanh ben phai*/
			AVLTree temp = findMinValue(root->pright);

			/* Tim duoc thi chep noi dung cua node thay the vao vi tri node can xoa*/
			root->data = temp->data;

			/* Xoa node thay the o vi tri cu */
			root->pright = deletePassenger(root->pright, temp->data);

		}
	}
	if (root == NULL)
		return root;


	// Cap nhat lai chieu cao cho cay
	root->height = 1 + findMax(height(root->pleft), height(root->pright));

	// Cap nhat lai he so can bang
	int balance = getBalanceFactor(root);

	// Neu cay mat can bang -> Co 4 truong hop
	// 1. Trai - Trai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
		return rotateRight(root);

	//2. Phai - Phai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
		return rotateLeft(root);

	//3. Trai - Phai
	if (balance > 1 && data.idPass > root->pleft->data.idPass)
	{
		root->pleft = rotateLeft(root->pleft);
		return rotateRight(root);
	}

	//4. Phai - Trai
	if (balance < -1 && data.idPass > root->pright->data.idPass)
	{
		root->pright = rotateRight(root->pleft);
		return rotateLeft(root);
	}

	return root;
}

