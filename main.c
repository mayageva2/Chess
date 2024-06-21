#include "allInclude.h"
#include "chess.h"
#include "tree.h"

void main()
{
	chessPos pos = { "A1" };
	pathTree tr;
	tr = findAllPossibleKnightPaths(pos);
	
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	lst = findKnightPathCoveringAllBoard(&tr);

	if (lst->head != NULL)
	{
		printf("\nyes\n");
		chessPosCell* current = lst->head;
		for (int i = 0; i < 25 && current != NULL; i++)
		{
			printf("%c %c\n", current->position[0], current->position[1]);
			current = current->next;
		}
	}
	else
		printf("\nno");
	

	/*int num = 0;
	scanf("%d", &num);
	void main()
    {
	printf("ARE YOU ACOUSTIC");
	}
	chessPosArray*** chessTableKnight = validKnightMoves();
	chessPosList list;
	chessPosCell* head = (chessPosCell*)malloc(sizeof(chessPosCell));
	list.head = head;
	head->position[0] = 'A';
	head->position[1] = '1';
	chessPosCell* node1 = (chessPosCell*)malloc(sizeof(chessPosCell));
	head->next = node1;
	node1->position[0] = 'A';
	node1->position[1] = '2';
	chessPosCell* node2 = (chessPosCell*)malloc(sizeof(chessPosCell));
	node1->next = node2;
	node2->position[0] = 'A';
	node2->position[1] = '5';
	chessPosCell* node3 = (chessPosCell*)malloc(sizeof(chessPosCell));
	node2->next = node3;
	node3->position[0] = 'A';
	node3->position[1] = '3';
	chessPosCell* node4 = (chessPosCell*)malloc(sizeof(chessPosCell));
	node3->next = node4;
	node4->position[0] = 'A';
	node4->position[1] = '4';
	chessPosCell* tail = (chessPosCell*)malloc(sizeof(chessPosCell));
	node4->next = tail;
	tail->position[0] = 'E';
	tail->position[1] = '1';
	tail->next = NULL;
	list.tail = tail;

	display(&list);

*/
}
