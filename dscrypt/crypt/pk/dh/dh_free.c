/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

#include "tomcrypt_private.h"

#ifdef LTC_MDH

/**
  Free the allocated ram for a DH key
  @param key   The key which you wish to free
*/
void dh_free(dh_key *key)
{
   LTC_ARGCHKVD(key != NULL);
   mp_cleanup_multi(&key->prime, &key->base, &key->y, &key->x, NULL);
}

#endif /* LTC_MDH */

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
