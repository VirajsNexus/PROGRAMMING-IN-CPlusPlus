#include <stdio.h>
#include <malloc.h>

struct node
{
    int iData;
    struct node *pNext;
};

// Function declarations
void InsertFirst(struct node **, int);
void InsertLast(struct node **, int);
void InsertAtPosition(struct node **, int, int);
int DeleteFirst(struct node **);
int DeleteLast(struct node **);
int DeleteAtPosition(struct node **, int);
void Display(struct node *);
int CountNodes(struct node *);
int SearchFirstOccurrence(struct node *, int);
int SearchLastOccurrence(struct node *, int);
int SearchAllOccurrences(struct node *, int);
void ReverseDisplay(struct node *);
void PhysicalReverse(struct node **);
void ConcatLists(struct node **, struct node **);
void ConcatAtPosition(struct node **, struct node **, int);
void DeleteAll(struct node **);

int main(void)
{
    int iData;
    struct node *pFirst = NULL;
    struct node *pSecond = NULL;

    Display(pFirst); // List is empty

    InsertFirst(&pFirst, 30);
    InsertFirst(&pFirst, 20);
    InsertFirst(&pFirst, 10);

    Display(pFirst); // 10 20 30

    InsertLast(&pFirst, 40);
    InsertLast(&pFirst, 50);
    InsertLast(&pFirst, 60);

    Display(pFirst); // 10 20 30 40 50 60

    InsertAtPosition(&pFirst, 20, 4);

    Display(pFirst); // 10 20 30 20 40 50 60

    iData = DeleteFirst(&pFirst);
    if(iData != -1)
        printf("Deleted data is %d\n", iData); // 10

    Display(pFirst); // 20 30 20 40 50 60

    iData = DeleteLast(&pFirst);
    if(iData != -1)
        printf("Deleted data is %d\n", iData); // 60

    Display(pFirst); // 20 30 20 40 50

    iData = DeleteAtPosition(&pFirst, 4);
    if(iData != -1)
        printf("Deleted data is %d\n", iData); // 40

    Display(pFirst); // 20 30 20 50

    iData = CountNodes(pFirst);
    printf("Total node count is %d\n", iData); // 4

    iData = SearchFirstOccurrence(pFirst, 20);
    if(iData != 0)
        printf("First occurrence of %d is at %d position\n" , 20, iData); // 1

    iData = SearchLastOccurrence(pFirst, 20);
    if(iData != 0)
        printf("Last occurrence of %d is at %d position\n" , 20, iData); // 3

    iData = SearchAllOccurrences(pFirst, 20);
    printf("%d found %d times\n", 20, iData); // 2

    Display(pFirst); // 20 30 20 50
    ReverseDisplay(pFirst); // 50 20 30 20
    printf("\n");
    Display(pFirst); // 20 30 20 50

    PhysicalReverse(&pFirst);
    Display(pFirst); // 50 20 30 20

    InsertLast(&pSecond, 100);
    InsertLast(&pSecond, 200);
    InsertLast(&pSecond, 300);

    Display(pFirst); // 50 20 30 20
    Display(pSecond); // 100 200 300

    ConcatLists(&pFirst, &pSecond);
    Display(pFirst); // 50 20 30 20 100 200 300
    Display(pSecond); // List is empty

    InsertLast(&pSecond, 400);
    InsertLast(&pSecond, 500);
    InsertLast(&pSecond, 600);

    Display(pFirst); // 50 20 30 20 100 200 300
    Display(pSecond); // 400 500 600

    ConcatAtPosition(&pFirst, &pSecond, 4);
    Display(pFirst); // 50 20 30 400 500 600 20 100 200 300
    Display(pSecond); // List is empty

    if(pFirst != NULL)
    {
        DeleteAll(&pFirst);
        pFirst = NULL;
    }

    if(pSecond != NULL)
    {
        DeleteAll(&pSecond);
        pSecond = NULL;
    }

    Display(pFirst); // List is empty
    Display(pSecond); // List is empty

    return 0;
}

// Function definitions
void InsertFirst(struct node **ppHead, int iNo)
{
    struct node *pNewnode = NULL; 
    pNewnode = (struct node *)malloc(sizeof(struct node));
    if (NULL == pNewnode)    
    {
        printf("Memory allocation failed!\n");
        return;
    }

    pNewnode->iData = iNo;
    if(NULL==*ppHead)                     // If linked list is empty
    {
        pNewnode->pNext = NULL;           // set last node's next as NULL
        *ppHead = pNewnode;               // New node is the first node now
        return;
    }

    pNewnode->pNext = *ppHead;            // Link new node with old first
    *ppHead = pNewnode;                   // Update head
}

void InsertLast(struct node **ppHead, int iNo)
{
    struct node *pNewnode = (struct node *)malloc(sizeof(struct node));
    if (pNewnode == NULL)   
    {
        printf("Memory allocation failed!\n");
        return;
    }

    pNewnode->iData = iNo;
    pNewnode->pNext = NULL;           // Always set last node’s next as NULL 

    if (*ppHead == NULL)              // If list is empty
    {   
        *ppHead = pNewnode;
        return;
    }

    struct node *pTemp = NULL;
    pTemp = *ppHead;                  // Pointing to first node
    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = pNewnode;          // Link new node at the end
}

void InsertAtPosition(struct node **ppHead, int iKey, int iPos)
{
    int iCount = CountNodes(*ppHead);
    struct node *pNewNode = NULL;
    struct node *pTemp = NULL;

    if(iPos <= 0 || iPos > iCount + 1)
    {
        printf("Invalid position %d! Node not inserted.\n", iPos);
        return;
    }

    if (iPos == 1)
    {
        InsertFirst(ppHead, iKey);
        return;
    }
    
    if (iPos == iCount + 1)
    {
        InsertLast(ppHead, iKey);
        return;
    }

    pNewNode = (struct node *)malloc(sizeof(struct node));
    if (pNewNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    pNewNode->iData = iKey;
    pTemp = *ppHead;

    for (iCount = 1; iCount < iPos - 1; iCount++)
    {
        pTemp = pTemp->pNext;
    }

    pNewNode->pNext = pTemp->pNext;
    pTemp->pNext = pNewNode;
}


int DeleteFirst(struct node **ppHead)
{
    struct node *pTemp = NULL;
    int iDelData = -1;

    if (*ppHead == NULL)                                        // If list is empty
    {
        printf("List is empty. Nothing to delete.\n");
        return iDelData;
    }
    pTemp = *ppHead;
    iDelData = pTemp->iData;
    *ppHead = (*ppHead)->pNext;                                     // Traverse head to next node
    free(pTemp);                                                    // Delete old first node
    pTemp = NULL;

    return iDelData;
}

int DeleteLast(struct node **ppHead)
{
    struct node *pTemp = NULL, *pPrev = NULL;
    int iDelData = -1;

    if (*ppHead == NULL)                                        
    {
        printf("List is empty. Nothing to delete.\n");
        return iDelData;
    }
    
    pTemp = *ppHead;
    if (pTemp->pNext == NULL)                                     
    {
        iDelData = pTemp->iData;
        free(*ppHead);
        *ppHead = NULL;
        return iDelData;
    }

    while (pTemp->pNext != NULL)                                    
    {
        pPrev = pTemp;
        pTemp = pTemp->pNext;
    }
    iDelData = pTemp->iData;
    pPrev->pNext = NULL;                                    
    free(pTemp);
    pTemp = NULL;
    
    return iDelData;                                            
}

int DeleteAtPosition(struct node **ppHead, int iPos)
{
    int iDelData = -1;
    int iCount = 0;

    iCount = CountNodes(*ppHead);
    if (iPos <= 0 || iPos > iCount)
    {
        printf("Invalid position %d! Node not deleted.\n", iPos);
        return iDelData;
    }
    
    if (iPos == 1)
    {
        return DeleteFirst(ppHead);
    }
    
    if (iPos == iCount)
    {
        return DeleteLast(ppHead);
    }

    struct node *pTemp = *ppHead;
    struct node *pDelNode = NULL;

    for (iCount = 1; iCount < iPos - 1; iCount++)
    {
        pTemp = pTemp->pNext;
    }

    pDelNode = pTemp->pNext;
    iDelData = pDelNode->iData;
    pTemp->pNext = pDelNode->pNext;
    free(pDelNode);
    pDelNode = NULL;

    return iDelData;
}


void Display(struct node *pHead)
{
    if (NULL == pHead)
    {
        printf("List is empty.\n\n");
        return;
    }

    while (pHead != NULL)
    {
        printf("| %d | -> ", pHead->iData);
        pHead = pHead->pNext;
    }
    printf("| NULL |\n");
}

void DeleteAll(struct node **ppHead)
{
    struct node *pTemp;
    while (*ppHead != NULL)
    {
        pTemp = *ppHead;
        *ppHead = (*ppHead)->pNext;
        free(pTemp);
    }
}

int CountNodes(struct node *pHead)
{
    int iCount = 0;
    while (pHead != NULL)
    {
        iCount++;
        pHead = pHead->pNext;
    }
    return iCount;
}

int SearchFirstOccurrence(struct node *pHead, int iKey)
{
    int iPos = 1;

    while (pHead != NULL)
    {
        if (pHead->iData == iKey)
        {
            return iPos;
        }
        pHead = pHead->pNext;
        iPos++;
    }

    return 0; // Return 0 if not found
}
int SearchLastOccurrence(struct node *pHead, int iKey)
{
    int iPos = 1;
    int iLastPos = 0;

    while (pHead != NULL)
    {
        if (pHead->iData == iKey)
        {
            iLastPos = iPos;
        }
        pHead = pHead->pNext;
        iPos++;
    }
        
    return iLastPos;
}
int SearchAllOccurrences(struct node *pHead, int iKey)
{
    int iCount = 0;

    while (pHead != NULL)
    {
        if (pHead->iData == iKey)
        {
            iCount++;
        }
        pHead = pHead->pNext;
    }

    return iCount;
}

void ReverseDisplay(struct node *pHead)
{
    if(pHead != NULL)
    {
        ReverseDisplay(pHead->pNext);
        printf("%d ", pHead->iData);
    }
}

void PhysicalReverse(struct node **ppHead)
{
    struct node *pPrev = NULL, *pCurr = *ppHead, *pNext = NULL;

    while (pCurr != NULL)
    {
        pNext = pCurr->pNext;
        pCurr->pNext = pPrev;
        pPrev = pCurr;
        pCurr = pNext;
    }

    *ppHead = pPrev;
}

void ConcatLists(struct node **ppHead1, struct node **ppHead2)
{
    if (*ppHead2 == NULL)
    {
        return; // Nothing to concatenate
    }

    if (*ppHead1 == NULL)
    {
        *ppHead1 = *ppHead2;
        *ppHead2 = NULL;
        return;
    }

    struct node *pTemp = *ppHead1;
    while (pTemp->pNext != NULL)
    {
        pTemp = pTemp->pNext;
    }
    pTemp->pNext = *ppHead2;

    *ppHead2 = NULL; // clear second list reference
}

void ConcatAtPosition(struct node **ppHead1, struct node **ppHead2, int pos)
{
    if (*ppHead2 == NULL)
    {
        printf("Second list is empty! Nothing to concatenate.\n");
        return;
    }
    
    int iCount = CountNodes(*ppHead1);
    if (pos <= 0 || pos > iCount + 1)
    {
        printf("Invalid position %d! Concatenation failed.\n", pos);
        return;
    }

    if (pos == 1)
    {
        struct node *last = *ppHead2;
        while (last->pNext != NULL)
        {
            last = last->pNext;
        }
        last->pNext = *ppHead1;
        *ppHead1 = *ppHead2;
        *ppHead2 = NULL;
        return;
    }

    struct node *pTemp = *ppHead1;
    for (int i = 1; i < pos - 1; i++)
    {
        pTemp = pTemp->pNext;
    }

    struct node *last = *ppHead2;
    while (last->pNext != NULL)
    {
        last = last->pNext;
    }

    last->pNext = pTemp->pNext;
    pTemp->pNext = *ppHead2;

    *ppHead2 = NULL;
}
