#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

	char *data=getenv("QUEREY_STRING");

	char option;

	sscanf(data,"option=%c",&option);

	

}
