#include "binary.h"
//#define ARRAY_LENGTH (8)

int main(void) {
	// Initialize Array and Root Tree 
	// �迭�� ��Ʈ Ʈ�� �ʱ�ȭ  

	// Add tree element to array 
	// �迭�� Ʈ����� �߰�
	int numArray[MAX_NUMS] = { 10,5,3,7,6,9,4,11 };
	TreeNode_t targetTree;
	for (int i = 0; i < MAX_NUMS; i++)
	{
		TreeNode_t tree;
		tree.left = NULL;
		tree.right = NULL;
		tree.parent = NULL;
		tree.value = numArray[i];
		targetTree = tree;
		treeArray[i] = tree;

		InsertTree(treeArray, &treeArray[i]);
	}

	// delete The second element of the array 
	// �迭�� �� ��°�� �� Ʈ��(value 7) ����
	// Ʈ�� ������ ���ŉ�����, �迭���� ���ŵ��� ����
	deleteTree(treeArray, &treeArray[3]);

	// Ʈ�� ���� ��ȸ
	traverseAllTree(treeArray);
	return 0;
}