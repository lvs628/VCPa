#ifndef DEFINETYPES_H
#define DEFINETYPES_H
#include <string>
#include <list>
using namespace std;

#ifndef TRUE
    #define  TRUE true
#endif
#ifndef FALSE
    #define FALSE false
#endif
//#define COLORREF QRgb


typedef unsigned long   COLORREF;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef unsigned char   BYTE;
typedef long            LONG;
typedef int            BOOL;
typedef unsigned int    UINT;
typedef int             _int16;
extern string itoa(int n);

#define CALLBACK __stdcall

typedef void *PVOID;
typedef PVOID HANDLE;

#endif // DEFINETYPES_H
