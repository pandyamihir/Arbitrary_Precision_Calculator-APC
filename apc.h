/*****************************************************************************************************
*Name       : Mihir Pandya (24012_008)
*Project    : Arbitrary Precision Calculator (APC)
*Title      : header file
*Description	: This file contain libraries, structure function and function prototype declaration.
******************************************************************************************************/ 

#ifndef APC_H
#define APC_H

// Standard libraries used for input/output, string manipulation, memory allocation, and character handling
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Defining constants for success and failure return values
#define SUCCESS 0
#define FAILURE -1

#define bool int
#define true 1
#define false 0

// Typedef for data type used in the doubly linked list
typedef int data_t;  // 'data_t' is a type alias for 'int', representing the type of data stored in each node

// Doubly Linked List Node structure definition
typedef struct node
{
    struct node *prev;   // Pointer to the previous node
    data_t data;         // Data stored in the node (of type 'data_t', which is an int)
    struct node *next;   // Pointer to the next node
} Dlist;  // 'Dlist' is a typedef for the 'node' struct, representing a doubly linked list node

// Function prototypes declared here (to be defined in the corresponding C file)

// Function to read input and validate command-line arguments
int read_and_validation(int argc, char *argv[]);

// Function to check if a given operand is valid (typically checks if it's a number or valid operator)
int is_valid_operand(char *operand);

// Function to convert a string representation of a number into a doubly linked list
void string_to_dlist(const char *str, Dlist **head, Dlist **tail);

// Function to check if a given operand is valid (typically checks if it's a number or valid operator)
void sign_validation(char *argv[]);

// Function to perform addition of two doubly linked lists representing numbers
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Function to perform subtraction of two doubly linked lists representing numbers
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Function to remove leading zeros from the given number (represented as a doubly linked list)
int removeLeadingZeros(Dlist **head, Dlist **tail);

// Function to compare two numbers represented as doubly linked lists
int compare(Dlist *ptr1, Dlist *ptr2);

// Function to perform multiplication of two doubly linked lists representing numbers
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

// Function to perform division of two doubly linked lists representing numbers
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);

/* Helper function to convert a linked list (digits) into a number */
long long get_number_from_list(Dlist *head, Dlist *tail);

/* Function to remove leading zeros from the result list */
void remove_leading_zeros(Dlist **head);

#endif  // End of the header guard to prevent multiple inclusions