#include "tommath_private.h"
#ifdef BN_MP_REDUCE_SETUP_C
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

/* pre-calculate the value required for Barrett reduction
 * For a given modulus "b" it calulates the value required in "a"
 */
int mp_reduce_setup(mp_int *a, const mp_int *b)
{
   int     res;

   if ((res = mp_2expt(a, b->used * 2 * DIGIT_BIT)) != MP_OKAY) {
      return res;
   }
   return mp_div(a, b, a, NULL);
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
