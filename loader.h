#ifndef _COMBOBREAKER_LOADER_H_
#define _COMBOBREAKER_LOADER_H_

int load_softfail(const char *filename, char **data, size_t *length);
void load(const char *filename, char **data, size_t *length);

#endif
