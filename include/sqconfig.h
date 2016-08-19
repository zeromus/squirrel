#ifdef _MSC_VER
typedef unsigned __int8 SQByte;
typedef __int16 SQInt16;
typedef __int32 SQInt32;
typedef __int64 SQInt64;
typedef unsigned __int32 SQUInt32;
typedef unsigned __int64 SQUInt64;
#else
#include <stdint.h>
typedef uint8_t SQByte;
typedef int16_t SQInt16;
typedef int32_t SQInt32;
typedef int64_t SQInt64;
typedef uint32_t SQUInt32;
typedef uint64_t SQUInt64;
#endif

//not a great name.. here for transitionary period
typedef SQUInt32 SQUnsignedInteger32;

//should be 64bits on 64bits processors, to take advantage of bigger ints
#ifdef _SQ64
typedef SQInt64 SQInteger; 
typedef SQUInt64 SQUnsignedInteger; 
#else
typedef SQInt32 SQInteger; 
typedef SQUInt32 SQUnsignedInteger; 
#endif

//huh? I dont follow this. any of these cases should bump the size up to 64
//#if defined(SQUSEDOUBLE) && !defined(_SQ64) || !defined(SQUSEDOUBLE) && defined(_SQ64)
#if defined(SQUSEDOUBLE) || defined(_SQ64) || defined(_SQ_NO_64)
typedef SQInt64 SQRawObjectVal;
#define SQ_OBJECT_RAWINIT() { _unVal.raw = 0; }
#else
typedef SQInt32 SQRawObjectVal;;
#define SQ_OBJECT_RAWINIT()
#endif

#if defined(_SQ64) || defined(_SQ_NO_64)
typedef SQInt64 SQHash; //should be the same size as a pointer
#else
typedef SQInt32 SQHash; //should be the same size as a pointer
#endif

#ifdef SQUSEDOUBLE
typedef double SQFloat;
#else
typedef float SQFloat;
#endif

#ifndef SQ_ALIGNMENT // SQ_ALIGNMENT shall be less than or equal to SQ_MALLOC alignments, and its value shall be power of 2.
#if defined(SQUSEDOUBLE) || defined(_SQ64)
#define SQ_ALIGNMENT 8
#else
#define SQ_ALIGNMENT 4
#endif
#endif

typedef void* SQUserPointer;
typedef SQUnsignedInteger SQBool;
typedef SQInteger SQRESULT;

#ifdef SQUNICODE
#include <wchar.h>
#include <wctype.h>


typedef wchar_t SQChar;


#define scstrcmp    wcscmp
#ifdef _WIN32
#define scsprintf   _snwprintf
#else
#define scsprintf   swprintf
#endif
#define scstrlen    wcslen
#define scstrtod    wcstod
#ifdef _SQ64
#define scstrtol    wcstoll
#else
#define scstrtol    wcstol
#endif
#define scstrtoul   wcstoul
#define scvsprintf  vswprintf
#define scstrstr    wcsstr
#define scprintf    wprintf

#ifdef _WIN32
#define WCHAR_SIZE 2
#define WCHAR_SHIFT_MUL 1
#define MAX_CHAR 0xFFFF
#else
#define WCHAR_SIZE 4
#define WCHAR_SHIFT_MUL 2
#define MAX_CHAR 0xFFFFFFFF
#endif

#define _SC(a) L##a


#define scisspace   iswspace
#define scisdigit   iswdigit
#define scisprint   iswprint
#define scisxdigit  iswxdigit
#define scisalpha   iswalpha
#define sciscntrl   iswcntrl
#define scisalnum   iswalnum


#define sq_rsl(l) ((l)<<WCHAR_SHIFT_MUL)

#else
typedef char SQChar;
#define _SC(a) a
#define scstrcmp    strcmp
#ifdef _MSC_VER
#define scsprintf   _snprintf
#else
#define scsprintf   snprintf
#endif
#define scstrlen    strlen
#define scstrtod    strtod
#ifdef _SQ64
#ifdef _MSC_VER
#define scstrtol    _strtoi64
#else
#define scstrtol    strtoll
#endif
#else
#define scstrtol    strtol
#endif
#define scstrtoul   strtoul
#define scvsprintf  vsnprintf
#define scstrstr    strstr
#define scisspace   isspace
#define scisdigit   isdigit
#define scisprint   isprint
#define scisxdigit  isxdigit
#define sciscntrl   iscntrl
#define scisalpha   isalpha
#define scisalnum   isalnum
#define scprintf    printf
#define MAX_CHAR 0xFF

#define sq_rsl(l) (l)

#endif

#ifdef _SQ64
#define _PRINT_INT_PREC _SC("ll")
#define _PRINT_INT_FMT _SC("%lld")
#else
#define _PRINT_INT_FMT _SC("%d")
#endif

#define SQ_TYPE_TAG_AS_USER_POINTER(TAG) ((SQUserPointer)((char *)0 + (TAG)))
