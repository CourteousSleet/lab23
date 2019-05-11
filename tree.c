#include "tree.h"

TreeNode *treeAddNode(TreeNode **node, const letters value)
{
	TreeNode *tmpBro = NULL, *tmpNode = (TreeNode *)malloc(sizeof(TreeNode));

	tmpNode->data = value;
	tmpNode->parent = NULL;
	tmpNode->olderBro = NULL;
	tmpNode->bro = NULL;
	tmpNode->son = NULL;

	if (*node == NULL)
		*node = tmpNode;
	else if ((*node)->son == NULL)
	{
		tmpNode->parent = *node;
		(*node)->son = tmpNode;
	}
	else
	{
		tmpBro = (*node)->son;

		while (tmpBro->bro != NULL)
			tmpBro = tmpBro->bro;

		tmpNode->parent = *node;
		tmpNode->olderBro = tmpBro;
		tmpBro->bro = tmpNode;
	}

	return tmpNode;
}

TreeNode *treeFindNode(TreeNode **node, const letters value)
{
	TreeNode *tmpNode = NULL;

	if ((*node)->data == value)
		tmpNode = *node;
	else if ((*node)->bro != NULL)
		tmpNode = treeFindNode(&(*node)->bro, value);

	if (tmpNode == NULL && (*node)->son != NULL)
		tmpNode = treeFindNode(&(*node)->son, value);

	return tmpNode;
}

int treeRemoveNode(TreeNode **node, const letters value)
{
	TreeNode *tmpNode = treeFindNode(node, value);

	if (tmpNode == NULL)
		return 0;

	if (tmpNode->parent == NULL)
	{
		treeDestroy(node);

		return 1;
	}

	if (tmpNode->olderBro == NULL)
		tmpNode->parent->son = tmpNode->bro;
	else
		tmpNode->olderBro->bro = tmpNode->bro;
		
	if (tmpNode->bro != NULL)
		tmpNode->bro->olderBro = tmpNode->olderBro;

	if (tmpNode->son != NULL)
		treeDestroy(&tmpNode->son);

	free(tmpNode);

	tmpNode = NULL;

	return 1;
}

void treeDestroy(TreeNode **node)
{
	if (*node == NULL)
		return;

	if ((*node)->bro != NULL)
		treeDestroy(&(*node)->bro);

	if ((*node)->son != NULL)
		treeDestroy(&(*node)->son);

	free(*node);

	*node = NULL;
}