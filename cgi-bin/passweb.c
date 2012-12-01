/*
 * passweb.c
 *
 *  Created on: Nov 16, 2012
 *      Author: davidwhitney (260407818)
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "cipher.c"
//#include "menu.c"

//verify function.
int verify(char username[50], char password[50]) {

	//these strings will hold the username, password
	//and type read from password.csv
	char fuser[50];
	char fpass[50];
	char ftype[50];

	//encrypt the username and password passes as
	//arguments to the function, so they match how
	//they would be in password.csv
	
	//encrypt(username);
	//encrypt(password);

	//open a file and create a pointer that points to it.
	FILE *fp = fopen("password.csv", "r");
	if (fp == NULL ) {
		printf("Could not open file!");
		return EXIT_FAILURE;
	}

	//goes through password.csv line by line, stopping when EOF is reached.
	while (!feof(fp)) {
	
		//uses the commas as delimiters to read each line into three strings.
		fscanf(fp, "%[^,], %[^,],%s\n", fuser, fpass, ftype);

		//if the username and password passed as arguments
		//match the username and password form the current line,
		//close the file and return EXIT_SUCCESS. 
		if (strcmp(fuser, username) == 0 && strcmp(fpass, password) == 0) {
			fclose(fp);
			//printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);		
			//printf("user info matches");
			if(strcmp(ftype, "user") == 0) {
				return 0;
			}
			else {
				return 2;
			}
		}
	}
	//if end of file is reached, close the file and return EXIT_FAILURE.
	fclose(fp);
	return EXIT_FAILURE;
}

//add function.
int add(char username[50], char password[50], char type[50]) {

	//will hold the username, password, and type from the current
	//line of password.csv
	char fuser[50];
	char fpass[50];
	char ftype[50];

	//encrypt the username, password, and type.
	
	//encrypt(username);
	//encrypt(password);
	//encrypt(type);

	//open the file
	FILE *fp = fopen("password.csv", "r");
	if (fp == NULL ) {
		printf("\nCould not open file!\n");
		return EXIT_FAILURE;
	}

	//scan through the file line by line.
	while (!feof(fp)) {
		
		//uses the commas as delimiters to read each line into three strings.
		fscanf(fp, "%[^,], %[^,],%s\n", fuser, fpass, ftype);

		//if the username passed as an argument matches the username from
		//the given line of password.csv, print "username already exists."
		//close the file and return EXIT_FAILURE.		
		if (strcmp(fuser, username) == 0) {
			fclose(fp);
			printf("\nUsername already exists.\n");
			return EXIT_FAILURE;
		}
	}
	//close the file.
	fclose(fp);

	//open the file in append mode. This allows fprintf to automatically
	//go to the end of the file.
	fp = fopen("password.csv", "a");
	if (fp == NULL ) {
		printf("Could not open file!");
		return EXIT_FAILURE;
	}
	//print the username, password, and type to the file. 
	fprintf(fp, "%s, %s, %s\n", username, password, type);

	//close the file and return EXIT_SUCCESS.	
	fclose(fp);
	return EXIT_SUCCESS;

}

//delete function. basic idea is that the function will
//create a new password.csv file and copy all entries except the
//one to be deleted. It then uses the system command to remove the
//old password file and rename the new one.
int del(char username[50]) {

	//will hold the username, password, and type from the current
	//line of password.csv
	char fuser[50];
	char fpass[50];
	char ftype[50];
		
	int exists = 0;

	
	//encrypt(username);

	//open the original password.csv file in read mode.
	FILE *ofp = fopen("password.csv", "r");
	if (ofp == NULL ) {
		printf("Could not open file!");
		return EXIT_FAILURE;
	}
	//create a new password2.csv file.
	FILE *nfp = fopen("password2.csv", "w");
	if (nfp == NULL ) {
		printf("Could not open file!");
		return EXIT_FAILURE;
	}

	//scan through old password.csv file line by line
	while (!feof(ofp)) {
		fscanf(ofp, "%[^,], %[^,],%s\n", fuser, fpass, ftype);
		
		//if the username passed as an argument doesn't match
		//the current line, then copy that line into the new csv file. 		
		if (strcmp(fuser, username)) {
			fprintf(nfp, "%s, %s, %s\n", fuser, fpass, ftype);
		} else {
			//if they match, increment exists.
			exists++;
		}
	}
	//close the old and new files.
	fclose(ofp);
	fclose(nfp);
	//use system to move the new file onto the old one.
	system("mv password2.csv password.csv");
	
	//if exists is 1, then a match was found, so return EXIT_SUCCESS	
	if (exists) {
		return EXIT_SUCCESS;
	} 
	//otherwise return EXIT_FAILURE	
	else {
		return EXIT_FAILURE;
	}
}

//edit function
int edit(char username[50], char password[50], char type[50], char user2[50], char pass2[50], char type2[50]) {

	//first check that the old username and password does exist
	if (verify(username, password)==1) {
		return EXIT_FAILURE;
	}
	//then check that the new username and password does not exist
	if (!(verify(user2, pass2))==1) {
		return EXIT_FAILURE;
	}

	//the calls to verify will have encrypted the passed arguments,
	//so they must be decrypted.
	
	//decrypt(username);
	//decrypt(password);
	//decrypt(user2);
	//decrypt(pass2);

	//delete the old user name
	if (del(username)) {
		return EXIT_FAILURE;
	}
	//add the new one
	if (add(user2, pass2, type2)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//main function
int main(int argc, char *argv[]) {
	
	//proprer syntax
	char *error ="\nProper Syntax: passweb -menu -add -del -edit -verify username password type user_2 pass_2 type_2\n";

	//attempt to open the file. If you can't, then it probably means it
	//doesn't exist, so open it in write mode, which creates it if it
	//doesn't exist.
	FILE *fp = fopen("password.csv", "r");
	if (fp == NULL ) {
		fp = fopen("password.csv", "w");
	}
	fclose(fp);

	//if there are no arguments, print out error and quit.
	if(argc < 2){
		printf("Error: No arguments found.\n");
		printf("%s", error);
		exit(EXIT_FAILURE);
	}

	//if the first argument isn't a switch, print out error and quit.
	if(*argv[1] != '-'){
		printf("Error: Switch must be first argument\n");
		printf("%s", error);
		exit(EXIT_FAILURE);
	}
	
	//if first argument is menu, go to menu. 
	if (strcmp(argv[1], "-menu") == 0) {
		//menu();
		exit(EXIT_FAILURE);
	}

	//first argument is add 
	else if (strcmp(argv[1], "-add") == 0) {
		
		//if there are less than 5 arguments, print error and quit.
		if (argc < 5) {
			printf("\nError: Not enough arguments.\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		}
		//if the second argument starts with a '-', then it is a switch,
		//so print an error message and quit.
		if (*argv[2] == '-') {
			printf("\nError: cannot have two switches\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		} else {
			//add the given user
			if (add(argv[2], argv[3], argv[4])) {
				printf("Could not add user.\n");
				exit(EXIT_FAILURE);
			} else {
				printf("User added.\n");
				exit(EXIT_SUCCESS);
			}
		}
	}

	else if (strcmp(argv[1], "-del") == 0) {

		//if there are less than 3 arguments, print error and quit.
		if (argc < 3) {
			printf("\nError: Not enough arguments.\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		}
		//if the second argument starts with a '-', then it is a switch,
		//so print an error message and quit.
		if (*argv[2] == '-') {
			printf("\nError: cannot have two switches\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		} else {
			//delete the given user
			if (del(argv[2])) {
				printf("Could not remove user.\n");
				exit(EXIT_FAILURE);
			} else {
				printf("User removed.\n");
				exit(EXIT_SUCCESS);
			}
		}
	}

	else if (strcmp(argv[1], "-edit") == 0) {
		
		//if there are less than 8 arguments, print error and quit.		
		if (argc < 8) {
			printf("\nError: Not enough arguments.\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		}
		//if the second argument starts with a '-', then it is a switch,
		//so print an error message and quit.
		if (*argv[2] == '-') {
			printf("\nError: cannot have two switches\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		} else {
			//edit the given user info
			if (edit(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7])) {
				printf("Could not edit information.\n");
				exit(EXIT_FAILURE);
			} else {
				printf("Information edited.\n");
				exit(EXIT_SUCCESS);
			}
		}
	}

	else if (strcmp(argv[1], "-verify") == 0) {
		
		//if there are less than 4 arguments, print error and quit.
		if (argc < 4) {
			printf("\nError: Not enough arguments.\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		}
		//if the second argument starts with a '-', then it is a switch,
		//so print an error message and quit.
		if (*argv[2] == '-') {
			printf("\nError: cannot have two switches\n");
			printf("%s\n", error);
			exit(EXIT_FAILURE);
		} else {
			//verify the given user and password
			int ver = verify(argv[2], argv[3]);	
			//printf("ver = %d", ver);
			exit(ver);
		}
	}
	//if none of the above if statements are true, then the first argument
	//starts with a '-' but isn't any of the allowed switches. Most likely
	//a typo.
	else {
		printf("Must enter a proper switch as first argument");
		printf("%s", error);
		exit(EXIT_FAILURE);
	}
}

