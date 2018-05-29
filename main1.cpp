#include <iostream>
#include <math.h>
#include <Windows.h>
#include <string>
using namespace std;


struct Node
{
	int Data;
	Node* pNext;
};

struct LIST
{
	Node *pHead, *pTail;
};


struct OHashtable
{
	int m;//số lượng phần tử có trong mảng
	LIST *buckets;
};
void CreateLIST(LIST  &l)
{
	l.pHead = l.pTail = NULL;

}


void createOhashtable(OHashtable &ht, int m)
{
	//Cấp phát bộ nhớ cho buckets
	ht.buckets = new LIST[m];
	
	if (ht.buckets == NULL)
	{
		ht.m = 0;
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			//Từng buckets là một danh sách liên kết đơn.
			CreateLIST(ht.buckets[i]);
		}
		//Cập nhật Bảng Băm có m phần tử
		ht.m = m;
	}

}

Node* CreateNode(int x)
{
	Node * p = new Node;
	if (p == NULL) return NULL;
	if (p)
	{
		p->Data = x;
		p->pNext = NULL;
	}
	return  p;
}

void AddLast(LIST &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}

	if (l.pHead)
	{
		l.pTail = p;
		l.pTail->pNext = NULL;

	}
}

void AddHead(LIST &l, Node *p)
{
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p;
	}

	if (l.pHead)
	{
		p->pNext = l.pHead;
		l.pHead = p;

	}
}

int OHashCode(int key, int m)
{
	return key % m;
}
int OPutKey(OHashtable &ht, int key)
{
	if (ht.m == 0) return 0;

	Node *p = CreateNode(key);
	if (p == NULL) return 0;

	int i = OHashCode(key, ht.m);

	AddLast(ht.buckets[i], p);
	return 1;
}


//Tìm phần tử có khóa Key trong Bảng Băm
Node * Search(LIST &l, int x)
{
	Node *p = l.pHead;
	while (p != NULL && p->Data != x)
	{
		p = p->pNext;

	}
	return p;

}
Node *OGetKey(OHashtable ht, int key)
{
	if (ht.m == 0) return NULL;
	int i = OHashCode(key, ht.m);
	return Search(ht.buckets[i], key);


}

//Xóa phần tử có khóa key trong bảng băm
int Remove(LIST &l, int x)
{
	if (l.pHead == NULL)
		return 0;
	Node * p;
	if (l.pHead->Data == x)
	{
		p = l.pHead;
		l.pHead = p->pNext;
		delete[]p;
	}

	else
	{
		p = l.pHead;
		Node  *q = NULL;
		while (p != NULL && p->Data != x)
		{
			q = p;
			p = p->pNext;
		}

		if (p = l.pTail)
		{
			l.pTail = q;
			l.pTail->pNext = NULL;
			delete[]p;
		}

		q->pNext = p->pNext;
		delete[]p;

	}


}//Trả về 1 khi tìm thấy, 0 khi không tìm thấy
int ORemoveKey(OHashtable ht, int key)
{
	if (ht.m == 0) return 0;
	int i = OHashCode(key, ht.m);
	return Remove(ht.buckets[i], key);
}

void RemoveList(LIST &l)
{
	if (l.pHead == NULL) return;

	Node *p = NULL ;
	while (p != NULL)
	{
		p = l.pHead;
		l.pHead = p->pNext;
		delete[]p;
		
	}
}
void RemoveOHashtable(OHashtable &ht) {
	for (int i = 0; i < ht.m; i++) {
		RemoveList(ht.buckets[i]);
		//ht.buckets[i] = NULL;
	}
	delete[] ht.buckets;
	ht.m = 0;
}

void print(OHashtable ht) {
	int i;
	Node *p;
	if (ht.m == 0) return;
	for (i = 0; i < ht.m; i++) {
		p = ht.buckets[i].pHead;
		while (p != NULL) {
			cout << p->Data << ' ';
			p = p->pNext;
		}
		cout << endl;
	}
}

int GetTableSize(int m) {
	int n = 1, k, i;
	double x;
	while (n < m) n = n * 2;
	n = n + 1;
	k = m;
	do {
		x = sqrt((double)k);
		for (i = 2; i < x; i++)
			if ((k % i) == 0) break;
		if (i < x) k++;
	} while ((x > i) && (k < n));
	return k;
}


void main() 
{
	OHashtable ht;
	int x, n;
	cout << "Nhap kich thuoc bang bam ";
	cin >> n;
	n = GetTableSize(n);
	createOhashtable(ht, n);
	cout << "So luong khoa can nhap ";
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		cin >> x;
		if (!OPutKey(ht, x)) return;
	}
	print(ht);
	cout << "nhap khoa can tim ";
	cin >> x;
	Node * p = OGetKey(ht, x);
	if (p == NULL)
		cout << "khong tim thay" << endl;
	else
		cout << "tim thay " << p->Data << endl;

	system("color e");
	system("pause");


}

