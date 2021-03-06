#include "tommath_private.h"
#ifdef BN_MP_MUL_C
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

/* high level multiplication (handles sign) */
int mp_mul(const mp_int *a, const mp_int *b, mp_int *c)
{
   int     res, neg;
   neg = (a->sign == b->sign) ? MP_ZPOS : MP_NEG;

   /* use Toom-Cook? */
#ifdef BN_MP_TOOM_MUL_C
   if (MIN(a->used, b->used) >= TOOM_MUL_CUTOFF) {
      res = mp_toom_mul(a, b, c);
   } else
#endif
#ifdef BN_MP_KARATSUBA_MUL_C
      /* use Karatsuba? */
      if (MIN(a->used, b->used) >= KARATSUBA_MUL_CUTOFF) {
         res = mp_karatsuba_mul(a, b, c);
      } else
#endif
      {
         /* can we use the fast multiplier?
          *
          * The fast multiplier can be used if the output will
          * have less than MP_WARRAY digits and the number of
          * digits won't affect carry propagation
          */
         int     digs = a->used + b->used + 1;

#ifdef BN_FAST_S_MP_MUL_DIGS_C
         if ((digs < (int)MP_WARRAY) &&
             (MIN(a->used, b->used) <=
              (int)(1u << (((size_t)CHAR_BIT * sizeof(mp_word)) - (2u * (size_t)DIGIT_BIT))))) {
            res = fast_s_mp_mul_digs(a, b, c, digs);
         } else
#endif
         {
#ifdef BN_S_MP_MUL_DIGS_C
            res = s_mp_mul(a, b, c); /* uses s_mp_mul_digs */
#else
            res = MP_VAL;
#endif
         }
      }
   c->sign = (c->used > 0) ? neg : MP_ZPOS;
   return res;
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
