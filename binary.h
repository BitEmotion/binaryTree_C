#pragma once
#include <stdio.h>
#include <limits.h> 
enum { NULL_INT = INT_MIN, FALSE = 0, TRUE = 1, MAX_NUMS = 8 };

typedef struct TreeNode_t {
	struct TreeNode_t* parent;
	struct TreeNode_t* left;
	int value;
	struct TreeNode_t* right;
} TreeNode_t;

TreeNode_t treeArray[MAX_NUMS];
size_t treeArray_frontIndex = 0;
size_t treeArray_backIndex = 0;
size_t treeArray_numCount = 0;

TreeNode_t* treeQueue[MAX_NUMS];
size_t queue_frontIndex = 0;
size_t queue_backIndex = 0;
size_t queue_numCount = 0;

int isEmpty(void)
{
	return (queue_numCount == 0);
}

void enqueue(TreeNode_t* p_treeNode)
{
	treeQueue[queue_backIndex] = p_treeNode;
	queue_backIndex = (queue_backIndex + 1) % MAX_NUMS;
	++queue_numCount;
}

TreeNode_t* dequeue(void)
{
	TreeNode_t* p_treeNode;
	p_treeNode = treeQueue[queue_frontIndex];
	--queue_numCount;
	queue_frontIndex = (queue_frontIndex + 1) % MAX_NUMS;
	return (p_treeNode);
}

void checkIsDataAndResetQueue(void)
{
	while (queue_numCount != 0)
	{
		dequeue();
	}
	queue_frontIndex = 0;
	queue_backIndex = 0;
}

void InsertTree(TreeNode_t* root, TreeNode_t* newNode) {
	TreeNode_t** pp_currentTree = &root;
	while (*pp_currentTree) {
		if (newNode->value < (*pp_currentTree)->value) {
			newNode->parent = *pp_currentTree;
			pp_currentTree = &((*pp_currentTree)->left);
		}
		else {
			newNode->parent = *pp_currentTree;
			pp_currentTree = &((*pp_currentTree)->right);
		}
	}
	*pp_currentTree = newNode;
	newNode->left = newNode->right = NULL;
}

void traverseAllTree(TreeNode_t* root) {
	TreeNode_t** pp_currentTree = &root;

	enqueue(*pp_currentTree);

	while (*pp_currentTree = dequeue()) {

		if ((*pp_currentTree)->left != NULL)
		{
			enqueue(((*pp_currentTree)->left));
		}
		if ((*pp_currentTree)->right != NULL)
		{
			enqueue(((*pp_currentTree)->right));
		}
		printf("Tree value : %d Tree pointer : %p\n", (*pp_currentTree)->value, *pp_currentTree);
		if (isEmpty() == TRUE) {
			break;
		};
	}

	checkIsDataAndResetQueue();
}

void deleteAllTree(TreeNode_t* root) {
	TreeNode_t* p_currentTree = root;
	enqueue(p_currentTree);

	while (p_currentTree = dequeue())
	{
		if ((p_currentTree)->left != NULL)
		{
			enqueue(((p_currentTree)->left));
			p_currentTree->left = NULL;
		}
		if ((p_currentTree)->right != NULL)
		{
			enqueue(((p_currentTree)->right));
			p_currentTree->right = NULL;
		}
		p_currentTree->value = NULL_INT;
	}

	checkIsDataAndResetQueue();
}

void deleteTree(TreeNode_t* root, TreeNode_t* targetTree)
{
	TreeNode_t* p_currentTree = root;
	TreeNode_t* p_targetTree = targetTree;
	TreeNode_t* p_parentTree;
	enqueue(p_currentTree);
	while (p_currentTree = dequeue())
	{
		if (p_currentTree->value != p_targetTree->value)
		{
			goto CHECK_CURRENT_TREE_LEFT_OR_LIGHT_NOT_NULL_ENQUEUE;
		}
		else
		{
			checkIsDataAndResetQueue();

			int targetNum = p_targetTree->value;

			enqueue(p_currentTree);
			while (p_currentTree = dequeue())
			{
				p_parentTree = p_currentTree->parent;

				//Node to be deleted is leaf
				if (p_currentTree->left == NULL && p_currentTree->right == NULL)
				{
					if (p_parentTree->left == p_currentTree)
					{
						p_parentTree->left = NULL;
					}
					else
					{
						p_parentTree->right = NULL;
					}
					goto FINISH;
				}
				// Node to be deleted has two child
				else if (p_currentTree->left != NULL && p_currentTree->right != NULL)
				{
					goto NODE_TO_BE_DELETED_HAS_TWO_CHILD;
				}
				// Node to be deleted has only one child
				else
				{
					if (p_currentTree->left != NULL && p_currentTree->right == NULL)
					{
						if (p_parentTree->left == p_currentTree)
						{
							p_parentTree->left = p_currentTree->left;
						}
						else
						{
							p_parentTree->right = p_currentTree->left;
						}
					}
					else
					{
						if (p_parentTree->left == p_currentTree)
						{
							p_parentTree->left = p_currentTree->right;
						}
						else
						{
							p_parentTree->right = p_currentTree->right;
						}
					}
					goto FINISH;
				}
			}
		}
		NODE_TO_BE_DELETED_HAS_TWO_CHILD:
		{
			TreeNode_t* p_tempTree = p_currentTree->right;
			TreeNode_t* p_replacedTree = p_tempTree;
			p_parentTree = p_currentTree->parent;
			int currentValue = p_currentTree->value;
			int minValue = p_tempTree->value;

			enqueue(p_tempTree);
			while (p_tempTree = dequeue())
			{
				if (p_tempTree->value < minValue)
				{
					minValue = p_tempTree->value;
					p_replacedTree = p_tempTree;
				}
				if (p_tempTree->left != NULL)
				{
					enqueue(p_tempTree->left);
				}
				if (p_tempTree->right != NULL)
				{
					enqueue(p_tempTree->right);
				}
				if (isEmpty() == TRUE)
				{
					if (p_currentTree->right == p_replacedTree) {
						p_tempTree = p_currentTree->left;
						if (p_parentTree->left == p_currentTree)
						{
							p_currentTree = p_replacedTree;
							p_parentTree->left = p_currentTree;
						}
						else
						{
							p_currentTree = p_replacedTree;
							p_parentTree->right = p_currentTree;
						}
						p_currentTree->parent = p_parentTree;
						p_currentTree->left = p_tempTree;
					}
					else {
						p_tempTree = p_replacedTree->parent;
						p_currentTree->value = p_replacedTree->value;
						if (p_replacedTree->left == NULL && p_replacedTree->right == NULL)
						{
							p_tempTree->left = p_replacedTree = NULL;
						}
						else
						{
							p_tempTree->left = p_replacedTree->right;
						}
					}
					goto FINISH;
				};
			}
		}
		CHECK_CURRENT_TREE_LEFT_OR_LIGHT_NOT_NULL_ENQUEUE:
		{
			if (p_currentTree->left != NULL)
			{
				enqueue(p_currentTree->left);
			}
			if (p_currentTree->right != NULL)
			{
				enqueue(p_currentTree->right);
			}
		}
	}

	FINISH:
	{
		checkIsDataAndResetQueue();

		int offsetFromRoot = 0;
		TreeNode_t* p_tempTree = root;
		while (p_tempTree++ != targetTree)
		{
			offsetFromRoot++;
		}
		treeArray[offsetFromRoot].value = NULL_INT;
		treeArray[offsetFromRoot].left = treeArray[offsetFromRoot].right = NULL;
	}

	return;
}