#include <stdio.h>
#include <stdlib.h>
#include <limits.h> 

#include "binaryTree.h"

Node* treeQueue[MAX_NUMS];
size_t queue_frontIndex = 0;
size_t queue_backIndex = 0;
size_t queue_numCount = 0;

void enqueue(Node* p_Node)
{
	treeQueue[queue_backIndex] = p_Node;
	queue_backIndex = (queue_backIndex + 1) % MAX_NUMS;
	++queue_numCount;
}
Node* dequeue(void)
{
	Node* p_Node;
	p_Node = treeQueue[queue_frontIndex];
	--queue_numCount;
	queue_frontIndex = (queue_frontIndex + 1) % MAX_NUMS;
	return p_Node;
}

int isEmpty(void)
{
	return (queue_numCount == 0);
}

void checkIsData_And_resetQueue(void)
{
	while (queue_numCount != 0)
	{
		dequeue();
	}
	queue_frontIndex = 0;
	queue_backIndex = 0;
}

void InsertTree(Node* root, const int paramValue) 
{
	Node* p_newNode = (Node*)malloc(sizeof(Node));

	if (p_newNode != NULL)
	{
		p_newNode->p_left = NULL;
		p_newNode->p_right = NULL;
		p_newNode->p_parent = NULL;
		p_newNode->value = paramValue;

		Node** pp_currentNode = &root;
		while (*pp_currentNode)
		{
			if (p_newNode->value < (*pp_currentNode)->value) {
				p_newNode->p_parent = *pp_currentNode;
				pp_currentNode = &((*pp_currentNode)->p_left);
			}
			else {
				p_newNode->p_parent = *pp_currentNode;
				pp_currentNode = &((*pp_currentNode)->p_right);
			}
		}
		*pp_currentNode = p_newNode;
		p_newNode->p_left = p_newNode->p_right = NULL;
	}
}

void traverseAllTree(Node* root) 
{
	Node** pp_currentNode = &root;

	enqueue(*pp_currentNode);

	while (*pp_currentNode = dequeue())
	{
		if ((*pp_currentNode)->p_left != NULL)
		{
			enqueue(((*pp_currentNode)->p_left));
		}
		if ((*pp_currentNode)->p_right != NULL)
		{
			enqueue(((*pp_currentNode)->p_right));
		}

		printf("Tree value : %d Tree pointer : %p\n",
			(*pp_currentNode)->value, *pp_currentNode);

		if (isEmpty() == TRUE) {
			break;
		};
	}

	checkIsData_And_resetQueue();
}

void DeleteAllTree(Node* root)
{
	Node* p_currentNode = root;
	enqueue(p_currentNode);

	while (p_currentNode = dequeue())
	{
		if ((p_currentNode)->p_left != NULL)
		{
			enqueue(((p_currentNode)->p_left));
			p_currentNode->p_left = NULL;
			free(p_currentNode->p_left);
		}
		if ((p_currentNode)->p_right != NULL)
		{
			enqueue(((p_currentNode)->p_right));
			p_currentNode->p_right = NULL;
			free(p_currentNode->p_right);
		}
		//p_currentNode -> value = NULL_INT;
	}

	checkIsData_And_resetQueue();
}

void DeleteTree(Node* root, const int paramValue)
{
	Node* p_currentNode = root;
	Node* p_parentNode;

	enqueue(p_currentNode);
	while (p_currentNode = dequeue())
	{
		if (p_currentNode->value != paramValue)
		{
			goto ENQUEUE_AFTER_CHECK_CURRENT_TREE_LEFT_OR_LIGHT_NOT_NULL;
		}
		else
		{
			checkIsData_And_resetQueue();

			int targetNum = paramValue;

			enqueue(p_currentNode);
			while (p_currentNode = dequeue())
			{
				p_parentNode = p_currentNode->p_parent;

				//Node to be deleted is leaf
				if (p_currentNode->p_left == NULL && p_currentNode->p_right == NULL)
				{
					if (p_parentNode->p_left == p_currentNode)
					{
						p_parentNode->p_left = NULL;
					}
					else
					{
						p_parentNode->p_right = NULL;
					}
					printf("Node to be deleted is leaf \n");
					free(p_currentNode);
					goto FINISH;
				}
				// Node to be deleted has two child
				else if (p_currentNode->p_left != NULL && p_currentNode->p_right != NULL)
				{
					goto NODE_TO_BE_DELETED_HAS_TWO_CHILD;
				}
				// Node to be deleted has only one child
				else
				{
					if (p_currentNode->p_left != NULL && p_currentNode->p_right == NULL)
					{
						if (p_parentNode->p_left == p_currentNode)
						{
							p_parentNode->p_left = p_currentNode->p_left;
						}
						else
						{
							p_parentNode->p_right = p_currentNode->p_left;
						}
					}
					else
					{
						if (p_parentNode->p_left == p_currentNode)
						{
							p_parentNode->p_left = p_currentNode->p_right;
						}
						else
						{
							p_parentNode->p_right = p_currentNode->p_right;
						}
					}
					printf("Node to be deleted has only one child \n");
					free(p_currentNode);
					goto FINISH;
				}
			}
		}

	NODE_TO_BE_DELETED_HAS_TWO_CHILD:
		{
			Node* p_tempNode = p_currentNode->p_right;
			Node* p_replacedNode = p_tempNode;
			p_parentNode = p_currentNode->p_parent;
			int currentValue = p_currentNode->value;
			int minValue = p_tempNode->value;

			enqueue(p_tempNode);
			while (p_tempNode = dequeue())
			{
				if (p_tempNode -> value < minValue)
				{
					minValue = p_tempNode -> value;
					p_replacedNode = p_tempNode;
				}
				if (p_tempNode -> p_left != NULL)
				{
					enqueue(p_tempNode -> p_left);
				}
				if (p_tempNode -> p_right != NULL)
				{
					enqueue(p_tempNode -> p_right);
				}
				if (isEmpty() == TRUE)
				{
					if (p_currentNode -> p_right == p_replacedNode)
					{
						p_tempNode = p_currentNode -> p_left;
						if (p_parentNode -> p_left == p_currentNode)
						{
							p_currentNode = p_replacedNode;
							p_parentNode -> p_left = p_currentNode;
						}
						else
						{
							p_currentNode = p_replacedNode;
							p_parentNode -> p_right = p_currentNode;
						}
						p_currentNode -> p_parent = p_parentNode;
						p_currentNode -> p_left = p_tempNode;

						printf("Right Node to be deleted has two child \n");
						free(p_currentNode->p_right);
					}
					else
					{
						p_tempNode = p_replacedNode->p_parent;
						p_currentNode->value = p_replacedNode->value;
						if (p_replacedNode->p_left == NULL && p_replacedNode->p_right == NULL)
						{
							p_tempNode->p_left = p_replacedNode = NULL;
						}
						else
						{
							p_tempNode->p_left = p_replacedNode->p_right;
						}
						printf("Left Node to be deleted has two child \n");
						free(p_replacedNode);
					}
					printf("Node to be deleted has two child \n");

					goto FINISH;
				};
			}
		}

	ENQUEUE_AFTER_CHECK_CURRENT_TREE_LEFT_OR_LIGHT_NOT_NULL:
		{
			if (p_currentNode->p_left != NULL)
			{
				enqueue(p_currentNode->p_left);
			}
			if (p_currentNode->p_right != NULL)
			{
				enqueue(p_currentNode->p_right);
			}
		}

	}

	FINISH:
	{
		checkIsData_And_resetQueue();
	}

	return;
}