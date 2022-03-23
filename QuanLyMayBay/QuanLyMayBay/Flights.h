#pragma
#include<iostream>

struct Flights {

};
struct node
{
	Flights info;
	struct node* next;
};
typedef node* PTR;

void Initialize(PTR& First)
{
	First = NULL;
}

PTR NewNode(void)
{
	PTR p = new node;
	return p;
}

void InsertFirst(PTR& First, Flights x)
{
	PTR p;
	p = new node;
	p->info = x;
	p->next = First;
	First = p;
}

void InsertAfter(PTR p, Flights x)
{
	PTR q;
	if (p == NULL)
		printf("Khong them chuyen bay vao danh sach duoc.");
	else
	{
		q = new node;
		q->info = x;
		q->next = p->next;
		p->next = q;
	}
}

PTR SearchInfo(PTR First, Flights x)
{
	PTR p;
	for (p = First; p != NULL; p = p->next)
		if (p->info == x) return p;
	return NULL;
}

int Empty(PTR First)
{
	return(First == NULL ? 1 : 0);
}

void DeleteFirst(PTR& First)
{
	PTR p;
	if (Empty(First))
		printf("Khong co chuyen bay trong danh sach");
	p = First;
	First = p->next;
	delete p;
}

void  DeleteAfter(PTR p)
{
	PTR q;
	if ((p == NULL) || (p->next == NULL))
		printf("Khong xoa chuyen bay nay duoc");
	q = p->next;
	p->next = q->next;
	delete q;
}

//incomplete
int DeleteInfo(PTR& First, Flights x)
{
	PTR p = First;
	if (First == NULL) return 0;
	if (First->info == x) {
		DeleteFirst(First); return 1;
	}

	for (p = First; p->next != NULL && p->next->info != x; p = p->next);
	if (p->next != NULL) {
		DeleteAfter(p);  return 1;
	}
	return 0;
}

void DeleteAllInfo(PTR& First, Flights x)
{
	PTR q, p = First;
	if (First == NULL) { return 0; }
	while (p->next != NULL)
	{
		if (p->next->info == x)
		{
			q = p->next;
			p->next = q->next;
			delete q;
		}
		else p = p->next;
	}
	if (First->info == x) {
		p = First;
		First = First->next;
		delete p;
	}
}

void ClearList(PTR& First)
{
	PTR p;
	while (First != NULL)
	{
		p = First;
		First = First->next;
		delete p;
	}
}

void Traverse(PTR First)
{
	PTR p;
	int stt = 0;
	p = First;
	if (p == NULL)
		printf("\nKhong co chuyen bay trong danh sach");
	while (p != NULL)
	{
		printf("\n %5d %8d %-50s %-10s", ++stt, p->info);
		p = p->next;
	}
}

void SelectionSort(PTR& First)
{
	PTR p, q, pmin;
	Flights min;

	for (p = First; p->next != NULL; p = p->next)
	{
		min = p->info;
		pmin = p;
		for (q = p->next; q != NULL; q = q->next)
			if (q->info < min)
			{
				min = q->info;
				pmin = q;
			}
		// hoan doi truong info cua hai nut p va pmin

		pmin->info = p->info;
		p->info = min;
	}
}

void Insert_Order(PTR& First, Flights x)
{
	PTR p, t, s;  // t la nut truoc, s la nut sau
	p = new node;
	p->info = x;
	for (s = First; s != NULL && s->info < x; t = s, s = s->next);
	if (s == First)  // them nut vao dau danh sach lien ket
	{
		p->next = First;
		First = p;
	}
	else           // them nut p vao truoc nut s
	{
		p->next = s;
		t->next = p;
	}
}

void InsertOrder(PTR& First, Flights x)
{
	PTR q, p;  // q la nut truoc, p la nut sau
	q = NULL;
	for (p = First; p != NULL && p->info < x; p = p->next)
		q = p;
	if (q == NULL)  // them nut vao dau danh sach lien ket
		InsertFirst(First, x);
	else           // them nut vao sau nut q
		InsertAfter(q, x);
}

PTR Merge_Order(PTR& First1, PTR& First2)
{
	PTR p1, p2, p3;
	PTR First3 = new node; // tạo vùng nhớ tạm 
	p1 = First1; p2 = First2; p3 = First3;
	while (p1 != NULL && p2 != NULL)
		if (p1->info < p2->info)
		{
			p3->next = p1;      p3 = p1;      p1 = p1->next;
		}
		else
		{
			p3->next = p2;      p3 = p2;      p2 = p2->next;
		}

	if (p1 == NULL)      p3->next = p2;
	else p3->next = p1;

	p3 = First3;    First3 = p3->next;    delete p3; // xóa 
	First1 = First2 = NULL;
	return First3;
}



