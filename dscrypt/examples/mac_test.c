/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
/* test pmac/omac/hmac */
#include <tomcrypt_test.h>

int mac_test(void)
{
#ifdef LTC_HMAC
   DO(hmac_test());
#endif
#ifdef LTC_PMAC
   DO(pmac_test());
#endif
#ifdef LTC_OMAC
   DO(omac_test());
#endif
#ifdef LTC_XCBC
   DO(xcbc_test());
#endif
#ifdef LTC_F9_MODE
   DO(f9_test());
#endif
#ifdef LTC_EAX_MODE
   DO(eax_test());
#endif
#ifdef LTC_OCB_MODE
   DO(ocb_test());
#endif
#ifdef LTC_OCB3_MODE
   DO(ocb3_test());
#endif
#ifdef LTC_CCM_MODE
   DO(ccm_test());
#endif
#ifdef LTC_GCM_MODE
   DO(gcm_test());
#endif
#ifdef LTC_PELICAN
   DO(pelican_test());
#endif
#ifdef LTC_POLY1305
   DO(poly1305_test());
#endif
#ifdef LTC_CHACHA20POLY1305_MODE
   DO(chacha20poly1305_test());
#endif
#ifdef LTC_BLAKE2SMAC
   DO(blake2smac_test());
#endif
#ifdef LTC_BLAKE2BMAC
   DO(blake2bmac_test());
#endif
   return 0;
}

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
