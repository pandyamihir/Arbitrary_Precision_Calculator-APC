/*****************************************************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title			: Addition
*Description		: This function performs Addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
********************************************************************************************************************************/
#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    Dlist *ptr1 = *tail1, *ptr2 = *tail2, *result = NULL;
    int carry = 0, sum = 0;

    // Traverse both lists from the tail (least significant digit)
    while (ptr1 != NULL || ptr2 != NULL || carry != 0)
    {
        // Get the current digits, or 0 if the list is shorter
        int digit1 = (ptr1 != NULL) ? ptr1 -> data : 0;
        int digit2 = (ptr2 != NULL) ? ptr2 -> data : 0;

        // Calculate sum and carry
        sum = digit1 + digit2 + carry;
        carry = sum / 10;  // Carry will be either 0 or 1
        sum = sum % 10;    // Only store the last digit

        // Create a new node for the result (insert at the head of the result list)
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));

        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE;
        }

        new_node -> data = sum;
        new_node -> next = result;
        new_node -> prev = NULL;

        // Update the result pointer to the new node
        if (result != NULL)
        {
            result -> prev = new_node;
        }

        result = new_node;

        // Move to the next nodes in the original lists
        if (ptr1 != NULL)
        {
            ptr1 = ptr1 -> prev;
        }
        
        if (ptr2 != NULL)
        {
            ptr2 = ptr2 -> prev;
        }
    }

    *headR = result; // Now `result` is the head of the result list

    return SUCCESS;
}