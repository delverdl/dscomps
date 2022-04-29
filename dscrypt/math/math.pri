INCLUDEPATH     +=  $$PWD/.

HDR_PRIVATE     +=  $$PWD/tommath_private.h
HDR_INSTALL     +=  $$PWD/tommath.h       $$PWD/tommath_class.h     $$PWD/tommath_superclass.h
HEADERS         +=  $${HDR_INSTALL}       $${HDR_PRIVATE}

SOURCES         +=  $$PWD/bn_error.c      $$PWD/bn_fast_mp_invmod.c $$PWD/bn_fast_mp_montgomery_reduce.c \
                    $$PWD/bn_mp_abs.c     $$PWD/bn_mp_mod_2d.c      $$PWD/bn_fast_s_mp_mul_digs.c \
                    $$PWD/bn_mp_add.c     $$PWD/bn_mp_neg.c         $$PWD/bn_fast_s_mp_mul_high_digs.c \
                    $$PWD/bncore.c        $$PWD/bn_mp_dr_setup.c    $$PWD/bn_mp_get_long_long.c \
                    $$PWD/bn_mp_and.c     $$PWD/bn_mp_get_long.c    $$PWD/bn_mp_dr_is_modulus.c \
                    $$PWD/bn_mp_div.c     $$PWD/bn_mp_init_set.c    $$PWD/bn_mp_exptmod_fast.c \
                    $$PWD/bn_mp_exch.c    $$PWD/bn_mp_cmp_mag.c     $$PWD/bn_mp_init_set_int.c \
                    $$PWD/bn_mp_2expt.c   $$PWD/bn_mp_cnt_lsb.c     $$PWD/bn_mp_clear_multi.c \
                    $$PWD/bn_mp_add_d.c   $$PWD/bn_mp_exptmod.c     $$PWD/bn_mp_init_multi.c \
                    $$PWD/bn_mp_addmod.c  $$PWD/bn_mp_get_int.c     $$PWD/bn_fast_s_mp_sqr.c \
                    $$PWD/bn_mp_clamp.c   $$PWD/bn_mp_count_bits.c  $$PWD/bn_mp_montgomery_calc_normalization.c \
                    $$PWD/bn_mp_clear.c   $$PWD/bn_mp_exteuclid.c   $$PWD/bn_mp_montgomery_reduce.c \
                    $$PWD/bn_mp_cmp.c     $$PWD/bn_mp_init_copy.c   $$PWD/bn_mp_montgomery_setup.c \
                    $$PWD/bn_mp_cmp_d.c   $$PWD/bn_mp_dr_reduce.c   $$PWD/bn_mp_karatsuba_mul.c \
                    $$PWD/bn_mp_copy.c    $$PWD/bn_mp_expt_d_ex.c   $$PWD/bn_mp_karatsuba_sqr.c \
                    $$PWD/bn_mp_div_2.c   $$PWD/bn_mp_init_size.c   $$PWD/bn_mp_invmod_slow.c \
                    $$PWD/bn_mp_export.c  $$PWD/bn_mp_is_square.c   $$PWD/bn_mp_prime_rabin_miller_trials.c \
                    $$PWD/bn_mp_expt_d.c  $$PWD/bn_mp_n_root_ex.c   $$PWD/bn_mp_prime_fermat.c \
                    $$PWD/bn_mp_div_3.c   $$PWD/bn_mp_toom_mul.c    $$PWD/bn_mp_prime_is_divisible.c \
                    $$PWD/bn_mp_div_d.c   $$PWD/bn_mp_toom_sqr.c    $$PWD/bn_mp_prime_is_prime.c \
                    $$PWD/bn_mp_div_2d.c  $$PWD/bn_mp_toradix.c     $$PWD/bn_mp_prime_miller_rabin.c \
                    $$PWD/bn_mp_fread.c   $$PWD/bn_mp_toradix_n.c   $$PWD/bn_mp_prime_next_prime.c \
                    $$PWD/bn_mp_fwrite.c  $$PWD/bn_mp_gcd.c         $$PWD/bn_mp_prime_random_ex.c \
                    $$PWD/bn_mp_grow.c    $$PWD/bn_mp_import.c      $$PWD/bn_mp_read_signed_bin.c \
                    $$PWD/bn_mp_init.c    $$PWD/bn_mp_invmod.c      $$PWD/bn_mp_read_unsigned_bin.c \
                    $$PWD/bn_mp_jacobi.c  $$PWD/bn_mp_lcm.c         $$PWD/bn_mp_reduce_2k_setup.c \
                    $$PWD/bn_mp_lshd.c    $$PWD/bn_mp_radix_size.c  $$PWD/bn_mp_reduce_2k_setup_l.c \
                    $$PWD/bn_mp_mod.c     $$PWD/bn_mp_radix_smap.c  $$PWD/bn_mp_reduce_is_2k_l.c \
                    $$PWD/bn_mp_mod_d.c   $$PWD/bn_mp_read_radix.c  $$PWD/bn_mp_reduce_is_2k.c \
                    $$PWD/bn_mp_mul.c     $$PWD/bn_mp_reduce_2k_l.c $$PWD/bn_mp_reduce_setup.c \
                    $$PWD/bn_mp_mul_2.c   $$PWD/bn_mp_reduce_2k.c   $$PWD/bn_mp_set_long_long.c \
                    $$PWD/bn_mp_mul_2d.c  $$PWD/bn_mp_reduce.c      $$PWD/bn_mp_signed_bin_size.c \
                    $$PWD/bn_mp_mul_d.c   $$PWD/bn_mp_set_long.c    $$PWD/bn_mp_sqrtmod_prime.c \
                    $$PWD/bn_mp_mulmod.c  $$PWD/bn_mp_n_root.c      $$PWD/bn_mp_to_signed_bin.c \
                    $$PWD/bn_mp_or.c      $$PWD/bn_mp_rand.c        $$PWD/bn_mp_to_signed_bin_n.c \
                    $$PWD/bn_mp_rshd.c    $$PWD/bn_mp_set.c         $$PWD/bn_mp_to_unsigned_bin.c \
                    $$PWD/bn_mp_set_int.c $$PWD/bn_mp_shrink.c      $$PWD/bn_mp_to_unsigned_bin_n.c \
                    $$PWD/bn_mp_sqr.c     $$PWD/bn_mp_sqrmod.c      $$PWD/bn_mp_unsigned_bin_size.c \
                    $$PWD/bn_mp_sqrt.c    $$PWD/bn_mp_sub.c         $$PWD/bn_s_mp_mul_high_digs.c \
                    $$PWD/bn_mp_sub_d.c   $$PWD/bn_mp_submod.c      $$PWD/bn_s_mp_mul_digs.c \
                    $$PWD/bn_mp_xor.c     $$PWD/bn_s_mp_exptmod.c   $$PWD/bn_mp_zero.c \
                    $$PWD/bn_prime_tab.c  $$PWD/bn_reverse.c        $$PWD/bn_s_mp_add.c \
                    $$PWD/bn_s_mp_sqr.c   $$PWD/bn_s_mp_sub.c
