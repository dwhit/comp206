#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
//#include <python.h>

//main function
int main(void) {

	//stores the command that will be passed to the system() function
	char command[150];

	//stores the status of the system() function
	int status;
	
	printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
	

	int n = atoi(getenv("CONTENT_LENGTH"));
	int x = 0;
	int i = 8; //8 for each character in username= (where u is 0 and = is 8)
	char inputArray[n];


	
	//initialize array to \0
	for(x=0;x<n;x++) {
		inputArray[x]='\0';
	}
	fgets(inputArray, n+1, stdin);
	//this if/while loop determines the number of character in username
	x=i+1;
	int u;
	//if nothing inputed for username make array size 0;
	if(inputArray[x] == '&' && inputArray[x+1] =='p') {
		u=0;
	}
	else {
		while(inputArray[x] != '&' && inputArray[x+1] != 'p') {
			x++;
		}
		u=x-i-1;
	}
	printf("<br />");
	char username[u];
	//size of password
	int y;
	y=n-u-19; //total char- (char in user)-19(8 for user 8 for pass 3 for ==&
	// printf("n=%d,y=%d,x=%d<br />",n,y,u);
	char password[y];

	// printf("chara user:%d, char passw:%d, i:%d<br />",u,y,i);

	//this part reads inputArray and puts the characters in the username
	int j = 0;
	i = 9;
	// printf("%c",inputArray[i]);

	if(inputArray[i] == '&' && inputArray[i+1] == 'p') {
		username[0]='\0';
	}
	else {
		while(inputArray[i] != '&' && inputArray[i+1] != 'p') {
			username[j] = inputArray[i];
			i++;
			j++;
		}
	}

	while(inputArray[i] != '=') {
		i++;
	}
	i++;
	j=0;

	//fill password
	if(i==n) {
		password[0]='\0';
	}
	
	else {
		while(i <= n) {
			password[j] = inputArray[i];
			i++;
			j++;
		}
	}
	
	//printf("<br /> username:^%s^<br />password:^%s^<br />", username, password);

	
	//add the username and password to a string. 
	sprintf(command,"./passweb.cgi -verify %s %s", username, password);	

	//use that string as a series of commands for the command line,
	//accessed using system().	
	status = system(command);
	//printf("wexit = %d\n",WEXITSTATUS(status));

	//if the exit status of passweb was EXIT_FAILURE (1)
	if (WEXITSTATUS(status) == 1) {
		//printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
		printf("<html><head><title>Login Error!</title></head>");	
		printf("<body>Login information incorrect! Click below to return to home.<p>");	
		printf("<a href=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\">HOME</a><br />");
		printf("</body></html>");
		exit(EXIT_FAILURE);
	} 
	
	//else the exit status must have been EXIT_SUCCESS
	else if(WEXITSTATUS(status) == 0) {
		printf("<html><head><title>User Menu</title></head>");
		printf("<body>Welcome to the user prefrences page for Python Pearls ++.<p>");
		printf("<form name=\"input\" action=\"menu.cgi\" method=\"get\">");
		printf("<input type=\"hidden\" name=\"user\" value=\"%s\">", username);
 		printf("<input type=\"hidden\" name=\"oldpass\" value=\"%s\">", password);		
		printf("<input type=\"radio\" name=\"option\" value=\"H\">View Purchase History.<br>");
		printf("<input type=\"radio\" name=\"option\" value=\"C\">Change Password: &nbsp;");
		printf("<input type=\"password\" name=\"newpass\"><br>");
		printf("<a href=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\">Return Home.</a><br>");
		printf("<input type=\"submit\" value=\"Submit\"></form></body></html>");
		exit(EXIT_SUCCESS);
	}
	else {
		
		printf("Sysop!");
		exit(2);	
	}
} 
