#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
int main() {

	printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
	printf("<html>");	

	char *data=getenv("QUERY_STRING");
	//data[strlen(data)] = '\n';	

	//printf("%s<br>", data);
	
	if(data == NULL) {
		printf("<head><title>Error!</title></head><body>Could not read form!</body>");
		printf("</html>");
		exit(EXIT_FAILURE);
	}
	else {

		//printf("%s<br>", data);

		char option;
		char newpass[50];
		char user[50];
		char oldpass[50];
		char type[50] = "user";
		char command[150];

		
		sscanf(data,"option=%c&newpass=%[^&]&user=%[^&]&oldpass=%s", &option, newpass, user, oldpass);

		printf("option=%c; newpass=%s; user=%s; oldpass=%s<br><br>", option, newpass, user, oldpass);
	
		if(option == 'H') {
			//fill in with patricia tomorrow		
		}
		else {
			sprintf(command,"./passweb.cgi -edit %s %s %s %s %s %s", user, oldpass, type, user, newpass, type);		
			printf("%s", command);			

			int status = system(command);

			printf("%d", WEXITSTATUS(status));
			if(0) {
					
				//printf("<head><title>Error!</title></head>");	
				//printf("<body>Could not change password.<p>");	
				//printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME<a><br />");
				//printf("<a href=\"#\" onclick\"history.go(-1); return true;\">Go Back to Menu</a>");			
				//printf("</form></body></html>");

				//exit(WEXITSTATUS(status));
			}
			else {
				//printf("<head><title>Success!</title></head>");	
				//printf("<body>Password Changed!<p>");	
				//printf("<a href=\"http://www.cs.mcgill.ca/~parauj2/homepage\">HOME<a><br />");
				//printf("<a href=\"#\" onclick\"history.go(-1); return true;\">Go Back to Menu</a>");			
				//printf("</form></body></html>");

				//exit(WEXITSTATUS(status));	
			}
		}
	}
	printf("</html>");
	exit(0);
}
