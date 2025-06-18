/****************************************************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title            : Division
*Description      : This function performs division of two given large numbers and stores the result in the resultant list.
*Prototype        : int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters : head1: Pointer to the first node of the first doubly linked list.
*                   tail1: Pointer to the last node of the first doubly linked list.
*                   head2: Pointer to the first node of the second doubly linked list (divisor).
*                   tail2: Pointer to the last node of the second doubly linked list.
*                   headR: Pointer to the first node of the resultant doubly linked list (quotient).
*Output           : Status (SUCCESS / FAILURE)
*****************************************************************************************************************************/

#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    // Check if the divisor is empty or NULL
    if (*head2 == NULL || get_number_from_list(*head2, *tail2) == 0)
    {
        printf("Error: Division by zero is not allowed!\n");
        return FAILURE;  // Return error code for division by zero
    }

    Dlist *ptr1 = *head1;  // Pointer to traverse the dividend
    Dlist *ptr2 = *head2;  // Pointer to traverse the divisor
    Dlist *result = NULL;  // Head pointer for the result list (quotient)
    Dlist *current_quotient = NULL;  // To build the result list (quotient)

    long long remainder = 0;  // Variable to store the remainder during division
    int quotient_digit = 0;   // To store the quotient digit for each division

    // Iterate through the digits of the dividend (head1)
    while (ptr1 != NULL)
    {
        // Build the current portion of the dividend by multiplying the remainder by 10
        // and adding the current digit from the dividend (ptr1->data).
        remainder = remainder * 10 + ptr1->data;

        // Perform the division if the current portion is greater than or equal to the divisor
        if (remainder >= get_number_from_list(*head2, *tail2))
        {
            quotient_digit = remainder / get_number_from_list(*head2, *tail2);  // Get the quotient for this portion
            remainder = remainder % get_number_from_list(*head2, *tail2);  // Update the remainder after division
        }
        else
        {
            quotient_digit = 0;  // If divisor is greater, the quotient for this portion is 0
        }

        // Create a new node for the quotient digit and add it to the result list
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));

        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE;  // Exit if memory allocation fails
        }

        new_node->data = quotient_digit;
        new_node->next = NULL;  // This will be the last node in the result list

        if (result == NULL)
        {
            result = new_node;  // Set the first node in the result list
        }
        else
        {
            current_quotient -> next = new_node;  // Append to the result list
        }
        current_quotient = new_node;  // Move the current pointer to the new node

        // Move to the next digit in the dividend
        ptr1 = ptr1->next;
    }

    // Set the result list to the output pointer
    *headR = result;

    // Remove leading zeros from the result list
    remove_leading_zeros(headR);

    // Return success
    return SUCCESS;
}

/* Helper function to convert a linked list (digits) into a number */
long long get_number_from_list(Dlist *head, Dlist *tail)
{
    long long number = 0;
    Dlist *temp = head;

    while (temp != NULL)
    {
        number = number * 10 + temp->data;  // Construct the number from the linked list
        temp = temp->next;
    }

    return number;
}

/* Function to remove leading zeros from the result list */
void remove_leading_zeros(Dlist **head)
{
    Dlist *temp = *head;
    
    // If the list is empty or has only one node with zero, do nothing
    if (temp == NULL) return;

    // Remove leading zeros
    while (temp != NULL && temp->data == 0)
    {
        *head = temp->next;  // Move the head pointer to the next node
        free(temp);  // Free the old node
        temp = *head;  // Move temp to the next node
    }

    // If the list becomes empty, create a node with 0
    if (*head == NULL)
    {
        *head = (Dlist *)malloc(sizeof(Dlist));
        
        if (*head == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }

        (*head)->data = 0;  // Set the single node to 0
        (*head)->next = NULL;
    }
}