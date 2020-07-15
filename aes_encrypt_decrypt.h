#ifndef __AES_ENCRYPT_H_
#define __AES_ENCRYPT_H_ 1
extern const unsigned char sbox[];

extern const unsigned char inv_sbox[];

extern const unsigned char mul_2[];

extern const unsigned char mul_3[];

extern const unsigned char mul_9[];

extern const unsigned char mul_11[];

extern const unsigned char mul_13[];

extern const unsigned char mul_14[];

extern const unsigned char RCON[];

extern void rotate_left(unsigned char*, int);
extern void rotate_right(unsigned char*, int);
extern void keyExpansionCore(unsigned char*, int);
extern void keyExpansion(unsigned char*, unsigned char*);
extern void addRoundKey(unsigned char*, unsigned char*);
extern void subBytes(unsigned char*);
extern void inv_subBytes(unsigned char*);
extern void shiftRows(unsigned char*);
extern void inv_shiftRows(unsigned char*);
extern void mixColumns(unsigned char*);
extern void inv_mixColumns(unsigned char*);
extern void AES_Encrypt(unsigned char*, unsigned char*);
extern void AES_Decrypt(unsigned char*, unsigned char*);
#endif
