#include "test_sha.h"
#include "../include/sha1.h"
#include <string.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

void testSha() {
    uint8_t hash[20];
    const char *message = "Testing SHA1.";
    char hash_hex[41];
    const char *expected_hash = "3b513157ac6c5dff2b8af5610e1580d4e4393b16";

    sha1((const uint8_t *)message, strlen(message), hash);
    hex_hash(hash, sizeof(hash), hash_hex);

    CU_ASSERT_STRING_EQUAL(hash_hex, expected_hash);
}
