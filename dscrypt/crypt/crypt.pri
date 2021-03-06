DEFINES         +=  LTM_DESC LTC_SOURCE LTC_NO_TEST LTC_NO_PROTOTYPES

win32: DEFINES  +=  _CRT_SECURE_NO_WARNINGS _CRT_NONSTDC_NO_DEPRECATE

INCLUDEPATH     +=  $$PWD/. $$PWD/headers

HDR_PRIVATE     +=  $$PWD/headers/tomcrypt_private.h
HDR_INSTALL     +=  $$PWD/headers/tomcrypt.h            $$PWD/headers/tomcrypt_argchk.h $$PWD/headers/tomcrypt_cfg.h \
                    $$PWD/headers/tomcrypt_cipher.h     $$PWD/headers/tomcrypt_custom.h $$PWD/headers/tomcrypt_hash.h \
                    $$PWD/headers/tomcrypt_mac.h        $$PWD/headers/tomcrypt_macros.h $$PWD/headers/tomcrypt_math.h \
                    $$PWD/headers/tomcrypt_misc.h       $$PWD/headers/tomcrypt_pk.h     $$PWD/headers/tomcrypt_pkcs.h \
                    $$PWD/headers/tomcrypt_prng.h
HEADERS         +=  $${HDR_INSTALL}                     $${HDR_PRIVATE}

SOURCES         +=  $$PWD/ciphers/anubis.c              $$PWD/ciphers/blowfish.c        $$PWD/encauth/chachapoly/chacha20poly1305_done.c \
                    $$PWD/ciphers/cast5.c               $$PWD/ciphers/des.c             $$PWD/encauth/chachapoly/chacha20poly1305_init.c \
                    $$PWD/ciphers/khazad.c              $$PWD/ciphers/kseed.c           $$PWD/encauth/eax/eax_decrypt_verify_memory.c \
                    $$PWD/ciphers/rc2.c                 $$PWD/ciphers/rc5.c             $$PWD/misc/crypt/crypt_ltc_mp_descriptor.c \
                    $$PWD/ciphers/skipjack.c            $$PWD/ciphers/xtea.c            $$PWD/misc/crypt/crypt_prng_rng_descriptor.c \
                    $$PWD/hashes/blake2s.c              $$PWD/hashes/md2.c              $$PWD/misc/crypt/crypt_register_all_hashes.c \
                    $$PWD/hashes/rmd128.c               $$PWD/hashes/rmd160.c           $$PWD/misc/crypt/crypt_register_cipher.c \
                    $$PWD/hashes/sha1.c                 $$PWD/hashes/sha3.c             $$PWD/misc/crypt/crypt_register_prng.c \
                    $$PWD/math/gmp_desc.c               $$PWD/math/ltm_desc.c           $$PWD/misc/crypt/crypt_unregister_cipher.c \
                    $$PWD/math/rand_bn.c                $$PWD/math/rand_prime.c         $$PWD/misc/crypt/crypt_find_cipher_any.c \
                    $$PWD/misc/compare_testvector.c     $$PWD/misc/copy_or_zeromem.c    $$PWD/encauth/ocb3/ocb3_decrypt_last.c \
                    $$PWD/misc/error_to_string.c        $$PWD/misc/mem_neq.c            $$PWD/mac/blake2/blake2bmac_memory.c \
                    $$PWD/prngs/chacha20.c              $$PWD/prngs/fortuna.c           $$PWD/encauth/ocb3/ocb3_encrypt_last.c   \
                    $$PWD/prngs/rng_make_prng.c         $$PWD/prngs/sober128.c          $$PWD/encauth/ocb3/ocb3_int_xor_blocks.c \
                    $$PWD/ciphers/aes/aes.c             $$PWD/ciphers/aes/aes_tab.c     $$PWD/misc/pkcs12/pkcs12_utf8_to_utf16.c \
                    $$PWD/ciphers/safer/safer_tab.c     $$PWD/ciphers/safer/saferp.c    $$PWD/misc/crypt/crypt_register_hash.c \
                    $$PWD/stream/chacha/chacha_test.c   $$PWD/encauth/ccm/ccm_add_aad.c $$PWD/misc/crypt/crypt_find_hash_any.c \
                    $$PWD/encauth/ccm/ccm_done.c        $$PWD/encauth/ccm/ccm_init.c    $$PWD/pk/asn1/der/set/der_encode_set.c \
                    $$PWD/encauth/ccm/ccm_process.c     $$PWD/encauth/ccm/ccm_reset.c   $$PWD/encauth/ocb/ocb_done_decrypt.c \
                    $$PWD/mac/f9/f9_file.c              $$PWD/ciphers/kasumi.c          $$PWD/encauth/chachapoly/chacha20poly1305_decrypt.c \
                    $$PWD/ciphers/camellia.c            $$PWD/ciphers/noekeon.c         $$PWD/encauth/chachapoly/chacha20poly1305_encrypt.c \
                    $$PWD/ciphers/idea.c                $$PWD/ciphers/serpent.c         $$PWD/encauth/chachapoly/chacha20poly1305_memory.c \
                    $$PWD/stream/rc4/rc4_test.c         $$PWD/hashes/md5.c              $$PWD/encauth/chachapoly/chacha20poly1305_setiv.c \
                    $$PWD/encauth/eax/eax_addheader.c   $$PWD/hashes/rmd320.c           $$PWD/encauth/chachapoly/chacha20poly1305_test.c \
                    $$PWD/encauth/eax/eax_decrypt.c     $$PWD/ciphers/multi2.c          $$PWD/encauth/ocb/ocb_decrypt_verify_memory.c \
                    $$PWD/encauth/eax/eax_done.c        $$PWD/encauth/eax/eax_encrypt.c $$PWD/hashes/helper/hash_memory_multi.c \
                    $$PWD/encauth/eax/eax_init.c        $$PWD/misc/adler32.c            $$PWD/encauth/eax/eax_encrypt_authenticate_memory.c \
                    $$PWD/encauth/eax/eax_test.c        $$PWD/encauth/gcm/gcm_add_aad.c $$PWD/mac/poly1305/poly1305_memory_multi.c \
                    $$PWD/encauth/gcm/gcm_add_iv.c      $$PWD/encauth/gcm/gcm_done.c    $$PWD/misc/crypt/crypt_find_hash_oid.c \
                    $$PWD/encauth/gcm/gcm_init.c        $$PWD/encauth/gcm/gcm_memory.c  $$PWD/misc/crypt/crypt_prng_is_valid.c \
                    $$PWD/encauth/gcm/gcm_process.c     $$PWD/encauth/gcm/gcm_reset.c   $$PWD/stream/salsa20/salsa20_keystream.c \
                    $$PWD/encauth/ocb/ocb_decrypt.c     $$PWD/hashes/tiger.c            $$PWD/misc/crypt/crypt_hash_descriptor.c \
                    $$PWD/encauth/ccm/ccm_test.c        $$PWD/prngs/rng_get_bytes.c     $$PWD/encauth/ocb/ocb_done_encrypt.c \
                    $$PWD/encauth/ocb/ocb_encrypt.c     $$PWD/misc/burn_stack.c         $$PWD/encauth/ocb/ocb_encrypt_authenticate_memory.c\
                    $$PWD/encauth/ocb/ocb_init.c        $$PWD/encauth/ocb/ocb_ntz.c     $$PWD/encauth/ocb/ocb_shift_xor.c \
                    $$PWD/encauth/ocb/ocb_test.c        $$PWD/encauth/ocb/s_ocb_done.c  $$PWD/encauth/ocb3/ocb3_add_aad.c \
                    $$PWD/encauth/ocb3/ocb3_decrypt.c   $$PWD/misc/crc32.c              $$PWD/encauth/ocb3/ocb3_encrypt_authenticate_memory.c \
                    $$PWD/encauth/ocb3/ocb3_done.c      $$PWD/pk/dh/dh_export_key.c     $$PWD/encauth/ocb3/ocb3_decrypt_verify_memory.c \
                    $$PWD/encauth/ocb3/ocb3_encrypt.c   $$PWD/misc/zeromem.c            $$PWD/pk/asn1/der/sequence/der_encode_sequence_ex.c \
                    $$PWD/prngs/rc4.c                   $$PWD/encauth/ocb3/ocb3_init.c  $$PWD/encauth/ocb3/ocb3_int_ntz.c \
                    $$PWD/prngs/sprng.c                 $$PWD/encauth/ocb3/ocb3_test.c  $$PWD/pk/asn1/x509/x509_decode_subject_public_key_info.c \
                    $$PWD/hashes/chc/chc.c              $$PWD/hashes/helper/hash_file.c $$PWD/hashes/helper/hash_filehandle.c \
                    $$PWD/hashes/helper/hash_memory.c   $$PWD/math/radix_to_bin.c       $$PWD/pk/asn1/der/sequence/der_length_sequence.c \
                    $$PWD/hashes/sha2/sha224.c          $$PWD/hashes/sha2/sha256.c      $$PWD/mac/blake2/blake2smac_memory_multi.c \
                    $$PWD/hashes/sha2/sha512.c          $$PWD/hashes/sha2/sha512_224.c  $$PWD/stream/sober128/sober128_stream.c \
                    $$PWD/hashes/whirl/whirl.c          $$PWD/hashes/whirl/whirltab.c   $$PWD/stream/sosemanuk/sosemanuk_test.c \
                    $$PWD/mac/blake2/blake2bmac_file.c  $$PWD/misc/pk_get_oid.c         $$PWD/mac/blake2/blake2bmac_memory_multi.c \
                    $$PWD/mac/blake2/blake2bmac_test.c  $$PWD/mac/blake2/blake2smac.c   $$PWD/mac/blake2/blake2smac_file.c \
                    $$PWD/misc/base16/base16_encode.c   $$PWD/hashes/sha2/sha384.c      $$PWD/pk/asn1/der/general/der_length_asn1_length.c \
                    $$PWD/mac/blake2/blake2smac_test.c  $$PWD/mac/f9/f9_done.c          $$PWD/encauth/chachapoly/chacha20poly1305_add_aad.c \
                    $$PWD/mac/f9/f9_init.c              $$PWD/mac/f9/f9_memory.c        $$PWD/mac/omac/omac_memory_multi.c \
                    $$PWD/mac/f9/f9_process.c           $$PWD/mac/f9/f9_test.c          $$PWD/mac/blake2/blake2smac_memory.c \
                    $$PWD/mac/hmac/hmac_file.c          $$PWD/mac/hmac/hmac_init.c      $$PWD/misc/crypt/crypt_find_prng.c \
                    $$PWD/mac/hmac/hmac_memory_multi.c  $$PWD/mac/hmac/hmac_process.c   $$PWD/misc/crypt/crypt_register_all_ciphers.c \
                    $$PWD/mac/omac/omac_done.c          $$PWD/mac/omac/omac_file.c      $$PWD/misc/crypt/crypt_register_all_prngs.c \
                    $$PWD/mac/omac/omac_memory.c        $$PWD/mac/f9/f9_memory_multi.c  $$PWD/misc/crypt/crypt_constants.c \
                    $$PWD/mac/omac/omac_test.c          $$PWD/mac/pelican/pelican.c     $$PWD/mac/pelican/pelican_memory.c \
                    $$PWD/mac/pelican/pelican_test.c    $$PWD/mac/pmac/pmac_done.c      $$PWD/mac/poly1305/poly1305_memory.c \
                    $$PWD/mac/pmac/pmac_init.c          $$PWD/mac/pmac/pmac_memory.c    $$PWD/mac/pmac/pmac_memory_multi.c \
                    $$PWD/mac/pmac/pmac_ntz.c           $$PWD/mac/pmac/pmac_process.c   $$PWD/misc/crypt/crypt_find_hash.c \
                    $$PWD/mac/pmac/pmac_test.c          $$PWD/mac/poly1305/poly1305.c   $$PWD/mac/poly1305/poly1305_file.c \
                    $$PWD/misc/padding/padding_pad.c    $$PWD/prngs/yarrow.c            $$PWD/pk/asn1/der/custom_type/der_encode_custom_type.c \
                    $$PWD/mac/poly1305/poly1305_test.c  $$PWD/mac/xcbc/xcbc_done.c      $$PWD/misc/crypt/crypt_find_hash_id.c \
                    $$PWD/mac/xcbc/xcbc_init.c          $$PWD/mac/xcbc/xcbc_memory.c    $$PWD/mac/xcbc/xcbc_memory_multi.c \
                    $$PWD/mac/xcbc/xcbc_process.c       $$PWD/mac/xcbc/xcbc_test.c      $$PWD/misc/crypt/crypt_unregister_prng.c \
                    $$PWD/misc/base16/base16_decode.c   $$PWD/mac/hmac/hmac_done.c      $$PWD/misc/crypt/crypt_find_cipher_id.c \
                    $$PWD/misc/base32/base32_encode.c   $$PWD/encauth/gcm/gcm_test.c    $$PWD/misc/crypt/crypt_cipher_is_valid.c \
                    $$PWD/misc/crypt/crypt.c            $$PWD/misc/crypt/crypt_argchk.c $$PWD/misc/crypt/crypt_cipher_descriptor.c \
                    $$PWD/misc/base64/base64_encode.c   $$PWD/mac/omac/omac_process.c   $$PWD/pk/asn1/der/printable_string/der_decode_printable_string.c \
                    $$PWD/pk/pkcs1/pkcs_1_pss_decode.c  $$PWD/math/tfm_desc.c           $$PWD/pk/asn1/der/printable_string/der_length_printable_string.c \
                    $$PWD/misc/base32/base32_decode.c   $$PWD/mac/pmac/pmac_shift_xor.c $$PWD/pk/asn1/der/short_integer/der_encode_short_integer.c \
                    $$PWD/encauth/ccm/ccm_add_nonce.c   $$PWD/mac/xcbc/xcbc_file.c      $$PWD/pk/asn1/der/teletex_string/der_decode_teletex_string.c \
                    $$PWD/encauth/gcm/gcm_gf_mult.c     $$PWD/mac/hmac/hmac_memory.c    $$PWD/pk/asn1/der/sequence/der_decode_sequence_flexi.c \
                    $$PWD/misc/crypt/crypt_fsa.c        $$PWD/misc/pk_oid_str.c         $$PWD/misc/crypt/crypt_hash_is_valid.c \
                    $$PWD/misc/crypt/crypt_inits.c      $$PWD/ciphers/rc6.c             $$PWD/misc/crypt/crypt_prng_descriptor.c \
                    $$PWD/encauth/gcm/gcm_mult_h.c      $$PWD/hashes/blake2b.c          $$PWD/pk/asn1/der/bit/der_decode_bit_string.c \
                    $$PWD/mac/hmac/hmac_test.c          $$PWD/hashes/md4.c              $$PWD/pk/asn1/der/utctime/der_decode_utctime.c \
                    $$PWD/mac/omac/omac_init.c          $$PWD/hashes/rmd256.c           $$PWD/pk/asn1/der/utctime/der_length_utctime.c \
                    $$PWD/ciphers/twofish/twofish.c     $$PWD/hashes/sha3_test.c        $$PWD/pk/asn1/der/utf8/der_encode_utf8_string.c \
                    $$PWD/misc/crypt/crypt_sizes.c      $$PWD/math/multi.c              $$PWD/misc/crypt/crypt_unregister_hash.c \
                    $$PWD/math/fp/ltc_ecc_fp_mulmod.c   $$PWD/misc/hkdf/hkdf.c          $$PWD/stream/salsa20/salsa20_setup.c \
                    $$PWD/misc/padding/padding_depad.c  $$PWD/mac/pmac/pmac_file.c      $$PWD/stream/salsa20/xsalsa20_setup.c \
                    $$PWD/ciphers/safer/safer.c         $$PWD/misc/pkcs5/pkcs_5_1.c     $$PWD/stream/sober128/sober128_test.c \
                    $$PWD/misc/pkcs5/pkcs_5_test.c      $$PWD/modes/cbc/cbc_decrypt.c   $$PWD/pk/asn1/der/bit/der_decode_raw_bit_string.c \
                    $$PWD/modes/cbc/cbc_encrypt.c       $$PWD/modes/cbc/cbc_getiv.c     $$PWD/pk/asn1/der/bit/der_encode_raw_bit_string.c \
                    $$PWD/modes/cbc/cbc_start.c         $$PWD/modes/cfb/cfb_decrypt.c   $$PWD/pk/asn1/der/boolean/der_decode_boolean.c \
                    $$PWD/modes/cfb/cfb_encrypt.c       $$PWD/modes/cfb/cfb_getiv.c     $$PWD/pk/asn1/der/boolean/der_length_boolean.c \
                    $$PWD/modes/cfb/cfb_start.c         $$PWD/modes/ctr/ctr_decrypt.c   $$PWD/pk/asn1/der/custom_type/der_decode_custom_type.c \
                    $$PWD/modes/ctr/ctr_encrypt.c       $$PWD/modes/ctr/ctr_getiv.c     $$PWD/pk/asn1/der/custom_type/der_length_custom_type.c \
                    $$PWD/modes/ctr/ctr_start.c         $$PWD/modes/ctr/ctr_test.c      $$PWD/pk/asn1/der/general/der_decode_asn1_identifier.c \
                    $$PWD/modes/ecb/ecb_done.c          $$PWD/modes/ecb/ecb_encrypt.c   $$PWD/pk/asn1/der/general/der_encode_asn1_identifier.c \
                    $$PWD/modes/f8/f8_decrypt.c         $$PWD/modes/f8/f8_done.c        $$PWD/pk/asn1/der/general/der_length_asn1_identifier.c \
                    $$PWD/modes/f8/f8_getiv.c           $$PWD/modes/f8/f8_setiv.c       $$PWD/pk/asn1/der/ia5/der_decode_ia5_string.c \
                    $$PWD/modes/f8/f8_test_mode.c       $$PWD/modes/lrw/lrw_decrypt.c   $$PWD/pk/asn1/der/ia5/der_encode_ia5_string.c \
                    $$PWD/modes/lrw/lrw_encrypt.c       $$PWD/modes/lrw/lrw_getiv.c     $$PWD/pk/asn1/der/sequence/der_sequence_free.c \
                    $$PWD/modes/lrw/lrw_setiv.c         $$PWD/modes/lrw/lrw_start.c     $$PWD/pk/asn1/der/set/der_encode_setof.c \
                    $$PWD/modes/ofb/ofb_decrypt.c       $$PWD/modes/ofb/ofb_done.c      $$PWD/pk/asn1/der/bit/der_encode_bit_string.c \
                    $$PWD/modes/ofb/ofb_getiv.c         $$PWD/modes/ofb/ofb_setiv.c     $$PWD/pk/asn1/der/bit/der_length_bit_string.c \
                    $$PWD/modes/xts/xts_decrypt.c       $$PWD/modes/xts/xts_done.c      $$PWD/pk/asn1/der/boolean/der_encode_boolean.c    \
                    $$PWD/modes/xts/xts_init.c          $$PWD/modes/xts/xts_mult_x.c    $$PWD/pk/asn1/der/choice/der_decode_choice.c \
                    $$PWD/pk/dh/dh.c                    $$PWD/pk/dh/dh_check_pubkey.c   $$PWD/pk/asn1/der/octet/der_length_octet_string.c \
                    $$PWD/pk/dh/dh_free.c               $$PWD/pk/dh/dh_generate_key.c   $$PWD/pk/asn1/der/general/der_asn1_maps.c \
                    $$PWD/pk/dh/dh_set.c                $$PWD/pk/dh/dh_set_pg_dhparam.c $$PWD/pk/asn1/der/general/der_decode_asn1_length.c \
                    $$PWD/pk/dsa/dsa_decrypt_key.c      $$PWD/pk/dsa/dsa_encrypt_key.c  $$PWD/pk/asn1/der/general/der_encode_asn1_length.c \
                    $$PWD/pk/dsa/dsa_free.c             $$PWD/pk/dsa/dsa_generate_key.c $$PWD/stream/sosemanuk/sosemanuk.c \
                    $$PWD/pk/dsa/dsa_import.c           $$PWD/pk/dsa/dsa_make_key.c     $$PWD/stream/chacha/chacha_setup.c \
                    $$PWD/pk/dsa/dsa_set_pqg_dsaparam.c $$PWD/pk/dsa/dsa_sign_hash.c    $$PWD/stream/chacha/chacha_keystream.c \
                    $$PWD/pk/dsa/dsa_verify_hash.c      $$PWD/pk/dsa/dsa_verify_key.c   $$PWD/stream/chacha/chacha_ivctr32.c \
                    $$PWD/pk/ecc/ecc_ansi_x963_export.c $$PWD/pk/ecc/ecc_decrypt_key.c  $$PWD/pk/ecc/ecc_ansi_x963_import.c \
                    $$PWD/pk/ecc/ecc_encrypt_key.c      $$PWD/pk/ecc/ecc_export.c       $$PWD/stream/salsa20/salsa20_crypt.c \
                    $$PWD/pk/ecc/ecc_find_curve.c       $$PWD/pk/ecc/ecc_free.c         $$PWD/pk/ecc/ltc_ecc_mulmod_timing.c \
                    $$PWD/pk/ecc/ecc_get_oid_str.c      $$PWD/pk/ecc/ecc_get_size.c     $$PWD/pk/asn1/der/utf8/der_decode_utf8_string.c \
                    $$PWD/pk/ecc/ecc_import_openssl.c   $$PWD/pk/ecc/ecc_import_x509.c  $$PWD/stream/salsa20/salsa20_done.c \
                    $$PWD/pk/ecc/ecc_set_curve.c        $$PWD/pk/ecc/ecc_set_key.c      $$PWD/pk/ecc/ecc_set_curve_internal.c \
                    $$PWD/pk/ecc/ecc_shared_secret.c    $$PWD/pk/ecc/ecc_sign_hash.c    $$PWD/pk/ecc/ltc_ecc_projective_dbl_point.c \
                    $$PWD/pk/ecc/ecc_test.c             $$PWD/pk/ecc/ecc_verify_hash.c  $$PWD/pk/ecc/ltc_ecc_export_point.c \
                    $$PWD/pk/ecc/ltc_ecc_import_point.c $$PWD/pk/ecc/ltc_ecc_is_point.c $$PWD/pk/ecc/ltc_ecc_is_point_at_infinity.c \
                    $$PWD/pk/ecc/ltc_ecc_map.c          $$PWD/pk/ecc/ltc_ecc_mul2add.c  $$PWD/pk/pkcs1/pkcs_1_v1_5_decode.c \
                    $$PWD/pk/ecc/ltc_ecc_verify_key.c   $$PWD/pk/ecc/ltc_ecc_points.c   $$PWD/pk/ecc/ltc_ecc_projective_add_point.c \
                    $$PWD/pk/ecc/ecc_sizes.c            $$PWD/pk/ecc/ecc_get_key.c      $$PWD/pk/asn1/der/utf8/der_length_utf8_string.c \
                    $$PWD/pk/pkcs1/pkcs_1_i2osp.c       $$PWD/pk/pkcs1/pkcs_1_mgf1.c    $$PWD/pk/pkcs1/pkcs_1_oaep_decode.c \
                    $$PWD/pk/pkcs1/pkcs_1_oaep_encode.c $$PWD/pk/pkcs1/pkcs_1_os2ip.c   $$PWD/misc/crypt/crypt_find_cipher.c \
                    $$PWD/pk/pkcs1/pkcs_1_pss_encode.c  $$PWD/pk/ecc/ltc_ecc_mulmod.c   $$PWD/pk/pkcs1/pkcs_1_v1_5_encode.c \
                    $$PWD/pk/rsa/rsa_decrypt_key.c      $$PWD/pk/rsa/rsa_encrypt_key.c  $$PWD/pk/asn1/der/utctime/der_encode_utctime.c \
                    $$PWD/pk/rsa/rsa_exptmod.c          $$PWD/pk/rsa/rsa_free.c         $$PWD/pk/asn1/der/octet/der_encode_octet_string.c \
                    $$PWD/pk/rsa/rsa_import.c           $$PWD/pk/rsa/rsa_import_pkcs8.c $$PWD/pk/asn1/der/ia5/der_length_ia5_string.c \
                    $$PWD/pk/rsa/rsa_make_key.c         $$PWD/pk/rsa/rsa_set.c          $$PWD/pk/asn1/der/integer/der_encode_integer.c \
                    $$PWD/pk/rsa/rsa_sign_saltlen_get.c $$PWD/pk/rsa/rsa_verify_hash.c  $$PWD/pk/asn1/der/object_identifier/der_encode_object_identifier.c \
                    $$PWD/stream/chacha/chacha_done.c   $$PWD/pk/ecc/ecc.c              $$PWD/stream/chacha/chacha_ivctr64.c \
                    $$PWD/pk/dsa/dsa_shared_secret.c    $$PWD/pk/dsa/dsa_set.c          $$PWD/ciphers/twofish/twofish_tab.c \
                    $$PWD/stream/rabbit/rabbit.c        $$PWD/stream/rc4/rc4_stream.c   $$PWD/encauth/chachapoly/chacha20poly1305_setiv_rfc7905.c \
                    $$PWD/pk/ecc/ecc_export_openssl.c   $$PWD/pk/ecc/ecc_make_key.c     $$PWD/stream/salsa20/salsa20_ivctr64.c \
                    $$PWD/encauth/ccm/ccm_memory.c      $$PWD/misc/hkdf/hkdf_test.c     $$PWD/pk/asn1/der/generalizedtime/der_encode_generalizedtime.c \
                    $$PWD/stream/salsa20/salsa20_test.c $$PWD/misc/pkcs12/pkcs12_kdf.c  $$PWD/stream/salsa20/xsalsa20_test.c \
                    $$PWD/hashes/sha2/sha512_256.c      $$PWD/misc/pkcs5/pkcs_5_2.c     $$PWD/pk/asn1/der/object_identifier/der_decode_object_identifier.c \
                    $$PWD/stream/sober128/sober128tab.c $$PWD/pk/dsa/dsa_generate_pqg.c $$PWD/pk/asn1/der/object_identifier/der_length_object_identifier.c \
                    $$PWD/mac/blake2/blake2bmac.c       $$PWD/modes/lrw/lrw_process.c   $$PWD/pk/asn1/der/teletex_string/der_length_teletex_string.c \
                    $$PWD/pk/ecc/ecc_import.c           $$PWD/modes/lrw/lrw_test.c      $$PWD/pk/asn1/x509/x509_encode_subject_public_key_info.c \
                    $$PWD/modes/cbc/cbc_done.c          $$PWD/modes/ofb/ofb_encrypt.c   $$PWD/pk/asn1/der/sequence/der_sequence_shrink.c \
                    $$PWD/modes/cbc/cbc_setiv.c         $$PWD/modes/ofb/ofb_start.c     $$PWD/pk/asn1/der/printable_string/der_encode_printable_string.c \
                    $$PWD/modes/cfb/cfb_done.c          $$PWD/modes/xts/xts_encrypt.c   $$PWD/pk/asn1/der/sequence/der_decode_sequence_ex.c \
                    $$PWD/modes/cfb/cfb_setiv.c         $$PWD/modes/xts/xts_test.c      $$PWD/pk/asn1/der/sequence/der_decode_sequence_multi.c \
                    $$PWD/modes/ctr/ctr_done.c          $$PWD/pk/dh/dh_export.c         $$PWD/pk/asn1/der/short_integer/der_length_short_integer.c \
                    $$PWD/modes/ctr/ctr_setiv.c         $$PWD/pk/dh/dh_import.c         $$PWD/pk/asn1/der/generalizedtime/der_decode_generalizedtime.c \
                    $$PWD/modes/ecb/ecb_decrypt.c       $$PWD/pk/dh/dh_shared_secret.c  $$PWD/pk/asn1/der/generalizedtime/der_length_generalizedtime.c \
                    $$PWD/modes/ecb/ecb_start.c         $$PWD/pk/dsa/dsa_export.c       $$PWD/pk/asn1/der/sequence/der_encode_sequence_multi.c \
                    $$PWD/modes/f8/f8_encrypt.c         $$PWD/pk/rsa/rsa_export.c       $$PWD/pk/asn1/der/short_integer/der_decode_short_integer.c \
                    $$PWD/misc/base64/base64_decode.c   $$PWD/pk/rsa/rsa_get_size.c     $$PWD/pk/asn1/der/octet/der_decode_octet_string.c \
                    $$PWD/modes/f8/f8_start.c           $$PWD/pk/rsa/rsa_import_x509.c  $$PWD/pk/asn1/der/integer/der_decode_integer.c \
                    $$PWD/modes/lrw/lrw_done.c          $$PWD/pk/rsa/rsa_sign_hash.c    $$PWD/pk/asn1/der/integer/der_length_integer.c \
                    $$PWD/stream/chacha/chacha_crypt.c
