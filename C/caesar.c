#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool is_valid_integer(const char *str, int *out_value);
string encrypt(string text,int key);
int main(int argc, string argv[]){
    int key;
    if (argc == 2 && is_valid_integer(argv[1], &key)){
        // get key
        key = atoi(argv[1]);
        // input plain text
        string plaintext = get_string("plaintext: ");
        // encrypt text
        string ciphertext = encrypt(plaintext, key);
        // print cipher text
        printf("ciphertext: %s\n", ciphertext);
    }
    else{
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

string encrypt(string text,int key){
    for (int i = 0, n =  strlen(text); i < n; i++){
        if (isalpha(text[i])){
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + key) % 26 + offset;
        }
    }
    return text;
}


bool is_valid_integer(const char *str, int *out_value) {
    char *endptr;
    int errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 10);

    // Check for conversion errors
    if (errno != 0 || *endptr != '\0' || endptr == str) {
        return false;
    }

    // Check for out-of-range values
    if (val < INT_MIN || val > INT_MAX) {
        return false;
    }

    // If we reach here, str is a valid integer and within the range of int
    *out_value = (int)val;
    return true;
}
