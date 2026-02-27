////////////////////////////////////////////////////////////////////////////////
// Automatic Vigenere Decryption tool
// Created for fun
//
// Uses Kasiski's method to estimate key length given some ciphertext
//
// by Oliver Hales
// starting 2026-01-09
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 10000
#define ALPHABET_SIZE 26
#define Pc_RAND 0.0385
#define Pc_ENG 0.0658

double findKeyLength(char *ciphertext);
void getFrequencies(char *ciphertext, int frequencies[], int *total_letters);

int main(int argc, char *argv[]) {
    char *ciphertext = malloc(MAX_SIZE * sizeof(char));
    fgets(ciphertext, MAX_SIZE, stdin);

    int keylength = findKeyLength(ciphertext);
    printf("keylength: %d\n", keylength);

    return 0;
}

// using Kasiski's Method to estimate key length
double findKeyLength(char *ciphertext) {
    // referred to in formulas as n
    int total_letters = 0;
    // each letter frequency referred to in formulas as f
    int frequencies[ALPHABET_SIZE] = {0};

    getFrequencies(ciphertext, frequencies, &total_letters);

    // I_c = (SUM(f^2) - n)/(n^2 - n)
    double indexCoincidence = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        indexCoincidence += frequencies[i] * frequencies[i];
    }
    indexCoincidence -= total_letters;
    indexCoincidence = indexCoincidence / ((total_letters * total_letters) - total_letters);


    // L ~= 0.0273n / ((n-1)I_c - 0.0385n + 0.0658)
    double keylength = (Pc_ENG - Pc_RAND) * total_letters;
    keylength = keylength / ((total_letters - 1) * indexCoincidence - Pc_RAND * total_letters + Pc_ENG);
    
    return keylength;
}

void getFrequencies(char *ciphertext, int frequencies[], int *total_letters) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        char c = ciphertext[i];
        
        if (isalpha(c)) {
            frequencies[tolower(c) - 'a']++;
            (*total_letters)++;
        }

        i++;
    }
}