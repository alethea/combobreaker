#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <errno.h>
#include "loader.h"

long fsize(FILE *fp);

/* Get the size of a seekable file. -1 on error */
long fsize(FILE *fp) {
    long size;

    if(fseek(fp, 0L, SEEK_END)) {
        return -1;
    }
    size = ftell(fp);
    if (size == -1) {
        return -1;
    }
    if (fseek(fp, 0L, SEEK_SET)) {
        return -1;
    }
    return size;
}

/* Load the contents of a file into heap memory.
 * Store a pointer to the newly-allocated file in data and
 * the number of bytes allocated in length.
 *
 * Adds and extra 0 byte on the end of memory not counted in
 * length, so that the file may be used as a string.
 *
 * If an error occurs, print it to stderr and exit.
 */
void load(const char *filename, char **data, size_t *length) {
    if(load_softfail(filename, data, length)) {
        error(-1, errno, "Cannot load %s", filename);
    }
}

/* Version of load that returns -1 on failure instead of exiting */
int load_softfail(const char *filename, char **data, size_t *length) {
    FILE *fp;
    size_t size;
    char *buf;

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    size = (size_t) fsize(fp);
    if (size == -1) {
        return -1;
    }
    buf = (char *) calloc(size + 1, sizeof (char));
    if (buf == NULL) {
        return -1;
    }
    buf[size] = '\0';

    if (fread((void *) buf, sizeof (char), size, fp) != size) {
        return -1;
    }

    if (fclose(fp)) {
        return -1;
    }

    *length = size;
    *data = buf;
    return 0;
}
