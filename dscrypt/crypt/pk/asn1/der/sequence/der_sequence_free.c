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
  @file der_sequence_free.c
  ASN.1 DER, free's a structure allocated by der_decode_sequence_flexi(), Tom St Denis
*/

#ifdef LTC_DER

/**
  Free memory allocated by der_decode_sequence_flexi()
  @param in     The list to free
*/
void der_sequence_free(ltc_asn1_list *in)
{
   ltc_asn1_list *l;

   if (!in) return;

   /* walk to the start of the chain */
   while (in->prev != NULL || in->parent != NULL) {
      if (in->parent != NULL) {
          in = in->parent;
      } else {
          in = in->prev;
      }
   }

   /* now walk the list and free stuff */
   while (in != NULL) {
      /* is there a child? */
      if (in->child) {
         /* disconnect */
         in->child->parent = NULL;
         der_sequence_free(in->child);
      }

      switch (in->type) {
         case LTC_ASN1_SETOF: break;
         case LTC_ASN1_INTEGER : if (in->data != NULL) { mp_clear(in->data); } break;
         default               : if (in->data != NULL) { XFREE(in->data);    }
      }

      /* move to next and free current */
      l = in->next;
      XFREE(in);
      in = l;
   }
}

#endif

/* ref:         HEAD -> develop, streams-enforce-call-policy */
/* git commit:  c9c3c4273956ae945aecec7122cd0df71a210803 */
/* commit time: 2018-07-10 07:11:39 +0200 */
