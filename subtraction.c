/********************************************************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
**********************************************************************************************************************************/

#include "apc.h"

extern int flag;

// Function to perform subtraction of two large numbers represented as doubly linked lists
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *ptr1 = *tail1, *ptr2 = *tail2;
    int borrow = 0, diff = 0;
    bool is_negative_result = false;

    // Remove leading zeros from both input numbers
    if (removeLeadingZeros(head1, tail1) == FAILURE || removeLeadingZeros(head2, tail2) == FAILURE)
    {
        return FAILURE; // Return failure if removing leading zeros fails
    }

    // Compare the lengths of the two numbers
    int len1 = 0, len2 = 0;
    while (ptr1 != NULL) { len1++; ptr1 = ptr1->prev; } // Count digits of the first number
    while (ptr2 != NULL) { len2++; ptr2 = ptr2->prev; } // Count digits of the second number

    // Swap numbers if the first number is smaller than the second
    if (len1 < len2 || (len1 == len2 && compare(*head1, *head2) < 0))
    {
        is_negative_result = true; // Set flag for negative result

        // Swap the pointers using temporary variables
        Dlist *temp_head = *head1, *temp_tail = *tail1;

        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = temp_head;
        *tail2 = temp_tail;
    }

    // Start subtraction from the least significant digit (tail)
    ptr1 = *tail1;
    ptr2 = *tail2;

    Dlist *result = NULL; // Initialize result linked list

    // Subtract digit by digit, considering the borrow
    while (ptr1 != NULL || ptr2 != NULL || borrow != 0)
    {
        // Get the current digits from both numbers (or 0 if the digit is missing)
        int digit1 = (ptr1 != NULL) ? ptr1->data : 0;
        int digit2 = (ptr2 != NULL) ? ptr2->data : 0;

        // Perform the subtraction
        diff = digit1 - digit2 - borrow;
        if (diff < 0)
        {
            diff += 10;  // Adjust if the result is negative (borrow required)
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        // Create a new node for the result
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));

        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE; // Return failure if memory allocation fails
        }

        new_node->data = diff; // Set the digit of the result
        new_node->next = result;
        new_node->prev = NULL;

        if (result != NULL)
        {
            result->prev = new_node; // Update the previous pointer of the existing result
        }
        result = new_node; // Move the result pointer to the new node

        if (ptr1 != NULL) ptr1 = ptr1->prev; // Move to the next digit of the first number
        if (ptr2 != NULL) ptr2 = ptr2->prev; // Move to the next digit of the second number
    }

    // Remove leading zeros from the result
    if (removeLeadingZeros(&result, &result) == FAILURE)
    {
        return FAILURE; // Return failure if removing leading zeros from result fails
    }

    *headR = result; // Set the result's head pointer

    // If the result is negative, set the negative result flag
    if (is_negative_result)
    {
        flag = 1; // Negative result flag
    }

    return SUCCESS; // Return success after successful subtraction
}

// Function to remove leading zeros from the given number (represented as a doubly linked list)
int removeLeadingZeros(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    // Traverse the list and remove leading zeros
    while (temp != NULL && temp->data == 0)
    {
        // Remove the first node (leading zero)
        *head = temp->next;

        if (*head != NULL)
        {
            (*head)->prev = NULL;  // Adjust the previous pointer of the new head
        }
        
        free(temp);  // Free the memory of the removed node
        temp = *head;  // Move to the next node
    }

    // If the list is empty after removing zeros, create a new node with value 0
    if (*head == NULL)
    {
        *head = (Dlist *)malloc(sizeof(Dlist));

        if (*head == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE; // Return failure if memory allocation fails
        }

        (*head)->data = 0;  // Set the node data to zero
        (*head)->next = NULL;
        (*head)->prev = NULL;
        *tail = *head;  // Tail and head both point to the same single node
    }

    return SUCCESS; // Return success after removing leading zeros
}

// Function to compare two numbers represented as doubly linked lists
int compare(Dlist *ptr1, Dlist *ptr2)
{
    // Traverse the lists from tail to head (for least significant to most significant digits)
    while (ptr1 != NULL && ptr2 != NULL)
    {
        if (ptr1->data > ptr2->data)
        {
            return 1;  // First number is larger
        }
        else if (ptr1->data < ptr2->data)
        {
            return -1; // Second number is larger
        }
        ptr1 = ptr1->prev;  // Move to the previous node
        ptr2 = ptr2->prev;  // Move to the previous node
    }

    // If both lists are exhausted and they are equal up to the last digit:
    if (ptr1 == NULL && ptr2 == NULL)
        return 0;

    // If one list is shorter but equal up to the last node
    return (ptr1 == NULL) ? -1 : 1;
}