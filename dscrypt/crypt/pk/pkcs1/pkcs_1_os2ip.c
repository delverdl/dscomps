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
  @file pkcs_1_os2ip.c
  Octet to Integer OS2IP, Tom St Denis
*/
#ifdef LTC_PKCS_1

/**
  Read a binary string into an mp_int
  @param n          [out] The mp_int destination
  @param in         The binary string to read
  @param inlen      The length of the binary string
  @return CRYPT_OK if successful
*/
int pkcs_1_os2ip(void *n, unsigned char *in, unsigned long inlen)
{
   return mp_read_unsigned_bin(n, in, inlen);
}

#endif /* LTC_PKCS_1 */


/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
