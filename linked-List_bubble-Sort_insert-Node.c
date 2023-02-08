#include <stdio.h>
#include <stdlib.h>

/* - - - Define linked list structured data type: Node - - - */
typedef struct linkedList
{
    int nodeVal;                // Node element value
    struct linkedList *next;    // A pointer to the next node
} Node;

/* - - - Define linked list pointer data type: nodePtr - - - */
typedef Node *nodePtr;

/* - - - - - -   Create a Linked List from an Array   - - - - - - */
nodePtr createLinkedList(int arr[], int num)
{
    nodePtr headPtr, currPtr;       // Declare linked list pointer variables
    int idx;

    /* - - -   Create first node & Get the starting address of linked list   - - - */
    headPtr = (nodePtr)malloc(sizeof(Node));    // Allocate memory space for the first node
    currPtr = headPtr;                          // Assign current pointer to first node

    /* - - - - - - - - -   Create subsequent nodes   - - - - - - - - - */
    for (idx = 0; idx < num; idx++)
    {
        currPtr->nodeVal = arr[idx];                   // Write the value to the new node

        if (idx == num - 1)
        {
            currPtr->next = NULL;       // The end of the linked list
        }
        else
        {
            // Connect and allocate memory space to the new node
            currPtr->next = (nodePtr)malloc(sizeof(Node));
            currPtr = currPtr->next;    // Assign current pointer to next node
        }
    }

    return headPtr;     // Return the head pointer of the Linked List
}

/* - - -   Sort linked list node values in ascending order   - - - */
void bubbleSort(nodePtr ptr, int num)
{
    nodePtr tempPtr;
    int i, j, tempVal;
    int flag;

    for (i = 1; i < num; i++)
    {
        tempPtr = ptr;
        flag = 1;

        for (j = 1; j < num; j++)
        {
            if (tempPtr->nodeVal > tempPtr->next->nodeVal)
            {
                tempVal = tempPtr->nodeVal;
                tempPtr->nodeVal = tempPtr->next->nodeVal;
                tempPtr->next->nodeVal = tempVal;
                flag = 0;
            }

            tempPtr = tempPtr->next;    // Assign current pointer to next node
        }

        if (flag)
            break;
    }
}

/* - - - - - -   Insert new node into sorted linked list   - - - - - - */
nodePtr insertNode(nodePtr ptr, nodePtr aheadInsertPtr, int value)
{
    nodePtr insertNodePtr;

    /* - - - The new node is inserted before the first node of the linked list - - - */
    if (aheadInsertPtr == NULL)
    {
        insertNodePtr = (nodePtr)malloc(sizeof(Node));
        insertNodePtr->nodeVal = value;    // Write the value to the new node
        insertNodePtr->next = ptr;         // The new node is connected to the first node of the linked list
        return insertNodePtr;
    }
    else
    {
        /* - - - The new node is inserted after the last node of the linked list - - - */
        if (aheadInsertPtr->next == NULL)
        {
            insertNodePtr = (nodePtr)malloc(sizeof(Node));
            insertNodePtr->nodeVal = value;
            aheadInsertPtr->next = insertNodePtr;  // The last node of the linked list is connected to the new node
            insertNodePtr->next = NULL;            // Set the end of the linked list
        }
        /* - - -   The new node is inserted inside the linked list   - - - */
        else
        {
            insertNodePtr = (nodePtr)malloc(sizeof(Node));
            insertNodePtr->nodeVal = value;
            insertNodePtr->next = aheadInsertPtr->next; // Connect the inserted node to the next node
            aheadInsertPtr->next = insertNodePtr;       // Connect the previous node to the inserted node
        }

        return ptr;
    }
}

/* - - - - - -   Search insert position for the new node   - - - - - - */
nodePtr searchInsertPosition(nodePtr headPtr, int value)
{
    nodePtr ptr;
    nodePtr aheadInsertPtr = NULL;  // Initial value: NULL
    int notFoundFlag = 1;

    ptr = headPtr;

    while (ptr && notFoundFlag)
    {
        if (value < ptr->nodeVal)
            notFoundFlag = 0;       // Leave the loop when an insertable position is found

        if (notFoundFlag)
        {
            aheadInsertPtr = ptr;
            ptr = ptr->next;
        }
    }

    headPtr = insertNode(headPtr, aheadInsertPtr, value);
    return headPtr;
}

/* - - - - - -   Print the node values of linked list   - - - - - - */
void printLinkedList(nodePtr ptr)
{
    while (ptr)
    {
        printf("%d ", ptr->nodeVal);
        ptr = ptr->next;    // Assign current pointer to next node
    }

    printf("\n\n");
}

int main()
{
    static int numArr[] = {28, 42, 35, 16};
    int arrLen = sizeof(numArr) / sizeof(numArr[0]);    // Calculate the array length

    /* - - - - - -   Create the linked list   - - - - - - */
    nodePtr headNodePtr;
    headNodePtr = createLinkedList(numArr, arrLen);
    printf("Current linked list node values => ");
    printLinkedList(headNodePtr);

    /* - - - - - -   Sort linked list node values   - - - - - - */
    bubbleSort(headNodePtr, arrLen);
    printf("The node values after sorting in ascending order => ");
    printLinkedList(headNodePtr);

    /* - - -   Insert a new linked list node values   - - - */
    headNodePtr = searchInsertPosition(headNodePtr, 38);
    printf("The node values after inserting new value 38 into sorted linked list => ");
    printLinkedList(headNodePtr);

    system("pause");
    return 0;
}
