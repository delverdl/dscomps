#include "tommath_private.h"
#ifdef BN_MP_NEG_C
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

/* b = -a */
int mp_neg(const mp_int *a, mp_int *b)
{
   int     res;
   if (a != b) {
      if ((res = mp_copy(a, b)) != MP_OKAY) {
         return res;
      }
   }

   if (mp_iszero(b) != MP_YES) {
      b->sign = (a->sign == MP_ZPOS) ? MP_NEG : MP_ZPOS;
   } else {
      b->sign = MP_ZPOS;
   }

   return MP_OKAY;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
