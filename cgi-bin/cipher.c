/*
 * cipher.c for q1
 *
 *  Created on: Nov 16, 2012
 *      Author: davidwhitney (260407818)
 */

#include <stdio.h>
#include <string.h>

//the size of the shift of the cipher
int key = 0;

//encrypt function. Takes a char array size 50 
//as input and shifts each character right by the key. 
//If the new ascii value goes over 127, 128 is 
//subtracted from the value.
void encrypt(char line[50]) {
	int i, newChar;
	for (i = 0; i < strlen(line); i++) {
		newChar = line[i] + (key % 128);
		if (newChar > 127) {
			line[i] = newChar - 128;
		} else {
			line[i] = newChar;
		}
	}
}

//decrypt function. Takes a char array size 50
//as input and shifts each character left by the key.
//If the new ascii value is below 0, 128 is added
//to the value.
void decrypt(char line[50]) {
	int i, oldChar;
	for (i = 0; i < strlen(line); i++) {
		oldChar = line[i] - (key % 128);
		if (oldChar < 0) {
			oldChar = 128 + oldChar;
		}
		line[i] = oldChar;
	}
}
