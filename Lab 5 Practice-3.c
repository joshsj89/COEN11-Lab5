/*
*****************************************************************
*
*       Lab 5   Phone Book      Linked List
*       COEN 11 -- Fall 2021
*
*****************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE struct contact

/*
*****************************************************************
*
*       node implementation
*
*****************************************************************
*/

struct contact //Node of the linked list
{
    char name[20];
    char number[20];
    NODE *next;
};

/*
*****************************************************************
*
*       global variables
*
*****************************************************************
*/

int counter = 0; //global variable; indicataes position in array

NODE *head; //Pointer to the head node of the linked list

/*
*****************************************************************
*
*       function declarations
*
*****************************************************************
*/

void insert(); //Function declaration of Insert
void delete(); //Function declaration of Delete
void show(); //Function declaration of Show

/*
*****************************************************************
*
*       main
*
*****************************************************************
*/

int main(void)
{

    head = NULL; //Creates empty linked list
    
    int command;
    int boolean = 1;

    while(boolean)
    {
        printf("Options: 1. ADD PEOPLE\t 2. DELETE PEOPLE\t 3. SHOW\t 4. QUIT\nEnter Number: ");
        scanf("%d", &command); //User inputs 1-4

        switch (command)
        {
            case 1: //Insert
                insert();
                break;
            case 2: //Delete
                delete();
                break;
            case 3: //Show
                show();
                break;
            case 4: //Quit
                boolean = 0;
                break;
            default: //If any number other than 1-4 is inputted
                printf("Not a valid option. Try again.\n");
                break;
        }
    }

    free(head);
}

/*
*****************************************************************
*
*       functions implementation
*
*****************************************************************
*/

void characterInsert(char newName[20], char newNumber[20])
{
    NODE *temp, *prev, *new_node;

    if (((temp = (NODE *)malloc(sizeof(NODE))) == NULL) || ((prev = (NODE *)malloc(sizeof(NODE))) == NULL) || ((new_node = (NODE *)malloc(sizeof(NODE))) == NULL))
    {//Allocate pointers
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }

    temp = head;

    strcpy(new_node->name, newName);
    strcpy(new_node->number, newNumber);
    

    if (head == NULL || strcmp(temp->name, new_node->name) > 0) //If the list is empty or the inputted name comes before the first name on the list
    {
        new_node->next = head; //Makes the new node point to the first on the list
        head = new_node; //Makes the new node the head
        return;
    }
    
    while (temp->next != NULL && (strcmp(temp->name, new_node->name) < 0)) //Continues to the next node when the inputted name comes after the first name on list and is not the last node
    {
            prev = temp;
            temp = temp->next;
    }
    
    if (temp->next == NULL && (strcmp(temp->name, new_node->name) < 0)) //Continues to the next node when the inputted name comes after the first name on list but is also the last node
    {
        new_node->next = temp->next;
        temp->next = new_node;
        return;
    }
    
    if (strcmp(temp->name, new_node->name) > 0) //If the inputted name comes before the name being checked
    {
        prev->next = new_node;
        new_node->next = temp;
        return;
    }
    
    if (temp != NULL && (strcmp(newName, temp->name) == 0)) //If the inputted name is already on the list
    {
        printf("Sorry, this name and/or number is already in the phonebook.\n");
        return;
    }
}

void insert() //Insert function
{
    char newName[20];
    printf("Type the name to add: ");
    scanf("%s", newName); //Inputted name
    
    char newNumber[20];
    printf("Type the number to add for %s: ", newName);
    scanf("%s", newNumber); //Inputted number
    
    characterInsert(newName, newNumber);
}

void characterDelete(char inputtedName[20]) //Checks if name is in the phonebook before deleting
{
    NODE *temp = head; 
    NODE *prev;

    if (head == NULL) //If the list is empty
    {
        printf("The list is empty.\n");
        return;
    }
    
    if (strcmp(temp->name, inputtedName) == 0) //When the name to be deleted is in the head node
    {
        head = temp->next;
        return;
    }

    while (temp != NULL && (strcmp(temp->name, inputtedName) != 0)) //Continues to the next node until a name matches or until the end of the list
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) //If the end of the list is reached without finding a name match
    {
        printf("Sorry, the name you want to delete is not in the phonebook.\n");
        return;
    }
    
    printf("%s has been deleted.\n", temp->name);
    prev->next = temp->next; //Makes the node before the deleted one point to the node following the deleted one

    free(temp);
}

void delete() //Delete function
{
    char deletedName[20];
    printf("Enter the name you want to delete: ");
    scanf("%s", deletedName); //User inputs the name that is to be deleted

    characterDelete(deletedName);
}

void show() //Show function
{
    NODE *n;

    if (head == NULL)
    {
        printf("The list is empty.\n");
    }
    
    n = head;

    while (n != NULL) //While node is not null
    {
        printf("%s\t%s\n", n->name, n->number); //Prints the name and number of one node
        n = n->next; //Contiues to the next node
    }
}