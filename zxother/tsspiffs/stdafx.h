// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define _CRT_SECURE_NO_WARNINGS 1

//#include "targetver.h"

//#include <tchar.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <process.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <stdint.h>

#define lo(a)	(U8)(a)
#define hi(a)	(U8)((a) >> 8)

#define countof(a)  (sizeof(a) / sizeof(a[0]))
