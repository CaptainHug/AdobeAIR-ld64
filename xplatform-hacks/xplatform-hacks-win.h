#ifndef __XPLATFORM_HACKS_WIN
#define __XPLATFORM_HACKS_WIN

#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <malloc.h>
#include "xplatform-hacks.h"
#include "../../libgw32c/strlcpy.h"
#include "../../md5/md5.h"

// Contents of generated configure.h for Mac build
#define DEFAULT_MACOSX_MIN_VERSION "10.6"
#define SUPPORT_ARCH_i386  1
#define SUPPORT_ARCH_x86_64  1
#define SUPPORT_ARCH_armv4t  1
#define SUPPORT_ARCH_armv5  1
#define SUPPORT_ARCH_armv6  1
#define SUPPORT_ARCH_armv7  1
#define SUPPORT_ARCH_armv7f  1
#define SUPPORT_ARCH_armv7k  1
#define SUPPORT_ARCH_armv7s  1
#define ALL_SUPPORTED_ARCHS  "i386 x86_64 armv4t armv5 armv6 armv7 armv7f armv7k armv7s"

#define CTL_KERN 1
#define KERN_OSRELEASE 2
#define HAVE_PTHREADS 0

#define	S_IRWXU		0000700
#define	S_IRGRP		0000040
#define	S_IXGRP		0000010
#define	S_IROTH		0000004
#define	S_IXOTH		0000001

#define RTLD_LAZY 0
#define PROT_READ 0
#define MAP_PRIVATE 0
#define MAP_FILE 0

#define MAXPATHLEN  PATH_MAX
#define __uint16_t  uint16_t
#define __uint32_t  uint32_t
#define __uint64_t  uint64_t

typedef unsigned char   __darwin_uuid_t[16];
typedef char    __darwin_uuid_string_t[37];
typedef void* caddr_t;
typedef	unsigned char uuid_t[16];

#define OS_INLINE static inline	
typedef unsigned int mach_port_t;
//#define ULLONG_MAX	0xffffffffffffffffULL

extern "C" {
    
    void* mmap (void* addr, size_t len, int prot, int flags, int fd, off_t offset);

    int munmap (void* addr, size_t len);

    void* mmap_win (const char* addr, short allowWrite);
    
    int munmap_win (void* addr);    
    
    void bcopy(const void *b1, void *b2, size_t len);
    
    int vasprintf(char **ret, const char *format, va_list ap);
    
    int asprintf(char **ret, const char *format, ...);
    
    ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset);
    
    void uuid_generate_random(uuid_t out);
    
    void bzero(void *, size_t);
    
    unsigned int sleep (unsigned int seconds);
    
    char* realpath(const char * file_name, char * resolved_name);

	char* strdup(const char* str);

	//int fileno(int fileDesc);
}

// Declaration for CC_MD5 functions -
#define CC_MD5_CTX  MD5_CTX
#define CC_MD5_DIGEST_LENGTH    16
typedef uint32_t CC_LONG;
int CC_MD5_Init(CC_MD5_CTX *c);
int CC_MD5_Update(CC_MD5_CTX *c, const void *data, CC_LONG len);
int CC_MD5_Final(unsigned char *md, CC_MD5_CTX *c);
unsigned char *CC_MD5(const void *data, CC_LONG len, unsigned char *md);

// Declaration for some other functions - 
#if __cplusplus
extern "C" {
#endif 
void qsort_r(void *base, unsigned int nel, unsigned int width, void *thunk,int (*compar)(void *, const void *, const void *));
size_t strlcat(char *dst, const char *src, size_t size);
int sysctl(int *name, unsigned int namelen, void *oldp, size_t *oldlenp, void *newp, size_t newlen);
#if __cplusplus
}
#endif 

#endif // __XPLATFORM_HACKS_WIN
