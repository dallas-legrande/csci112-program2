#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Author: Dallas LeGrande
 * CSCI112 program2 assignment
 * Date: April 16, 2018
 * file to read in the grocery list text file and send it to a binary file
 * grocery list has a maximum number of items of 100
 */


typedef struct { //structure for holding grocery list items
        char name[20];
        int cost;
        int aisle;
        char category;
} masterlist_t;

int main(int argc, char** argv)
    {
	masterlist_t ml [100]; //structure arrray for holding all the grocery items
	char str[50]; //string being read in
	char str_copy[50]; //copy of read in string for tokenizing
	int item_counter = 0; //keeps track of the number of items
	FILE *input; //file to be read from
	FILE *output; //file to write to 
	char *name; //name from token
	int num1; //number from token
	int num2;
	char a; //character from token

	input = fopen("grocery.txt", "r"); //opens the file to be read and sets the pointer to the file
	if(input == NULL)//if the file is not there print an error message
	    {
		fprintf(stderr, "ERROR: Could not find input file\n");
		return(1);
	    }
	int z; //integer for tracking the end of file marker
	while(fscanf(input, "%d", &z) == 0)
	    {
		fgets(str,80,input); //get the line of the file
		strcpy(str_copy, str);//copy that line to a new string
		name = strtok(str_copy, " ");//tokenize the new string to get the name of the grocery item
		strcpy(ml[item_counter].name, name);//copy the name into the structure
		num1 = atoi(strtok(NULL, " "));//get the cost of the item from the tokenized string
		ml[item_counter].cost = num1;//set the cost in the structure
		num2 = atoi(strtok(NULL, " "));//get the aisle number from the tokenized string
		ml[item_counter].aisle = num2;//set the aisle in the structure
		a = *strtok(NULL, " ");// get the category of the item from the tokenized string
		ml[item_counter].category = a; //set the category in the structure
		item_counter++; //increment the number of items in the list
	    }
	fclose(input); //close the file
	output = fopen("output.bin", "wb"); //opens the binary file to write to it
	fwrite(&ml, sizeof(masterlist_t), item_counter+1, output); //writes the binary file and adds the EOF
	fclose(output);//closes the binary file
	return(0);    
}
