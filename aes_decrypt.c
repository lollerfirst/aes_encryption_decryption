#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aes_encrypt_decrypt.h"
#define ROUNDS 9

void rotate_right(unsigned char* word, int n){
	unsigned char tmp[4];

	switch(n){
		case 1: tmp[0] = word[3];
			tmp[1] = word[0];
			tmp[2] = word[1];
			tmp[3] = word[2];
			break;
		
		case 2: tmp[0] = word[2];
			tmp[1] = word[3];
			tmp[2] = word[0];
			tmp[3] = word[1];
			break;
		
		case 3: tmp[0] = word[1];
			tmp[1] = word[2];
			tmp[2] = word[3];
			tmp[3] = word[0];
			break;

		default: return;
	}

	word[0] = tmp[0];
	word[1] = tmp[1];
	word[2] = tmp[2];
	word[3] = tmp[3];
}

void inv_subBytes(unsigned char* state){
	int i;
	for(i=0; i<16; i++)
		state[i] = inv_sbox[state[i]];

}

void inv_shiftRows(unsigned char* state){
	rotate_right(state+12, 3);
	rotate_right(state+8, 2);
	rotate_right(state+4, 1);
}

void inv_mixColumns(unsigned char* state){
	/* 14  11  13  9
	 *  9  14  11  13
	 * 13   9  14  11
	 * 11  13   9  14 */

	unsigned char tmp[16];
	
	tmp[0] = mul_14[state[0]] ^  mul_11[state[4]] ^ mul_13[state[8]] ^ mul_9[state[12]];
	tmp[1] = mul_14[state[1]] ^  mul_11[state[5]] ^ mul_13[state[9]] ^ mul_9[state[13]];
	tmp[2] = mul_14[state[2]] ^  mul_11[state[6]] ^ mul_13[state[10]] ^ mul_9[state[14]];
	tmp[3] = mul_14[state[3]] ^  mul_11[state[7]] ^ mul_13[state[11]] ^ mul_9[state[15]];
	
	tmp[4] = mul_9[state[0]] ^ mul_14[state[4]] ^ mul_11[state[8]] ^  mul_13[state[12]];
	tmp[5] = mul_9[state[1]] ^ mul_14[state[5]] ^ mul_11[state[9]] ^  mul_13[state[13]];
	tmp[6] = mul_9[state[2]] ^ mul_14[state[6]] ^ mul_11[state[10]] ^  mul_13[state[14]];
	tmp[7] = mul_9[state[3]] ^ mul_14[state[7]] ^ mul_11[state[11]] ^  mul_13[state[15]];
	
	tmp[8] = mul_13[state[0]] ^ mul_9[state[4]] ^ mul_14[state[8]] ^ mul_11[state[12]];
	tmp[9] = mul_13[state[1]] ^ mul_9[state[5]] ^ mul_14[state[9]] ^ mul_11[state[13]];
	tmp[10] = mul_13[state[2]] ^ mul_9[state[6]] ^ mul_14[state[10]] ^ mul_11[state[14]];
	tmp[11] = mul_13[state[3]] ^ mul_9[state[7] ^ mul_14[state[11]] ^ mul_11[state[15]];
					   
	tmp[12] = mul_11[state[0]] ^ mul_13[state[4]] ^ mul_9[state[8]] ^ mul_14[state[12]];
	tmp[13] = mul_11[state[1]] ^ mul_13[state[5]] ^ mul_9[state[9]] ^ mul_14[state[13]];
	tmp[14] = mul_11[state[2]] ^ mul_13[state[6]] ^ mul_9[state[10]] ^ mul_14[state[14]];
	tmp[15] = mul_11[state[3]] ^ mul_13[state[7]] ^ mul_9[state[11]] ^ mul_14[state[15]];
					   
	int i;
	for(i=0; i<16; i++)
		state[i] = tmp[i];
}

void AES_Decrypt(unsigned char* block, unsigned char* expandedKey){
	unsigned char state[16];
	int i;
	expandedKeys = expandedKeys+160;

	for(i=0; i<16; i++)
		state[i] = block[i];

	addRoundKey(state, expandedKeys); //reverse the add operation on the last roundkey
	inv_shiftRows(state);
	inv_subBytes(state);

	for(i=0; i<ROUNDS; i++){
		expandedKeys -= 16;
	        addRoundKey(state, expandedKeys);
		inv_mixColumns(state);
		inv_shiftRows(state);
		inv_subBytes(state);	
	}

	expandedKeys -= 16;
	addRoundKey(state, expandedKeys);

	for(i=0; i<16; i++)
		block[i] = state[i];
}
