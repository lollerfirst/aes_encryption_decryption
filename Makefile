encrypt: aes_encrypt.o
	gcc aes_encrypt.o -o encrypt
aes_encrypt.o: aes_encrypt.c aes_encrypt_decrypt.h
	gcc -c aes_encrypt.c
clean:
	rm *.o encrypt
