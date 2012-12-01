#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main() {	

	char *data=getenv("QUERY_STRING");
	
	if(data == NULL) {
		printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
		printf("<html>");		
		printf("<head><title>Error!</title></head><body>Could not read form!</body>");
		printf("</html>");
		exit(EXIT_FAILURE);
	}
	else {

		char option;
		char newpass[50];
		char user[50];
		char oldpass[50];
		char type[50] = "user";
		char command[150];

		
		sscanf(data,"user=%[^&]&oldpass=%[^&]&option=%c&newpass=%s", user, oldpass, &option, newpass);
		
		if(option == 'H') {
			printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
			printf("<html>");	
			printf("<head><title>Purchases</title></head>");	
			printf("<body>Here is your purchase history.<br><br>");	

			FILE *fp = fopen("log.csv", "r");
			if (fp == NULL ) {
				printf("Could not open file!<br><br>");
				return EXIT_FAILURE;
			}			
			char username[50];
			char itemname[50];
			int itemcode;
			int quantity;
			float price;
			
			//printf("User from query_string = ^%s^ <br><br>", user);
			
			while(!feof(fp)){
				fscanf(fp, "%[^,], %[^,], %d, %d, %f\n", username, itemname, &itemcode, &quantity, &price);				
				if(strcmp(user, username) == 0) {
					printf("You purchased %d unit(s) of item %s (itemnumber: %d), at $%.2f each, for a total of $%.2f<br><br>", quantity, itemname, itemcode, (float) price/quantity, price); 
				}			
			}
			fclose(fp);			




			printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
			printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");
			printf("</body></html>");
			return(0);
		}
		else {
			sprintf(command,"./passweb.cgi -edit %s %s %s %s %s %s", user, oldpass, type, user, newpass, type);					

			int status = system(command);

			if(WEXITSTATUS(status)) {
				printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
				printf("<html>");	
				printf("<head><title>Error!</title></head>");	
				printf("<body>Must select new password.<p>");

				//printf("User from query_string = ^%s^ <br><br>", user);
	
				printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
				printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");		
				printf("</body></html>");

				return(EXIT_FAILURE);
			}
			else {
				printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
				printf("<html>");
				printf("<head><title>Success!</title></head>");	
				printf("<body>Password Changed!<p>");	

				//printf("User from query_string = ^%s^ <br><br>", user);
		
				printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME</a><br>");
				printf("<form><input type=\"button\" value =\"Back to menu\" onClick=\"history.go(-1);return true;\"></form><br>");			
				printf("</body></html>");

				return(EXIT_SUCCESS);	
			}
		}
	}
}
