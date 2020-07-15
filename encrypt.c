#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes_encrypt_decrypt.h"

int main(int argc, char** argv){
	switch(argc){
		case 3: break;
		default: printf("Usage: encrypt <path> <key>\n");
				 return -1;
	}
	
	char* filepath = argv[1];
	unsigned char key[16];
	unsigned char expandedKeys[176];
	int j;
	for(j=0; j<16; j++)
		key[j] = argv[2][j];
	
	
	
	FILE* fptr = fopen(filepath, "rb");
	if(fptr == NULL){
		printf("Error: file not accessible\n");
		return -1;
	}
	
	unsigned char* message = malloc(sizeof(unsigned char)*128);
	int len = 0;
	
	size_t check = fread(message, sizeof(unsigned char), 128, fptr);
	while(check == 128){
		len += 128;
		message = realloc(message, sizeof(unsigned char) * (len + 128));
		check = fread(message, sizeof(unsigned char), 128, fptr);
	}
	len += check;
	fclose(fptr);
	
	//check if len is a multiple of 16, if not add some padding
	int remainder = len % 16;
	if(remainder > 0){
		int padding_n = 16 - remainder;
		int i;
		for(i=0; i < padding_n; i++)
			message[len+i] = 0x00;
		len += i;
	}
	
	memset(expandedKeys, 0x00, sizeof(expandedKeys));
	keyExpansion(key, expandedKeys);
	
	//main loop of cipher
	int i;
	for(i=0; i<len; i+=16)  // encrypt blocks of data
		AES_Encrypt(message+i, expandedKeys);
	
	fptr = fopen(filepath, "wb");
	if(fptr == NULL){
		printf("Error: file not accessible\n");
		return -1;
	}
	check = fwrite(message, sizeof(unsigned char), len, fptr);
	if(check < len){
		printf("Error: couldn't write to file\n");
		return -1;
	}
	fclose(fptr);
	free(message);

	printf("Success: file successfully encrypted.\n");
	return 0;
}
