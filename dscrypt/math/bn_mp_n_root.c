#include "tommath_private.h"
#ifdef BN_MP_N_ROOT_C
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

/* wrapper function for mp_n_root_ex()
 * computes c = (a)**(1/b) such that (c)**b <= a and (c+1)**b > a
 */
int mp_n_root(const mp_int *a, mp_digit b, mp_int *c)
{
   return mp_n_root_ex(a, b, c, 0);
}

#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
