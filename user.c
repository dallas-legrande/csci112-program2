#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
 * Author: Dallas LeGrande
 * CSCI112 program2 assignment
 * Date: April 16, 2018
 * file to read in the grocery list binary file. Then has a user interface for: adding additional items to the list, printing how many items are in a category, and printing the whole list
 * grocery list has a maximum number of items of 100
 */


typedef struct { //structure for holding grocery list items
        char name[20];
        int cost;
        int aisle;
        char category;
} masterlist_t;

//method for adding an item
void add_item(masterlist_t *ml, int num)
    {
	char trash;//character holder to clear the buffer
	char nombre[20]; //temp variable for read in name
	int price; //temp variable for read in cost
	int loc; //temp variable for read in loc
	char cat; //temp variable for read in category
	printf("Enter the name of the item to add (all one word, 20 characters MAX): ");
	scanf("%s", &nombre[0]); //reads in from the user
	strcpy(ml[num].name, nombre);//copies the name into the array
	printf("Enter the cost (in cents as a whole number) of the item: ");
	scanf("%d", &price);//reads in from the user
	ml[num].cost = price; //copies the price into the array
	printf("Enter the aisle number of the item: ");
	scanf("%d", &loc); //reads in the aisle number
	ml[num].aisle = loc; //copies the aisle number into the array
	printf("Enter the category for the item (M for Meats, P for Produce, D for Dairy, C for Canned Foods): ");
	scanf(" %c%c", &cat, &trash);//reads in the category from the user and the end of line to clear the buffer
	ml[num].category = cat;//copies the category to the array
    }

//method to count the number of items in a category
void num_items(masterlist_t ml[], int size)
    {
	char cat; //holds the value of the category to be checked
	char trash;
        int count = 0;
	int j;
	printf("Enter the letter of the category you want to check (M for Meats, P for Produce, D for Dairy, C for Canned Foods): ");
	scanf(" %c%c", &cat, &trash); //gets the character from the buffer and clears the buffer
        for(j = 0; j < size; j++) //goes through the list and prints anything that is in the category
            {
                if(ml[j].category == cat)//if the category matches the users request, count it
                    {
			count++;
                    } //end of if
            }//end of for loop
        if(cat == 'C')//if the category chosen is canned goods print this
           {
		printf("There are %d items in the Canned Goods category\n", count);
           } //end of if
        if(cat == 'D')//if the category chosen is dairy print this
           {
		printf("There are %d items in the Dairy category\n", count);
           }//end of if
        if(cat == 'M')//if the category chosen is meat print this
           {
		printf("There are %d items in the Meat category\n", count);
           }//end of if
        if(cat == 'P')//if the category chosen is produce print this
	   {
		printf("There are %d items in the Produce category\n", count);
	   }//end of if
    }//end of method

//method to print everything in the list
void list_items(masterlist_t a[], int num_items)
    {
	char trash; //variable to clear the buffer
        int i;
        printf("Canned Goods\n");//prints the category name
        for(i = 0; i < num_items; i++) //goes through the list and prints anything that is in the category
            {
                if(a[i].category == 'C')
                    {
                        printf("%s, price: %d cents, Aisle: %d\n", a[i].name, a[i].cost, a[i].aisle);
                    } //end of if
            }//end of for loop
        printf("\n");
        printf("Dairy\n"); //prints the category name
        for(i = 0; i < num_items; i++) //goes through the list and prints anything that is in the category
            {
                if(a[i].category == 'D')
                    {
                        printf("%s, price: %d cents, Aisle: %d\n", a[i].name, a[i].cost, a[i].aisle);
                    }//end of if
            }//end of for loop
        printf("\n");
        printf("Meats\n");//prints the category name
        for(i = 0; i < num_items; i++)//goes through the list and prints anything that is in the category
            {
                if(a[i].category == 'M')
                    {
                        printf("%s, price: %d cents, Aisle: %d\n", a[i].name, a[i].cost, a[i].aisle);
                    }//end of if
            }//end of for loop
        printf("\n");
	printf("Produce\n");//prints the category name
        for(i = 0; i < num_items; i++)//goes through the list and prints anything that is in the category
            {
                if(a[i].category == 'P')
                    {
                        printf("%s, price: %d cents, Aisle: %d\n", a[i].name, a[i].cost, a[i].aisle);
                    }//end of if
            }//end of for loop
	scanf("%c", &trash);//clear the buffer before returning to main menu
    }//end of method

int main(int argc, char** argv)
    {
	masterlist_t ml[100];
	FILE *input; //file to be read from
	input = fopen("output.bin", "rb"); //opens the file to be read and sets the pointer to the file
	if(input == NULL)//if the file is not there print an error message
	    {
		fprintf(stderr, "ERROR: Could not find input file\n");
		return(1);
	    }
	int z; //integer for tracking the end of file marker
	int items = 0;
	while(fscanf(input, "%d", &z) == 0)
	    {
		fread(&ml[items], sizeof(masterlist_t), 1, input);
		items++;
	    }
	fclose(input);
	items--;
	char c = c;
	while(c != 'X')//while the user has not selected to exit keep bringing up the menu
	    {
		
		printf("\nSelect an Option (A-add item, N-number of items in a category, L-listall items, X-exit program) ");
		scanf("%c", &c);//read the input from the user. Two statements per category to take care of capital or not capital letters.
		switch(c){
		    case 'A': //if capital A is entered add an item
			add_item(ml,items);		
			items++;
			break;
		    case 'N':
			num_items(ml, items);
			break;
		    case 'L':
			list_items(ml, items);
			break;
		    case 'X':
			c = 'X';
			break;
		    case 'a': //if lower case a is entered add an item
			add_item(ml,items);
			items++;
			break;
		    case 'n':
			num_items(ml, items);
			break;
		    case 'l':
			list_items(ml, items);
			break;
		    case 'x':
			c = 'X';
			break;
		    default:
			printf("That is not a valid choice. Try again\n");
		}
	    }//end of while loop
	return(0);
    }
