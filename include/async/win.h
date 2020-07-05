#include <winsock2.h>
#include <windows.h>

#if !defined(SSIZE_T_DEFINED) && defined(SSIZE_T)
typedef intptr_t ssize_t;
#define SSIZE_MAX INTPTR_MAX
#define _SSIZE_T_
#define SSIZE_T_DEFINED
#endif

#define AS_HANDLE_PLATFORM_FIELDS /* empty */

#define AS_LOOOP_PLATFORM_FIELDS /* empty */

#define AS__IO_PLATFORM_FIELDS /* empty */

#define AS_STREAM_PLATFORM_FIELDS /* empty */
