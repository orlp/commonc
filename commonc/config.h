/*

    Copyright 2012 Orson Peters. All rights reserved.

    Redistribution of this work, with or without modification, is permitted if
    Orson Peters is attributed as the original author or licensor of
    this work, but not in any way that suggests that Orson Peters endorses
    you or your use of the work.

    This work is provided by Orson Peters "as is" and any express or implied
    warranties are disclaimed. Orson Peters is not liable for any damage
    arising in any way out of the use of this work.


    ----


    This header file defines a few macros which are used to configure the rest of commonc. Set them here.

*/

#ifndef CC_CONFIG_H_GUARD
#define CC_CONFIG_H_GUARD

/* CC_IEEE754, this macro should be defined if commonc can assume IEEE754. */

#define CC_IEEE754


/* CC_NO_BRANCH, this should be defined on a platform where branches are very expensive and should be avoided. */

/* #define CC_NO_BRANCH */


/* CC_DOUBLE_PREC, if this is defined commonc will assume double-precision FPU mode */

#define CC_DOUBLE_PREC

#endif /* CC_CONFIG_H_GUARD */
