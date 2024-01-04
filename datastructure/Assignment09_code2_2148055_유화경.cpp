#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left;
	struct TreeNode* right;
}TreeNode;

typedef struct TreeType {
	TreeNode* root;
}TreeType;

void init(TreeType* bt) {
	bt->root = NULL;
}


TreeNode* create_node(int key) {
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	node->key = key;
	node->left = node->right = NULL;
	return node;
}

void insert_node(TreeType* bt, int key) {
	TreeNode* parent = NULL;
	TreeNode* current = bt->root;

	while (current != NULL) {
		if (key == current->key) {
			return;  // Duplicate key, do nothing
		}
		else {
			parent = current;
			if (key < current->key)
				current = current->left;
			else
				current = current->right;
		}
	}

	TreeNode* new_node = create_node(key);

	if (parent != NULL) {
		if (key < parent->key)
			parent->left = new_node;
		else
			parent->right = new_node;
	}
	else {
		bt->root = new_node;
	}
}

void inorder_traversal(TreeNode* node) {
	if (node != NULL) {
		inorder_traversal(node->left);
		printf("%d ", node->key);
		inorder_traversal(node->right);
	}
}

int main() {
	int input_size = 1000;
	int data_maxval = 10000;

	// output: sorted result
	int* input = (int*)malloc(sizeof(int) * input_size);

	TreeType* bt = (TreeType*)malloc(sizeof(TreeType));
	init(bt);

	// Generate an input data randomly
	for (int i = 0; i < input_size; i++) {
		input[i] = rand() % data_maxval;
		insert_node(bt, input[i]);
	}

	printf("Sorted result: ");
	inorder_traversal(bt->root);
	printf("\n");
}


