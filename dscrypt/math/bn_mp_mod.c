#include "tommath_private.h"
#ifdef BN_MP_MOD_C
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

/* c = a mod b, 0 <= c < b if b > 0, b < c <= 0 if b < 0 */
int mp_mod(const mp_int *a, const mp_int *b, mp_int *c)
{
   mp_int  t;
   int     res;

   if ((res = mp_init_size(&t, b->used)) != MP_OKAY) {
      return res;
   }

   if ((res = mp_div(a, b, NULL, &t)) != MP_OKAY) {
      mp_clear(&t);
      return res;
   }

   if ((mp_iszero(&t) != MP_NO) || (t.sign == b->sign)) {
      res = MP_OKAY;
      mp_exch(&t, c);
   } else {
      res = mp_add(b, &t, c);
   }

   mp_clear(&t);
   return res;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
