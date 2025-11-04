#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCKS_COUNT 1
#define ROUNDS_COUNT 32

typedef uint16_t word;
typedef uint32_t block;
typedef uint64_t key;

word left_shift(word x, int n) {

}

word right_shift(word x, int n) {

}

void simon_round(word *left, word *right, word round_key, int round_num) {

}

void key_schedule(word key_words[4], word round_keys[ROUNDS_COUNT]) {

}

block simon_encrypt(block plaintext, key k) {
    word key_words[4];
    word round_keys[ROUNDS_COUNT];

    key_words[0] = (k >> 48) & 0xFFFF;
    key_words[1] = (k >> 32) & 0xFFFF;
    key_words[2] = (k >> 16) & 0xFFFF;
    key_words[3] = k & 0xFFFF;

    key_schedule(key_words, round_keys);

    word left = (plaintext >> 16) & 0xFFFF;
    word right = plaintext & 0xFFFF;

    for (int round = 0; round < ROUNDS_COUNT; round++) {
        simon_round(&left, &right, round_keys[round], round);
    }

    block ciphertext = ((block)left << 16) | right;

    return ciphertext;
}

void test_simon() {
    printf("==========Simon 32/64 test==========\n");

    block plaintext = 0x6574694c;
    key k = 0x1918111009080100;
    block desired_ciphertext = 0xa86842f2;

    block received_ciphertext = simon_encrypt(plaintext, k);
    
    printf("\n==========Results==========\n");
    printf("Plaintext: %08X\n", plaintext);
    printf("Desired ciphertext: %08X\n", desired_ciphertext);
    printf("Received ciphertext: %08X\n", received_ciphertext);
}

int main() {
    test_simon();
    return 0;
}