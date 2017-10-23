#include<stdint.h>
#include<stdio.h>
#include<dlfcn.h>
#include<string.h>
#include<errno.h>
#include<execinfo.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdarg.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
/* We aren't providing much code here.  You'll need to implement quite a bit
 * for your library. */

/* Declarations for the functions in part2_hash.cc, so that we don't need an
 * extra header file. */
void malloc_insert(size_t size);
void malloc_dump();
void so_allocate();
void so_deallocate();

static int ignoreMalloc = 0;
static int ignoreFopen = 0;
static int ignoreGetBalance = 0;

void *malloc(size_t bytes)
{
	static void* (*origMalloc)(size_t) = NULL;
	if(!origMalloc)
	{
		origMalloc = (void* (*)(size_t))dlsym(RTLD_NEXT, "malloc");
	}

	if(ignoreMalloc)
	{
		return origMalloc(bytes);
	}

	ignoreMalloc = 1;
	malloc_insert(bytes);
	ignoreMalloc = 0;

	return origMalloc(bytes);
}

FILE *fopen(const char *filename, const char *mode){
	static FILE *(*origFopen)(const char *, const char *) = NULL;
	if(!origFopen)
	{
		origFopen = dlsym(RTLD_NEXT, "fopen");
	}

	if(ignoreFopen)
	{
		return origFopen(filename,mode);
	}

	ignoreFopen = 1;
	if(strcmp(filename,"alice.data") == 0){
		filename = "bob.data";
	}
	else if(strcmp(filename,"bob.data") == 0){
		filename = "alice.data";
	}
	FILE *ret = origFopen(filename,mode);
	ignoreFopen = 0;
	return ret;
}

int getBalance(int a, int b, int c){
	static int (*origGetBalance)(int, int, int) = NULL;
	if(!origGetBalance)
	{
		origGetBalance = dlsym(RTLD_NEXT, "getBalance");
	}

	if(ignoreGetBalance)
	{
		return origGetBalance(a,b,c);
	}

	ignoreGetBalance = 1;
	printf("Hi from getBalance");
	int ret = origGetBalance(a,b,c);
	ignoreFopen = 0;
	return ret;
}


__attribute__((destructor))
static void deallocate()
{
	malloc_dump();
	so_deallocate();
}


__attribute__((constructor))
static void allocate()
{
	so_allocate();
}
