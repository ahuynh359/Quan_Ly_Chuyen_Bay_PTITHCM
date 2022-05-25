
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

AVLTree rotateRight(AVLTree& y) {
    AVLTree x = y->pleft;
    AVLTree T2 = x->pright;

    // Thuc hien xoay
    x->pright = y;
    y->pleft = T2;

    // Cap nhat chieu cao
    y->height = max(findHeight(y->pleft), findHeight(y->pright)) + 1;
    x->height = max(findHeight(x->pleft), findHeight(x->pright)) + 1;


    return x;
}



AVLTree rotateLeft(AVLTree& x) {
    AVLTree y = x->pright;
    AVLTree T2 = y->pleft;

    // Thuc hien xoay
    y->pleft = x;
    x->pright = T2;

    // Cap nhat chieu cao
    x->height = max(findHeight(x->pleft), findHeight(x->pright)) + 1;
    y->height = max(findHeight(y->pleft), findHeight(y->pright)) + 1;


  
    return y;
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

void adjustPassenger(Passenger &p,AVLTree &temp) {
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

AVLTree findMin(AVLTree &root)
{
    AVLTree current = root;
    if (current->pleft != NULL)
    {
        current = current->pleft;
    }
    return current;
}

AVLTree deletePassenger(AVLTree& root, Passenger& data)
{
    // B1 tim vi tri ung voi cai node can xoa
    if (root == NULL)
    {
        return root;
    }

    if (strcmp(data.idPass , root->data.idPass) < 0)
    {
        root->pleft = deletePassenger(root->pleft, data);
    }
    else if (strcmp(data.idPass, root->data.idPass) > 0)
    {
        root->pright = deletePassenger(root->pright, data);
    }
    // neu da tim ra CMND bang dung CMND co trong cay AVL,thi no la node can xoa
    else
    {
        // TH1: ID co 1 cay con hoac khong co cay con nao
        if ((root->pleft == NULL) || (root->pright == NULL))
        {
            AVLTree tempo = root->pleft ? root->pleft : root->pright;

            // TH khong co nhanh con
            if (tempo == NULL)
            {
                tempo = root;
                root = NULL;
            }
            // TH co 1 nhanh con TRAI hoac PHAI
            else
            {
                *root = *tempo;/*TRUYEN DIA CHI CUA *TEMPO cho *ROOT*/
                free(tempo);/*GIAI PHONG VUNG NHO TEMPO DO khong dung toi nua*/
            }
        }
        // TH2 :node can xoa co 2 nhanh con
        else
        {
            /*Node thay the la node trai nhat cua nhanh ben PHAI*/
            /*Vi no lon hon tat ca node ben o nhanh ben trai va nho hon tat
            ca node o nhanh ben phai*/
            AVLTree tempo = findMin(root->pright);
            /*tim duoc thi chep noi dung cua node thay the vao vi tri node can
            xoa*/
            root->data = tempo->data;
            /*xoa node thay the o vi tri cu di*/
            root->pright = deletePassenger(root->pright, tempo->data);
        }
        // B2: cap nhat do cao cua node
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
    }
}


void savePassengerData(AVLTree& passengerList, ofstream& out) {
    if (passengerList == NULL) {
        return;
    }
    out.write(reinterpret_cast<char*>(&passengerList->data), sizeof(Passenger));
    savePassengerData(passengerList->pleft, out);
    savePassengerData(passengerList->pright, out);
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