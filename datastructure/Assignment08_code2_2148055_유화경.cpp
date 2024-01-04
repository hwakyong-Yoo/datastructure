
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAX_ELEMENT 100
#define KEYS 10

#define MAX_VERTICES 8
#define INF 1000L

#define SWAP(x,y) { int t; t = x; x = y; y = t;}

int weight[MAX_VERTICES][MAX_VERTICES] =
{ { 0,3,INF,INF,INF,INF,INF,14 },
{ 3,0,8,INF,INF,INF,INF,10 },
{ INF,8,0,15,2,INF,INF,INF },
{ INF,INF,15,0,INF,INF,INF,INF },
{ INF,INF,2,INF,0,9,4,5 },
{ INF,INF,INF,INF,9,0,INF,INF },
{ INF,INF,INF,INF,4,INF,0,6 },
{ 14,10,INF,INF,5,INF,6,0 } };


int selected[MAX_VERTICES]; 
int dist[MAX_VERTICES + 1];



typedef struct element {
	int key; //dist
	int vertex; //index
}element;

typedef struct HeapType {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

typedef struct TreeNode {
	element node; 
	struct TreeNode* parent;
	struct TreeNode* child[MAX_VERTICES];
}TreeNode;

typedef struct TreeType {
	TreeNode* root;
}TreeType;

TreeType* t = (TreeType*)malloc(sizeof(TreeType));

void init(HeapType* h)
{
	h->heap_size = 0;
}

void t_init(TreeType* t) {
	t->root = NULL;
}

int is_empty(HeapType* h)
{
	if (h->heap_size == 0)
		return true;
	else
		return false;
}

void insert_min_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	// compare it with the parent node in an order from the leaf to the root
	while ((i != 1) && (item.vertex < h->heap[i / 2].vertex)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item; // Insert new node
}

void build_min_heap(HeapType* h, int dist[], int n) { 
	for (int i = 0; i < n; i++) {
		element item;
		item.key = dist[i];
		item.vertex = i;
		h->heap[i + 1] = item;
		insert_min_heap(h, item);
	}
	printf("\n");
}

bool heap_search(HeapType* h, int n) {
	for (int i = 1; i <= h->heap_size; i++) {
		if (h->heap[i].vertex == n)
			return true;
	}
	return false;
}

element delete_min_heap(HeapType* h)
{
	element item = h->heap[1];
	element temp = h->heap[(h->heap_size)--];
	int parent = 1;
	int child = 2;
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].vertex) > h->heap[child + 1].vertex)
			child++;
		if (temp.vertex <= h->heap[child].vertex) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int compare(int i, element A[]) {
	if (A[i * 2].key < A[i * 2 + 1].key) return i * 2;
	else return i * 2 + 1;
}

void decrease_key_min_heap(element A[], int i, int key) {
	if (key >= A[i].key) {
		//printf("error: new key is not smaller than current key");
		return;
	}
	A[i].key = key;
	while ((i > 1) && (A[i / 2].key > A[i].key)) {
		SWAP(A[i].key, A[i / 2].key);
		SWAP(A[i].vertex, A[i / 2].vertex);
		i /= 2;
	}
}


int next_child(TreeNode* node, int idx) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		if (node->child[i] == NULL || node->child[i]->node.vertex == idx)
			return i;
	}
	return 0;
}

void setchild_init(TreeNode* n) {
	for (int i = 0; i < MAX_VERTICES; i++) {
		n->child[i] = NULL;
	}
}

void insert_node(TreeNode* now_node, element child_node, TreeType* h) {
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;

	n->node.key = child_node.key;
	n->node.vertex = child_node.vertex;
	setchild_init(n);

	if (now_node->node.vertex == 0) {
		now_node->parent = NULL;
		h->root = now_node;
	}
	n->parent = now_node;
	int idx = next_child(now_node, n->node.vertex);
	now_node->child[idx] = n;

}

TreeNode* find_indexNode(TreeNode* node, int idx, TreeType* th) {
	
	if (node != NULL) {
		if (node->node.vertex == idx)
			return node;
		else {
			for (int i = 0; i < MAX_VERTICES; i++) {
				find_indexNode(node->child[i], idx, th);
			}
			return th->root;
		}
	}
	return NULL;
}

void prim(int s, int n) {
	int count = 0;
	for (int u = 0; u <= n; u++) {
		dist[u] = INF;
	}
	dist[s] = 0;

	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	init(h);

	build_min_heap(h, dist, n);

	for (int i = 0; i < n; i++) {
		element p = delete_min_heap(h);
		int cost = p.key;
		int here = p.vertex;
		if (dist[here] == INF) return;
		for (int v = 0; v < n; v++) {
			if (weight[here][v] != INF) {
				if (dist[v] > weight[here][v] && i != v && heap_search(h, v)) {
					dist[v] = weight[here][v];

					TreeNode* preNode;
					if (!count) {
						preNode = (TreeNode*)malloc(sizeof(TreeNode));
						preNode->node = p;
						setchild_init(preNode);
					}
					else {
						preNode = find_indexNode(t->root, p.vertex, t);
					}
					count++;

					element next;
					next.key = dist[v];
					next.vertex = v;

					insert_node(preNode, next, t);
				}
			}
		}

		for (int i = 0; i < MAX_VERTICES; i++) {
			printf("%d ", dist[i]);
		}
		printf("\n");
	}
}


void print_prim(TreeNode* node) {
	if (node != NULL) {
		for (int i = 0; i < MAX_VERTICES; i++) {
			if (node->child[i] != NULL) {
				printf("Vertex %d -> %d            edge: %d\n", node->node.vertex, node->child[i]->node.vertex, node->child[i]->node.key);
			}
		}
		for (int i = 0; i < MAX_VERTICES; i++) {
			print_prim(node->child[i]);
		}
	}
}


int main()
{
	t_init(t);
	prim(0, MAX_VERTICES);
	print_prim(t->root);
	return 0;
}

