#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DlistNode {
	element data;
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

void init(DlistNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

void display(DlistNode* phead) {
	DlistNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<---|%x| data:%d, address:%x |%x|--->\n", p->llink, p->data, p, p->rlink);
	}
}

void dinsert_node(DlistNode* before, DlistNode* new_node) {
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;
}

void dinsert_first_node(DlistNode* phead, DlistNode* new_node) {
	new_node->rlink = phead->rlink;
	new_node->llink = phead;

	if (phead->rlink != phead) {
		phead->rlink->llink = new_node;
	}

	phead->rlink = new_node;
}

void dinsert_last_node(DlistNode* phead, DlistNode* new_node) {
	new_node->rlink = phead;
	new_node->llink = phead->llink;
	phead->llink->rlink = new_node;
	phead->llink = new_node;
}

int main() {
	DlistNode head_node;
	DlistNode* phead = &head_node;

	DlistNode* p[12];

	init(&head_node);

	for (int i = 0; i < 5; i++) {
		p[i] = (DlistNode*)malloc(sizeof(DlistNode));
		p[i]->data = i;
		dinsert_node(&head_node, p[i]);
	}

	DlistNode* first_node = (DlistNode*)malloc(sizeof(DlistNode));
	first_node->data = 42;
	dinsert_node(phead, first_node);

	DlistNode* last_node = (DlistNode*)malloc(sizeof(DlistNode));
	last_node->data = 42;
	dinsert_node(phead->llink, last_node);

	DlistNode* last_insert = (DlistNode*)malloc(sizeof(DlistNode));
	last_insert->data = 100;
	dinsert_last_node(&head_node, last_insert);

	DlistNode* first_insert = (DlistNode*)malloc(sizeof(DlistNode));
	first_insert->data = 10;
	dinsert_first_node(&head_node, first_insert);

	display(&head_node);
}