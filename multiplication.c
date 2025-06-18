/***********************************************************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*************************************************************************************************************************************/
#include "apc.h"

// Function to perform multiplication of two large numbers represented as doubly linked lists
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
    // If either number is zero, the result is also zero
    if (*head1 == NULL || *head2 == NULL)
    {
        // Create a doubly linked list with a single node containing 0
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE;
        }

        new_node->data = 0;
        new_node->next = NULL;
        new_node->prev = NULL;
        *headR = *tail2 = new_node; // Set the result as 0

        return SUCCESS;
    }

    // Get the lengths of the two numbers
    int len1 = 0, len2 = 0;
    Dlist *temp = *head1;
    while (temp != NULL)
    {
        len1++;
        temp = temp->next;
    }

    temp = *head2;
    while (temp != NULL)
    {
        len2++;
        temp = temp->next;
    }

    // The maximum length of the result can be at most len1 + len2
    int result_len = len1 + len2;
    int *result = (int *)calloc(result_len, sizeof(int)); // Array to hold the result digits

    Dlist *p1 = *tail1; // Start from the least significant digit of the first number
    for (int i = 0; p1 != NULL; i++)
    {
        Dlist *p2 = *tail2; // Start from the least significant digit of the second number
        for (int j = 0; p2 != NULL; j++)
        {
            // Multiply the digits and add to the result array
            int product = p1->data * p2->data + result[i + j];
            result[i + j] = product % 10;  // Store the current digit
            result[i + j + 1] += product / 10; // Carry over the remainder to the next place value
            p2 = p2->prev;
        }
        p1 = p1->prev;
    }

    // Now, convert the result array to a doubly linked list
    *headR = NULL;
    *tail2 = NULL;
    int leading_zero = 1; // Flag to skip leading zeros
    for (int i = result_len - 1; i >= 0; i--)
    {
        // Skip leading zeros
        if (result[i] == 0 && leading_zero)
        {
            continue;
        }
        leading_zero = 0;

        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE;
        }

        new_node->data = result[i];
        new_node->next = NULL;
        new_node->prev = *tail2;

        if (*tail2 != NULL)
        {
            (*tail2)->next = new_node;
        }
        *tail2 = new_node;

        if (*headR == NULL)
        {
            *headR = new_node;
        }
    }

    // Handle the case where result is zero and skip the loop above (leading_zero will be 1)
    if (leading_zero)
    {
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return FAILURE;
        }

        new_node->data = 0;
        new_node->next = NULL;
        new_node->prev = NULL;
        *headR = *tail2 = new_node; // Result is zero
    }

    free(result); // Free the result array
    return SUCCESS;
}