#include <stdio.h>
#include <stdlib.h>

#include "binaryTree.h"

int main(void)
{

	int numArray[MAX_NUMS] = { 10,5,3,7,6,9,4,11 };

	Node* p_treeNodePool = (Node*)malloc(sizeof(Node));
	if (p_treeNodePool != NULL)
	{
		p_treeNodePool->p_left = NULL;
		p_treeNodePool->p_right = NULL;
		p_treeNodePool->p_parent = NULL;
		p_treeNodePool->value = numArray[0];
	}

	for (int i = 1; i < MAX_NUMS; i++)
	{
		InsertTree(p_treeNodePool, numArray[i]);
	}

	TraverseAllTree(p_treeNodePool);
	DeleteTree(p_treeNodePool, 9);

	printf("-------------------------- \n");

	TraverseAllTree(p_treeNodePool);

	return 0;
}