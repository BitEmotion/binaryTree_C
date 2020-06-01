#pragma once

enum { NULL_INT = INT_MIN, FALSE = 0, TRUE = 1, MAX_NUMS = 8 };

typedef struct Node {
	struct Node* p_parent;
	struct Node* p_left;
	struct Node* p_right;
	int value;
} Node;

typedef struct TreeNode {
	Node* p_entryNode;
	Node nodeArray[MAX_NUMS];
	size_t frontIndex;
	size_t backIndex;
	size_t numCount;
} TreeNode;


void enqueue(Node* p_Node);
Node* dequeue(void);

int isEmpty(void);

void CheckIsData_And_resetQueue(void);
void InsertTree(Node* root, int paramValue);
void TraverseAllTree(Node* root);
void DeleteAllTree(Node* root);
void DeleteTree(Node* root, int paramValue);
