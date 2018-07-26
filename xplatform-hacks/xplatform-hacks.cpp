#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/stat.h>

extern "C" {

/*
	void* readfd(int fd);
	void* read_helper(FILE *f, int *size);
    
    void* readfile(const char *path, int *size) {
        FILE *f = fopen(path, "rb");
        if(f == 0) {
            printf("couldn't open file %s\n", path);
            exit(-1);
        }
        void *data = read_helper(f, size); 
        fclose(f);
        return data;
    }

	void* read_helper(FILE *f, int *size) {
        fseek(f, 0, SEEK_END);
        *size = (int)ftell(f);
        rewind(f);
        char *data = (char*)malloc(*size);
        fread(data, 1, *size, f);
        return data;
    }
	
    void* readfd(int fd) {
        int size = 0;
        FILE *f = NULL; //fdopen(fd, "rb");
        return read_helper(f, &size);
    }
*/

}

