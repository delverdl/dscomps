/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include "tomcrypt_private.h"

/**
   @file copy_or_zeromem.c
   Either copy or zero a block of memory in constant time, Steffen Jaeckel
*/

/**
   Either copy or zero a block of memory in constant time
   @param src    The source where to read from
   @param dest   The destination where to write to
   @param len    The length of the area to process (octets)
   @param coz    Copy (on 0) Or Zero (> 0)
*/
void copy_or_zeromem(const unsigned char* src, unsigned char* dest, unsigned long len, int coz)
{
   unsigned long y;
#ifdef LTC_FAST
   unsigned long z;
   LTC_FAST_TYPE fastMask = ~(LTC_FAST_TYPE)0; /* initialize fastMask at all ones */
#endif
   unsigned char mask = 0xff; /* initialize mask at all ones */

   LTC_ARGCHK(src  != NULL);
   LTC_ARGCHK(dest != NULL);

   if (coz != 0) coz = 1;
   y = 0;
   mask *= 1 - coz; /* mask = ( coz ? 0 : 0xff ) */
#ifdef LTC_FAST
   fastMask *= 1 - coz;
   if (len & ~15) {
      for (; y < (len & ~15); y += 16) {
        for (z = 0; z < 16; z += sizeof(LTC_FAST_TYPE)) {
          *(LTC_FAST_TYPE_PTR_CAST(&dest[y+z])) = *(LTC_FAST_TYPE_PTR_CAST(&src[y+z])) & fastMask;
        }
      }
   }
#endif
   for (; y < len; y++) {
      dest[y] = src[y] & mask;
   }
#ifdef LTC_CLEAN_STACK
#ifdef LTC_FAST
   fastMask = 0;
#endif
   mask = 0;
#endif
}

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
