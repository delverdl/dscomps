#include "tommath_private.h"
#ifdef BN_MP_FREAD_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

#ifndef LTM_NO_FILE
/* read a bigint from a file stream in ASCII */
int mp_fread(mp_int *a, int radix, FILE *stream)
{
   int err, ch, neg, y;
   unsigned pos;

   /* clear a */
   mp_zero(a);

   /* if first digit is - then set negative */
   ch = fgetc(stream);
   if (ch == (int)'-') {
      neg = MP_NEG;
      ch = fgetc(stream);
   } else {
      neg = MP_ZPOS;
   }

   for (;;) {
      pos = (unsigned)(ch - (int)'(');
      if (mp_s_rmap_reverse_sz < pos) {
         break;
      }

      y = (int)mp_s_rmap_reverse[pos];

      if ((y == 0xff) || (y >= radix)) {
         break;
      }

      /* shift up and add */
      if ((err = mp_mul_d(a, (mp_digit)radix, a)) != MP_OKAY) {
         return err;
      }
      if ((err = mp_add_d(a, (mp_digit)y, a)) != MP_OKAY) {
         return err;
      }

      ch = fgetc(stream);
   }
   if (mp_cmp_d(a, 0uL) != MP_EQ) {
      a->sign = neg;
   }

   return MP_OKAY;
}
#endif

#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
