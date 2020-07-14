encrypt: encrypt.o aes_encrypt_decrypt.o
	gcc encrypt.o aes_encrypt_decrypt.o -o encrypt
encrypt.o: encrypt.c
	gcc -c encrypt.c
aes_encrypt_decrypt.o: aes_encrypt_decrypt.h
	gcc -c aes_encrypt_decrypt.c
clean:
	rm *.o encrypt
