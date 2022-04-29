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
   @file cbc_done.c
   CBC implementation, finish chain, Tom St Denis
*/

#ifdef LTC_CBC_MODE

/** Terminate the chain
  @param cbc    The CBC chain to terminate
  @return CRYPT_OK on success
*/
int cbc_done(symmetric_CBC *cbc)
{
   int err;
   LTC_ARGCHK(cbc != NULL);

   if ((err = cipher_is_valid(cbc->cipher)) != CRYPT_OK) {
      return err;
   }
   cipher_descriptor[cbc->cipher].done(&cbc->key);
   return CRYPT_OK;
}



#endif

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
