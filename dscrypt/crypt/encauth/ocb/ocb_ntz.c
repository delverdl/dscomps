/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

/**
   @file ocb_ntz.c
   OCB implementation, internal function, by Tom St Denis
*/

#include "tomcrypt_private.h"

#ifdef LTC_OCB_MODE

/**
   Returns the number of leading zero bits [from lsb up]
   @param x  The 32-bit value to observe
   @return   The number of bits [from the lsb up] that are zero
*/
int ocb_ntz(unsigned long x)
{
   int c;
   x &= 0xFFFFFFFFUL;
   c = 0;
   while ((x & 1) == 0) {
      ++c;
      x >>= 1;
   }
   return c;
}

#endif

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */