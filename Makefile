encrypt: main.o aes_encrypt.o
	gcc main.o aes_encrypt.o -o encrypt
main.o: main.c
	gcc -c main.c
aes_encrypt.o: aes_encrypt.c aes_encrypt_decrypt.h
	gcc -c aes_encrypt.c
clean:
	rm *.o encrypt
