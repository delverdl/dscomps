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
  @file ecc_test.c
  ECC Crypto, Tom St Denis
*/

#ifdef LTC_MECC

int ecc_test(void)
{
   /* the main ECC tests are in tests/ecc_test.c
    * this function is kept just for API compatibility
    */
   return CRYPT_NOP;
}

#endif

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */

