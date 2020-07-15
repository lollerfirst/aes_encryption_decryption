#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes_encrypt_decrypt.h"

int main(int argc, char** argv){
	FILE* fptr;
	unsigned char* message;
	size_t len;
	unsigned char expandedKeys[176];
	unsigned char key[16];
	int i;

	switch(argc){
		case 3: break;
		default: printf("Usage: decrypt <filepath> <16B-key>\n");
			 return -1;
	}

	for(i=0; i<16; i++)
		key[i] = argv[2][i];
	
	fptr = fopen(argv[1], "rb");
	if(fptr == NULL){
		printf("Error: file not accessible.\n");
		return -1;
	}

	message = malloc(sizeof(unsigned char)*128);
	len = 0;

	size_t check = fread(message, sizeof(unsigned char), 128, fptr);
	while(check == 128){
		len += check;
		message = realloc(message, sizeof(unsigned char)*(len+128));
		check = fread(message, sizeof(unsigned char), 128, fptr);
	}
	
	len += check;
	fclose(fptr);

	if(len % 16 != 0){
		free(message);
		printf("Error: bytes are not multiples of 16. Cannot decrypt.\n");
		return -1;
	}

	memset(expandedKeys, 0x00, sizeof(expandedKeys));
	keyExpansion(key, expandedKeys);

	for(i=0; i<len; i += 16)
		AES_Decrypt(message+i, expandedKeys);

	fptr = fopen(argv[1], "wb");
	if(fptr == NULL){
		printf("Error: file not accessible for write.\n");
		free(message);
		return -1;
	}

	check = fwrite(message, sizeof(unsigned char), len, fptr);
	if(check < len){
		printf("Error: coulnd't write to file\n");
		free(message);
		fclose(fptr);
		return -1;
	}

	fclose(fptr);
	free(message);
	printf("Success: file successfully decrypted\n");
	return 0;
}
