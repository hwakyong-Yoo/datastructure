#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef int element;

typedef struct StackNode {
	element item;
	struct StackNode* llink;
	struct StackNode* rlink;
} StackeNode;

typedef struct {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s)
{
	s->top = NULL;
}

int is_empty(LinkedStackType* s)
{
	return (s->top == NULL);
}

void push(LinkedStackType* s, element item)
{
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "Memory allocation error\n");
		return;
	}

	temp->item = item;
	if (is_empty(s)) {
		temp->llink = temp;
		temp->rlink = temp;
	}
	else {
		temp->llink = s->top->llink;
		temp->rlink = s->top;
		s->top->llink->rlink = temp;
		s->top->llink = temp;
	}
	s->top = temp;
}

element pop(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		StackNode* temp = s->top;
		int item = temp->item;
		if (s->top == s->top->llink) {
			s->top = NULL;
		}
		else {
			s->top->llink->rlink = s->top->rlink;
			s->top->rlink->llink = s->top->llink;
			s->top = s->top->rlink;
		}

		free(temp);
		return item;

	}
}

element peek(LinkedStackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "Stack is empty\n");
		exit(1);
	}
	else {
		return s->top->item;
	}
}

void main()
{
	LinkedStackType s;
	init(&s);
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);

	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
	printf("%d\n", pop(&s));
}




