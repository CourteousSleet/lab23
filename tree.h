#ifndef TREE_H
#define TREE_H

#include <stdlib.h>

typedef enum _letters
{
	A = 0, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
} letters;

typedef struct _TreeNode
{
	letters data;
	struct _TreeNode *parent;
	struct _TreeNode *olderBro;
	struct _TreeNode *bro;
	struct _TreeNode *son;
} TreeNode;

TreeNode *treeAddNode(TreeNode **node, const letters value);
TreeNode *treeFindNode(TreeNode **node, const letters value);
int treeRemoveNode(TreeNode **node, const letters value);
void treeDestroy(TreeNode **node);

#endif