#include <dlfcn.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef wchar_t str_utf16;
typedef char str_ansi;
typedef int BOOL;

class IAPETag
{
public:
    virtual ~IAPETag() {}
    virtual int GetFieldString(const str_utf16 * pFieldName, str_ansi * pBuffer, int * pBufferCharacters, BOOL bUTF8Encode = false) { printf("not me!\n"); }
};

class CTagInfo : public IAPETag
{
public:
  virtual ~CTagInfo() {}
  virtual int GetFieldString(const str_utf16 * pFieldName, str_ansi * pBuffer, int * pBufferCharacters, BOOL bUTF8Encode = false) 
  {
    printf("Called!\n");
    return 0;
  }
};

main()
{
    IAPETag* (*GetAPETag)(const char *filename, bool bCheckID3Tag);
  
    void* handle = dlopen("MACDll-osx.so", RTLD_NOW);
    if (handle == 0)
      printf("Error: %s\n", dlerror());
      
    GetAPETag = (IAPETag* (*)(const char*, bool))dlsym(handle, "c_GetAPETag");
    printf("GetAPETag: 0x%08lx\n", GetAPETag);
    
    IAPETag* tag = GetAPETag("/tmp/xbmc/Music/10,000 Maniacs/Blind Man's Zoo/10,000 Maniacs - Blind Man's Zoo - 01 - Eat for Two.mp3", false);
    char* buffer = (char* )malloc(128);
    int size = 128;

    if (tag == 0)
    {
      printf("NO TAG!\n");
      exit(0);
    }

    if (tag->GetFieldString(L"Title", buffer, &size, true) != -1)
      printf("Tag: %s\n", buffer);
    else
      printf("FALSE\n");
}
