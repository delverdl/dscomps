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
  @file der_length_asn1_length.c
  ASN.1 DER, determine the length of the ASN.1 length field, Steffen Jaeckel
*/

#ifdef LTC_DER
/**
  Determine the length required to encode len in the ASN.1 length field
  @param len      The length to encode
  @param outlen   [out] The length that's required to store len
  @return CRYPT_OK if successful
*/
int der_length_asn1_length(unsigned long len, unsigned long *outlen)
{
   return der_encode_asn1_length(len, NULL, outlen);
}

#endif

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
