/*

    Copyright 2012 Orson Peters. All rights reserved.

    Redistribution of this work, with or without modification, is permitted if
    Orson Peters is attributed as the original author or licensor of
    this work, but not in any way that suggests that Orson Peters endorses
    you or your use of the work.

    This work is provided by Orson Peters "as is" and any express or implied
    warranties are disclaimed. Orson Peters is not liable for any damage
    arising in any way out of the use of this work.

*/

#ifndef CC_INTEGER_H_GUARD
#define CC_INTEGER_H_GUARD

#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

#endif /* CC_INTEGER_H_GUARD */
