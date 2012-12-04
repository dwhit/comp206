#include<string.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	printf("%s%c%c\n","Content-Type:text/html;charset= iso-8859-1",13,10);
	int n = atoi(getenv("CONTENT_LENGTH"));
	int x = 0;
	int i = 8; //8 for each character in username= (where u is 0 and = is 8)
	char inputArray[n];
	
	//initialize array to \0
	for(x=0;x<n;x++)
	{
		inputArray[x]='\0';
	}


	fgets(inputArray, n+1, stdin);


	//this if/while loop determines the number of character in username
	x=i+1;
	int u;
	//if nothing inputed for username make array size 0;
	if(inputArray[x] == '&' && inputArray[x+1] =='p')
	{	
		u=0;
	}
	else
	{

		while(inputArray[x] != '&' && inputArray[x+1] != 'p')
			{
				x++;
			}

		u=x-i-1;
	}
	printf("<br />");
	char username[u];
	//size of password	
	int y;

	y=n-u-19;
	
	char password[y];
 	if(u==0 || y==0)
	{
		printf("<html><head><title>Login Error!</title></head><body bgcolor=\"red\">");		
		printf("<font face=\"Helvetica\" color=\"Black\">MUST ENTER A USERNAME AND PASSWORD</font>");
		printf("<br/><br/><form><input type=\"button\" value =\"Back to Login \" onClick=\"history.go(-1);return true;\"></form><br>");
		printf("<form action=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\"><input value=\"Homepage\" type=\"submit\"></form></font></body></html>");
		exit(EXIT_FAILURE);
	}
	sscanf(inputArray,"username=%[^&]&password=%s",username,password);
	verify(&username, &password);
	return 0;
}

int verify(char *user, char *pass)
{	
	char u[strlen(user)];
	char p[strlen(pass)];
	char t[10];
 	FILE *pFile;
	char SYS[7]="SYSTEM";
	char USE[5]="USER";

	pFile =  fopen("Members.csv","r");
	if(pFile==NULL)
	{
		perror("couldn't open Members.csv");
		return EXIT_FAILURE;
	}
	else
	{
		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,], %[^,],%s\n", u, p, t);	
			if(strcmp(user,u)==0 && strcmp(pass,p)==0){
				fclose(pFile);
				if(!strcmp(t,USE) || !strcmp(t,SYS))
				{
					return(menu(&t, &u, &p));
				}
				else 
				{
					printf("<br /> undefined user type<br/>");
					return EXIT_FAILURE;
				}

				return EXIT_SUCCESS;
			}
		}
	}
	fclose(pFile);	
	printf("<html><head><title>Login Error!</title></head><body bgcolor=\"red\">");	
	printf("<font face=\"Helvetica\" color=\"Black\">INCORRECT PASSWORD OR USERNAME</font>");
	printf("<br/><br/><form><input type=\"button\" value =\"Back to Login \" onClick=\"history.go(-1);return true;\"></form><br>");
	printf("<form action=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\"><input value=\"Homepage\" type=\"submit\"></form></font></body></html>");
	return EXIT_FAILURE;
	
}

int menu(char *type, char *user, char *password)
{

	char USER[5]="USER";
	char SYS[7]="SYSTEM";
	if(strcmp(type,USER)==0)
	{
		printf("<html><head><title>User Menu</title></head>");
		printf("<body bgcolor=\"6699CC\"><font face=\"Helvetica\">Welcome to the user prefrences page for Python Pearls ++.<p>");
		printf("<form name=\"input\" action=\"menu.cgi\" method=\"get\">");
		printf("<input type=\"hidden\" name=\"type\" value=\"USER\">");			
		printf("<input type=\"hidden\" name=\"user\" value=\"%s\">", user);
 		printf("<input type=\"hidden\" name=\"oldpass\" value=\"%s\">", password);	
		printf("<input type=\"radio\" name=\"option\" value=\"H\">View Purchase History.<br>");		
		printf("<input type=\"radio\" name=\"option\" value=\"C\">Change Password.<br>");
		printf("<input type=\"password\" name=\"newpass\"><br>");
		printf("<input type=\"submit\" value=\"Submit\"></form><br><br>");
		printf("<form action=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\"><input value=\"Homepage\" type=\"submit\"></form></font></body></html>");
		return EXIT_SUCCESS;
	}

	else if(!strcmp(type,SYS))
	{
		printf("<html><head><title>SYSTEM MENU</title></head><body bgcolor=\"6699CC\"><font face=\"Helvetica\"><center>Welcome to the SYSTEM MENU<br/><br/>Usage: You may only select one option: ADD, DEL, EDIT, VERIFY, or INVENTORY. Only fill in text boxes relavent to you selection.<br/><br/>");
		printf("<form name=\"input\" action=\"menu.cgi\" method=\"get\">");
		printf("<input type=\"hidden\" name=\"type\" value=\"SYSTEM\">");
		printf("<input type=\"radio\" name=\"opt\" value=\"a\" >ADD<br />");
		printf("Username<input type=\"text\"  name=\"user\">");
		printf("Password<input type=\"text\"  name=\"pass\">");
		printf("Type<input type=\"text\" name=\"type\">");
		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"d\">DEL<br />");
		printf("Username<input type=\"text\" name=\"user\">");
		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"e\">EDIT<br />");
		printf("Old Username<input type=\"text\" name=\"Ouser\">");
		printf("Old Password<input type=\"text\" name=\"Opass\">");
		printf("Old Type<input type=\"text\" name=\"Otype\">");
		printf("<br />New Username<input type=\"text\" name=\"Nuser\">");
		printf("New Password<input type=\"text\" name=\"Npass\">");
		printf("New Type<input type=\"text\" name=\"Ntype\">");
		printf("<br /><br/><input type=\"radio\" name=\"opt\" value=\"v\">VERIFY<br />");
		printf("Username<input type=\"text\" name=\"user\">");
		printf("Password<input type=\"text\" name=\"pass\">");
		printf("<br /><br /><input type=\"radio\" name=\"opt\" value=\"i\">INVENTORY<br />");
		printf("<input type=\"submit\" value=\"Submit\"></form>");
	
		printf("<form action=\"http://www.cs.mcgill.ca/~dwhitn/pythonpearlsplusplus.html\"><input value=\"Homepage\" type=\"submit\"></form></center></font></body></html>");
		



		return EXIT_SUCCESS;
		
	}
	else
	{
		perror("<br />ERROR IN DETECTING USER TYPE<br />");
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}
