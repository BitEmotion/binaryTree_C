#include "binary.h"
//#define ARRAY_LENGTH (8)

int main(void) {
	// Initialize Array and Root Tree 
	// 배열과 루트 트리 초기화  

	// Add tree element to array 
	// 배열에 트리요소 추가
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
	// 배열에 네 번째로 들어간 트리(value 7) 제거
	// 트리 참조로 제거됬지만, 배열에서 제거되지 않음
	deleteTree(treeArray, &treeArray[3]);

	// 트리 참조 조회
	traverseAllTree(treeArray);
	return 0;
}