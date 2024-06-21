#pragma once
#include "allInclude.h"
#include "chess.h"


//DEFINITIONS OF TREE AND LIST IN THE TREE//
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNodeList {
	treeNodeListCell* head;
	treeNodeListCell* tail;
} treeNodeList;

typedef struct _treeNode {
	chessPos position;
	treeNodeList next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;


typedef struct _pathTree {
	treeNode* root;
} pathTree;



//TR.LIST FUNCS//
void findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, bool board[ROWS][COLS]);

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);

void insertNodeToEndList(treeNodeList* lst, treeNodeListCell* newTail); //INSERTING A NODE LIST TO THE END OF THE LIST

bool isEmptyTreeList(treeNodeList lst); // MAKING AN EMPTY LIST

void makeEmptyList(treeNodeList* lst);

treeNodeListCell* makeListFromArrRec(chessPos* arr, int logSize, treeNodeList* lst);

void insertNodeToStartList(chessPosList* lst, chessPosCell* newHead);

treeNodeList* makeListFromArr(chessPos pos);

/*void freeList(treeNodeList* list);           // NO IMPLEMENT
void freeListRec(treeNodeListCell* cell);    // NO IMPLEMENT

void freeTree(pathTree tr);                  // NO IMPLEMENT
void freeTreeRec(treeNode* node);             // NO IMPLEMENT

void freeListNode(treeNodeListCell* cell); //NO IMPLEMENT*/

pathTree findAllPossibleKnightPaths(chessPos* startingPosition); //THE MAIN FUNC THAT BUILDING A TREE TO DESCRIBE A KNIGHT PATHS IN THE BOARD

treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode);

void findAllPossibleKnightPathsRec(bool forbidden[ROWS][COLS], treeNode* root, int* count); //CHANGE FUNC NAME

treeNodeListCell* createNewListNode(treeNode* node, treeNodeListCell* next);

void displayBoard(treeNodeListCell** cell, bool** board); //NEED TO GET THE ACTUAL FUNC!!!!

void addChildToTreeNode(treeNode* parent, treeNode* child);

treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode);

treeNode* createNewTreeNode(chessPos* position);

void removeNodeFromStartList(chessPosList* lst);

