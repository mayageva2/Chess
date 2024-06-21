#pragma once
#include "allInclude.h"

#define ROWS 5
#define COLS 5
#define OPTIONAL_KNIGHT_MOVES 8


// CHESS DEF//
typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;



//---------- CHESS POSITION LIST------------//
typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


chessPosArray*** validKnightMoves(); //THE MAIN FUNC THAT CREATES AND RETURNING THE CHESSBOARD ARRAY FROM Q1

bool isValidMove(chessPos knight, chessPos optionalKnightPos); //RETURNING TRUE/FALSE IF THE KNIGHT CAN MOVE THE THE SUGGESTION PLACE
chessPos* arrForKnightPos(chessPos knightPos, int* logSize); //FUNC TO CREATE AND RETARNING AN ARRAY OF POSITIONS FOR A KNIGHT TO MOVE TO FROM A POSITION ON THE BOARD
void checkAllocation(void* ptr); //CHECKING ALLOCATION OF DYNAMIC MEMORY
void display(chessPosList* lst); //DISPLAYING A CHESS BOARD FROM Q2
void printTable(chessPosList lst); //ACTUALLY PRINTING THE TABLE
chessPos* chessPosToBoardPos(chessPos Pos); //"CORRERCTING" THE CHESS POSITION TO A POSITION THE BOOLEAN ARRAY COULD UNDERSTAND
bool isEmptyChessList(chessPosList lst);
/*void display(chessPosList* lst);
void displayBoard(chessPosCell* cell);*/
