/*
 * menu.c
 *
 *  Created on: Nov 16, 2012
 *      Author: davidwhitney (260407818)
 */
#include <stdio.h>
#include <string.h>

//this function clears the buffer.
void clear(void) {
	while (getchar() != '\n')
		;
}

//menu function. 
void menu() {
	char username[50];
	char password[50];
	char type[50];
	char user2[50];
	char pass2[50];
	char type2[50];
	int option = 0;

	//user inputs value that is stored in the int option. 
	//While option is not 5, this loop will continue.
	while (option != 5) {
		printf("\n");
		printf("MAIN MENU\n");
		printf("=========\n");
		printf("1. Add user\n");
		printf("2. Delete user\n");
		printf("3. Edit user info\n");
		printf("4. Verify user\n");
		printf("5. Exit\n");

		scanf("%d", &option);
		clear();
		switch (option) {
		
		//User inputs 1, which represents add. Function asks 
		//for username, password and type, and passes them to
		//the add function inside passweb.c. If passweb.c returns
		//EXIT_FAILURE (1), then an error message is printed
		//to the screen. If EXIT_SUCCESS (0) is returned, then
		// "User added." is printed to the screen.
		case 1:
			printf("You selected Add user.\n");
			printf("Please enter a username, then press enter: ");
			gets(username);
			printf("Please enter a password, then press enter: ");
			gets(password);
			printf("Please enter a type, then press enter: ");
			gets(type);
			if (add(username, password, type)) {
				printf("\nUnable to add user.\n");
			} else {
				printf("\nUser added.\n");
			}
			break;

		//User inputs 2, which represents delete. Function asks
		//for username, then passes that arguments to the delete
		//function in passweb.c. A message is desplayed describing
		//the failure or success of the delete attempt.
		case 2:
			printf("You selected Delete user.\n");
			printf("Please enter username of user to remove, then press enter: ");
			gets(username);
			if(del(username)){
				printf("\nUnable to remove user.\n");
			}
			else {
				printf("\nUser removed.\n");
			}
			break;

		//User inputs 3, which represents edit. Function asks for
		//old username, password, and type, and new username, password,
		//and type. It then passes those arguments to the edit function.
		//A message is displayed describing the sucess of the edit attempt.
		case 3:
			printf("You selected Edit user info.\n");
			printf("Please enter old username, then press enter: ");
			gets(username);
			printf("Please enter old password, then press enter: ");
			gets(password);
			printf("Please enter old type, then press enter: ");
			gets(type);
			printf("Please enter new username, then press enter: ");
			gets(user2);
			printf("Please enter new password, then press enter: ");
			gets(pass2);
			printf("Please enter new type, then press enter: ");
			gets(type2);
			if(edit(username, password, type, user2, pass2, type2)){
				printf("\nUnable to edit user info.\n");
			}
			else{
				printf("\nUser info edited.\n");
			}
			break;

		//User inputs 4, which represents verify. Function asks for
		//username and password, and passes those as arguments to the\
		//verify method. If verify returns FAILURE, "INVALID" is printed
		//to the screen. Otherwsie VALID is printed. 
		case 4:
			printf("You selected Verify.\n");
			printf("Please enter the username you wish to verify, then press enter: ");
			gets(username);
			printf("Please enter the password you wish to verify, then press enter: ");
			gets(password);
			if (verify(username, password)) {
				printf("\nINVALID\n");
			} else {
				printf("\nVALID\n");
			}
			break;
		}
	}
}
