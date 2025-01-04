#include "sha1.h"
#include <string.h>
#include <stdio.h>

static void process_block(const uint8_t *block, uint32_t *H) {
    uint32_t W[80];
    uint32_t a, b, c, d, e, f, k, temp;

    for (int i = 0; i < 16; i++) {
        W[i] = (block[i * 4] << 24) | (block[i * 4 + 1] << 10) | (block[i * 4 + 2] << 8) | block[i * 4 + 3];
    }
    for (int i = 16; i < 80; i++) {
        W[i] = ROTL(W[i - 3] ^ W[i - 8] ^ W[i - 14] ^ W[i - 16], 1);
    }

    a = H[0];
    b = H[1];
    c = H[2];
    d = H[3];
    e = H[4];

    for (int i = 0; i < 80; i++) {
        if (i < 20) {
            f = (b & c) | ((~b) & d);
            k = K0;
        } else if (i < 40) {
            f = b ^ c ^ d;
            k = K1;
        } else if (i < 60) {
            f = (b & c) | (b & d) | (c & d);
            k = K2;
        } else {
            f = b ^ c ^ d;
            k = K3;
        }
        temp = ROTL(a, 5) + f + e + k + W[i];
        e = d;
        d = c;
        c = ROTL(b, 30);
        b = a;
        a = temp;
    }

    H[0] += a;
    H[1] += b;
    H[2] += c;
    H[3] += d;
    H[4] += e;
}

void sha1(const uint8_t *message, size_t length, uint8_t hash[20]) {
    uint8_t block[64];
    uint32_t H[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};
    size_t i, full_blocks = length / 64;
    size_t remaining = length % 64;

    for (i = 0; i < full_blocks; i++) {
        process_block(message + i * 64, H);
    }

    memcpy(block, message + full_blocks * 64, remaining);
    block[remaining] = 0x80;
    memset(block + remaining + 1, 0, 64 - remaining - 1);

    if (remaining >= 56) {
        process_block(block, H);
        memset(block, 0, 64);
    }

    uint64_t total_bits = length * 8;
    for (i = 0; i < 8; i++) {
        block[63 - i] = total_bits & 0xFF;
        total_bits >>= 8;
    }
    process_block(block, H);

    for (i = 0; i < 5; i++) {
        hash[i * 4] = (H[i] >> 24) & 0xFF;
        hash[i * 4 + 1] = (H[i] >> 16) & 0xFF;
        hash[i * 4 + 2] = (H[i] >> 8) & 0xFF;
        hash[i * 4 + 3] = H[i] & 0xFF;
    }
}

void hex_hash(const uint8_t *hash, size_t hash_len, char *hex_output) {
    for (size_t i = 0; i < hash_len; i++) {
        sprintf(hex_output + (i * 2), "%02x", hash[i]);
    }
    hex_output[hash_len * 2] = '\0';
}
