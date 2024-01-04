
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 100
#define KEYS 10

#define SWAP(x,y) { int t; t = x; x = y; y = t;}

typedef struct element {
	int key;
}element;

typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


void init(HeapType* h)
{
	h->heap_size = 0;
}

int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return true;
	else
		return false;
}

int compare(int i2, int i21, element A[]) {
	if (A[i2].key < A[i21].key) return i2;
	else return i21;
}

void increase_key_min_heap(element A[], int i, int key) {
	if (key <= A[i].key) {
		printf("error: new key is not larger than current key");
		return;
	}
	A[i].key = key;
	int ind = compare(2 * i, 2 * i + 1, A);
	while ((i > 1) && (A[i].key > A[ind].key) && ind <= KEYS) {
		SWAP(A[i].key, A[ind].key);
		i = ind;
		ind = compare(2 * i, 2 * i + 1, A);
	}
}

void decrease_key_min_heap(element A[], int i, int key) {
	if (key >= A[i].key) {
		printf("error: new key is not smaller than current key");
		return;
	}
	A[i].key = key;
	while ((i > 1) && (A[i / 2].key > A[i].key)) {
		SWAP(A[i].key, A[i / 2].key);
		i /= 2;
	}
}

int main()
{
	int keys[] = { 1,4,2,7,5,3,3,7,8,9 };
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	init(h);

	for (int i = 0; i < KEYS; i++) {
		h->heap[i + 1].key = keys[i];
	}
	h->heap_size = KEYS + 1;

	
	decrease_key_min_heap(h->heap, 4, 3);

	for (int i = 1; i < KEYS + 1; i++) {
		printf("%d ", h->heap[i].key);
	}
	printf("\n");

	increase_key_min_heap(h->heap, 3, 10);

	for (int i = 1; i < KEYS + 1; i++) {
		printf("%d ", h->heap[i].key);
	}
	return 0;
}