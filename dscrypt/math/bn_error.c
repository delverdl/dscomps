#include "tommath_private.h"
#ifdef BN_ERROR_C
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

static const struct {
   int code;
   const char *msg;
} msgs[] = {
   { MP_OKAY, "Successful" },
   { MP_MEM,  "Out of heap" },
   { MP_VAL,  "Value out of range" }
};

/* return a char * string for a given code */
const char *mp_error_to_string(int code)
{
   size_t x;

   /* scan the lookup table for the given message */
   for (x = 0; x < (sizeof(msgs) / sizeof(msgs[0])); x++) {
      if (msgs[x].code == code) {
         return msgs[x].msg;
      }
   }

   /* generic reply for invalid code */
   return "Invalid error code";
}

#endif

/* ref:         HEAD -> develop */
/* git commit:  bc685fd4a58a8ffb132d10635a96bf46e144cde3 */
/* commit time: 2018-06-10 23:34:19 +0200 */
