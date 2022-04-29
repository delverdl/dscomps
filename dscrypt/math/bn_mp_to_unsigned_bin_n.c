#include "tommath_private.h"
#ifdef BN_MP_TO_UNSIGNED_BIN_N_C
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

/* store in unsigned [big endian] format */
int mp_to_unsigned_bin_n(const mp_int *a, unsigned char *b, unsigned long *outlen)
{
   if (*outlen < (unsigned long)mp_unsigned_bin_size(a)) {
      return MP_VAL;
   }
   *outlen = (unsigned long)mp_unsigned_bin_size(a);
   return mp_to_unsigned_bin(a, b);
}
#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
