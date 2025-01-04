#ifndef SHA1_H
#define SHA1_H

#define ROTL(x, n) ((x << n) | (x >> (32 - n)))

#define K0 0x5a827999
#define K1 0x6ed9eba1
#define K2 0x8f1bbcdc
#define K3 0xca64c1d6

#include <stdint.h>
#include <stddef.h>

void sha1(const uint8_t *message, size_t length, uint8_t hash[20]);
void hex_hash(const uint8_t *hash, size_t hash_len, char *hex_output);

#endif
