#pragma once

int setenv(const char *name, const char *value, int override);

#define RTLD_NOW 0

void *dlopen(const char *filename, int flag);

char *dlerror();

void *dlsym(void *handle, const char *symbol);

int dlclose(void *handle);

