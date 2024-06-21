#include "chess.h"
#include "tree.h"

chessPos* arrForKnightPos(chessPos knightPos, int* logSize)
{
    chessPos optionalMove = { 0,0 };

    optionalMove[0] = knightPos[0];
    optionalMove[1] = knightPos[1];
    chessPos* knightMovesArr = (chessPos*)malloc(8 * sizeof(chessPos));
    int phSize = 8;
    int curr = 0;

    // arr to idendify where is the next optional knight move
    int charArr[8] = { -2,-1, 1, 2, 2, 1, -1, -2 };
    int numberArr[8] = { 1, 2, 2, 1,-1,-2, -2,-1 };


    for (int i = 0; i < OPTIONAL_KNIGHT_MOVES; i++)
    {
        optionalMove[0] += charArr[i];
        optionalMove[1] += numberArr[i];
        if (isValidMove(knightPos, optionalMove))
        {
            knightMovesArr[curr][0] = optionalMove[0];
            knightMovesArr[curr][1] = optionalMove[1];
            curr++;
            if (curr >= phSize)
            { // If current size exceeds or equals the allocated size, reallocate
                phSize += 8; // Allocate memory for 8 more moves
                knightMovesArr = (chessPos*)realloc(knightMovesArr, phSize * sizeof(chessPos));
                if (!knightMovesArr)
                {
                    printf("Memory reallocation failed.\n");
                    exit(-1);
                }
            }

        }
        optionalMove[0] = knightPos[0];
        optionalMove[1] = knightPos[1];
    }
    *logSize = curr;

    return knightMovesArr;
}

chessPosArray*** validKnightMoves()
{
    int i = 0, j = 0;
    chessPos curr = { 0,0 };

    // Allocate memory for an array of chessPosArray pointers
    chessPosArray*** validMoves = (chessPosArray***)malloc(5 * sizeof(chessPosArray**));
    checkAllocation(validMoves);

    for (i = 0; i < ROWS; i++)
    {
        // Allocate memory for each chessPosArray
        validMoves[i] = (chessPosArray**)malloc(5 * sizeof(chessPosArray*));
        for (j = 0; j < COLS; j++)
        {
            curr[0] = j + 'A';
            curr[1] = i + '1';

            // Allocate memory for the positions array in each chessPosArray
            validMoves[i][j] = (chessPosArray*)malloc(sizeof(chessPosArray));
            validMoves[i][j]->size = 0;
            validMoves[i][j]->positions = arrForKnightPos(curr, &(validMoves[i][j]->size));
        }
    }

    return validMoves;
}


bool isValidMove(chessPos knight, chessPos optionalKnightPos)
{
    if (optionalKnightPos[1] < '1' || optionalKnightPos[1] > '5')
        return false;
    else if (optionalKnightPos[0] < 'A' || optionalKnightPos[0] > 'E')
        return false;
    else
        return true;
}


void display(chessPosList* lst)
{
    
    bool board[ROWS][COLS];
    // Allocate memory for each row
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = false;

        }

    }

    displayBoard(lst->head, board);
    printTable(*lst);
}

void displayBoard(treeNodeListCell** curr, bool board[ROWS][COLS])
{
    ///////////////////////////////////////////;
}

void createATable(chessPosList lst, int board[COLS][ROWS])
{
    int count = 1;
    chessPosCell* current = lst.head;

    while (current != NULL) {
        int row = current->position[0] - 'A';
        int col = current->position[1] - '1';
        board[row][col] = count++;
        current = current->next;
    }
}
void printTable(chessPosList lst)
{
    int i, j, board[5][5] = { 0 };
    createATable(lst, board);
    printf("   1  2  3  4  5\n");
    for (i = 0; i < 5; i++)
    {
        printf("%c|", 'A' + i);

        for (j = 0; j < 5; j++)
        {
            if (board[i][j] == 0)
                printf("  |");
            else
                printf("%2d|", board[i][j]);
        }
        printf("\n");
    }
}

chessPos* chessPosToBoardPos(chessPos pos)
{
    chessPos* boardPos = (chessPos*)calloc(1, sizeof(chessPos));
    checkAllocation(boardPos);
    switch (pos[0])
    {
    case 'A':
        *(boardPos[0]) = 0;
        break;
    case 'B':
        *(boardPos[0]) = 1;
        break;
    case 'C':
        *(boardPos[0]) = 2;
        break;
    case 'D':
        *(boardPos[0]) = 3;
        break;
    case 'E':
        *(boardPos[0]) = 4;
        break;
    }

    *(boardPos[1]) = pos[1] - 1;

    return boardPos;

}

void checkAllocation(void* ptr)      //this func gets a pointer and checks if the allocation failed
{
    if (ptr == NULL)
    {
        printf("Allocation error\n");
        exit(-1);
    }
}
