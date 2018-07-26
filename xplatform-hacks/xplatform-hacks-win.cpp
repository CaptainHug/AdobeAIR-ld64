#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include <ctype.h>
#include <stdarg.h>
#include <windows.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <sys/param.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#include "ld.hpp"
#include "macho_relocatable_file.h"
#include "lto_file.h"


extern const char ldVersionString[] = "1";
unsigned int mach_task_self_ = 0;

extern "C" {

    unsigned int sleep (unsigned int seconds) {
        Sleep(seconds * 1000);
        return 0;
    }

    void bzero(void *buf, size_t num) {
        memset(buf, 0, num);
    }

char* realpath(const char * file_name, char * resolved_name) {
        printf("realpath not implemented\n");
        return 0;
    }

    int vasprintf(char **ret, const char *format, va_list ap) {
        // Generate string in tempfile.
        // You can't use tmpfile() because #2424888 on Vista/UAC.
        //char* tmpName = tmpnam(NULL);
		char* tmpName = _tempnam(NULL,"ld64_");
        FILE *f = fopen( tmpName, "w+b" );
        int len = vfprintf(f, format, ap);
        rewind(f);
        
        // read string
        *ret = (char*)malloc(len + 1);
        fread(*ret, len, 1, f);
        (*ret)[len] = 0;
        fclose(f);
        unlink(tmpName);
        free(tmpName);
        return len;
    }
    
    int asprintf(char **ret, const char *format, ...) {
        va_list ap;
        va_start(ap, format);
        int num = vasprintf(ret, format, ap);
        va_end(ap);
        return num;
    }

    void uuid_generate_random(unsigned char* out) {
        printf("uuid_generate_random not implemented\n");
    }

    unsigned long long mach_absolute_time() {
        //printf("mach_absolute_time not implemented\n");
        return 0;
    }

    ssize_t pwrite(int fildes, const void *buf, size_t nbyte, off_t offset) 
    {
        printf("pwrite not implemented\n");
        return -1;
    }
    
    void* mmap (void* addr, size_t len, int prot, int flags, int fd, off_t offset)
    {
        printf("mmap not implemented\n");
        return 0;
    }
    
    int munmap (void* addr, size_t len)
    {
        printf("munmap not implemented\n");
        return 0;
    }

	void exit_win(const char* msg)
	{
		fprintf(stderr, "%s, error = %d\n", msg, GetLastError());
		exit(-1);
	}

	void* mmap_win(const char* path, short allowWrite)
	{
		void* data = NULL;
		const char* errMsg = NULL;
		HANDLE hFile = INVALID_HANDLE_VALUE;

		int rwFlag = GENERIC_READ;

		if(allowWrite)
			rwFlag |= GENERIC_WRITE;

		//the path here is encoded with the default code page on Windows, hence CreateFile works fine.
		hFile = CreateFile(path, rwFlag, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hFile == INVALID_HANDLE_VALUE)
			errMsg = "mmap_win failed in CreateFile";

		HANDLE hMapFile = NULL;
		if(!errMsg)
		{
			int rwFlag = PAGE_READONLY;
			if(allowWrite)
				rwFlag = PAGE_READWRITE;
			hMapFile = CreateFileMapping(hFile, NULL, rwFlag, 0, 0, NULL);
			CloseHandle(hFile);
			if(hMapFile == NULL)
				errMsg = "mmap_win failed in CreateFileMapping";
		}

		if(!errMsg)
		{
			int rwFlag = FILE_MAP_READ;
			if(allowWrite)
				rwFlag |= FILE_MAP_WRITE;
			data = MapViewOfFile(hMapFile, rwFlag, 0, 0, 0);
			CloseHandle(hMapFile);
			if(data == NULL)
				errMsg = "mmap_win failed in MapViewOfFile";
		}

		if(errMsg)
			exit_win(errMsg);

		return data;
	}

    int munmap_win (void* addr)
	{
		UnmapViewOfFile(addr);
		return 0;
	}
   
    void bcopy(const void *b1, void *b2, size_t len)
    {
        printf("bcopy\n");
        memmove((b2), (b1), (len));
    }
    
    int vm_allocate
    (
     int target_task,
     void** address,
     size_t size,
     int flags
    )
    {
        printf("vm_allocate %d\n", size);
        *address = malloc(size);
        return 0;
    }
}

char *mach_error_string( int e )
{
	printf("mach_error_string: %d\n", e);
	return 0;
}

int index(const char *str, int c) {
    printf("index\n");
    int i = 0;
    while(str[i] != c && str[i] != 0)
        i++;
    return i;
}

// Implementation for CC MD5 functions - 
int CC_MD5_Init(CC_MD5_CTX *c)
{
    MD5Init(c);
    return 1;
}

int CC_MD5_Update(CC_MD5_CTX *c, const void *data, CC_LONG len)
{
    MD5Update (c, (unsigned char*)data, len);
    return 1;
}

int CC_MD5_Final(unsigned char *md, CC_MD5_CTX *c)
{
    MD5Final(c);
    memcpy(md, c->digest, CC_MD5_DIGEST_LENGTH);
    return 1;
}

unsigned char *CC_MD5(const void *data, CC_LONG len, unsigned char *md)
{
    CC_MD5_CTX c;
    CC_MD5_Init(&c);
    CC_MD5_Update(&c, data, len);
    CC_MD5_Final(md, &c);

    return md; 
}


// LTO stubs - 
namespace lto
{
    const char* version()
    {
    	return NULL;
    }

    bool libLTOisLoaded()
    {
	    return false;
    }

    const char* archName(const uint8_t* fileContent, uint64_t fileLength)
    {
	    return NULL;
    }

    bool optimize(  const std::vector<const ld::Atom*>&	allAtoms,
				ld::Internal&						state,
				const OptimizeOptions&				options,
				ld::File::AtomHandler&				handler,
				std::vector<const ld::Atom*>&		newAtoms, 
				std::vector<const char*>&			additionalUndefines)
    { 
	    return false;
    }

    bool isObjectFile(const uint8_t* fileContent, uint64_t fileLength, cpu_type_t architecture, cpu_subtype_t subarch)
    {
	    return false;
    }

    ld::relocatable::File* parse(const uint8_t* fileContent, uint64_t fileLength, 
									const char* path, time_t modTime, ld::File::Ordinal ordinal,
									cpu_type_t architecture, cpu_subtype_t subarch, bool logAllFiles)
    {
        return NULL;
    }
}


// Some helper functions
class Mutex
{
public:
	Mutex() {InitializeCriticalSection(&m_mutex);}
	~Mutex() {DeleteCriticalSection(&m_mutex);}

	void acquire() {EnterCriticalSection(&m_mutex);}
	void release() {LeaveCriticalSection(&m_mutex);}

private:
	CRITICAL_SECTION m_mutex;
};
static Mutex sMutex;
static int (*sCompar)(void *, const void *, const void *) = NULL;
static void* sThunk = NULL;
static int myCompare(const void * l , const void *r)
{
    return sCompar(sThunk,l,r);
}
void qsort_r_impl(void *base, unsigned int nel, unsigned int width, void *thunk,int (*compar)(void *, const void *, const void *))
{
    sMutex.acquire();
    sCompar = compar;
    sThunk = thunk;
    qsort(base, nel, width, myCompare);
    sMutex.release();
}

// Other Stubs
#if __cplusplus
extern "C" {
#endif 
int _NSGetExecutablePath(char* buf, uint32_t* bufsize) 
{
    printf("get executable path called - not implemented\n");
    return -1;
}
void qsort_r(void *base, unsigned int nel, unsigned int width, void *thunk,int (*compar)(void *, const void *, const void *))
{
    qsort_r_impl(base, nel, width, thunk, compar);
}
size_t strlcat(char *dst, const char *src, size_t size)
{
   	register char *d = dst;
	register const char *s = src;
	register size_t n = size;

    //traverse dst
    while(*d && n--) d++;

    // copy src
    while(n>1 && *s)
    {
        *d++ = *s++;
        n--;
    }

    // Add NUL
    *d = '\0';

    //count does not include NUL
	return size - n;	
}

int sysctl(int *name, unsigned int namelen, void *oldp, size_t *oldlenp, void *newp, size_t newlen)
{
    return -1;
}

int64_t OSAtomicAdd64(int64_t theAmount, volatile int64_t* theValue)
{
    *theValue += theAmount;
    return *theValue;
}

int32_t OSAtomicAdd32(int32_t theAmount, volatile int32_t* theValue)
{
    *theValue += theAmount;
    return *theValue;
}

void __assert_rtn(const char* func, const char* file, int line, const char* failedexpr)
{
}

#if __cplusplus
}
#endif 


// Snapshot stubs    
Snapshot *Snapshot::globalSnapshot = NULL;
Snapshot::Snapshot() : fRecordArgs(false), fRecordObjects(false), fRecordDylibSymbols(false), fRecordArchiveFiles(false), fRecordUmbrellaFiles(false), fRecordDataFiles(false), fFrameworkArgAdded(false), fSnapshotLocation(NULL), fSnapshotName(NULL), fRootDir(NULL), fFilelistFile(-1), fCopiedArchives(NULL) { }
Snapshot::~Snapshot() { }
void Snapshot::setSnapshotMode(SnapshotMode mode){}
void Snapshot::setSnapshotName(const char *path) {}
void Snapshot::setSnapshotPath(const char *path) {}
void Snapshot::recordRawArgs(int argc, const char *argv[]) {}
void Snapshot::addSnapshotLinkArg(int argIndex, int argCount, int fileArg) {}
void Snapshot::recordArch(const char *arch) {}
void Snapshot::recordObjectFile(const char *path) {}
void Snapshot::recordDylibSymbol(ld::dylib::File* dylibFile, const char *name) {}
void Snapshot::recordArchive(const char *archiveFile) {}
void Snapshot::recordSubUmbrella(const char *frameworkPath) {}
void Snapshot::recordSubLibrary(const char *dylibPath) {}
void Snapshot::recordAssertionMessage(const char *fmt, ...) {}
void Snapshot::createSnapshot() {}

