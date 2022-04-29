#include "tommath_private.h"
#ifdef BN_MP_INIT_SET_C
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

/* initialize and set a digit */
int mp_init_set(mp_int *a, mp_digit b)
{
   int err;
   if ((err = mp_init(a)) != MP_OKAY) {
      return err;
   }
   mp_set(a, b);
   return err;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
