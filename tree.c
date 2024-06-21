#include "chess.h"
#include "allInclude.h"
#include "tree.h"

void findKnightPathCoveringAllBoardRec(chessPosList* lst, treeNode* root, int* count)
{
    chessPosCell* cell = (chessPosCell*)malloc(sizeof(chessPosCell));
    checkAllocation(cell);

    cell->position[0] = root->position[0];
    cell->position[1] = root->position[1];
    cell->next = NULL;

    insertNodeToStartList(lst, cell); 

    (*count)++;

    if (*count == 25)
        return lst;

    if (isEmptyTreeList(root->next_possible_positions))
    {
        (*count)--;
        removeNodeFromStartList(lst); 
        return;
    }
    else
    {
        treeNodeListCell* curr = root->next_possible_positions.head;
        while (curr != NULL) {
            findKnightPathCoveringAllBoardRec(lst, curr->node, count);
            
            if (*count == 25) 
                return;  
            curr = curr->next;
        }
        (*count)--;
        removeNodeFromStartList(lst);
    }
   
}

void removeNodeFromStartList(chessPosList* lst) 
{
    if (lst->head == NULL) 
        return;

    chessPosCell* temp = lst->head;
    lst->head = lst->head->next;

    if (lst->head == NULL) 
        lst->tail = NULL;

    free(temp);
}

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) 
{
   // bool haveWeBeenHere[ROWS][COLS] = { false };

    int count = 0;
    chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocation(lst);
    makeEmptyList(lst);

    findKnightPathCoveringAllBoardRec(lst, path_tree->root, &count);
    return lst;
}
void insertNodeToEndList(treeNodeList* lst, treeNodeListCell* newTail)
{
    if (isEmptyTreeList(*lst))
    {
        lst->head = lst->tail = newTail;
    }
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}

void makeEmptyList(treeNodeList* lst)
{
    lst->head = lst->tail = NULL;
}

bool isEmptyTreeList(treeNodeList lst)
{
    return (lst.head == NULL);
}

bool isEmptyChessList(chessPosList lst)
{
    return (lst.head == NULL);
}

void insertNodeToStartList(chessPosList* lst, chessPosCell* newHead)
{
    if (isEmptyChessList(*lst))
    {
        lst->head = lst->tail = newHead;
    }
    else
    {
        newHead->next = lst->head;
        lst->head = newHead;
    }
}

treeNodeListCell* createNewListNode(treeNode* node, treeNodeListCell* next)
{
    treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkAllocation(cell);
    cell->node = node;
    cell->next = next;
    return cell;

}

treeNode* createTreeNode(chessPos pos, treeNodeList lst)
{
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(node);
    node->position[0] = pos[0];
    node->position[1] = pos[1];
    node->next_possible_positions = lst;
    return node;

}

void findAllPossibleKnightPathsRec(bool forbidden[ROWS][COLS], treeNode* root, int* count)
{
    int currRow = 0;
    int currColumm = 0;
    currRow = (root->position[0]) - 'A';
    currColumm = (root->position[1]) - '1'; //כל הארבע שורות האלו שקולות לפונקצייה שלנו שמעביר נקודה מייצוג שחמט לייצוג במערך הבוליאני

    if (forbidden[currRow][currColumm])     // תנאי עצירה רקורסיבי - תעצור כשהמיקום של הרוט כבר הופיע במערך הבוליאני
    {
        return root;
    }
    else
    {
        treeNodeList* currentTreeNodeList = makeListFromArr(root->position); //הפונקציה שלנו שיוצרת רשימה ממערך
        root->next_possible_positions.head = currentTreeNodeList->head; //מקשרים את הרשימה של הרוט לרשימה שיצרנו
        root->next_possible_positions.tail = currentTreeNodeList->tail;


        bool newForbidden[ROWS][COLS]; //כאן מגיע הקאצ': יוצרים מערך בוליאני *סטטי!!!!* אבל שמים בתוכו את הערכים של המערך שהעברנו בארגומנט
        for (int i = 0; i < ROWS; i++)       // זה מוזר אבל אפשר לחשוב על זה כפשוט מערך סטטי עם מספרים שאנחנו משנים אותם כל פעם ומעבירים אותו הלאה, וככה לא צריך להתעסק עם פוינטרים כשחוזרים מהרקורסיה
        {
            for (int j = 0; j < COLS; j++)
            {
                newForbidden[i][j] = forbidden[i][j];
            }
        }
        newForbidden[currRow][currColumm] = true;  //וכאן אנחנו מייצרים את השינוי בהעתק - שמים את הערך של הרוט הספציפי 

       //הלולאה הענקית הבאה היא בעצם התחליף לדיספליי בורד המסריח שלנו

        treeNodeListCell* cell = root->next_possible_positions.head;  //אלו בדיוק כמו קודם בשביל לטפל בשחרורים
        treeNodeListCell* prev = root->next_possible_positions.head;
        treeNodeListCell* toDelete = root->next_possible_positions.head;
        while (cell != NULL)
        {
            int currRow = 0;
            int currColumm = 0;
            currRow = cell->node->position[0] - 'A';
            currColumm = cell->node->position[1] - '1';  //שוב השורות ששקולות לפונקציה שמעבירה נקודה לייצוג במערל הבוליאני
            if (forbidden[currRow][currColumm])   //אם הנקודה הופיעה במערך צריך לשחרר אותה וחילקתי לתנאים
            {
                if (cell == root->next_possible_positions.head) //אם מדובר בראש הרשימה 
                {
                    if (root->next_possible_positions.head == root->next_possible_positions.tail) //עוד תנאי קצה ספציפי שבודק אם מדובר בכך שראש הרשימה וזנב הרשימה זה אותו אחד
                    {
                        free(cell);
                        root->next_possible_positions.head = root->next_possible_positions.tail = NULL;
                        break; 
                    }

                    root->next_possible_positions.head = cell->next;  //זה בעצם ה''אחרת'', אם ראש הרשימה שונה מהזנב
                    free(cell);
                    
                    cell = root->next_possible_positions.head; //יש לנו עכשיו ראש חדש לרשימה 
                    
                    continue;
                    
                }
                else if (cell == root->next_possible_positions.tail) //אם מדובר בזנב טיפול אחר
                {
                    prev->next = NULL;
                    root->next_possible_positions.tail = prev;
                    free(cell);
                    break;
                }
                else  //אם מדובר באיבר מאמצע הרשימה אז זה ''שחרור קלאסי'' ורגיל
                {
                    toDelete = cell;
                    cell = cell->next;
                    prev->next = cell;
                    free(toDelete);
                }
            }
            prev = cell;
            cell = cell->next;
        }

        if (root->next_possible_positions.head == NULL) //סופר עלים
        {
            (*count)++;
        }

       //עדכנו את הרשימה אז עכשיו שמים פוינטר ששווה לראש רשימה ואיתו מבצעים את הרקורסיה
        treeNodeListCell* currSubRoot = root->next_possible_positions.head;
       
        while (currSubRoot != NULL) //רקורסיה בדיוק כמו אצלנו
        {
            findAllPossibleKnightPathsRec(newForbidden, currSubRoot->node, count);
            currSubRoot = currSubRoot->next;
        }

        if (currentTreeNodeList != NULL) //את השורה הזאת לא הבנתי עד הסוף כאילו משחררים רשימות זבל או משהו כזה לא ברור לי תנסי לרוץ עם התוכנית את בטוח תביני
        {
            free(currentTreeNodeList);
        }
    }

    return root;


}

pathTree findAllPossibleKnightPaths(chessPos* startingPosition)
{
    pathTree tree;
    bool haveWeBeenHere[ROWS][COLS] = { false }; //	מגדירים את המערך הבוליאני מסתבר שככה אפשר ישר לאפס הכל

    tree.root = createNewTreeNode(startingPosition); //פונקציית עזר שיוצרת את הרוט

    int count = 0; //קאונטר כשנבין איפה לשים


    findAllPossibleKnightPathsRec(haveWeBeenHere, tree.root, &count); //הפונקציה הרק'ורסיבית מקבלת מערך בוליאני *סטטי!!* ורוט אח''כ יגיע הסבר איך זה סטטי ולא דינאמי
    printf("%d", count);

    return tree;
}

treeNodeListCell* createNewTreeNodeListCell(treeNode* addNode)
{
    treeNodeListCell* newCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
    checkAllocation(newCell);
    newCell->node = addNode;
    newCell->next = NULL;
    return newCell;
}


treeNode* createNewTreeNode(chessPos* position)
{
    treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(newNode);
    newNode->position[0] = (*position)[0];
    newNode->position[1] = (*position)[1];
    newNode->next_possible_positions.head = NULL;
    newNode->next_possible_positions.tail = NULL;

    return newNode;
}


void addChildToTreeNode(treeNode* parent, treeNode* child) 
{
    treeNodeListCell* newCell = createNewTreeNodeListCell(child);

    if (parent->next_possible_positions.tail)
    {
        parent->next_possible_positions.tail->next = newCell;
    }
    else
    {
        parent->next_possible_positions.head = newCell;
    }
    parent->next_possible_positions.tail = newCell;
}


treeNodeListCell* makeListFromArrRec(chessPos* arr, int logSize, treeNodeList* list)
{
    if (!logSize)
    {
        return NULL;
    }
    else
    {
        for (int i = 0; i < logSize; i++)
        {
            treeNodeListCell* cell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
            checkAllocation(cell);
            cell->node = (treeNode*)malloc(sizeof(treeNode));
            checkAllocation(cell->node);
            cell->node->position[0] = arr[i][0];
            cell->node->position[1] = arr[i][1];
            cell->node->next_possible_positions.head = NULL;
            cell->node->next_possible_positions.tail = NULL;
            insertNodeToEndList(list, cell);

            cell->next = makeListFromArrRec(++arr, --logSize, list);

            return cell;

        }

    }

}

treeNodeList* makeListFromArr(chessPos pos)
{
    int logSize = 0;
    chessPos* arr = arrForKnightPos(pos, &logSize);


    treeNodeList* lst = (treeNodeList*)malloc(sizeof(treeNodeList));
    checkAllocation(lst);
    makeEmptyList(lst);
    treeNodeListCell* head = makeListFromArrRec(arr, logSize, lst);
    lst->head = head;
    treeNodeListCell* node = head;
    treeNodeListCell* prev = head;

    while (node != NULL)
    {
        prev = node;
        node = node->next;
    }

    lst->tail = prev;


    return lst;
}