#include <stdio.h>
#include <string.h>

/* XOR every byte of buf with key. Used for BOTH encrypt and decrypt. */
void xor_crypt(char* buf, size_t len, unsigned char key) {
    for (size_t i = 0; i < len; i++) {
        buf[i] = buf[i] ^ key;
    }
}

/* Print each byte as two hex digits, e.g. "6B 4F 46 ..." */
void print_hex(const char* buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", (unsigned char)buf[i]);
    }
    printf("\n");
}

int main(void) {
    char message[] = "Hello COMP 211";
    unsigned char key = 0x2A;


    size_t len = strlen(message);

    printf("Original:  %s\n", message);
    printf("Key:       0x%02X\n", key);

    xor_crypt(message, len, key);
    printf("Encrypted: ");
    print_hex(message, len);

    xor_crypt(message, len, key);
    printf("Decrypted: %s\n", message);

    return 0;
}