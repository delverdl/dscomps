#include "tommath_private.h"
#ifdef BN_MP_SET_C
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

/* set to a digit */
void mp_set(mp_int *a, mp_digit b)
{
   mp_zero(a);
   a->dp[0] = b & MP_MASK;
   a->used  = (a->dp[0] != 0u) ? 1 : 0;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
