encrypt: encrypt.o aes_encrypt_decrypt.o
	gcc encrypt.o aes_encrypt_decrypt.o -o encrypt

decrypt: decrypt.o aes_encrypt_decrypt.o
	gcc decrypt.o aes_encrypt_decrypt.o -o decrypt
decrypt.o: decrypt.c aes_encrypt_decrypt.h
	gcc -c decrypt.c
encrypt.o: encrypt.c aes_encrypt_decrypt.h
	gcc -c encrypt.c
aes_encrypt_decrypt.o: aes_encrypt_decrypt.c 
	gcc -c aes_encrypt_decrypt.c
clean:
	rm *.o encrypt decrypt
