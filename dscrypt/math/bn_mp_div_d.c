#include "tommath_private.h"
#ifdef BN_MP_DIV_D_C
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

static int s_is_power_of_two(mp_digit b, int *p)
{
   int x;

   /* fast return if no power of two */
   if ((b == 0u) || ((b & (b-1u)) != 0u)) {
      return 0;
   }

   for (x = 0; x < DIGIT_BIT; x++) {
      if (b == ((mp_digit)1<<(mp_digit)x)) {
         *p = x;
         return 1;
      }
   }
   return 0;
}

/* single digit division (based on routine from MPI) */
int mp_div_d(const mp_int *a, mp_digit b, mp_int *c, mp_digit *d)
{
   mp_int  q;
   mp_word w;
   mp_digit t;
   int     res, ix;

   /* cannot divide by zero */
   if (b == 0u) {
      return MP_VAL;
   }

   /* quick outs */
   if ((b == 1u) || (mp_iszero(a) == MP_YES)) {
      if (d != NULL) {
         *d = 0;
      }
      if (c != NULL) {
         return mp_copy(a, c);
      }
      return MP_OKAY;
   }

   /* power of two ? */
   if (s_is_power_of_two(b, &ix) == 1) {
      if (d != NULL) {
         *d = a->dp[0] & (((mp_digit)1<<(mp_digit)ix) - 1uL);
      }
      if (c != NULL) {
         return mp_div_2d(a, ix, c, NULL);
      }
      return MP_OKAY;
   }

#ifdef BN_MP_DIV_3_C
   /* three? */
   if (b == 3u) {
      return mp_div_3(a, c, d);
   }
#endif

   /* no easy answer [c'est la vie].  Just division */
   if ((res = mp_init_size(&q, a->used)) != MP_OKAY) {
      return res;
   }

   q.used = a->used;
   q.sign = a->sign;
   w = 0;
   for (ix = a->used - 1; ix >= 0; ix--) {
      w = (w << (mp_word)DIGIT_BIT) | (mp_word)a->dp[ix];

      if (w >= b) {
         t = (mp_digit)(w / b);
         w -= (mp_word)t * (mp_word)b;
      } else {
         t = 0;
      }
      q.dp[ix] = t;
   }

   if (d != NULL) {
      *d = (mp_digit)w;
   }

   if (c != NULL) {
      mp_clamp(&q);
      mp_exch(&q, c);
   }
   mp_clear(&q);

   return res;
}

#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
