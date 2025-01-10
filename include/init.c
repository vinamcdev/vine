#include "init.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int init() {
    printf("init .vine\n");
    if (mkdir("./.vine", S_IRWXU | S_IRWXG | S_IRWXO) == -1) {
        printf("failed init: %s\n", strerror(errno));
        return 1;
    }
    printf("init success");
    return 0;
}
