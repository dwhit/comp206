#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include "passweb.c"
//#include "menu.c"
#define MAXLEN 800
#define EXTRA 5
#define MAXINPUT MAXLEN+EXTRA+2
#define DATAFILE "data.txt"


char username[100];
char password[100];
char type[100];
char array[100];
char *check;
char buffer[500];

char c;
int a=0;
//	int n= atoi(getenv("CONTENT_LENGTH"));

//	fgets(username, n, stdin);
//	printf("%s\n", username);

//THIS METHOD WILL OPEN THE MEMBERS.CSV AND LOOK FOR MATCHING USERNAME AND PASSWORD.
//IF IT IS FOUND THEN IT WILL GRAB THE CURRENT RECORD TYPE AND STORE IT IN THE ARRAY type[50]

int openMembers(char username[100], char password[100]){
        FILE *ptr = fopen("Members.csv", "rt");
                if(ptr == NULL){
                        //return EXIT_FAILURE;
                }
                fgets(array, 50, ptr);
                        while(!feof(ptr)){
                                check = strtok(array, ", ");
                                        while(check != NULL){
                                                //printf("%s\n", check);
                                                if(strcmp(check, username)==0){
                                                        //printf("USERNAME EXIST\n");
                                                        check = strtok(NULL, ", ");
                                                        if (strcmp(check, password)==0){
                                                                check = strtok(NULL, ", ");
                                                                strcpy(type, check);

									//IF THE TYPE IS USER BY LOOKING AT THE 1ST CHARACTER
                                                                        if(type[0]=='u')
                                                                                return 1;
									//IF THE TYPE IS SYSTEM
                                                                        else{
                                                                                return 2;
                                                                        }

                                                                        //printf("PASSWORD EXITS\n");
                                                                        //encrypt("password.csv");
                                                                        //system("cp temp.csv password.csv");
                                                                        //system("rm temp.csv");
                                                                        printf("Congratulations, you've made it!\n");
                                                                        //return EXIT_SUCCESS;
                                                        }
                                                }
                                                check = strtok(NULL, ", ");
                                        }
                                        fgets(array, 50, ptr);
                                }
                        fclose(ptr);
                        printf("The user is not in the list of Members\n");
			//IF THE USERNAME AND PASSWORD IS NOT IN THE MEMBERS.CSV FILE
                        return 0;
}






int compare(char *string, char buffer[])
{

	int count=0, i, j, matchCount;
	for(i=0; i<strlen(buffer);i++)
	{
		if(*string == buffer[i])
		{
			for(j=0, matchCount=0;j<strlen(string) && (i+j)<strlen(buffer);j++){
				if(*(string+j) == buffer[i+j]) matchCount++;
			}
				if (matchCount == strlen(string)) count++;
		}
	}
		
	if (count == 0){
		return -1;
	}
	else{
		return count;
	}
}


void unencode(char *src, char *last, char *dest)
{
	for(; src != last; src++, dest++)
		if(*src=='+')
			*dest=' ';
		else if(*src=='%')
		{
			int code;
			if(sscanf(src+1,"%2x",&code)!=1) code = '?';
			*dest = code;
			src +=2;
		}
		else
			*dest = *src;
		*dest='\n';
		*++dest = '\0';
}

void main()
{


	char *lenstr;
	char input[MAXINPUT], data[MAXINPUT];
	long len;
	printf("Content-Type:text/html\n\n");
	printf("<html><title>LOGIN</title><body><p>hello</p></body></html>\n");
	//do the menu thing for system and user
/*
	lenstr = getenv("CONTENT_LENGTH");
	if(lenstr == NULL || sscanf(lenstr, "%ld", &len)!=1 || strlen(lenstr) > MAXLEN){
		printf("<p>Error in invocation - wrong FORM code probably.\n");
	}
	else
	{
		printf("hello");
		FILE *f;
		fgets(input, len+1, stdin);
		unencode(input+EXTRA, input+len, data);
		printf("%s", data);
		int i, j, k;
		int eqCount=0;int amCount=0;
		for(i=0; i<strlen(data); i++)
		{
			if(eqCount>0 && amCount==0)
			{
				username[j]=data[i];
				j++;
			}
			if(eqCount>0 && amCount>0)
			{
				password[k]=data[i];
				k++;
			}


			if(data[i]=='=')
			{
				eqCount++;
				
			}
			if(data[i]=='&')
			{
				amCount++;
			}
		}	
	}


		


		int result;
			result=openMembers(username, password);
			if (result==0)
		
			{

				printf("Content-Type:text/html\n\n");
	                	printf("<title>INCORRECT</title>\n");
				printf("<body><p>The username and/or password is invalid.<p>");
				printf("<a href='http://www.cs.mcgill.ca/~lchiu13/home.html/' style=\"text-decoration:none\">          HOME </a>");
				printf("<a href=\"http://www.cs.mcgill.ca/~lchiu13/login.html\" target=\"_blank\" style=\"text-decoration:none\">        LOGIN</a>");
			}
			else if(result  == 1){
				//change password radio buttons
				//see user's [urchase history (log.csv) radio button
				//home page web link

				//Written in html code in menu.c
				
				printf("Content-type: text/html\n\n");
				printf("<html></html>");
											

	
			}
			else if(result == 2){
				//radio buttons to all of passweb.c
				//radio button lists inventory.csv (without csv formatting)
				//home page web linl

				//CODE HERE WILL ONLY CALL IN MENU.C
			}
*/
}//Closes the main method



			



