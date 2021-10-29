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

struct contact 
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

struct contact phonebook[10]; //People's Names and Numbers (up to 10 people) (Array of Structures)



/*
*****************************************************************
*
*       function declarations
*
*****************************************************************
*/

void insert(NODE** head_ref); //Function declaration of Insert
void delete(NODE **head_ref); //Function declaration of Delete
void show(NODE *n); //Function declaration of Show
int duplicate(char inputtedName[20], char inputtedNumber[20]); //Function declaration of Duplicate (only used inside Insert)

/*
*****************************************************************
*
*       main
*
*****************************************************************
*/

int main(void)
{

    NODE *head = NULL;
    
    int command;
    int boolean = 1;

    while(boolean)
    {
        printf("Options: 1. ADD PEOPLE\t 2. DELETE PEOPLE\t 3. SHOW\t 4. QUIT\nEnter Number: ");
        scanf("%d", &command); //User inputs 1-4

        switch (command)
        {
            case 1: //Insert
                insert(&head);
                break;
            case 2: //Delete
                delete(&head);
                break;
            case 3: //Show
                show(head);
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

int duplicate(char inputtedName[20], char inputtedNumber[20]) //Duplicate function
{
    int i;
    int boolean; //Variable to show the result of the comparison
    struct contact *p = phonebook; //Pointer to refer to the array of structures

    for (i = 0; i <= counter; ++i, ++p) //Checks all names/numbers
    { 
        if ((strcmp(p->name, inputtedName) == 0) || (strcmp(p->number, inputtedNumber)) == 0) 
        { //If the inputted name or number is the same as one already on the list
            printf("Sorry, this name and/or number is already in the phonebook.\n");
            boolean = 0;
            break;
        }
        else //If the inputted name or number is not already on the list
        {
            boolean = 1;
        }
    }

    return boolean; //returns 0 if a duplicate, and 1 if not
}

/*
void characterInsert(NODE** head_ref, char newName[20], char newNumber[20])
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    
    if (new_node == (NODE*)NULL)
    {
        printf("Memory could not be allocated.\n");
    }

    strcpy(new_node->name, newName);
    strcpy(new_node->number, newNumber);

    new_node->next = (*head_ref);
    (*head_ref) = new_node;
    
}
*/

void characterInsert(NODE** head_ref, char newName[20], char newNumber[20])
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));
    NODE *temp = *head_ref;
    NODE *prev = (NODE *)malloc(sizeof(NODE));
    
    if (new_node == (NODE*)NULL)
    {
        printf("Memory could not be allocated.\n");
    }

    while (temp != NULL && (strcmp(newName, temp->name) == -1))
    {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp != NULL && (strcmp(newName, temp->name) == 0))
    {
        printf("Sorry, this name and/or number is already in the phonebook.\n");
        return;
    }

    if (temp != NULL && (strcmp(newName, temp->name) == 1))
    {
        strcpy(new_node->name, newName);
        strcpy(new_node->number, newNumber);
        
        
        new_node->next = prev->next;
        prev->next = new_node;
    }

    if (*head_ref == NULL)
    {
        strcpy(new_node->name, newName);
        strcpy(new_node->number, newNumber);

        new_node->next = (*head_ref);
        (*head_ref) = new_node;
    }

    free(temp);
}

void insert(NODE **head_ref) //Insert function
{
    char newName[20];
    printf("Type the name to add: ");
    scanf("%s", newName); //Inputted name
    
    char newNumber[20];
    printf("Type the number to add for %s: ", newName);
    scanf("%s", newNumber); //Inputted number
    
    characterInsert(head_ref, newName, newNumber);
    /*
    if(duplicate(newName, newNumber) == 1) //Checks if the inputted name and number are duplicates
    {
        strcpy(phonebook[counter].name, newName); //Adds inputted name to counter's position
        strcpy(phonebook[counter].number, newNumber); //Adds inputted number to counter's position

        printf("Added %s with phone number %s succesfully!\n", phonebook[counter].name, phonebook[counter].number); //Lets user know input was successful

        counter++; //Increases counter to next position for further use
    }
    */
}

void characterDelete(NODE **head_ref, char inputtedName[20]) //Checks if name is in the phonebook before deleting
{
    NODE *temp = *head_ref, *prev;

    if (temp != NULL && (strcmp(temp->name, inputtedName) == 0))
    {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && (strcmp(temp->name, inputtedName) != 0))
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Sorry, the name you want to delete is not in the phonebook.\n");
        return;
    }
    prev->next = temp->next;

    free(temp);
}

void delete(NODE **head_ref) //Delete function
{
    char deletedName[20];
    printf("Enter the name you want to delete: ");
    scanf("%s", deletedName); //User inputs the name that is to be deleted

    characterDelete(head_ref, deletedName);

    /*
    if (checkDelete(deletedName) == 1) //If the name is in the phonebook, it will be deleted
    {
        counter--; //Decreases the counter
    }
    else //If name is not in phonebook
    {
        printf("Sorry, the name you want to delete is not in the phonebook.\n");
    }
    */
}

void show(NODE *n) //Show function
{
    while (n != NULL)
    {
        printf("%s\t%s\n", n->name, n->number);
        n = n->next;
    }
}