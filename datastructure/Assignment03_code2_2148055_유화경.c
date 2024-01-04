#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void init(ListNode **phead) {
	*phead = NULL;
}

void insert_last(ListNode** phead, element data) {
	ListNode* new_node = (ListNode*)malloc(sizeof(ListNode));

	new_node->link = NULL;
	new_node->data = data;
	if (*phead == NULL) {
		*phead = new_node;
	}
	else {
		struct ListNode* last = *phead;
		while (last->link != NULL) {
			last = last->link;
		}
		last->link = new_node;
	}
}

void display(ListNode* head)
{
	ListNode* p = head;
	while (p != NULL) {
		printf("%d->", p->data);
		p = p->link;
	}
	printf("\n");
}

void make_list_C(ListNode* A, ListNode* B, ListNode** C) {
	while (!(A == NULL) || !(B == NULL)) {
		element input_C;
		if (A == NULL || B == NULL) {
			if (A == NULL) {
				input_C = B->data;
				B = B->link;
			}
			else {
				input_C = A->data;
				A = A->link;
			}
		}
		else {
			if (A->data < B->data) {
				input_C = A->data;
				A = A->link;
			}
			else {
				input_C = B->data;
				B = B->link;
			}
		}
		insert_last(C, input_C);
	}
}

int main() {
	ListNode* A = (ListNode*)malloc(sizeof(ListNode));
	init(&A);

	ListNode* B = (ListNode*)malloc(sizeof(ListNode));
	init(&B);

	ListNode* C = (ListNode*)malloc(sizeof(ListNode));
	init(&C);

	int a[] = { 1,2,5,10,15,20,25 };
	int b[] = { 3,7,8,15,18,30 };

	for (int i = 0; i < sizeof(a) / sizeof(int); i++) {
		insert_last(&A, a[i]);
	}

	for (int i = 0; i < sizeof(b) / sizeof(int); i++) {
		insert_last(&B, b[i]);
	}

	printf("a = ");
	display(A);

	printf("b = ");
	display(B);

	make_list_C(A, B, &C);
	printf("c = ");
	display(C);
}