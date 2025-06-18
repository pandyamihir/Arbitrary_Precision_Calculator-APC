/*************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title		: main function(Driver function) 
*Description	: This function is used as the driver function for all the functions 
**************************************************************************************/

#include "apc.h"
int flag = 0;

int main(int argc, char *argv[])
{
    /* Declare the pointers */
    Dlist *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL;
    char operator = 0;

    /* Validate the input arguments */
    if (read_and_validation(argc, argv) != 0)
    {
        return -1;
    }

    // Convert operand1 and operand2 from strings to doubly linked lists
    string_to_dlist(argv[1], &head1, &tail1);
    string_to_dlist(argv[3], &head2, &tail2);
    
    /* Validate the operator and perform the operation */
    switch (*argv[2])
    {
        case '+':
            /* Call the function to perform the addition operation */
            if (addition(&head1, &tail1, &head2, &tail2, &headR) == SUCCESS)
            {
                // Print the result after addition
                printf("Result of Addition : ");
                
                Dlist *temp = headR;
                while (temp != NULL)
                {
                    printf("%d", temp->data);
                    temp = temp -> next;
                }
                printf("\n");
            }
            else
            {
                printf("Addition failed.\n");
            }
        break;

        case '-':    
            /* Call the function to perform the subtraction operation */
            if (subtraction(&head1, &tail1, &head2, &tail2, &headR) == SUCCESS)
            {
                // Print the result after subtraction
                if(flag == 1)
                {
                    printf("Result of Subtraction : -");
                }
                else
                {
                    printf("Result of subtraction : ");
                }

                Dlist *temp = headR;
                
                while (temp != NULL)
                {
                    printf("%d", temp->data);
                    temp = temp -> next;
                }
                printf("\n");
            }
            else
            {
                printf("Subtraction failed.\n");
            }
        break;

        case 'x':
            // Call the function to perform the multiplication operation
            if (multiplication(&head1, &tail1, &head2, &tail2, &headR) == SUCCESS)
            {
                // Print the result after multiplication
                printf("Result of Multiplication : ");
                
                Dlist *temp = headR;
                while (temp != NULL)
                {
                    printf("%d", temp->data);  // Print each digit of the result
                    temp = temp->next;  // Move to the next node
                }
                printf("\n");  // New line after printing the result
            }
            else
            {
                printf("Multiplication failed.\n");
            }
            break;

        case '/':
            /* Call the function to perform the division operation */
            if (division(&head1, &tail1, &head2, &tail2, &headR) == SUCCESS)
            {
                // Print the result after divion
                printf("Result of Division : ");
                Dlist *current = headR;

                while (current != NULL)
                {
                    printf("%d", current->data);
                    current = current->next;
                }
                printf("\n");
            }
            else
            {
                printf("Division failed.\n");
            }
        break;

        default:
            printf("Invalid Input :- Try again...\n");
    }
    return 0;
}

/* Function to validate command line arguments */
int read_and_validation(int argc, char *argv[])
{
    char word[50];
    int count = 0;
    float len;

    // Check if arguments are provided
    if (argc == 1)
    {
        printf("FAILURE: No arguments provided.\n");
        return -1;
    }

    // Check if three arguments are provided (operand1 operator operand2)
    if (argc != 4)
    {
        printf("FAILURE: Incorrect number of arguments.\nExpected 3 arguments.\n");
        return -1;
    }

    if(argc == 4)
    {
        // Validate first operand (argv[1])
        strcpy(word, argv[1]);
        len = strlen(word);

        if (!is_valid_operand(word))  // Check if the operand is valid
        {
            printf("Argument 1 is not a valid operand.\n");
            return -1;
        }

        // Validate operator (argv[2])
        if (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '/')
        {
            printf("Argument 2 is not a valid operator.\n");
            return -1;
        }

        // Validate second operand (argv[3])
        strcpy(word, argv[3]);
        if (!is_valid_operand(word))  // Check if the operand is valid
        {
            printf("Argument 3 is not a valid operand.\n");
            return -1;
        }
    }

    return 0;  // Success
}

/* Helper function to check if a string represents a valid operand (integer or float) */
int is_valid_operand(char *operand)
{
    int has_digit = 0, has_decimal = 0, has_sign = 0;

    for (int i = 0; operand[i] != '\0'; i++)
    {
        if (isdigit(operand[i]))  // Check if it's a digit
        {
            has_digit = 1;
        }
        else if (operand[i] == '.' && !has_decimal)  // Decimal point allowed only once
        {
            has_decimal = 1;
        }
        else if ((operand[i] == '+' || operand[i] == '-') && i == 0)  // Sign allowed only at the start
        {
            has_sign = 1;
        }
        else
        {
            return 0;  // Invalid character
        }
    }

    return has_digit;  // Return true if there's at least one digit
}

void string_to_dlist(const char *str, Dlist **head, Dlist **tail)
{
    *head = NULL;
    *tail = NULL;

    // Loop through each character of the string
    for (int i = 0; str[i] != '\0'; i++)
    {
        Dlist *new_node = (Dlist *)malloc(sizeof(Dlist));
        if (new_node == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }

        new_node->data = str[i] - '0';  // Convert char to integer
        new_node->next = NULL;
        new_node->prev = *tail;

        if (*tail != NULL)
        {
            (*tail)->next = new_node;
        }

        *tail = new_node;
        if (*head == NULL)
        {
            *head = new_node;
        }
    }
}