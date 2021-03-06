#include "tommath_private.h"
#ifdef BN_MP_2EXPT_C
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

/* computes a = 2**b
 *
 * Simple algorithm which zeroes the int, grows it then just sets one bit
 * as required.
 */
int mp_2expt(mp_int *a, int b)
{
   int     res;

   /* zero a as per default */
   mp_zero(a);

   /* grow a to accomodate the single bit */
   if ((res = mp_grow(a, (b / DIGIT_BIT) + 1)) != MP_OKAY) {
      return res;
   }

   /* set the used count of where the bit will go */
   a->used = (b / DIGIT_BIT) + 1;

   /* put the single bit in its place */
   a->dp[b / DIGIT_BIT] = (mp_digit)1 << (mp_digit)(b % DIGIT_BIT);

   return MP_OKAY;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
