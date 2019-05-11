#include <stdio.h>
#include "tree.h"

void FDN(TreeNode **node, const int level);
int min(int a, int b);
int max(int a, int b);
int treeMaxNode(TreeNode **node);
int treeNodeSDN(TreeNode **node, const int value, const int level);
TreeNode *getNodeByPath(TreeNode **node, const char *path);

int main(void)
{
	int i;
	char lcom[255], ch;
	TreeNode *root = NULL, *tmpNode = NULL;

	do
	{
		printf("Enter a command (h - help):\n");
		scanf("%s", lcom);

		if (lcom[0] == '+')
		{
			scanf(" %c", &ch);

			if (lcom[1] == 'r')
			{
				if (root == NULL)
				{
					if (ch >= 'A' && ch <= 'Z')
					{
						treeAddNode(&root, ch - 'A');

						printf("The root %c has been created\n", ch);
					}
					else
						printf("ERROR: Wrong symbol\n");
				}
				else
					printf("The root is already created\n");
			}
			else if (root == NULL)
				printf("The root hasn't been created\n");
			else
			{
				tmpNode = root;

				if (lcom[1] != '\0')
					tmpNode = getNodeByPath(&root, &lcom[1]);

				if (tmpNode == NULL)
					printf("ERROR: Wrong path\n");
				else if (ch >= 'A' && ch <= 'Z')
				{
					if (treeAddNode(&tmpNode, ch - 'A') != NULL)
						printf("The node %c has been added to the node %c\n", ch, tmpNode->data + 'A');
				}
				else
					printf("ERROR: Wrong symbol\n");
			}
		}
		else if (lcom[0] == '-')
		{
			scanf(" %c", &ch);

			if (ch >= 'A' && ch <= 'Z')
			{
				if (treeRemoveNode(&root, ch - 'A'))
					printf("The node %c has been deleted\n", ch);
				else
					printf("The node %c is lost\n", ch);
			}
			else
				printf("ERROR: Wrong symbol\n");
		}
		else if (lcom[0] == 'p')
		{
			FDN(&root, 0);
		}
		else if (lcom[0] == 't')
		{
			if (root != NULL)
				printf("Max tree depth: %d\n", treeNodeSDN(&root, treeMaxNode(&root), 1));
			else
				printf("Tree is empty\n");
		}
		else if (lcom[0] == 'h')
		{
			printf("#INSTRUCTION\n");
			printf("List of commands:\n");
			printf("+r CHAR - create the root of CHAR\n");
			printf("+ CHAR - add son of CHAR to the root\n");
			printf("+PATH CHAR - add node of CHAR with prescriped path (s - son, b - brother)\n");
			printf("- CHAR - delete first found node of CHAR and its subtree\n");
			printf("p - print tree\n");
			printf("t - do the task on tree\n");
			printf("q - quit the program\n");
			printf("#END\n");
		}
		else if (lcom[0] != 'q')
		{
			printf("Unknown command\n");
		}
	}
	while (lcom[0] != 'q');

	treeDestroy(&root);

	return 0;
}

void FDN(TreeNode **node, const int level)
{
	if (*node == NULL)
	{
		printf("The tree is empty\n");

		return;
	}

	printf("%*s%c\n", level * 2, "", (*node)->data + 'A');

	if ((*node)->son != NULL)
		FDN(&(*node)->son, level + 1);

	if ((*node)->bro != NULL)
		FDN(&(*node)->bro, level);
}

int min(int a, int b)
{
	return (a < b ? a : b);
}

int max(int a, int b)
{
	return (a > b ? a : b);
}

int treeMaxNode(TreeNode **node)
{
	if (*node == NULL)
		return 0;

	if ((*node)->bro == NULL && (*node)->son == NULL)
		return (*node)->data;

	return max(treeMaxNode(&(*node)->son), treeMaxNode(&(*node)->bro));
}

int treeNodeSDN(TreeNode **node, const int value, const int level)
{
	int maxLevel = 0;

	if (*node == NULL)
		return 0;

	if ((*node)->data == value)
		return level;

	maxLevel = treeNodeSDN(&(*node)->bro, value, level);

	if (maxLevel)
		return maxLevel;

	return treeNodeSDN(&(*node)->son, value, level + 1);
}

TreeNode *getNodeByPath(TreeNode **node, const char *path)
{
	int i = 0;
	TreeNode *tmpNode = *node;

	while (path[i] != '\0')
	{
		if (path[i] == 's')
			if (tmpNode->son != NULL)
				tmpNode = tmpNode->son;
			else
				return NULL;
		else if (path[i] == 'b')
			if (tmpNode->bro != NULL)
				tmpNode = tmpNode->bro;
			else
				return NULL;
		else
			return NULL;

		i++;
	}

	return tmpNode;
}